#include <iostream>
#include <cstdlib>
#include < mpi.h>
#define MaxN 1000000            // number of maximum vector 
#define NS 3                    // number of simulation. 100, 10000, 1000000 

using namespace std;

int main(int argc, char *argv[]) 
{
  // Initialize MPI
MPI::Status status;
MPI::Init(argc, argv);
  // Determine process rank
int num_proc = MPI::COMM_WORLD.Get_size();
  // Determine the number of available processes
int my_rank = MPI::COMM_WORLD.Get_rank();
  // N=100: i=0, N=10000: i=1, N=1000000: i=2
float x[1000000], y[1000000];
int vector_size;
int offset;  
float time1 ;

int sum, subdp;
  // root
  if (my_rank == 0) {
    time1 = MPI::Wtime();

    // initialize data (x and y)
	for (int i = 0 ; i < 1000000; i++){
	x[i] = 1;
	y[i] = 1;
	}

    // calculate vector size
	vector_size = 1000000/num_proc;
    remaining = 1000000%num_proc;
    offset = vector_size + remaining;

    for (int dest=1; dest<num_proc; dest++) {
      MPI::COMM_WORLD.Send(&vector_size, 1, MPI::INT, dest, 1);
      MPI::COMM_WORLD.Send(&x[offset], vector_size, MPI::FLOAT, dest, 2);
      MPI::COMM_WORLD.Send(&y[offset], vector_size, MPI::FLOAT, dest, 3);
      offset = offset + vector_size;
    }
 for (int i = 0; i < vector_size+ remaining; i++){
        sum += x[i] * y[i];
}
offset = vector_size+remaining;
    // calculate my part
   
    // receive sub dot results and sum
    for (int source=1; source <num_proc; source++) {
      MPI::COMM_WORLD.Recv(&subdp, 1, MPI::FLOAT, MPI::ANY_SOURCE, 4, status);
      sum=sum+subdp;
    }
time1 = MPI::Wtime() - time1; 
cout << sum << endl ;
cout <<   time << endl ; 
}
    // for total cpu execution time
  
  // worker
  else {
    // receive data
    MPI::COMM_WORLD.Recv(&vector_size, 1, MPI::INT, 0, 1, status);
    MPI::COMM_WORLD.Recv(&x, vector_size, MPI::FLOAT, 0, 2, status);
    MPI::COMM_WORLD.Recv(&y, vector_size, MPI::FLOAT, 0, 3, status);
    
    sum = 0;
    for(int k = 0; k < vector_size; k++){
        sum = sum + x[k] * y[k];
    }
    // calculate sub dot product
    subdp = 0.0;
   
    // Send the sub dot product to root
    MPI::COMM_WORLD.Send(&sum, 1, MPI::FLOAT, 0, 4);
  }

  // Terminate MPI
  MPI::Finalize();

  return EXIT_SUCCESS;
}
