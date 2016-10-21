#include<stdio.h>
#include<string.h>
#include<mpi.h>

const int MAX_STRING = 100;

int main(int argc, char * argv[])
{
	char greeting[MAX_STRING];
	int comm_sz;
	int my_rank;
	
	int q;
	
	// SETS UP EVERYTHING AND STORES IN MPI_COMM_WORLD
	MPI_Init(NULL, NULL); 

	// GETS THE INFORMATION FROM MPI_COMM_WORLD
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	// every process but the 0-th does this!	
	if(my_rank != 0)
	{	
		sprintf(greeting, "Greetings from process %d of %d",
				my_rank, comm_sz);
				
		MPI_Send(greeting, strlen(greeting)+1, MPI_CHAR, 0, 0,
				MPI_COMM_WORLD);
	}
	
	// THE ZEROTH PROCESS DOES THIS
	else
	{
		printf("Greetings from process %d of %d!\n", my_rank,
				comm_sz);
				
		for(q = 1; q< comm_sz; q++)
		{
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, q, 0,
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				
			printf("%s\n", greeting);
		}
	}	
	
	MPI_Finalize();
	return 0;
}


