#pragma once
#include "mpi.h"
#include <iostream>
using namespace std;
int computeSum(int v[], int length)
{
	int s = 0;
	for (int i = 0; i < length; i++)
		s += v[i];
	return s;
}
int computeProd(int v[], int length)
{
	int prod = 1;
	for (int i = 0; i < length; i++)
		prod *= v[i];
	return prod;
}
int computeMin(int v[], int length)
{
	int min = INT_MAX;
	for (int i = 0; i < length; i++)
		if (min > v[i])
			min = v[i];
	return min;
}
int computeMax(int v[], int length)
{
	int max = INT_MIN;
	for (int i = 0; i < length; i++)
		if (max < v[i])
			max = v[i];
	return max;
}
void multipleGroups(int NPROCS, int v[], const int length)
{
	int rank, new_rank, numtasks,
		ranks1[2] = { 0,1 }, ranks2[2] = { 2,3 }, ranks3[2] = { 4 , 5 }, ranks4[2] = { 6,7 };
	MPI_Group  orig_group, max_group, min_group, sum_group, prod_group;   // required variables
	MPI_Comm   sum_comm, prod_comm, min_comm, max_comm;   // required variable
	int sum = 0, min = INT_MAX, max = INT_MIN, prod = 1;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &numtasks);


	// extract the original group handle
	MPI_Comm_group(MPI_COMM_WORLD, &orig_group);

	//  divide tasks into two distinct groups based upon rank

	MPI_Group_incl(orig_group, 2, ranks1, &sum_group);
	MPI_Group_incl(orig_group, 2, ranks2, &prod_group);
	MPI_Group_incl(orig_group, 2, ranks3, &min_group);
	MPI_Group_incl(orig_group, 2, ranks4, &max_group);

	// create new new communicator and then perform collective communications
	MPI_Comm_create(MPI_COMM_WORLD, sum_group, &sum_comm);
	MPI_Comm_create(MPI_COMM_WORLD, prod_group, &prod_comm);
	MPI_Comm_create(MPI_COMM_WORLD, min_group, &min_comm);
	MPI_Comm_create(MPI_COMM_WORLD, max_group, &max_comm);
	if (rank < 2)
	{
		int* receiveBuffer = new int[length / 2];
		MPI_Scatter(v, length / 2, MPI_INT, receiveBuffer, length / 2, MPI_INT, 0, sum_comm);
		int s = computeSum(receiveBuffer, length / 2);
		MPI_Allreduce(&s, &sum, 1, MPI_INT, MPI_SUM, sum_comm);
		if (rank == 0)
			printf("Sum is %d\n", sum);
	}
	else if (rank < 4)
	{
		int* receiveBuffer = new int[length / 2];
		//root is 0 because inside prod_comm each process will get a new rank from 0 to comm size - 1
		MPI_Scatter(v, length / 2, MPI_INT, receiveBuffer, length / 2, MPI_INT, 0, prod_comm);
		int p = computeProd(receiveBuffer , length / 2);
		//the process with process 0 inside prod_comm will get the value produced by MPI_REDUCE
		//rank 0 inside prod_comm means rank 2 inside MPI_COMM_WORLD
		MPI_Reduce(&p, &prod, 1, MPI_INT, MPI_PROD, 0, prod_comm);
		//rank 0 inside prod_comm means rank 2 inside MPI_COMM_WORLD.You can see that in the array ranks[2]={2,3}
		if (rank == 2)
			printf("Prod is %d\n", prod);
	}
	else if (rank < 6)
	{
		//same process as above
		int* receiveBuffer = new int[length / 2];
		MPI_Scatter(v, length / 2, MPI_INT, receiveBuffer, length / 2, MPI_INT, 0, min_comm);
		int m = computeMin(receiveBuffer, length / 2);
		MPI_Reduce(&m, &min, 1, MPI_INT, MPI_MIN, 0, min_comm);
		if (rank == 4)
			cout << "Min is " << min << endl;
	}
	else if (rank < 8)
	{
		//same process as for product
		int* receiveBuffer = new int[length / 2];
		MPI_Scatter(v, length / 2, MPI_INT, receiveBuffer, length / 2, MPI_INT, 0, max_comm);
		int m = computeMax(receiveBuffer, length / 2);
		MPI_Reduce(&m, &max, 1, MPI_INT, MPI_MAX, 0, max_comm);
		if (rank == 6)
			cout << "Max is " << max << endl;
	}
	MPI_Finalize();
}

