
// MEEN 689 Computing Concepts Project 3
#include <cmath>
#include <iostream>
#include <string>
#include <vector>
#include "heat.hpp"
using namespace std;
//using namespace heat;

namespace heat {
    bool Crystal_Flag;
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
    vector<double> Tg;
    vector<double> alphas = {0.0, 0.0, 0.0, 0.0 , 0.0};
    //0:felt 1:carbon fiber 2:epoxy 3:aluminum 4:steel
    vector<double> glass_t = {1273.15, 523.15, 396.15, 610.0, 1033.15};
    //0:felt 1:carbon fiber 2:epoxy 3:aluminum 4:steel
}

vector<double> heat::set_alpha(double alpha1,double alpha2,double alpha3,double alpha4,double alpha5){
  {
    alphas[0] = alpha1;
    alphas[1] = alpha2;
    alphas[2] = alpha3;
    alphas[3] = alpha4;
    alphas[4] = alpha5;
    //vector<double> alpha = {0.0, (10.0/(1850 * 1100)), (0.44/(300*1730)), (210.0/(2700*890)), (21.5/(8000*510))};
  }
  return alphas;
}

double heat::Define_Tg(double x, int layup,double temp4){
	double output;
    if(layup == 0){
    	if(x<=4.0){ //2.0){
	     output = glass_t[4];
             //output = 0.15/(130*2e4);

	}
	else{
             output = glass_t[0];
	       //output = 21.5/(8000*510);
	}
    }
    else if(layup==1){
            if (x>=0 && x<=0.020){                //Felt
                output = glass_t[0];
            }else if(x>0.020 && x<=0.025){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>0.025 && x<=0.026){        //Epoxy
                output = glass_t[2];
            }else if(x>0.026 && x<=0.034){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>0.034 && x<=0.035){        //Epoxy
                output = glass_t[2];
            }else if(x>0.035 && x<=2.035){        //Aluminium
                output = glass_t[3];
            }else if(x>2.035 && x<=5.965){        //Steel
                output = glass_t[4];
            }else if(x>5.965 && x<=7.965){        //Aluminium
                output = glass_t[3];
            }else if(x>7.965 && x<=7.966){        //Epoxy
                output = glass_t[2];
            }else if(x>7.966 && x<=7.974){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>7.974 && x<=7.975){        //Epoxy
                output = glass_t[2];
            }else if(x>7.975 && x<=7.980){        //Caxbon Fibex
                output = glass_t[1];
            }else{                                //Felt
                output = glass_t[0];
              }
            }

    else if(layup==2){
            if (x>=0 && x<=0.030){                //Felt
                output = glass_t[0];
            }else if(x>0.030 && x<=0.033){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>0.033 && x<=0.034){        //Epoxy
                output = glass_t[2];
            }else if(x>0.034 && x<=0.046){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>0.046 && x<=0.047){        //Epoxy
                output = glass_t[2];
            }else if(x>0.047 && x<=2.047){        //Aluminium
                output = glass_t[3];
            }else if(x>2.347 && x<=5.653){        //Steel
                output = glass_t[4];
            }else if(x>5.653 && x<=7.953){        //Aluminium
                output = glass_t[3];
            }else if(x>7.953 && x<=7.954){        //Epoxy
                output = glass_t[2];
            }else if(x>7.954 && x<=7.966){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>7.966 && x<=7.967){        //Epoxy
                output = glass_t[2];
            }else if(x>7.967 && x<=7.970){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>7.970 && x<=8.000){       //Felt
                output = glass_t[0];
              }else{                                //Felt
                output = glass_t[0];
              }
            }

    else if(layup==3){
            if (x>=0 && x<=0.020){                //Felt
                output = glass_t[0];
            }else if(x>0.020 && x<=0.030){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>0.030 && x<=0.031){        //Epoxy
                output = glass_t[2];
            }else if(x>0.031 && x<=0.043){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>0.043 && x<=0.044){        //Epoxy
                output = glass_t[2];
            }else if(x>0.044 && x<=1.744){        //Aluminium
                output = glass_t[3];
            }else if(x>1.744 && x<=6.256){        //Steel
                output = glass_t[4];
            }else if(x>6.256 && x<=7.956){        //Aluminium
                output = glass_t[3];
            }else if(x>7.956 && x<=7.957){        //Epoxy
                output = glass_t[2];
            }else if(x>7.957 && x<=7.969){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>7.969 && x<=7.970){        //Epoxy
                output = glass_t[2];
            }else if(x>7.970 && x<=7.980){        //Caxbon Fibex
                output = glass_t[1];
            }else if (x>7.980 && x<=8.000){       //Felt
                output = glass_t[0];
              }else{                                //Felt
                output = glass_t[0];
              }
            }

    else if(layup==4){
            if (x>=0 && x<=0.0050){                 //Felt
                output = glass_t[0];
            }else if(x>0.0050 && x<=0.0051){        //Carbon Fiber
                output = glass_t[1];
            }else if(x>0.0051 && x<=0.0061){        //Epoxy
                output = glass_t[2];
            }else if(x>0.0061 && x<=0.0062){        //Carbon Fiber
                output = glass_t[1];
            }else if(x>0.0062 && x<=0.0072){        //Epoxy
                output = glass_t[2];
            }else if(x>0.0072 && x<=2.8072){        //Aluminium
                output = glass_t[3];
            }else if(x>2.8072 && x<=5.1928){        //Steel
                output = glass_t[4];
            }else if(x>5.1928 && x<=7.9928){        //Aluminium
                output = glass_t[3];
            }else if(x>7.9928 && x<=7.9938){        //Epoxy
                output = glass_t[2];
            }else if(x>7.9938 && x<=7.9939){        //Caxbon Fibex
                output = glass_t[1];
            }else if(x>7.9939 && x<=7.9949){        //Epoxy
                output = glass_t[2];
            }else if(x>7.9949 && x<=7.9950){        //Caxbon Fibex
                output = glass_t[1];
            }else if (x>7.9950 && x<=8.000){       //Felt
                output = glass_t[0];
              }else{                                //Felt
                output = glass_t[0];
              }
            }
	else{
		cout<<"Layup not found"<<endl;
		output = 0.0;
	}
      return output;
}

