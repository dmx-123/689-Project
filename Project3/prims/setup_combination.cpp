// 11/22 Mingxin, 11/25 Vishal Indivar Kandala 11/30 Yash Narendra
// MEEN 689 Computing Concepts Project 3
#include <cmath>
#include <iostream>
#include <vector>
#include "heat.hpp"
using namespace std;
//using namespace heat;

namespace heat {
    double dt;
    double dr;
    int Num_of_nodes;
    int N;
    int Nt;
    double ft;
    double t;
    double avgcput;
    std::vector<std::vector<double>> T;
    std::vector<std::vector<double>> Told;
    std::vector<std::vector<double>> A;
    std::vector<double> B;
    vector<double> r;
}

double heat::Define_Q(int layup){
    double result;
    if(layup==1){
        result = (2e4)/(0.15);
    }else if(layup==2){
        result = (4e4/(0.15);
    }else if(layup==3){
        result = (3.2e4/(0.15));
    }else if(layup==4){
        result = (5e4/(0.15));
      }
    return result;
}

/*
int heat::layup_det(double theta){
    if(theta>=0 && theta<90){
        return 1;
    }else if(theta>=180 && theta<270){
        return 1;
    }else{
        return 2;
    }
}
*/
double heat::Define_Alpha(double r, int layup){
    //int layup = layup_det(theta);
    double result;
    if(layup==1){
            if (r>=0 && r<=0.020){                //Felt
                result = 0.15/(130*2e4);
            }else if(r>0.020 && r<=0.025){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.025 && r<=0.026){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.026 && r<=0.034){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.034 && r<=0.035){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.035 && r<=2.035){        //Aluminium
                result = 210/(2700*890);
            }else if(r>2.035 && r<=5.965){        //Steel
                result = 21.5/(8000*510);
            }else if(r>5.965 && r<=7.965){        //Aluminium
                result = 210/(2700*890);
            }else if(r>7.965 && r<=7.966){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.966 && r<=7.974){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>7.974 && r<=7.975){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.975 && r<=7.980){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if (r>7.980 && r<=8.000){       //Felt
                result = 0.15/(130*2e4);
              }
            }

    else if(layup==2){
            if (r>=0 && r<=0.030){                //Felt
                result = 0.15/(130*2e4);
            }else if(r>0.030 && r<=0.033){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.033 && r<=0.034){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.034 && r<=0.046){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.046 && r<=0.047){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.047 && r<=2.047){        //Aluminium
                result = 210/(2700*890);
            }else if(r>2.347 && r<=5.653){        //Steel
                result = 21.5/(8000*510);
            }else if(r>5.653 && r<=7.953){        //Aluminium
                result = 210/(2700*890);
            }else if(r>7.953 && r<=7.954){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.954 && r<=7.966){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>7.966 && r<=7.967){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.967 && r<=7.970){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if (r>7.970 && r<=8.000){       //Felt
                result = 0.15/(130*2e4);
              }
            }

    else if(layup==3){
            if (r>=0 && r<=0.020){                //Felt
                result = 0.15/(130*2e4);
            }else if(r>0.020 && r<=0.030){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.030 && r<=0.031){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.031 && r<=0.043){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.043 && r<=0.044){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.044 && r<=1.744){        //Aluminium
                result = 210/(2700*890);
            }else if(r>1.744 && r<=6.256){        //Steel
                result = 21.5/(8000*510);
            }else if(r>6.256 && r<=7.956){        //Aluminium
                result = 210/(2700*890);
            }else if(r>7.956 && r<=7.957){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.957 && r<=7.969){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>7.969 && r<=7.970){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.970 && r<=7.980){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if (r>7.980 && r<=8.000){       //Felt
                result = 0.15/(130*2e4);
              }
            }

    else if(layup==4){
            if (r>=0 && r<=0.0050){                 //Felt
                result = 0.15/(130*2e4);
            }else if(r>0.0050 && r<=0.0051){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.0051 && r<=0.0061){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.0061 && r<=0.0062){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>0.0062 && r<=0.0072){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>0.0072 && r<=2.8072){        //Aluminium
                result = 210/(2700*890);
            }else if(r>2.8072 && r<=5.1928){        //Steel
                result = 21.5/(8000*510);
            }else if(r>5.1928 && r<=7.9928){        //Aluminium
                result = 210/(2700*890);
            }else if(r>7.9928 && r<=7.9938){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.9938 && r<=7.9939){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if(r>7.9939 && r<=7.9949){        //Epoxy
                result = 0.44/(300*1730);
            }else if(r>7.9949 && r<=7.9950){        //Carbon Fiber
                result = 10/(1850*1100);
            }else if (r>7.9950 && r<=8.000){       //Felt
                result = 0.15/(130*2e4);
              }
            }
    return result;
    }


void heat::Define_Vars(int temp,double temp2,double temp3){
 // cout << "Please type in the number of nodes N" << endl;
 //   cin >> N;
    dt = temp2;
    ft = temp3;
    Nt = ceil(ft/dt); // Nt = dt/ft + 1
    Num_of_nodes = temp;
    avgcput = 0.0;
    N = temp;
    dr = 2.0/(N-1);
    t = 0.0;
// Initializing r
    r.resize(N);
    r[0] = 0;

    for(int i=1;i<N;i++){
	r[i] = r[i-1] + dr;
    }

// Initializing T
    T.resize(N);
    for(int i=0;i<N;i++){
	T[i].resize(8);
	for(int j=0;j<8;j++){
	T[i][j] = 200;
	}
}

// Initializing Told
    Told.resize(N);
    for(int i=0;i<N;i++){
	Told[i].resize(8);
	for(int j=0;j<8;j++){
	Told[i][j] = 200;
	}
}
// Initializing A
    A.resize(N);
    for(int i=0;i<N;i++){
	A[i].resize(3);
	for(int j=0;j<3;j++){
	A[i][j] = 0;
	}
}

// Initializing B
B.resize(N);

}


// if add more features
//

//  namespace heat{
    //add new things, the previously defined variables and methods won't disappear
//(Num_of_nodes,0);

//}


//Test
/*
int main(int argc, char **argv){
    using namespace heat;
    //double re = dr();
    //cout << re << endl;
    define_vars();
    cout << heat_flux(30.0) << endl;
    cout << Num_of_nodes << endl;
    cout << dr << endl;
    return 0;
}
*/
