#include<stdio.h>
#include<stdlib.h>

int print(double * x, int *n);
int makeMesh(double * x, int * n, double * a, double * b);
int fEuler(double * x, double * yVals, int * n, double * h);
double f(double val);

int main()
{
	int N = 5,
		i, j;
	
	double a, b, h;
		a = 0.0;
		b = 1.0;
		h = (b-a)/(N-1);
		
		printf("h = %f \n",h);
		
	double * mesh = calloc(sizeof(double),N);
	double * yVals = calloc(sizeof(double),N);
	
	makeMesh(mesh, &N, &a, &b);
	print(mesh, &N);
	fEuler(mesh, yVals, &N, &h); 
	print(yVals, &N);

	
	free(mesh);
	free(yVals);	
	return 0;
}

int fEuler(double * x, double * yVals, int * n, double * h)
{
	int i;
	
	for(i = 0; i < *n; i++)
	{
		yVals[i] = f(x[i]) * (*h);
	}
	
	return 0;
}

double f(double val)
{
	return val;
}

int makeMesh(double * x, int * n, double * a, double * b)
{
	int i;
	double h = (*b - *a)/(*n -1);
	
	for(i = 0; i < *n; i++)
		x[i] = *a + i*h;
		
	return 0;
}


int print(double * x, int * n)
{
	int i;
	for(i = 0; i < *n; i++)
		printf("%f ", x[i]);
	printf("\n");

	return 0;
}

