#include <stdio.h>
#include <mpi.h>

#define TAM 1000

int main(int argc, char **argv){
	int i, my_rank, procs, part, ind=0;
	int vet[TAM];
	int tag=10;
	MPI_Status status;

	int st = 0;
	int tmp;
	int a;

	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	part = (int)(TAM / (procs-1));

	if(my_rank == 0) {
		for (i = 0; i < TAM; ++i)
		{	
			vet[i] = i;
		}
		for (i = 1; i < procs; i++)
		{
			MPI_Send(&vet[ind],part,MPI_INT,i,tag,MPI_COMM_WORLD);
			ind = ind + part;
		}

		for (i = 1; i < procs; i++)
		{
			MPI_Recv( &a , 1 ,MPI_INT, MPI_ANY_SOURCE, MPI_ANY_TAG ,MPI_COMM_WORLD, &status);
			st += a;
		}

		printf("%d \n",st);

	}
	else{
		MPI_Recv(vet,part,MPI_INT,0,tag,MPI_COMM_WORLD,&status);
		//printf("Proc.%d recibe [ ", miRank);
		int s = 0;
		for(i = 0;i < part; i++) {
			s += vet[i];
		}

		// printf("%d\n", s);

		MPI_Send( &s , 1,MPI_INT,0,tag,MPI_COMM_WORLD);

	}
}