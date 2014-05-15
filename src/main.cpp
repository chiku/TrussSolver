#include "../include/truss.h"

int main()
{
    Truss truss;
    truss.getData("data/truss1.dat");
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();
    truss.printMatrices();
}
