#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>


int main()
{
	int mytid, ntids;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &ntids);
	MPI_Comm_rank(comm, &mytid);

	MPI_Status status;

	int N;
	int x;
	
	if(mytid == 0)
		N = 5;

	if(mytid == 2)
		x = 2;
		
	printf("process %i before : N = %i\n ", mytid, N);
	printf("process %i before : x= %i\n ", mytid, x);

	
	if(mytid == 0)
		MPI_Sendrecv( &N, 1, MPI_INT, 1, 0, 
			  	      &x, 1, MPI_INT, 2, 0,
			    	  comm, &status);
			    	  
	if(mytid == 1)
		MPI_Recv(&N, 1, MPI_INT, 0, 0,
			    	  comm, &status);
			    	  
	if(mytid == 2)
		MPI_Send(&x, 1, MPI_INT, 0, 0,
					comm);


	printf("process %i after: N = %i\n ", mytid, N);
	printf("process %i after: x= %i\n ", mytid, x);
	
	MPI_Finalize();

	return 0;
}

