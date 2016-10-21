#include<stdio.h>
#include<stdlib.h>
#include<mpi.h>

void init(double * local_A, int local_n, int n, int my_rank,
			MPI_Comm comm);
			
void print(double * local_A, int local_n, int n, int my_rank,
			MPI_Comm comm);
			
void vec_add(double * local_A, int local_n);



int main(void)
{
	int my_rank, comm_sz;
	int local_n, n= 50;
	double * local_A;
	
	
	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
	
	local_n = n/comm_sz;
	
	// NEED TO ALLOCATE MEMORY BEFORE ASSIGNING IT
	local_A = malloc(n*sizeof(double));
	
	// Initialize the array and scatter it to the other
	// processes
	init(local_A, local_n, n, my_rank, MPI_COMM_WORLD);
	
	// PRINT THE ARRAY
	print(local_A,local_n, n, my_rank, MPI_COMM_WORLD);
	
	// Have each process add 1 to their entries
	vec_add(local_A, local_n);
	
	// PRINT THE ARRAY
	print(local_A,local_n, n, my_rank, MPI_COMM_WORLD);
	
	// Free each local processors memory
	free(local_A);
	
	//print the vector
	
	MPI_Finalize();
	return 0;
}

void init(double * local_A, int local_n, int n, int my_rank,
			MPI_Comm comm)
{
	int i;
	double * A = NULL;
	
	if(my_rank == 0)
	{
		A = malloc(n*sizeof(double));
		
		for(i = 0; i < n; i++)
		{	
			A[i] = i;
	//		printf("%f\n", A[i]);
		}
		
		// scatter the send_buff, send_count, send_type, recv_buff,
		// recv_count, recv_type, src_proc, comm
		MPI_Scatter(A, local_n, MPI_DOUBLE, local_A, local_n,
					MPI_DOUBLE, 0, comm);
		free(A);
	}
	else
	{
		MPI_Scatter(A, local_n, MPI_DOUBLE, local_A, local_n,
					MPI_DOUBLE, 0, comm);
	}

}

void print(double * local_A, int local_n, int n, int my_rank,
			MPI_Comm comm)
{
	// EVERY PROCESS SHOULD HAVE AN A
	double * A = NULL;
	int i;
	
	
	// GATHER ALL THE LOCAL_A's into an A and then print it, 
	// and free it
	if(my_rank == 0)
	{
		A = malloc(n*sizeof(double));
		MPI_Gather(local_A, local_n, MPI_DOUBLE, A, local_n, 
					MPI_DOUBLE, 0, comm);
		printf("Array = \n");
		for(i = 0; i < n; i++)
			printf("%f \n", A[i]);
		
		free(A);
	}
	
	// ELSE GATHER THE LOCAL_A TO A on process 0?
	else 
	{
		MPI_Gather(local_A, local_n, MPI_DOUBLE, A, local_n,
					MPI_DOUBLE, 0, comm);
	}
}

	
void vec_add(double* local_A, int local_n)
{
	int local_i;
	
	for(local_i = 0; local_i < local_n; local_i++)
	{
		local_A[local_i] += 1;
	}
}
