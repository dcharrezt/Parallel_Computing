#include <stdio.h>
#include <mpi.h>

#define TIMES 10

int main(int argc, char **argv){

	int i, my_rank, procs, flag, flag_2;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	if(my_rank == 0) {
		flag = 1;
		for (i = 1; i < TIMES; i++) {
			MPI_Send( &flag, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

			MPI_Recv( &flag_2, 1, MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG, 
								MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if(flag_2 == 2) {
				printf("PONG %i\n", flag_2);
			// MPI_Send( &flag, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
		}
		

		}
	}	
	else if(my_rank == 1){
		for (i = 1; i < TIMES; i++) {
			MPI_Recv( &flag, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("PING %i\n", flag);
			flag_2 = 2;
			MPI_Send( &flag_2, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
		}
	}

    MPI_Finalize();

	return 0;
}