// 11/22 Vishal Indivar Kandala
// MEEN 689 Computing Concepts Project 3
#include<iostream>
#include<cmath>
#include "heat.hpp"
using namespace std;
int main(int argc, char **argv){
    int v = stoi(argv[1]);
    // v for verbose: when v = 1, basic info.
    // v = 2, A matrix.
    // v = 3 , B vector at every time step.

    // Reading command line inputs.
    int N = stoi(argv[2]); // Command line input for Number of nodes in radial direction.
    double dt = stod(argv[3]); // Command line input for time step size.
    double ft = stod(argv[4]); // Command line input for simulation interval.
    int outfreq = stoi(argv[5]);
    int layup = stoi(argv[6]);
    int BC = stoi(argv[7]);
    double Extra_Felt = stod(argv[8]);
    //Asking the user if he/she wants to change material properties for each layer
    string flag1, flag2, flag3, flag4, flag5; //these flags are used in the Define_Vars function later
    cout<<"Do you want to manually define material properties for Felt?(y/n): ";
    getline(cin,flag1);
    cout<<"Do you want to manually define material properties for Carbon Fiber?(y/n): ";
    getline(cin,flag2);
    cout<<"Do you want to manually define material properties for Epoxy?(y/n): ";
    getline(cin,flag3);
    cout<<"Do you want to manually define material properties for Aluminum?(y/n): ";
    getline(cin,flag4);
    cout<<"Do you want to manually define material properties for Steel?(y/n): ";
    getline(cin,flag5);

    // Define global variables using inputs.
    heat::Define_Vars(N,dt,ft,Extra_Felt,layup,flag1,flag2,flag3,flag4,flag5);
    //-------------------
    if(v==1){
    // Print out basic info when v = 1
    cout<<"Lambda: "<<heat::Define_Lambda(heat::r[50],layup)<<endl;
    cout << "Number of Nodes: "<<heat::Num_of_nodes << endl;
    cout << "Grid size: "<<heat::dr << endl;
    cout<<"Time step: "<<heat::dt<<endl;
    cout<<"Final time: "<<heat::ft<<endl;
    cout<<"No.of Time steps: "<<heat::Nt<<endl;
    cout << "Heat Flux/Conductivity at boundary: "<<heat::Define_Q(heat::r[0],layup,BC) << endl;
    /*cout<<"alpha_1: "<<heat::alphas[0]<<endl;
    cout<<"alpha_2: "<<heat::alphas[1]<<endl;
    cout<<"alpha_3: "<<heat::alphas[2]<<endl;
    cout<<"alpha_4: "<<heat::alphas[3]<<endl;
    cout<<"alpha_5: "<<heat::alphas[4]<<endl;*/
    }
    //-------------------
    // Time loop
    heat::Print_File(0,0);
    heat::Form_A(layup,v);
    int it2 = 0;
    for(int it = 1;it<=heat::Nt;it++){
    if(heat::Crystal_Flag == false){
    // Advance the solution by one Timestep(dt)
    heat::Advance_dt(layup,v,it,BC);
    // Update solution monitor time t.
    heat::t+=heat::dt;
    // If statement for outputting to file
    //cout<<it2<<endl;
    if(it%outfreq == 0){
    // Print solution at t to file.
    heat::Print_File(it,0);
    // Print the simulation monitor time.
    cout<<"t = "<<heat::t<<endl;
    	}
    }
    it2 = it;
    if(heat::Crystal_Flag == true){break;}
    }
    if(heat::Crystal_Flag == true){
	   if(v==1){
	    cout<<"Crystallization Temperature reached at time:"<<heat::t<<endl;
	   }
	   heat::Print_File(it2,0);
    }
    else{
    if(v==1){
    cout<<"Average CPU Time for T_Solve in ms: "<<heat::avgcput/heat::Nt<<endl;
    }
    }


return 0;
}
