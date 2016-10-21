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
	int N = 5;
	int * x = (int * ) calloc(N, sizeof(int));
	int i;
	
	if(mytid == 0)
	{
	
		for(i = 0; i < N; i ++)
			x[i] = i;
			
		MPI_Ssend(x, N, MPI_INT,
				 1, 0, comm);
	}
	
	if(mytid == 1)
	{
		int source, tag;
		MPI_Probe(source, tag, comm, &status);

		printf("source = %i\n", source);
		printf("tag = %i\n", tag);
		MPI_Recv(x, N, MPI_INT,
		
				MPI_ANY_SOURCE, 0,
				comm, &status);
	}
	
	printf("process %i: x =\n ", mytid);
	for(i = 0; i < N; i++)
		printf("x[%i] = %i \n", i, x[i]);
	
	
	MPI_Finalize();

	return 0;
}

