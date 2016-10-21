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
	
	int ntotal, nlocal = 2;
	int * sendarray1;
	int * sendarray2;
	int * localarray1;
	int * localarray2;
	int i, psum, gsum;
	
	localarray1 = (int *) malloc(nlocal*sizeof(int));
	localarray2 = (int *) malloc(nlocal*sizeof(int));
	
	if(myrank == 0)
	{	
		ntotal = nlocal*comm_sz;
		
		sendarray1 = (int *) malloc(ntotal*sizeof(int));	
		sendarray2 = (int *) malloc(ntotal*sizeof(int));	
		
		for(i = 0; i < ntotal; i++)
		{
			sendarray1[i] = i;
			sendarray2[i] = i;
		}
			
//		print(sendarray1,ntotal);
//		print(sendarray2,ntotal);
		printf("Distributed arrays = \n");
	}
	
	MPI_Scatter(sendarray1, nlocal, MPI_INT, localarray1,
				nlocal, MPI_INT, 0, comm);
				
	MPI_Scatter(sendarray2, nlocal, MPI_INT, localarray2,
				nlocal, MPI_INT, 0, comm);
	
	// print each distributed array
	printf("Process %i's array1: \n", myrank);
	print(localarray1, nlocal);
	printf("Process %i's array2: \n", myrank);
	print(localarray2, nlocal);
	
	// compute each processor local dot product	
	psum = 0;
	
	for(i = 0; i < nlocal; i++)
	{
		psum += localarray1[i]*localarray2[i];
	}

	/// make global dot product	
	MPI_Reduce(&psum, &gsum, 1, MPI_INT, MPI_SUM, 0, comm);
	
	if(myrank == 0)
		printf("dot product = %i \n", gsum);
	
	
	MPI_Finalize();
	return 0;
	
}

