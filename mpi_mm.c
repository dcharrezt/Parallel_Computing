
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>

#define MATRIX_SIZE 3
#define NRA MATRIX_SIZE            /* number of rows in matrix A */
#define NCA MATRIX_SIZE            /* number of columns in matrix A */
#define NCB MATRIX_SIZE            /* number of columns in matrix B */
#define MASTER 0               /* rank of first task */
#define FROM_MASTER 1          /* setting a message type */
#define FROM_WORKER 2          /* setting a message type */

int main (int argc, char *argv[]) {

int	size,                  /* number of tasks in partition */
      rank,                  /* a task identifier */
      num_workers,           /* number of worker tasks */
      source,                /* task id of message source */
      dest,                  /* task id of message destination */
      mtype,                 /* message type */
      rows,                  /* rows of matrix A sent to each worker */
      averow, extra, offset, /* used to determine rows sent to each worker */
      i, j, k, rc;           /* misc */

double	a[NRA][NCA],           /* matrix A to be multiplied */
         b[NCA][NCB],           /* matrix B to be multiplied */
         c[NRA][NCB];           /* result matrix C */

MPI_Status status;

MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&rank);
MPI_Comm_size(MPI_COMM_WORLD,&size);

if (size < 2 ) {
  printf("Need at least two MPI tasks. Quitting...\n");
  MPI_Abort(MPI_COMM_WORLD, rc);
  exit(1);
  }

num_workers = size-1;


/**************************** rank 0 ************************************/
   if (rank == MASTER) {
      printf("mpi_mm has started with %d tasks.\n",size);
      // printf("Initializing arrays...\n");
      for (i=0; i<NRA; i++)
         for (j=0; j<NCA; j++)
            a[i][j]= i+j;
      for (i=0; i<NCA; i++)
         for (j=0; j<NCB; j++)
            b[i][j]= i*j;

      /* Measure start time */
      double start = MPI_Wtime();

      /* Send matrix data to the worker tasks */
      averow = NRA/num_workers;
      extra = NRA%num_workers;
      offset = 0;
      mtype = FROM_MASTER;
      
/*      MPI_Bcast(&b, NCA*NCB, MPI_DOUBLE, 0, MPI_COMM_WORLD);*/
      
      for (dest=1; dest<=num_workers; dest++) {
         rows = (dest <= extra) ? averow+1 : averow;
         // printf("Sending %d rows to task %d offset=%d\n",rows,dest,offset);
         
         // mpi broadcast
         
         MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
		 MPI_Send(&a[offset][0], rows*NCA, MPI_DOUBLE, dest, mtype,
                   MPI_COMM_WORLD);
         MPI_Send(&b, NCA*NCB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
         offset = offset + rows;
      }

      /* Receive results from worker tasks */
      mtype = FROM_WORKER;
      for (i=1; i<=num_workers; i++) {
         source = i;
         MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&c[offset][0], rows*NCB, MPI_DOUBLE, source, mtype, 
                  MPI_COMM_WORLD, &status);
         // printf("Received results from task %d\n",source);
      }

      /* Print results */
      
      printf("******************************************************\n");
      printf("Result Matrix:\n");
      for (i=0; i<NRA; i++)
      {
         printf("\n"); 
         for (j=0; j<NCB; j++) 
            printf("%6.2f   ", c[i][j]);
      }
      printf("\n******************************************************\n");
      

      /* Measure finish time */
      double finish = MPI_Wtime();
      printf("Done in %f seconds.\n", finish - start);
   }


/**************************** worker task ************************************/
   if (rank > MASTER) {
      mtype = FROM_MASTER;
      MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&a, rows*NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&b, NCA*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

      for (k=0; k<NCB; k++)
         for (i=0; i<rows; i++) {
            c[i][k] = 0.0;
            for (j=0; j<NCA; j++)
               c[i][k] = c[i][k] + a[i][j] * b[j][k];
         }
      mtype = FROM_WORKER;
      MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&c, rows*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
   }
   MPI_Finalize();
}
