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

	MPI_Status  status[2];
	MPI_Request request[2];
	
	int N = 5;
	int * x = (int * ) calloc(N, sizeof(int));
	int i;
	
	if(mytid == 0)
	{
	
		for(i = 0; i < N; i ++)
			x[i] = i;
			
		MPI_Isend(x, N, MPI_INT,
				 1, 0, comm, &request[0]);
				 
		MPI_Isend(x, N, MPI_INT,
				 2, 0, comm, &request[1]);
	
		// has to be realized on right process
		MPI_Waitany(2, request, status);
	}
	
	
	if(mytid != 0)
		MPI_Recv(x, N, MPI_INT,
				 0, 0, comm, &status[mytid-1]);
				 

	
	printf("process %i: x =\n ", mytid);
	for(i = 0; i < N; i++)
		printf("x[%i] = %i \n", i, x[i]);
	
	
	MPI_Finalize();

	return 0;
}

