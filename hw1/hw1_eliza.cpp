/* Suppose the run-time of a serial program is given by Tserial = n2,
 *  where the units of the run-time are in microseconds. Suppose that
 *  a parallelization of this program has run-time Tparallel = n2/p+log2(p).
 *  Write a program that finds the speedups and effieciences of this
 *  program for various values of n and p. Run your program with n=
 *  10,20,40,...,320, and p = 1,2,4,...,128. What haappens to the
 *  speedups and efficiences as p is increased and n is held fixed?
 *  What happens when p is fixed and n is increased?
 */

#include<iostream>
#include<iomanip>
#include<cmath>
#include<iostream>

using namespace std;

float Ts(float n)
{
	return n*n;
}
float Tp (float n, float p)
{
    return((Ts(n)/p)+log2(p));
}

int main(){
    float p[]={1,2,4,8,16,32,64,128};
    float n[]={10,20,40,80,160,320};

    float resultSp[8][6];
    float resultE [8][6];

cout << setprecision(3) << fixed << setw(16) << left << "Sp,E";
for (int i = 0; i < 6; i++)
{
    cout << setw(16) << n[i];
}
for(int i = 0 ; i < 8; i++){
    cout << setw(16) << left << p[i];

for (int j = 0; j < 6;j++)
{
    resultSp[i][j] = Ts(n[j])/Tp(n[j],p[i]);
    resultE[i][j] = resultSp[i][j]/p[i];

    cout << setw(7) << resultSp[i][j] << setw(1) <<"," << setw(8) << resultE[i][j];
}
    cout << endl;
}
}
