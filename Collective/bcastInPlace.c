#include<stdio.h>
#include<mpi.h>

int main()
{
	int size, rank;
	MPI_Comm comm = MPI_COMM_WORLD;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(com, &size);
	MPI_Comm_rank(com, &rank);
	
	if(
	
	