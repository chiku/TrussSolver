// Fem analysis of a 2D truss

#include <string>

#include "cmatrix/src/matrix.h"

#ifndef __TRUSS_H__
#define __TRUSS_H__

const int MAX = 30;

struct Node
{
    double x;
    double y; // (x, y) are the coordinates
};

std::string read_file(const char *file_name);

// implementing 2D Truss class
class Truss
{
public:
    double *area;
    double *length;
    cmatrix::Matrix<double> *locforce;
    cmatrix::Matrix<double> uglobal;

    Truss();
    ~Truss();
    void getData(const std::string file_data); // accepts all input data
    void findKLocal();
    void findKGlobal();
    void condense();
    void solve();

    int members() { return total_members; };
    int nodes() { return total_nodes; };
    void modifyArea(double new_area[]);
    void printMatrices();

private:
    int total_nodes, total_members;
    Node *node;
    cmatrix::Matrix<double> force, displacement;
    cmatrix::Matrix<double> kglobal, kglobalcond, *klocal;
    cmatrix::Matrix<double> k11, k12, k21, k22;
    cmatrix::Matrix<double> Fknown, Funknown, uknown, uunknown;
    double E;

    char (*connectivity)[MAX];
    char *knowledgeF, *knowledgeu;
};

#endif
