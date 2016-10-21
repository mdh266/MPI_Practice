#include<stdio.h>
#include<mpi.h>


int main()
{
	int mytid, ntids;
	MPI_Comm comm = MPI_COMM_WORLD;
	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm, &ntids);
	MPI_Comm_rank(comm, &mytid);

	MPI_Status * status = MPI_STATUS_IGNORE;
	
	int N;
	
	if(mytid == 0)
	{
		N = 5;
		MPI_Send(&N, 1, MPI_INT,
				 1, 0, comm);
	}
	
	if(mytid == 1)
		MPI_Recv(&N, 1, MPI_INT,
				 0, 0, comm, status);
	
	
	printf("Value of N %i on process %i\n", N, mytid);

	
	
	MPI_Finalize();

	return 0;
}

