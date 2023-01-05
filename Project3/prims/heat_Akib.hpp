// 11/22 Vishal Indivar Kandala
// MEEN 689 Computing Concepts Project 3
#ifndef INIT_H
#define INIT_H
#include<vector>
#include<string>
// Naming convention for functions:
// 	Action_Changedvariable()
using namespace std;

namespace heat {
    // functions
    void Print_File(int it,int interactive);
    double Define_Tg(double x, int layup,double temp4);
    double Define_Q(double x, int layup,int BC);
    double Define_Alpha(double x, int layup);
    vector<double> set_alpha(double alpha1,double alpha2,double alpha3,double alpha4,double alpha5);
    void Define_Vars(int temp,double temp2,double temp3,double temp4, int layup, string flag1,string flag2,string flag3,string flag4,string flag5);
    void Print_Rfile();
    void Form_A(int layup,int v);
    void Form_B(int layup,int v, int it,int BC);
    void Solve_T(int layup,int v,int it);
    void Advance_dt(int layup,int v,int it,int BC);
    void Push_T(int layup,int v,int it);
    void Check_T(int layup,int v);
    double Define_Lambda(double x, int layup);
    // vars
    extern bool Crystal_Flag;
    extern double dr;
    extern int Num_of_nodes;
    extern int N;
    extern int Nt;
    extern double ft;
    extern double dt;
    extern double t;
    extern double avgcput;
    extern vector<vector<double>> T;
    extern vector<vector<double>> Told;
    extern vector<vector<double>> A;
    extern vector<double> B;
    extern vector<double> r;
    extern vector<double> Tg;
    extern vector<double> alphas;
    extern vector<double> glass_t;

}

//Used for crerating a Material class that is used for defining different objects corresponding to each layer
class Material {
public:
  double conductivity;
  double density;
  double specific_heat;
  double diffusivity;

  Material(const double k = 0.0, const double rho = 0.0, const double cp = 0.0, const double alpha = 0.0):conductivity(k), density(rho), specific_heat(cp), diffusivity(alpha){};
};

#endif
