// 11/22 Thomas Algorithm code Amira Bushagour, Yash Narendra, Akib Sarwar
#include <iostream>
#include <vector>

using namespace std;
// define thomas algorithm function as TDMA
// function takes in a vector of vectors A (tridiagonal matrix)
//and a vector n (the temperatures for the previous row)
vector<double> TDMA(vector<vector<double>>A, vector<double>n){
  //set N to the size of the matrix
  int N = n.size();
  //begin iterating at the second row (i = 1)
  int i = 1;
  while (i < N){
    //update the diagonal value for a gauss elimination
    A[i][1] = A[i][1] - (A[i][0] / A[i-1][1]) * A[i - 1][2];
    //update the collumn of temperatures in accordance w/Gauss elimination
    n[i] = n[i] - (A[i][0] / A[i-1][1]) * n[i - 1];
    //iterate through i
    i ++;
  }
  //initialize a vector x (the temperatures at the current point)
  vector<double> x (N, 0);
  // backwards substitution for the first row
  i = N-1;
  x[i] = n[i] / A[i][1];
  i--;
  //a bit more complicated backwards substitution
  while (i >= 0){
    x[i] = (n[i]- A[i][2] * x[i +1]) / A[i][1];
    i--;
  }
  //return the temperatures
  return x;
  }

int main()
{
    //test case matrix A and vector n
    vector<vector<double>> A = {{0,2,3}, {1,2,3}, {1,2,3}, {1,2,3}, {1,2, 0}};
    vector<double> n = {1,2,3,4,5};
    vector <double> B = TDMA(A, n);
    int i = 0;
    while (i < 5){
      cout << B[i] << endl;
      i++;
    }
    }



}