double heat::Define_Q(double x, int layup, int BC){
    double result;
    if(layup == 0){
	if(x == 0.0){
    	result = 10e4/(21.5);
	}
	else{
		result = 2e4/(0.15);
	}
    }
    else if(layup==1){
         if (BC == 1){
            if (x == 0.0){
               result = (2e4)/(0.15);
               }
            else {result = 0.0;}
         }
         else {result = (2e4)/(0.15);}


    }else if(layup==2){
        if (BC == 1){
            if (x == 0.0){
               result = (4e4)/(0.15);
               }
            else {result = 0.0;}
        }
        else {result = (4e4)/(0.15);}


    }else if(layup==3){
        if (BC == 1){
        if (x == 0.0){
               result = (3.2e4)/(0.15);
               }
            else {result = 0.0;}
        }
        else {result = (3.2e4)/(0.15);}


    }else{
        if (BC == 1){
        if (x == 0.0){
               result = (5e4)/(0.15);
               }
            else {result = 0.0;}
        }
        else {result = (5e4)/(0.15);}
      }
    return result;
}

double heat::Define_Alpha(double x, int layup){
    //int layup = layup_det(theta);
    double output;
    if(layup == 0){
    	if(x<=4.0){ //2.0){
	     output = 21.5/(8000*510);
             //output = 0.15/(130*2e4);

	}
//	else if(x>=0.02 && x<=7.98){
		//output = 210/(2700*890);
                //output = 21.5/(8000*510);
 //               output = 0.15/(130*2e4);



//	}
	else{
             output = 0.15/(130*2e4);
	       //output = 21.5/(8000*510);
	}
    }
    else if(layup==1){
            if (x>=0 && x<=0.020){                //Felt
                output = alphas[0];
            }else if(x>0.020 && x<=0.025){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>0.025 && x<=0.026){        //Epoxy
                output = alphas[2];
            }else if(x>0.026 && x<=0.034){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>0.034 && x<=0.035){        //Epoxy
                output = alphas[2];
            }else if(x>0.035 && x<=2.035){        //Aluminium
                output = alphas[3];
            }else if(x>2.035 && x<=5.965){        //Steel
                output = alphas[4];
            }else if(x>5.965 && x<=7.965){        //Aluminium
                output = alphas[3];
            }else if(x>7.965 && x<=7.966){        //Epoxy
                output = alphas[2];
            }else if(x>7.966 && x<=7.974){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>7.974 && x<=7.975){        //Epoxy
                output = alphas[2];
            }else if(x>7.975 && x<=7.980){        //Caxbon Fibex
                output = alphas[1];
            }else{                                //Felt
                output = alphas[0];
              }
            }

    else if(layup==2){
            if (x>=0 && x<=0.030){                //Felt
                output = alphas[0];
            }else if(x>0.030 && x<=0.033){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>0.033 && x<=0.034){        //Epoxy
                output = alphas[2];
            }else if(x>0.034 && x<=0.046){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>0.046 && x<=0.047){        //Epoxy
                output = alphas[2];
            }else if(x>0.047 && x<=2.047){        //Aluminium
                output = alphas[3];
            }else if(x>2.347 && x<=5.653){        //Steel
                output = alphas[4];
            }else if(x>5.653 && x<=7.953){        //Aluminium
                output = alphas[3];
            }else if(x>7.953 && x<=7.954){        //Epoxy
                output = alphas[2];
            }else if(x>7.954 && x<=7.966){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>7.966 && x<=7.967){        //Epoxy
                output = alphas[2];
            }else if(x>7.967 && x<=7.970){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>7.970 && x<=8.000){       //Felt
                output = alphas[0];
              }else{                                //Felt
                output = alphas[0];
              }
            }

    else if(layup==3){
            if (x>=0 && x<=0.020){                //Felt
                output = alphas[0];
            }else if(x>0.020 && x<=0.030){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>0.030 && x<=0.031){        //Epoxy
                output = alphas[2];
            }else if(x>0.031 && x<=0.043){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>0.043 && x<=0.044){        //Epoxy
                output = alphas[2];
            }else if(x>0.044 && x<=1.744){        //Aluminium
                output = alphas[3];
            }else if(x>1.744 && x<=6.256){        //Steel
                output = alphas[4];
            }else if(x>6.256 && x<=7.956){        //Aluminium
                output = alphas[3];
            }else if(x>7.956 && x<=7.957){        //Epoxy
                output = alphas[2];
            }else if(x>7.957 && x<=7.969){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>7.969 && x<=7.970){        //Epoxy
                output = alphas[2];
            }else if(x>7.970 && x<=7.980){        //Caxbon Fibex
                output = alphas[1];
            }else if (x>7.980 && x<=8.000){       //Felt
                output = alphas[0];
              }else{                                //Felt
                output = alphas[0];
              }
            }

    else if(layup==4){
            if (x>=0 && x<=0.0050){                 //Felt
                output = alphas[0];
            }else if(x>0.0050 && x<=0.0051){        //Carbon Fiber
                output = alphas[1];
            }else if(x>0.0051 && x<=0.0061){        //Epoxy
                output = alphas[2];
            }else if(x>0.0061 && x<=0.0062){        //Carbon Fiber
                output = alphas[1];
            }else if(x>0.0062 && x<=0.0072){        //Epoxy
                output = alphas[2];
            }else if(x>0.0072 && x<=2.8072){        //Aluminium
                output = alphas[3];
            }else if(x>2.8072 && x<=5.1928){        //Steel
                output = alphas[4];
            }else if(x>5.1928 && x<=7.9928){        //Aluminium
                output = alphas[3];
            }else if(x>7.9928 && x<=7.9938){        //Epoxy
                output = alphas[2];
            }else if(x>7.9938 && x<=7.9939){        //Caxbon Fibex
                output = alphas[1];
            }else if(x>7.9939 && x<=7.9949){        //Epoxy
                output = alphas[2];
            }else if(x>7.9949 && x<=7.9950){        //Caxbon Fibex
                output = alphas[1];
            }else if (x>7.9950 && x<=8.000){       //Felt
                output = alphas[0];
              }else{                                //Felt
                output = alphas[0];
              }
            }
	else{
		cout<<"Layup not found"<<endl;
		output = 0.0;
	}
    return output;
    }
