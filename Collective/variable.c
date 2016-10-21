// uses variable scattering!

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

	int * x;
	int * x_local;
	int N;
	int * sendcnts;
	int * dspls;

	sendcnts = (int *) calloc(ntids, sizeof(int) );
	dspls = (int *) calloc(ntids, sizeof(int) );
	
	if(mytid == 0)
	{
		N = 10;

		x = (int *) malloc(N* sizeof(int));
	
		int i;
		for(i = 0; i < N; i++)
		{
			if(i == 0)
				x[i] = 1;
			else if(i < 3)
				x[i] = 2;
			else if(i < 6)
				x[i] = 3;
			else
				x[i] = 4;
		}
		
		
		for(i = 0; i < N; i++)
			printf("x[%i] = %i\n", i, x[i]);
			
	
	
	for(i = 0; i < ntids; i++)
			sendcnts[i] = i + 1;
			
	dspls[0] = 0;
	dspls[1] = 1;
	dspls[2] = 3;
	dspls[3] = 6;
	
		printf("scatter! \n");
			
	}
	
	int i;
	
	x_local = (int * ) calloc(N, sizeof(int));
	
	int recvcnt = mytid+1;

	MPI_Scatterv(x, sendcnts, dspls, MPI_INT, 
				x_local, recvcnt, MPI_INT, 0, comm);
	

	printf("On processor %i, vector = \n",mytid);
	
	for(i = 0; i <= mytid; i++)
		printf("xlocal[%i] = %i\n", i, x_local[i]);
		
		
	// switch order!!!
	for(i = 0; i <= mytid; i++)
		x_local[i] *= x_local[i];
	
	MPI_Gatherv(x_local, recvcnt, MPI_INT,
				x, sendcnts, dspls, MPI_INT,
				0, comm);
				
	if(mytid == 0)
	{
		for(i = 0; i < N; i++)
			printf("x[%i] = %i\n", i, x[i]);
			
	}
	
	MPI_Allallv(
		
MPI_Finalize();

	return 0;
}

