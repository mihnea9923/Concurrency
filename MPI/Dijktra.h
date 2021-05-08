#pragma once
#include <vector>
#include "mpi.h"
#include <iostream>
using namespace std;

int findMinimum(int* distance, bool* visited, int nodes)
{
	int min = INT_MAX, min_index = 0;
	for (int i = 0; i < nodes; i++)
	{
		if (min > distance[i] && visited[i] == false)
		{
			min = distance[i];
			min_index = i;
		}
	}
	return min_index;
}

void updateDistances(int min, int* distances, int length, int m[], bool* visited , int rank)
{
	for (int i = 0; i < length; i++)
	{
		if (m[i] != 0 && visited[i + rank * length] == false && min != INT_MAX && min + m[i] < distances[i])
		{
			distances[i] = min + m[i];
		}
	}
}


void dijktra(int m[][8], int source, int nodes)
{
	int rank, numtasks;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);

	int* distance = new int[nodes];
	for (int i = 0; i < nodes; i++)
	{
		distance[i] = INT_MAX;
	}
	bool* visited = new bool[nodes];
	for (int i = 0; i < nodes; i++)
	{
		visited[i] = false;
	}
	distance[source] = 0;
	int* processDistance = new int[nodes / numtasks];
	for (int i = 0; i < nodes - 1; i++)
	{
		MPI_Scatter(distance, nodes / numtasks, MPI_INT, processDistance, nodes / numtasks, MPI_INT, 0,
			MPI_COMM_WORLD);
		int globalMin = 0;
		if (rank == 0)
		{
			globalMin = findMinimum(distance, visited, nodes);
		}
		MPI_Bcast(&globalMin, 1, MPI_INT, 0, MPI_COMM_WORLD);

		if (rank == 0)
		{
			visited[globalMin] = true;
		}
		int* initialDistances = new int[nodes / numtasks];
		MPI_Scatter(m[globalMin], nodes / numtasks, MPI_INT, initialDistances, nodes / numtasks, MPI_INT, 0, MPI_COMM_WORLD);
		updateDistances(distance[globalMin], processDistance, nodes / numtasks, initialDistances, visited , rank);
		MPI_Gather(processDistance, nodes / numtasks, MPI_INT, distance, nodes / numtasks, MPI_INT, 0, MPI_COMM_WORLD);
		MPI_Bcast(distance, nodes, MPI_INT, 0, MPI_COMM_WORLD);
		
	}
	if (rank == 0)
	{
		for (int i = 0; i < nodes; i++)
		{
			cout << "Node " << i << ": " << distance[i] << endl;
		}
	}

	MPI_Finalize();
}