#include <stdio.h>
#include "mpi.h"

#define N 4

int main(int argc, char *argv[])
{
	int xPowerOfTwo[N], xMultipleByY[N], x[N], y[N], rankForEachThread, sizeOfThread, tag = 123, root = 0;
	MPI_Status status;
	int sumX = 0, sumY = 0, sumXPowerOfTwo = 0, sumXMultipleByY = 0;
	int resultsumX = 0, resultsumY = 0, resultsumXPowerOfTwo = 0, resultsumXMultipleByY;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &sizeOfThread);
	MPI_Comm_rank(MPI_COMM_WORLD, &rankForEachThread);
	float m = 0.0, m1 = 0.0, m2 = 0.0, b = 0.0, b1 = 0.0, b2 = 0.0;
	float resultY[N]; //final y=mx+b
	if (rankForEachThread == 0)
	{
		srand(time(NULL));
		for (i = 0; i < N; i++)
		{
			x[i] = rand() % 100 + 1;
			y[i] = rand() % 100 + 1;
		}
	}
	MPI_Bcast(x, N, MPI_INT, root, MPI_COMM_WORLD);
	MPI_Bcast(y, N, MPI_INT, root, MPI_COMM_WORLD);
	for (int number = rankForEachThread; number < N; number = number + sizeOfThread)
	{
		xPowerOfTwo[number] = x[number] * x[number];
		xMultipleByY[number] = x[number] * y[number];
		sumX = sumX + x[number];
		sumY = sumY + y[number];
		sumXPowerOfTwo = sumXPowerOfTwo + xPowerOfTwo[number];
		sumXMultipleByY = sumXMultipleByY + xMultipleByY[number];
		printf("The process %d\ndo x^2 = %d\n x*y = %d\nsumx = %d\nsumy = %d\nsumXPowerOfTwo = %d\nsumXMultipleByY = %d\n", rankForEachThread, xPowerOfTwo[number], xMultipleByY[number], sumX, sumY, sumXPowerOfTwo, sumXMultipleByY);
	}
	//----reduce----
	MPI_Reduce(&sumX, &resultsumX, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	MPI_Reduce(&sumY, &resultsumY, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	MPI_Reduce(&sumXPowerOfTwo, &resultsumXPowerOfTwo, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);
	MPI_Reduce(&sumXMultipleByY, &resultsumXMultipleByY, 1, MPI_INT, MPI_SUM, root, MPI_COMM_WORLD);

	if (rankForEachThread == 0)
	{
		printf("\n\nThe process %d\nsumx = %d\nsumy = %d\nsumXPowerOfTwo = %d\nsumXMultipleByY = %d\n", rankForEachThread, resultsumX, resultsumY, resultsumXPowerOfTwo, resultsumXMultipleByY);

		m1 = (N * resultsumXMultipleByY) - (resultsumX * resultsumY);
		m2 = (N * resultsumXPowerOfTwo) - (resultsumX * resultsumX);
		m = m1 / m2;

		printf("---------- Calculate M ----------\nM1 = %.2f\nM2 = %.2f\nM1/M2 = %.2f\n", m1, m2, m);

		b1 = resultsumY - (m * resultsumX);
		b2 = N;
		b = b1 / b2;

		printf("---------- Calculate B ----------\nb1 = %.2f\nb2 = %.2f\nb1/b2 = %.2f\n", b1, b2, b);

		printf("---------- Calculate Y ----------\n");
	}

	MPI_Bcast(&m, 1, MPI_FLOAT, root, MPI_COMM_WORLD);
	MPI_Bcast(&b, 1, MPI_FLOAT, root, MPI_COMM_WORLD);

	for (int i = rankForEachThread; i < N; i = i + sizeOfThread)
	{
		resultY[i] = ((m * x[i]) + b);
	}

	if (rankForEachThread == 0)
	{
		for (int i = 0; i < N; i++)
		{
			printf("if x = %d\t Y [%d] = %.2f\n", x[i], i, resultY[i]);
		}
	}
	MPI_Finalize();
}