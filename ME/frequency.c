#include "mpi.h"

#define N 100


int main(int argc, char *argv[])
{

   int rank, size, tag = 123, root = 0;
   int temp = {1, 2, 3, 4, 5};
   int frequency = 0;
   int eachThreadNumber = 0;
   int result[5];
   MPI_Status status;

   int i, A[N];

   MPI_Init(&argc, &argv);

   MPI_Comm_size(MPI_COMM_WORLD, &size);

   MPI_Comm_rank(MPI_COMM_WORLD, &rank);

   if (rank == 0)
   {

      for (i = 0; i < N; i++)
      {
         srand(time(NULL));
         int r = rand() % 5;
         A[i] = r;
      }
   }
   MPI_Scatter((void *)temp, 1, MPI_INT, (void *)&eachThreadNumber, 1, MPI_INT, 0, MPI_COMM_WORLD);
   MPI_Bcast(data, 100, MPI_INT, root, MPI_COMM_WORLD);
   for (i = 0; i < N; i++)
   {
      if (eachThreadNumber == A[i])
      {
         frequency++;
      }
   }
   MPI_Gather(&frequency, 1, MPI_INT, result, 1, MPI_INT, 0, MPI_COMM_WORLD);
   if (rank == 0)
   {
      for (i = 0; i < 5; i++)
      {
         printf("%d has frequency %d", temp[i], result[i]);
      }
   }
   MPI_Finalize();
}
