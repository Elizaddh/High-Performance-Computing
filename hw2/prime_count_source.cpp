//tried without pragma line for serial and then used openmp pragas for all other processes with num_threads(2)

# include <cstdlib>
# include <iostream>
# include <iomanip>

# include <omp.h>

using namespace std;

int prime_static ( int n );
int prime_dynamic ( int n );

//****************************************************************************80
int main ( int argc, char *argv[] )
//****************************************************************************80
{
  int n;
  int total_primes_static;
  int total_primes_dynamic;
  double time1;
  double time2;

  cout << "\n";
  cout << "SCHEDULE_OPENMP\n";
  cout << "  C++/OpenMP version\n";
  cout << "  Count the primes from 1 to N.\n";
  cout << "  This is an unbalanced work load, particular for two threads.\n";
  cout << "  Demonstrate static and dynamic scheduling.\n";
  cout << "\n";
  cout << "  Number of processors available = " << omp_get_num_procs ( ) << "\n";
  cout << "  Number of threads =              " << omp_get_max_threads ( ) << "\n";
  cout << "For dynamic and static chunk   correct" << "\n" ;

  n =300000;

  time1 = omp_get_wtime ( );
  total_primes_static = prime_static ( n );
  time1 = omp_get_wtime ( ) - time1;

  time2 = omp_get_wtime ( );
  total_primes_dynamic = prime_dynamic ( n );
  time2 = omp_get_wtime ( ) - time2;

  cout << "  " << setw(8) << "n"
       << "  " << setw(12) << "static primes"
       << "  " << setw(12) << "dynamic primes"
       << "  " << setw(12) << "static time"
       << "  " << setw(12) << "dynamic time" << "\n";

  cout << "  " << setw(8) << n
       << "  " << setw(12) << total_primes_static
       << "  " << setw(12) << total_primes_dynamic
       << "  " << setw(12) << time1
       << "  " << setw(12) << time2 << "\n";
  

  return 0;
  
}


//****************************************************************************80
int prime_static ( int n )
//****************************************************************************80
{
  int i;
  int j;
  int prime;
  int total = 0;
# pragma omp parallel for num_threads(2) reduction ( + : total )  schedule ( static , 5  ) private ( i, j, prime )
//# pragma omp parallel for
//# pragma omp parallel private ( i, j, prime )
//# pragma omp for reduction ( + : total ) schedule ( static,  )
                      
  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    total += prime;
  }

  return total;
}


//****************************************************************************80
int prime_dynamic ( int n )
//****************************************************************************80
{
  int i;
  int j;
  int prime;
  int total = 0;

# pragma omp parallel for num_threads(2) reduction ( + : total ) schedule ( dynamic,  500  ) private ( i, j, prime )
//# pragma omp parallel for reduction ( + : total ) schedule ( dynamic,  ) private ( i, j, prime )

  for ( i = 2; i <= n; i++ )
  {
    prime = 1;

    for ( j = 2; j < i; j++ )
    {
      if ( i % j == 0 )
      {
        prime = 0;
        break;
      }
    }
    //#pragma omp atomic
    total += prime;
  }

  return total;
}
