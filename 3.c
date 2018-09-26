#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) 
{
    
	MPI_Init(NULL, NULL);
	int world_rank;

	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

	int num,rnum;
	if(world_rank == 0)
	{
		
		printf("Root process %d Enter a value\n",world_rank);
		scanf("%d",&num);
	
	}
	MPI_Bcast(&num, 1, MPI_INT, 0, MPI_COMM_WORLD);

	printf("process %d - Value received is %d\n",world_rank,num);

	MPI_Finalize();

}

