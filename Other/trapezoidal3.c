#include<stdio.h>
#include<mpi.h>

// remember can pass by ref in c
void Get_input(int my_rank, int comm_sz, double * a, double * b, int * n);

double Trap(double left_endpt, double right_endpt, 
			int trap_count, double base_len);
			
double f(double x);

int main(void)
{
	// IS THIS ALL GLOBAL DATA OR LOCAL TO EACH PROCESS?
	int
		my_rank,
		comm_sz, 
		n,
		local_n;
	double 
		a,
		b,
		h,
		local_a,
		local_b;
	double
		local_int,
		total_int;
	
	int source;
	
	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD,&my_rank);
	MPI_Comm_size(MPI_COMM_WORLD,&comm_sz);

	// every process will do this!
	Get_input(my_rank,comm_sz, &a, &b, &n);

	// every process create this data
	h = (b-a)/n;
	local_n = n/comm_sz;
	
	local_a = a + my_rank*local_n*h;
	local_b = local_a + local_n*h;

	// every process will do this
	local_int = Trap(local_a, local_b, local_n, h);


	// USE THE MPI REDUCE FUNCTION INSTEAD OF LOOPING THROUGH 
	// ALL THE OTHER PROCESSORS VALUES	
	MPI_Reduce(&local_int, &total_int, 1, MPI_DOUBLE, MPI_SUM, 0,
		 	MPI_COMM_WORLD);
	
	if(my_rank == 0)
	{
		printf("With n = %d trapezoid, our estimate \n", n);
		printf("of the integral from %f to %f = %.15e\n",
			a, b, total_int);		
	}

	
	MPI_Finalize();

	return 0;
}

double Trap(double left_endpt, double right_endpt, 
			int trap_count, double base_len)
{

	// EVERY PROCESS WILL DO THIS..  NOTE IT DOENST USE ANY
	// MPI INFORMATION

	double estimate, x;
	int i;
	
	estimate = (f(left_endpt) + f(right_endpt))/2.0;
	
	for(i = 1; i <= trap_count-1; i++)
	{
		x = left_endpt + i*base_len;
		estimate += f(x);
	}
	
	estimate = estimate*base_len;
	
	return estimate;
}


double f(double x)
{
	return x;
}
	
void Get_input(int my_rank, int comm_sz, double * a, double * b, int * n)
{
	int dest;
	
	// if the first process print and scan the inputs
	if(my_rank == 0)
	{
		printf("Enter a, b and n \n");
		scanf("%lf %lf %d", a, b, n);
		
		// now send this info to every other process
		for(dest = 1; dest < comm_sz; dest++)	
		{
			MPI_Send(a, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			MPI_Send(b, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
			MPI_Send(n, 1, MPI_DOUBLE, dest, 0, MPI_COMM_WORLD);
		}
	}
	// now every other process will receive that info
	else
	{
		MPI_Recv(a, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		MPI_Recv(b, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
		MPI_Recv(n, 1, MPI_DOUBLE, 0, 0, MPI_COMM_WORLD,
			MPI_STATUS_IGNORE);
	}
}
