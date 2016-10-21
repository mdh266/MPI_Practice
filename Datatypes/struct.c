#include<stdio.h>
#include<mpi.h>

typedef struct
{
		int n;
		double x, y;
} coordinate;

void print(coordinate coor)
{
	printf("%i = (%f, %f)\n", coor.n, coor.x, coor.y);
}

int main()
{
	
	int size, rank, root = 0;
	MPI_Comm comm = MPI_COMM_WORLD;

	MPI_Init(NULL,NULL);
	MPI_Comm_size(comm,&size);
	MPI_Comm_rank(comm,&rank);

	double x, y;
	int n;
	

	MPI_Aint arrayOfDispl[3];
	MPI_Type_extent(MPI_INT,&extent_Int);
	arrayOfDispl[0] = 0;
	arrayOfDispl[1] = 8; // sizeof(MPI_INT) = 8
	arrayOfDispl[2] = 16;// sizeof(MPI_DOUBLE) = 8

	int arrayOfLens[3] = {1, 1, 1};
	MPI_Datatype arrayOfTypes[3] = {MPI_INT, MPI_DOUBLE, MPI_DOUBLE};
		
	MPI_Datatype MPI_coordinate;
		
	MPI_Type_create_struct(3, arrayOfLens, arrayOfDispl,
						   arrayOfTypes, &MPI_coordinate);
						
								   
	MPI_Type_commit(&MPI_coordinate);
	
	coordinate coor;
	
	if(rank == root)
	{
		coor.n = 1;
		coor.x = -1.2;
		coor.y = 1.3;
		
		print(coor);
	}
	
	MPI_Bcast(&coor, 1, MPI_coordinate, root, comm);

	if(rank != root)		
		print(coor);
	
	// Free memory for this struct
	MPI_Type_free(&MPI_coordinate);
	
	MPI_Finalize();
	
	return 0;
}
