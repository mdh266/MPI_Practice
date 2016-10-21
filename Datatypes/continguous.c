#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


void print(int * x, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%i\n", x[i]);
}

int main()
{
	
	int size, rank, root = 0;
	MPI_Comm comm = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);
	
	MPI_Datatype MPI_x;
	int * x = (int *) malloc(size*sizeof(int));
	
	///  size MPI_INTs are stored in MPI_x
	MPI_Type_contiguous(size, MPI_INT, &MPI_x);
	
	MPI_Type_commit(&MPI_x);
	
	if(rank == root)
	{
		int i;
		for(i = 0; i < size; i++)
			x[i] = i;
			
		MPI_Send(x, 1, MPI_x, 
				 1, 0, comm);
	}
	
	if(rank == 1)
	{
		MPI_Recv(x, 1, MPI_x, 
				 0, 0, comm, MPI_STATUS_IGNORE);
				 
		print(x, size);
	}
	
	MPI_Type_free(&MPI_x);
	

	
	MPI_Finalize();
	
	return 0;
}
