# include <cstdlib>
# include <iostream>
#include<math.h>
#include<stdio.h>
#include<cstdlib>
# include <iomanip>

# include <omp.h>
//#include<iostream>


using namespace std;

double derifun(double x){
return (sqrt(1-x*x));
}

double calpi(int n_rect, int threadnum);
double PI ;
int main(int argc, char *argv[]){
   double time1;
    int n_rect;
    n_rect  = 500000000;
    //double sum;
    //sum = 0;
    //omp_set_num_threads(2);
     double integration;
     double  h = 2.0 / n_rect; 
     cout << "  " << setw(8) << "n_rect"
         << "   " << setw(12) << "num_threads"
                << "  " << setw(12) << "Pi"
                << "  " << setw(12) << "time" << endl ;

float p[]= {1,2,4,6,8,10};
for(int threadi = 0; threadi < 6; threadi++ ){
time1 = omp_get_wtime ( ) ;                
PI = calpi(n_rect, p[threadi]);
time1 = omp_get_wtime ( ) - time1 ; 

cout << "  " << setw(8) << n_rect
    << "    " << setw(12) << p[threadi]
     << "  " << setw(12) << PI
     << "  " << setw(12) << time1 << endl ;
}

       return 0;
}

double calpi(int  n_rect, int thr){
    double sum;
    double h = 2.0/n_rect;
    sum  = 0;
    int i;
    double x;
    float p[] = {1,2,4,6,8,10};
    double k;
 //   for (int t= 0 ; t <11; t++){
#pragma omp parallel for  private(i,x)  num_threads(thr)
    for ( i=0; i< n_rect; i++){
         x = -1+(i+.5)*h;
         k =derifun(x)*h;
//#pragma omp atomic
        sum = sum+k;
    }
  double pi = sum * 2.0 ;
  return pi;
}
