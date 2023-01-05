// Team Nebula
// MEEN 689 Computing Concepts Project 3
#include <iostream>
#include<cmath>
#include<ctime>
#include<vector>
#include "heat.hpp"

using namespace std;

/*Using the implicit Backward in Time Central in Space (BTCS) scheme, we convert the 1D heat equation
into a system of equations of the form Ax = B, where A is an NxN tridiagonal matrix, B is an
N-dimensional column vector and x is another N-dimensional vector containing the temperatures at
each grid location at the current time step.
*/

/* Since A is a tridiagonal matrix containing mostly zeros, we use the Thomas Algorithm to solve
Ax = b. As such, the Form_A function is used to create an Nx3 matrix with just the non-zero values
on the main diagonal and off-diagonals.
*/
void heat::Form_A(int layup,int v){
// Boundary condition at one edge (r = 0.0)
A[0][0] = 0.0;
A[0][1] = 1 + 2*Define_Lambda(r[0],layup);
A[0][2] = -1*2*Define_Lambda(r[0],layup);
// Interior points
for(int i=1;i<N-1;i++){
A[i][0] = -1*Define_Lambda(r[i],layup);
A[i][1] = 1 + (2*Define_Lambda(r[i],layup));
A[i][2] = -1*Define_Lambda(r[i],layup);
}
// Boundary condition at the other edge (r = 8.0)
A[N-1][0] =  -1*2*Define_Lambda(r[N-1],layup); //*((dt/pow(dr,2))*Define_Alpha(r[N-1],layup));
A[N-1][1] =  1 + (2*Define_Lambda(r[N-1],layup));  //*(dt/pow(dr,2))*Define_Alpha(r[N-1],layup));
A[N-1][2] = 0.0;

// Visualize the A matrix.
if(v==2){
cout<<"A matrix --layup:"<<layup<<endl;
for(int i = 0;i<N;i++){
cout<<A[i][0]<<"\t"<<A[i][1]<<"\t"<<A[i][2]<<endl;
}
}
}


/*The Form_B function is used to create the B vector for Ax = B, where aside from the first and last element,
all the other elements correspond to the temperature values at the previous time step.
*/
void heat::Form_B(int layup,int v, int it,int BC){
//Boundary condition at one edge (r = 0.0)
B[0] = Told[0][layup] + 2*dr*(Define_Q(r[0],layup,BC))*Define_Lambda(r[0],layup);
for(int i =1;i<N-1;i++){
B[i] = Told[i][layup];
}
//Boundary condition at one edge (r = 8.0)
B[N-1] = Told[N-1][layup] +  2*dr*(Define_Q(r[N-1],layup,BC))*Define_Lambda(r[N-1],layup);

//Visualize the B vector
if(v==3 && it>0){
cout<<"B vector --layup:"<<layup<<endl;
for(int i = 0;i<N;i++){
cout<<B[i]-200.0<<endl;
}
}
}


// 11/22 Thomas Algorithm code 
void heat::Solve_T(int layup,int v,int it){
  clock_t cputstart = clock();
  vector<vector<double>> At;
  At.resize(N); // Atemp
  //copy A matrix into At
  for(int i = 0;i<N;i++){
  	At[i].resize(3);
  	for(int j = 0; j<3;j++){
  		At[i][j] = A[i][j];
  	}
  }
//begin with the second row
  int i = 1;
  double ratio;
  while (i < N){
    //set the elimination ratio
    ratio = (At[i][0] / At[i-1][1]);
    //update diagonal values
    At[i][1] = At[i][1] - ratio * At[i - 1][2];
    //update lower diagonal values
    At[i][0] = At[i][0] - ratio * At[i-1][1];
    //update the column of temperatures in accordance w/Gauss elimination
    B[i] = B[i] - ratio * B[i - 1];
    //iterate through i
    i ++;
  }
  //print a matrix if verbose v is chosen
  if(v==4 && it == 2){
	cout<<"At & A matrices -- Atfter Elimination:"<<layup<<endl;
        for(int i = 0;i<N;i++){
        cout<<At[i][0]<<"\t"<<At[i][1]<<"\t"<<At[i][2]<<"|"<<A[i][0]<<A[i][1]<<A[i][2]<<endl;
        }
  }
  // backwards substitution for the first row
  T[N-1][layup] = B[N-1] / At[N-1][1];
  //iterate through back substitution in accordance w/Thomas algorithm
  for(int i = N-2;i>=0;i--){
    T[i][layup] = (B[i]- (At[i][2] * T[i +1][layup])) / At[i][1];
  }
  //return the temperatures

//Compute the average computation time for each iteration
clock_t cputend = clock();
double cput = 1000.0*(cputend-cputstart)/CLOCKS_PER_SEC; // calculating the time for calculation in milliseconds from clock speed.
avgcput+=cput;
}
void heat::Push_T(int layup,int v,int it){
for(int i=0;i<N;i++){
	Told[i][layup] = T[i][layup];
	}
if(v==5 && it>0){
cout<<"i,Told,T"<<endl;
for(int i = 0; i<N;i++){
cout<<i<<","<<Told[i][layup]<<","<<T[i][layup]<<endl;
}
}
}

// Advance the solution to the next time step
void heat::Advance_dt(int layup,int v, int it,int BC){

	// Form the right hand side vector for the linear equation which depends on Told.
	Form_B(layup,v,it,BC);
	//if(v==2){cout<<"B"<<endl;}
	// Solve the linear system with A formed outside the implicit function before the temporal loop.
	Solve_T(layup,v,it);
	// Check if Glass temperatures are reached.
	Check_T(layup,v);
	if(Crystal_Flag == false){
	Push_T(layup,v,it);}	// Push T values back to Told for next timestep
}


/*The function Check_T is used for checking the temperature values at each grid location against the
corresponding material glassing temperature. In case the temperature exceeds the glass temperature,
the material is assumed to have failed. The solver then stops and prints out the failure location and
the temperature at that location to the console.
*/
void heat::Check_T(int layup,int v){
//	cout<<Crystal_Flag<<endl;
	if(Crystal_Flag==false){
		for(int i = 0;i<N;i++){
			if (T[i][layup] >Tg[i] || T[i][layup] == Tg[i]){
				cout<<"Location of Failure:"<<r[i]<<","<<T[i][layup]<<endl;
				Crystal_Flag = true;
		        }
		}
	}
}
