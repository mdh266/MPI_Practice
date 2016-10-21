#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define N 2  // THE TOTAL NUMBER OF SENDS + RECEIVES
// Example of non-blocking wait
// FINALLY FIGURE THIS STUFF OUT

int main()
{
	int myrank, numprocs;
	
	MPI_Comm comm = MPI_COMM_WORLD;

	// this allow for a total of 2 requests
	// 1 send and 1 receive
	MPI_Request request[N];
	MPI_Status status[N];
	
	int next, prev, value;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &numprocs);
	MPI_Comm_rank(comm, &myrank);
	
	prev = myrank -1;
	next = myrank +1;
	
	if(myrank == 0)
		prev = numprocs-1;
	if(myrank == numprocs-1)
		next = 0;

	// send to each process' 0-th request
	MPI_Isend(&myrank, 1, MPI_INT, next, 0, comm, &request[0]);

	// this will work since it will just check the first request of each
	// process	
	//MPI_Waitall(1, request, status);
	
	// send to each process' 1-th request
	MPI_Irecv(&value, 1, MPI_INT, prev, 0, comm, &request[1]);

	MPI_Waitall(2, request, status);

	printf("Processor %i's value %i.\n", myrank, value);
	
	MPI_Finalize();
	return 0;
} 
