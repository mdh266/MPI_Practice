#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main()
{
	int size, rank;
	MPI_Comm comm = MPI_COMM_WORLD;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &size);
	MPI_Comm_rank(comm, &rank);
	
	int i;

	int * x = (int *) calloc(size, sizeof(int));
	int x_local;
	int * others = (int *) calloc(size, sizeof(int));
	
	if(rank == 0)
	{	
		for(i = 0; i < size; i++)
			x[i] = i;
	}
	
	MPI_Scatter(x, 1, MPI_INT, 
			    &x_local, 1, MPI_INT,
				0, comm);
	
	printf("Scattered array on process %i, x_local = %i \n", rank, x_local);
	

	MPI_Allgather(&x_local, 1, MPI_INT, 
 				  others, 1, MPI_INT, comm);
				

	printf("others on process %i\n", rank);
	
	for(i = 0; i < size; i++)
		printf("x[%i] = %i \n", i, others[i]);
		
	
	MPI_Finalize();
	return 0;
}	