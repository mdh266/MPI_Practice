#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

#define N 4
// Example of non-blocking wait
// lower overhaead if receive already posted when sender initiates
// communication
//
// BUT STILL WORKS!
int main()
{
	int myrank, numprocs;
	
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Request request[N];
	MPI_Status status[N];
	
	int next, prev, buf[2];
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &numprocs);
	MPI_Comm_rank(comm, &myrank);
	
	prev = myrank -1;
	next = myrank +1;
	if(myrank == 0)
		prev = numprocs-1;
	if(myrank == numprocs-1)
		next = 0;
	
	MPI_Isend(&myrank, 1, MPI_INT, next, 0, comm, &request[2]);
	MPI_Isend(&myrank, 1, MPI_INT, next, 0, comm, &request[3]);

	MPI_Irecv(&buf[0], 1, MPI_INT, prev, 0, comm, &request[0]);
	MPI_Irecv(&buf[1], 1, MPI_INT, prev, 0, comm, &request[1]);
	

	MPI_Waitall(4, request, status);
	
	MPI_Finalize();
	return 0;
} 
