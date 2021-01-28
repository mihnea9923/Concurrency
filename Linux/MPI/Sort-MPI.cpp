#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
using namespace std;
int main(int argc, char* argv[])
{
    int  numtasks, rank, len;
    char hostname[MPI_MAX_PROCESSOR_NAME];

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &numtasks); // Total number of processes.
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // The current process ID / Rank.
    MPI_Get_processor_name(hostname, &len);
    int array[4] = { 4 , 1 , 5 , 2 };
    int sum = 0;
    if (rank == 0)
    {
       
            for (int i = 0; i < 4; i++)
            {
                MPI_Send(&array[i], 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
            }
            for (int i = 0; i < 4; i++)
            {
                MPI_Recv(&array[i], 1, MPI_INT, i + 1, 0, MPI_COMM_WORLD, NULL);
                cout << array[i] << " ";
            }
            cout << endl;

    }
    else {
        int curentValue = 0;
        for (int i = rank; i <= 4; i++)
        {
            int receivedValue;
            MPI_Recv(&receivedValue, 1, MPI_INT, rank - 1, 0, MPI_COMM_WORLD, NULL);
            if (curentValue == 0)
            {
                curentValue = receivedValue;
            }
            else if (curentValue <= receivedValue)
            {
                MPI_Send(&receivedValue, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
            }
            else if (curentValue > receivedValue)
            {
                MPI_Send(&curentValue, 1, MPI_INT, rank + 1, 0, MPI_COMM_WORLD);
                curentValue = receivedValue;
            }
        }
        MPI_Send(&curentValue, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    }

    MPI_Finalize();

}
