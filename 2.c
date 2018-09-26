#include <mpi.h>
#include <stdio.h>

int main(int argc, char** argv) {
    MPI_Init(NULL, NULL);

    int world_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);

    int num,rnum;
    if(world_rank == 0)
    {
	printf("Master process %d - Enter input\n",world_rank);
	scanf("%d",&num);
        MPI_Send(&num, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);
    }
    else if(world_rank== 1)
    {
	MPI_Recv(&rnum, 1, MPI_INT, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	printf("slave process %d - value received from master process if %d\n",world_rank,rnum);
    }

    MPI_Finalize();
}

