#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

void init(double * A, int n);
void print(double * A, int n);

int main(void)
{
	int N = 4;
	int my_rank, comm_sz;
	
	double * A = NULL;
	
	MPI_Init(NULL,NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	init(A,N);

	if(my_rank == 0_)
		print(A,N);
	
	return 0;
}

void init(double * A, int n, int my_rank, MPI_Comm comm)
{
	double * local_A = NULL;
	
	if(my_rank == 0)
	{
		A = calloc(N*N, sizeof(double));
		int i, j;
	
		for(i = 0; i < n; i++)
			for(j = 0; j < n; j++)
				A[i*n+j] = i*n + j;
	}
}
		
void print(double * A, int n)
{
	int i, j;
	for(i = 0; i < n; i++)
	{
		for(j = 0; j < n; j++)
			printf("%f ", A[i*n + j]);
		printf("\n");
	}
}
