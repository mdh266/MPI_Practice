#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

// Example of 1 sided commmunication

int main()
{
	int myrank, numprocs;
	
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Win win; // each process must have own window?
	
	int value;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &numprocs);
	MPI_Comm_rank(comm, &myrank);

	if(myrank == 0)
	{
		value = 10;	
		// window to have things taken out of
		MPI_Win_create(NULL, 0, 1,
				MPI_INFO_NULL, comm, &win);
	}

	// must creat window for things to be placed
	if(myrank == 1)
		MPI_Win_create(&value, sizeof(int), 1, 
			MPI_INFO_NULL, comm, &win);
	
	printf("Before win_fence: \n Processor %i's value %i.\n", 
			myrank, value);
	
	// synchronize the windows
	MPI_Win_fence(0, win);
	
	// copy from one to the other
	if(myrank == 0)
		MPI_Put(&value,1,MPI_INT, 1, 0, 1, MPI_INT, win);		

	// synchronize the windows
	MPI_Win_fence(0,win);

	// clear the windows
	MPI_Win_free(&win);

	printf("After win_fence: \n Processor %i's value %i.\n", 
			myrank, value);
	
	MPI_Finalize();
	return 0;
} 
