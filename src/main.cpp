#include "truss.h"

int main()
{
    Truss truss;
    truss.getData(read_file("data/truss1.dat"));
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();
    truss.printMatrices();
}
