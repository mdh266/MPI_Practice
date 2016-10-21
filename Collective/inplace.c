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

	int * x, * y;
	int * x_local, * y_local;
	int sum;
	int N;
	int N_local;

	if(mytid == 0)
	{
		N = 100;
		N_local = N/ntids;

		x = (int *) malloc(N* sizeof(int));
		y = (int *) malloc(N* sizeof(int));
		
		int i;
		for(i = 0; i < N; i++)
		{
			x[i] = i;
			y[i] = i;
		}
		
		int sum = 0;

	}
	
	
	MPI_Bcast(&N_local, 1, MPI_INT, 0, comm);

	x_local = (int * ) calloc(N_local, sizeof(int));
	y_local = (int * ) calloc(N_local, sizeof(int));


	MPI_Scatter(x, N_local, MPI_INT, x_local, N_local, MPI_INT, 0, comm);
	MPI_Scatter(y, N_local, MPI_INT, y_local, N_local, MPI_INT, 0, comm);
	
	int i;
	int psum = 0;

	for(i = 0; i < N_local; i++)
		psum += x_local[i]*y_local[i];
	
	void * sendbuf;
	
	if(mytid == 0)
		sendbuf = MPI_IN_PLACE;
	else
		sendbuf =  &psum;
		
	MPI_Reduce(&psum, &sum, 1, MPI_INT, MPI_SUM, 0, comm);

	if(mytid == 0)
	{
		int i;

		printf("sums = %i \n", sum);
	
		sum = 0;	
		
		for(i = 0; i < 100; i++)
			sum += i*i;
		
		printf("sums = %i \n", sum);
	}
	MPI_Finalize();

	return 0;
}

