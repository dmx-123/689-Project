// Team Nebula
// MEEN 689 Computing Concepts Project 3
#include<iostream>
#include<cmath>
#include "heat.hpp"
using namespace std;
int main(int argc, char **argv){


	// Interface with the user for solver configuration using the terminal command line
	
	// create the structure that stores the solver parameters from the user
	heat::userParams solverParams;

	// call the function that gets user inputs on the command line and will return the solver parameters to run
	solverParams = heat::askUserParams();

	// define the variables that will be received for the solver
	int v = solverParams.v;	//verbose variable for solver output
	int N = solverParams.N;	//number of grid points. Larger the points, finer the mesh of solver
	double dt = solverParams.dt;	//time step size for the solver (sec)
	double ft = solverParams.ft;	//final time that the solver will run to (sec)
	int outfreq = solverParams.outfreq;	//frequency of output for solver iterations
	string filename = solverParams.filename;	//file name of the config file for material properties
	int layup = solverParams.layup;	//material layup number 
	int BC = solverParams.BC;	//boundary condition for the solver to apply
	double felt_Add = solverParams.felt_Add;	//amount of felt to add if running boundary condition 2 (symmetric heat flux)
	
    //function defined in setup.cpp
    heat::Define_Vars(N,dt,ft,felt_Add,layup, filename);

    //-------------------
    if(v==1){
    // Print out basic info when v = 1
    cout << "Config file name: " << filename << endl;
    cout<<"Lambda: "<<heat::Define_Lambda(heat::r[50],layup)<<endl;
    cout << "Number of Nodes: "<<heat::Num_of_nodes << endl;
    cout << "Grid size: "<<heat::dr << endl;
    cout<<"Time step: "<<heat::dt<<endl;
    cout<<"Final time: "<<heat::ft<<endl;
    cout<<"No.of Time steps: "<<heat::Nt<<endl;
    cout << "Heat Flux/Conductivity at boundary: "<<heat::Define_Q(heat::r[0],layup,BC) << endl;
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
    if(it%outfreq == 0){
    // Print solution at t to file.
    heat::Print_File(it,0);
    // Print the simulation monitor time.
    cout<<"t = "<<heat::t<<endl;
    	}
    }

    it2 = it;
    //Stop the solver if any material reaches it's glass temperature
    if(heat::Crystal_Flag == true){break;}
    }
    //Report out the location and temperature of failure
    if(heat::Crystal_Flag == true){
	   if(v==1){ 
	    cout<<"Crystallization Temperature reached at time:"<<heat::t<<endl;
	   }
	   heat::Print_File(it2,0);
    }
    else{
    if(v==1){
    cout<<"Average CPU Time for T_Solve in ms: "<<heat::avgcput/heat::Nt<<endl; //Output the average computation time 
    }
    }
  

return 0;
}
