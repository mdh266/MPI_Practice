#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

int main()
{
	int myrank, comm_sz;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Status status;
	MPI_Init(NULL,NULL);
	int irec = -1;
	
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &myrank);
	
	if(myrank == 0)
		MPI_Send(&myrank, 1, MPI_INT, 1, 0, comm);
		
	if(myrank == 1)
		MPI_Recv(&irec, 1, MPI_INT, 0, 0, comm, &status);
	
	printf("myrank = %d, received= %d \n", myrank, irec);
	printf("source is = %d \n", status.MPI_SOURCE);	
	printf("Tag = %d \n", status.MPI_TAG);
	
	MPI_Finalize();

	return 0;
}