#include<stdio.h>
#include<mpi.h>
#include<math.h>

// calculates pi using the power series definition.

int main()
{
	int myrank, comm_sz;
	MPI_Comm comm = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm,&comm_sz);
	MPI_Comm_rank(comm,&myrank);
	
		// roots parameters
	int n;
	double value, globalresult;
	double localval1, localval2;
	
	// processes parameters	
	int i, nlocal, deg;
	double localresult;
	
	if(myrank == 0)
	{
		n = 1000000;
		value = 1.0;
	}
	
	// broadcast n
	MPI_Bcast(&n, 1, MPI_INT, 0, comm);
	
	// broadcast globalvalue to use
	MPI_Bcast(&value, 1, MPI_DOUBLE, 0, comm);
	
	nlocal  = n / 2;
	
	for(i = myrank*nlocal; i < (myrank+1)*nlocal; i++)
	{
		deg = 2*i + 1;
		localresult += pow(-1.0,i) * pow(value,deg) / ((double) deg);
	}
	
	localresult *= 4.0;
	
	MPI_Gather(&localresult, 1, MPI_DOUBLE, 
			   &localval1, 1, MPI_DOUBLE, 0, comm);
	
	MPI_Gather(&localresult, 1, MPI_DOUBLE, 
			   &localval2, 1, MPI_DOUBLE, 0, comm);
			   
	if(myrank == 0)
	{
		globalresult = localval1 + localval2;
		printf("Pi = %0.15f \n", globalresult);	
	}	

	MPI_Finalize();
	
	return 0;
}
