#include "../include/truss.h"

int main()
{
  Truss T;
  T.getData();
  T.findKLocal();
  T.findKGlobal();
  T.condense();
  T.solve();
  T.printMatrices();
}
