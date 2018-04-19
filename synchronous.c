#include <stdio.h>
#include <mpi.h>

#define TIMES 10

int main(int argc, char **argv) {

	int i, my_rank, procs, count = 0;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank == 0) {
		for (i = 1; i < TIMES; i++) {
			count++;
			MPI_Ssend( &count, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
			
			MPI_Recv( &count, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, 
								MPI_COMM_WORLD, MPI_STATUS_IGNORE);

			printf("0 Recieved PING counter %i and sends to 1\n", count);
		}
	}	
	else if(my_rank == 1){
		for (i = 1; i < TIMES; i++) {
			MPI_Recv( &count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("1 Recieved PING counter %i and sends to 0\n", count);
			// count ++;
			MPI_Ssend( &count, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}

	MPI_Finalize();

	return 0;
}