#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main()
{
	int myrank, numprocs;
	
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Win win;
	
	int next, prev, value;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &numprocs);
	MPI_Comm_rank(comm, &myrank);
	
	prev = myrank -1;
	next = myrank +1;
	
	if(myrank == 0)
		prev = MPI_PROC_NULL;
	if(myrank == numprocs-1)
		next = MPI_PROC_NULL;
	
	// set the sending window
	MPI_Win_create(NULL, 0, 1, MPI_INFO_NULL, comm, &win);

	// see the receiving window
	MPI_Win_create(&value, sizeof(int), 1, MPI_INFO_NULL, comm, &win);
	
	MPI_Win_fence(0, win);
	
	MPI_Put(&myrank, 1, MPI_INT, next, 0, 1, MPI_INT, win);

	MPI_Win_fence(0, win);

	printf("Processor %i's value %i.\n", myrank, value);
	
	MPI_Finalize();
	return 0;
} 
