#include<math.h>
#include<stdio.h>
#include<stdlib.h>
#include<omp.h>


int main()
{
	int N = 10000000;
	int i;
	int a = 1.0;
	int b = 2;
	
	int * x = calloc(sizeof(int), N);

	for(i = 0; i < N; i++)
		x[i] = 0;
	

	for(i = 0; i < N; i++)
		x[i] = a*x[i]+b;
	


	return 0;
}
