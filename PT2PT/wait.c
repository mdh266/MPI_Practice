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
	MPI_Request request;
	
	int N = 5;
	int * x = (int * ) calloc(N, sizeof(int));
	int i;
	
	if(mytid == 0)
	{
	
		for(i = 0; i < N; i ++)
			x[i] = i;
			
		MPI_Isend(x, N, MPI_INT,
				 1, 0, comm, &request);
	}
	
	if(mytid == 1)
		MPI_Irecv(x, N, MPI_INT,
				 0, 0, comm, &request);
				 
		MPI_Wait(&request,&status);

	
	
	
	printf("process %i: x =\n ", mytid);
	for(i = 0; i < N; i++)
		printf("x[%i] = %i \n", i, x[i]);
	
	
	MPI_Finalize();

	return 0;
}

