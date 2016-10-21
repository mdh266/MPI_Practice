#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

void print(int * x, int n)
{
	int i;
	for(i = 0; i < n; i++)
		printf("%i \n", x[i]);
}

int main()
{
	int myrank, comm_sz;
	MPI_Comm comm;
	
	MPI_Init(NULL,NULL);
	comm = MPI_COMM_WORLD;
	MPI_Comm_size(comm,&comm_sz);
	MPI_Comm_rank(comm,&myrank);
	
	int localsize = myrank+1;
	int i;
	int * localarray = (int *) malloc(localsize*sizeof(int));
	int * globarray;
	int * rcnts = (int *) malloc(comm_sz*sizeof(int));
	int * rdispls (int *) malloc(comm_sz*sizeof(int));
	
	if(myrank == 0)
	{
		globarray = (int *) malloc(comm_sz*(comm_sz+1)*0.5*sizeof(int));
		for(i = 0; i < comm_sz; i++)
		{
			rcnts[i] = i+1;
			rdispls[i] = i+1;
		}
	}
	
	for(i = 0; i < localsize+1; i++)
		localarray[i] = i;
		
	//MPI_GatherV(localarray, localsize

	printf("Processors %i's local array \n", myrank);
	print(localarray, myrank+1);
	
	
	
	MPI_Finalize();
	return 0;
}
