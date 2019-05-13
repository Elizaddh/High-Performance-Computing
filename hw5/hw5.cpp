/*Consider the problem of computing row-wise matrix-vector multiplication. To make it simple, you just consider the matrix (A) size is 4x4 and vector (B) size is 4x1. Then, A x B = X where X size is 4x1. Complete below pseudocode. The values of matrix A and vector B are initialized such as A0,0 ~ A3,3 = 1 ~ 16, B0 ~ B3 = 1 in the root process. Be careful that only root process loads the B and C values. The other processes do not have th e values.
 *
 *MATRIX VECTOR MULTIPLICATION ROW-WISE
*/
#include<iostream>
#include<cstdlib>
#include<ctime>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

int N=4, M = 4;
int A[N][M];
int Apart[M] ;
int B[M] ; 
int X[N];
int Xpart = 0;
int root = 0;

MPI::Init (argc, argv); // Initialize MPI.
int nproc = MPI::COMM_WORLD.Get_size(); // get number of processes
int rank = MPI::COMM_WORLD.Get_rank();

if (rank ==root){
// Just simply set N(4) X M(4) matrix and M(4)X1 vector
 for (int i=0; i<N; i++) {
     B[i] = 1; X[i] = 0; Apart[i] = 0; for (int j=0; j<M; j++) {
     A[i][j] = M*i + j+1; }
 }
}

// // MPI Scatter the A Matrix
MPI::COMM_WORLD.Scatter(&A, 4, MPI::INT, &Apart , 4, MPI::INT, 0);
MPI::COMM_WORLD.Barrier();
// // Broadcast the B vector;
MPI::COMM_WORLD.Bcast (&B, 4 , MPI::INT, 0);
MPI::COMM_WORLD.Barrier();
// // Calculate Xpart
for (int i = 0; i < N ; i ++) { 
    Xpart = Xpart + Apart[i] * B[i] ;
}
 
// // MPI Gather
MPI::COMM_WORLD.Gather(&Xpart ,1, MPI::INT, &X, 1 ,MPI::INT, 0 );
MPI::COMM_WORLD.Barrier();

// // Print results
 if (rank == root){// // get rank of process
 for(int i=0; i<N; i++) {
 cout << "X[" << i << "]=" << X[i] << endl;
 }
}
   MPI::Finalize();  // MPI finalize
   return 0;     // Exit
}
