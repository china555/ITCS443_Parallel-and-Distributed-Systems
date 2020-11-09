#include <stdio.h>
#include "mpi.h"
#include <Math.h>
#define N 8

int main(int argc, char *argv[])
{
    int xPowerOfTwo[N];
    int xMultipleByY[N];
    int x[N] = {1, 3, 5, 7, 10, 12, 14, 16};
    int y[N] = {2, 4, 6, 8, 9, 11, 13, 15};
    int rankForEachThread, sizeOfThread, tag = 123, root = 0, i, interval, start, end;
    MPI_Status status;
    int sumX = 0, sumY = 0, sumXPowerOfTwo = 0, sumXMultipleByY = 0;
    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &sizeOfThread);
    MPI_Comm_rank(MPI_COMM_WORLD, &rankForEachThread);
    // if (rankForEachThread == 0)
    // {
    //     srand(time(NULL));
    //     for (i = 0; i < N; i++)
    //     {
    //         x[i] = rand() % 100;
    //         y[i] = rand() % 100;
    //     }
    // }
    // MPI_Bcast(x, N, MPI_INT, root, MPI_COMM_WORLD);
    // MPI_Bcast(y, N, MPI_INT, root, MPI_COMM_WORLD);

    for (number = rankForEachThread; number < N; number = number + sizeOfThread)
    {
        xPowerOfTwo[number] = pow(x[number], 2);
        xMultipleByY[number] = x[number] * y[number];
        sumX = sumX + x[number];
        sumY = sumY + y[number];
        sumXPowerOfTwo = sumXPowerOfTwo + xPowerOfTwo[number];
        sumXMultipleByY = sumXMultipleByY + xMultipleByY[number];
        printf("The process %d do x^2 = %d\n x*y = %d\nsumx = %d\nsumy = %d\nsumXPowerOfTwo = %d\nsumXMultipleByY = %d", rankForEachThread, xPowerOfTwo[start], xMultipleByY, sumX, sumY, sumXPowerOfTwo, sumXMultipleByY);
    }

    MPI_Finalize();
    return 0;
}
