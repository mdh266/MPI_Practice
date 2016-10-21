#include <stdlib.h>
#include <stdio.h>
#include <mpi.h>

int main(int argc,char **argv)
{
  MPI_Comm comm;
  MPI_Win win;  // Each process needs a window
  int ntids, mytid;

  MPI_Init(&argc,&argv);
  comm = MPI_COMM_WORLD;
  MPI_Comm_size(comm,&ntids);
  MPI_Comm_rank(comm,&mytid);

  int x;
  
  if(mytid == 0)
  	x = 1;
  
  printf("before, proc %i, x = %i\n", mytid, x);

  MPI_Win_create(&x, sizeof(int), 1, MPI_INFO_NULL, comm, &win);
  
  MPI_Win_fence(0,win);

  if(mytid == 0)
  	MPI_Put(&x, 1, MPI_INT,
  			1, 0, 1, MPI_INT, win);
  
  MPI_Win_fence(0,win);
  
  MPI_Win_free(&win);
  
  printf("after, proc %i, x = %i\n", mytid, x);

  MPI_Finalize();
  
  return 0;
}