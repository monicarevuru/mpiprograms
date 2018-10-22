#include <mpi.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char** argv) 
{
    
	MPI_Init(NULL, NULL);
	int world_rank;
	int world_size;
    	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
	int a[world_size];
	int i,sum=0;
	float avg;
	if(world_rank == 0)
	{
		printf("Random numbers\n");
		for(i=0;i<world_size;i++)
		{
			a[i]=rand()%100;
			printf("%d\n",a[i]);
			sum = sum + a[i];
		}
		avg = sum / world_size;
	}
	MPI_Bcast(&avg, 1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	float std = (a[world_rank] - avg)*(a[world_rank] - avg);
	float *std_avgs = NULL;
	if(world_rank == 0)
	{
		std_avgs = malloc(sizeof(float) * world_size);

	}
	MPI_Gather(&std, 1, MPI_FLOAT, std_avgs,1, MPI_FLOAT, 0, MPI_COMM_WORLD);
	double savg;
	float ssum=0;
	if(world_rank == 0)
	{
		for(i=0;i<world_size;i++)
		{
			ssum = ssum + std_avgs[i];
		}
		savg = (ssum / world_size);
		printf("Standard Deviation = %f\n",savg);
		
	}
	
	MPI_Finalize();

}
