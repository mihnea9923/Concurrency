#pragma once
#include <iostream>
#include "mpi.h"
using namespace std;
struct person {
	int age, height, nameSize;
	char name[20];
};

person* initializeStudents(int n)
{
	person* persons = new person[n];
	for (int i = 0; i < n; i++)
	{
		persons[i].age = i + 10;
		persons[i].height = i + 150;
		persons[i].nameSize = 3;
		persons[i].name[0] = 'a' + i;
		persons[i].name[1] = 'b' + i;
		persons[i].name[2] = 'c' + i;
	}

	return persons;
}

void searchStudent(int n, char student[], int studentNameLength)
{
	int rank, size;
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	int blockCounts[2];
	MPI_Datatype personType, oldType[2];
	MPI_Aint offsets[2], lb, extent;

	offsets[0] = 0;
	oldType[0] = MPI_INT;
	blockCounts[0] = 3;
	MPI_Type_get_extent(MPI_INT, &lb, &extent);

	offsets[1] = 3 * extent;
	oldType[1] = MPI_CHAR;
	blockCounts[1] = 20;

	MPI_Type_create_struct(2, blockCounts, offsets, oldType, &personType);
	MPI_Type_commit(&personType);
	person* persons = nullptr;
	if (rank == 0)
		persons = initializeStudents(n);

	int assignedElements = n / size;
	person* recvBuffer = new person[assignedElements];
	MPI_Scatter(persons, assignedElements, personType, recvBuffer, assignedElements,
		personType, 0, MPI_COMM_WORLD);
	for (int i = 0; i < assignedElements; i++)
	{
		if (recvBuffer[i].nameSize == studentNameLength)
		{
			int j;
			for (j = 0; j < recvBuffer[i].nameSize; j++)
				if (recvBuffer[i].name[j] != student[j])
					break;
			if (j == studentNameLength)
				cout << rank * assignedElements + i << " ";
		}

	}
	delete[] persons;
	delete[] recvBuffer;
	MPI_Type_free(&personType);
	MPI_Finalize();
}