//----------------------------------------
double heat::Define_Lambda(double x, int layup){
  double result;
  result = Define_Alpha(x,layup);
  result  = result*dt/pow(dr,2);
  return result;
}

void heat::Define_Vars(int temp,double temp2,double temp3,double temp4,int layup,string flag1,string flag2,string flag3,string flag4,string flag5){

    Crystal_Flag = false;
    dt = temp2;
    ft = temp3;
    Nt = ceil(ft/dt); // Nt = dt/ft + 1
    Num_of_nodes = temp;
    avgcput = 0.0;
    N = temp;
    dr = (8.0 + (2*temp4))/(N-1);
    t = 0.0;

// Initializing r
    r.resize(N);
    r[0] = 0-temp4;

    for(int i=1;i<N;i++){
	r[i] = r[i-1] + dr;
    }

    heat::Print_Rfile();

// Initializing T
    T.resize(N);
    for(int i=0;i<N;i++){
	T[i].resize(5);
	for(int j=0;j<5;j++){
	T[i][j] = 200.0;
	}
}

// Initializing Told
    Told.resize(N);
    for(int i=0;i<N;i++){
	Told[i].resize(5);
	for(int j=0;j<5;j++){
	Told[i][j] = 200.0;
	}
}
// Initializing A
    A.resize(N);
    for(int i=0;i<N;i++){
      A[i].resize(3);
	    for(int j=0;j<3;j++){
	    A[i][j] = 0.0;
    }
  }

// Initializing B
B.resize(N);

// Initializing Tg
Tg.resize(N);
for(int i=0;i<N;i++){
	Tg[i] = heat::Define_Tg(r[i],layup,temp4);
}

//Setting up material properties
//Felt
string k_s, rho_s, cp_s; // these will be assigned values by the user from the command line
double k, rho, cp; //used for calculating alpha for each material object
double alpha; // used for assigning diffusuivity to each material object
if (flag1=="y"){
  cout<<"Thermal conductivity for Felt: ";
  getline(cin,k_s);
  k = stod(k_s);
  cout<<"Density for Felt: ";
  getline(cin,rho_s);
  rho = stod(rho_s);
  cout<<"Specific heat for Felt?: ";
  getline(cin,cp_s);
  cp = stod(cp_s);
}
else{
  k = 0.107;
  rho = 145;
  cp = 2e4;
}
alpha = k/(rho*cp);

Material Felt(k, rho, cp, alpha);
double alpha1 = Felt.diffusivity;

//Carbon Fiber
if (flag2=="y"){
  cout<<"Thermal conductivity for Carbon Fiber: ";
  getline(cin,k_s);
  k = stod(k_s);
  cout<<"Density for Carbon Fiber: ";
  getline(cin,rho_s);
  rho = stod(rho_s);
  cout<<"Specific heat for Carbon Fiber?: ";
  getline(cin,cp_s);
  cp = stod(cp_s);
}
else{
  k = 10.0;
  rho = 1850;
  cp = 1100;
}
alpha = k/(rho*cp);

Material CarbonFiber(k, rho, cp, alpha);
double alpha2 = CarbonFiber.diffusivity;

//Epoxy
if (flag3=="y"){
  cout<<"Thermal conductivity for Epoxy: ";
  getline(cin,k_s);
  k = stod(k_s);
  cout<<"Density for Epoxy: ";
  getline(cin,rho_s);
  rho = stod(rho_s);
  cout<<"Specific heat for Epoxy: ";
  getline(cin,cp_s);
  cp = stod(cp_s);
}
else{
  k = 0.44;
  rho = 300;
  cp = 1730;
}
alpha = k/(rho*cp);

Material Epoxy(k, rho, cp, alpha);
double alpha3 = Epoxy.diffusivity;

//Aluminum
if (flag4=="y"){
  cout<<"Thermal conductivity for Aluminum: ";
  getline(cin,k_s);
  k = stod(k_s);
  cout<<"Density for Aluminum: ";
  getline(cin,rho_s);
  rho = stod(rho_s);
  cout<<"Specific heat for Aluminum: ";
  getline(cin,cp_s);
  cp = stod(cp_s);
}
else{
  k = 210.0;
  rho = 2700;
  cp = 890;
}
alpha = k/(rho*cp);

Material Aluminum(k, rho, cp, alpha);
double alpha4 = Aluminum.diffusivity;

//Steel
if (flag5=="y"){
  cout<<"Thermal conductivity for Steel: ";
  getline(cin,k_s);
  k = stod(k_s);
  cout<<"Density for Steel: ";
  getline(cin,rho_s);
  rho = stod(rho_s);
  cout<<"Specific heat for Steel: ";
  getline(cin,cp_s);
  cp = stod(cp_s);
}
else{
  k = 21.5;
  rho = 8000;
  cp = 510;
}
alpha = k/(rho*cp);

Material Steel(k, rho, cp, alpha);
double alpha5 = Steel.diffusivity;


vector<double> alphas = heat::set_alpha(alpha1,alpha2,alpha3,alpha4,alpha5);

}
