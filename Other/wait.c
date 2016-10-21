#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


// Example of non-blocking wait

int main()
{
	int myrank, numprocs;
	
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Request request;
	MPI_Status status;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &numprocs);
	MPI_Comm_rank(comm, &myrank);
	
	int value;
	
	if(myrank == 0)
	{
		value = 2;
		MPI_Isend(&value, 1, MPI_INT, 1, 0, comm, &request);
		printf("Before wait value = %i \n", value);
		MPI_Wait(&request, &status);
	}
	
	printf("After first wait\n");
	printf("Value = %i on proc %i \n", value, myrank);
	
	if(myrank == 1)
	{
		MPI_Irecv(&value, 1, MPI_INT, 0,0, comm, &request);
	    printf("After Irecv, Value = %i on proc %i \n", value, myrank);
		MPI_Wait(&request, &status);
		printf("After wait, Value = %i on proc %i \n", value, myrank);
	}
	
	MPI_Finalize();
	return 0;
} 