// Fem analysis of a 2D truss

#include <iostream>
#include <fstream>
#include <cmath>

#include "cmatrix/matrix/matrix.h"

#ifndef __TRUSS_H__
#define __TRUSS_H__

using namespace std;

const int MAX = 30;

struct Node
{
  double x;
  double y; // (x, y) are the coordinates
};


// implementing 2D Truss class
class Truss
{
  private:
    int total_nodes, total_members;
    Node *N;
    CMatrix::Matrix<double> force, displacement;
    CMatrix::Matrix<double> kglobal, kglobalcond, *klocal;
    CMatrix::Matrix<double> k11, k12, k21, k22;
    CMatrix::Matrix<double> Fknown, Funknown, uknown, uunknown;
    double E;

    char (*connectivity)[MAX];
    char *knowledgeF, *knowledgeu;

   public:
    double *area;
    double *length;
    CMatrix::Matrix<double> *locforce;
    CMatrix::Matrix<double> uglobal;

    void getData(const char *file_name = "data/truss.dat"); // accepts all input data
    Truss();
    ~Truss();
    void findKLocal();
    void findKGlobal();
    void condense();
    void solve();

    int members() { return total_members; };
    int nodes() { return total_nodes; };
    void modifyArea(double new_area[]);
    void printMatrices();
};

#endif
