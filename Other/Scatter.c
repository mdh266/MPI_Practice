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
	MPI_Comm comm = MPI_COMM_WORLD;
	int my_rank, comm_sz;
	int nlocal, ntotal;
	int * my_array, *send_array;
	int psum, gsum;
	int i;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(comm, &comm_sz);
	MPI_Comm_rank(comm, &my_rank);

	// create the local arrays
	nlocal = 4;
	my_array = (int *) malloc(nlocal*sizeof(int));

	// create the global array
	if(my_rank == 0)
	{
		ntotal = nlocal*comm_sz;
		send_array = (int *) malloc(ntotal*sizeof(int));

		for(i = 0; i < ntotal; i++)
			send_array[i] = i;
	
//		print(send_array,ntotal);
//		printf("Distributed arrays = \n");
	}	
	
	//send a data section to each process
	MPI_Scatter(send_array, nlocal, MPI_INT, my_array, nlocal, MPI_INT,0, comm);
		
	// print each distributed array
//	printf("Process %i's array: \n", my_rank);
//	print(my_array, nlocal);

	//partial sum;
	psum = 0;
	for(i = 0; i < nlocal; i++)
		psum += my_array[i];
	
	printf("Processos %i's partial sum = %i\n", my_rank, psum);
	
	// reduce the partial sums to the root
	MPI_Reduce(&psum, &gsum, 1, MPI_INT, MPI_SUM, 0, comm);

	// Print the total sum	
	if(my_rank == 0)
		printf("gsum = %d \n", gsum);

	MPI_Finalize();
	return 0;
}

