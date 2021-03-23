#pragma once
#include <vector>
#include <iostream>
#include <Windows.h>
#include "mpi.h"
using namespace std;

void findElement(int data[] , int length , int element)
{
	int rank, size;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	//MPI_Bcast(&data, length , MPI_INT, 0, MPI_COMM_WORLD);
	int elementsAssigned = length / size;
	int start = rank * elementsAssigned;
	int end = start + elementsAssigned;
	if (rank == size - 1)
		end += length % size;
	int position = -1;
	for (int i = end - 1; i >= start ;i--)
	{
		if (data[i] == element)
		{
			position = i;
			break;
		}
	}
	int maxPosition = -1;
	MPI_Reduce(&position, &maxPosition, 1, MPI_INT, MPI_MAX, 0, MPI_COMM_WORLD);
	if(rank == 0)
		cout << rank << " " <<  maxPosition << endl;
	MPI_Finalize();
}

void findElementScatter(int data[], int length, int element)
{
	int rank, size;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int* receive = new int[length / size];
	//in the "worst" case the desired element occurs on all data's postitions
	int* validPositions = new int[length];
	MPI_Scatter(data, length / size, MPI_INT, receive, length / size, MPI_INT, 0, MPI_COMM_WORLD);
	//the positions where that element occurs
	int* found = new int[length / size];
	for (int i = 0; i < length / size; i++)
		found[i] = -1;
	int foundSize = 0;
	for(int i = 0 ; i < length / size ; i++)
		if (receive[i] == element)
			found[foundSize++] = i + (rank * length / size);
	MPI_Gather(found, length / size, MPI_INT, validPositions, length / size, MPI_INT,0, MPI_COMM_WORLD);
	if (rank == 0)
	{
		for(int i = 0 ; i < length ; i++)
			if (validPositions[i] != -1)
				cout << validPositions[i] << " ";
	}
	delete(validPositions);
	delete(found);
	delete(receive);
	MPI_Finalize();
}