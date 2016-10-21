#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


void print(int * x, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf("%i ", x[i*n+j]);
		printf("\n");
	}
}

void printRow(int * x, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%i ", x[i]);
		
	printf("\n");
}

int main()
{
	
	int size, rank, root = 0;
	MPI_Comm comm = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	
	MPI_Datatype MPI_row;
	
	int * x = (int *) malloc(size*size*sizeof(int));
	int * z = (int *) malloc(size*sizeof(int));
	
	
	MPI_Type_vector(4, 2, 3, MPI_INT, &MPI_row);
	MPI_Type_commit(&MPI_row);
	
	if(rank == root)
	{
		int i;
		for(i = 0; i < size*size; i++)
		{
			x[i] = i;
		}
			
		print(x, size);
		
		MPI_Send(x, 1, MPI_row, 
			 1, 0, comm);
	}
	
	if(rank == 1)
	{
		MPI_Recv(z, 1, MPI_row, 
				 0, 0, comm, MPI_STATUS_IGNORE);
				 
		printRow(z, size);
	}
	
	MPI_Type_free(&MPI_row);
	
	MPI_Finalize();
	
	return 0;
}
