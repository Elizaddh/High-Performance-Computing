#include<iostream>
#include<cstdlib>
#include<ctime>
#include "mpi.h"

using namespace std;

int main(int argc, char *argv[]) {

int N=4, M = 4;
int A[M][N];
int B[M];
int Apart[M] ;
int Bpart=0; 
int X[N];
int Xpart[M] ;
int root = 0;
// SUBARRAY 
  MPI::Init (argc, argv); // Initialize MPI.
  int nproc = MPI::COMM_WORLD.Get_size(); // get number of processes
  int rank = MPI::COMM_WORLD.Get_rank();
   if (rank == root) {
      for (int i=0; i<N; i++) {
          B[i] = i+1; X[i] = 0; Apart[i] = 0; B[i] = 1; X[i] = 0; Apart[i] = 0;
          for (int j=0; j<M; j++) {
          A[i][j] = M*i + j+1; }
          } }
 
  MPI::Datatype my_datatype1, my_datatype2;
 
  my_datatype1 = MPI::INT.Create_vector(N, 1, M);

  my_datatype1.Commit ( ); // C++ syntax
 
  my_datatype2 = my_datatype1.Create_resized(0, 1*sizeof(int));

  my_datatype2.Commit ( ); // C++ syntax

  MPI::COMM_WORLD.Scatter(&A, 1, my_datatype2, &Apart, N, MPI::INT, root);
  MPI::COMM_WORLD.Barrier();
  MPI::COMM_WORLD.Scatter (&B, 1 , MPI::INT, &Bpart, 1, MPI::INT ,root);
  MPI::COMM_WORLD.Barrier();
// 
  for (int j=0; j<M; j++) {//independent vector scaler multiplication
     Xpart[j] = Apart[j]*Bpart;
 }
MPI::COMM_WORLD.Reduce(&Xpart, &X , N, MPI::INT, MPI::SUM, root);

 if(rank  == 0) {
     for (int i=0 ; i < N; i++){
         cout<< "A[" << i << "]" << X[i] << endl;
     }
 }
 
   MPI::Finalize();  // MPI finalize
   return 0;     // Exit
}
