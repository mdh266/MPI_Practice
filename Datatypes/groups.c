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
	
	MPI_Group iegroup, iogroup, iwgroup;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	
	MPI_Comm_group(MPI_COMM_WORLD, &iwgroup);

	

	MPI_Finalize();
	
	return 0;
}
