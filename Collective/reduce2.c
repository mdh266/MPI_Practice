#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main()
{
	int size, rank;
	
	MPI_Init(NULL,NULL);
	MPI_Comm comm = MPI_COMM_WORLD;
	
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	
	int * x;
	int prod;
	int val;
	
	if(rank == 0)
	{
		x = (int *)calloc(size, sizeof(int));
		int i;
		for(i = 0; i < size; i++)
			x[i] = i+1;
	}
	
	MPI_Scatter(x, 1, MPI_INT,
				&val, 1, MPI_INT,
				0, comm);
				
	MPI_Reduce(&val, &prod, 1, MPI_INT, MPI_PROD, 0, comm);
	
	if(rank == 0)
		printf("prod = %i \n", prod);
	
	MPI_Finalize();
	
}

