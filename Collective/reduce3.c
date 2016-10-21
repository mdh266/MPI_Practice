#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


// finds min or max


int main()
{
	int mytid, ntids;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &ntids);
	MPI_Comm_rank(comm, &mytid);

	int * x;
	int min;
	int max;
	int value;

	if(mytid == 0)
	{
		int N = ntids;
		int i;

		x = (int *) malloc(N* sizeof(int));
	
		for(i = 0; i < N; i++)
			x[i] = i;
		
		int min = 0;
	}

	MPI_Scatter(x, 1, MPI_INT, &value, 1, MPI_INT, 0, comm);
	
	MPI_Reduce(&value, &min, 1, MPI_INT, MPI_MIN, 0, comm);
	
	MPI_Reduce(&value, &max, 1, MPI_INT, MPI_MAX, 0, comm);

	if(mytid == 0)
	{
		printf("min = %i \n", min);
		printf("max = %i \n", max);
	}
		
	

	MPI_Finalize();

	return 0;
}

