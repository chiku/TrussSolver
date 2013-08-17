#include "truss.cpp"

#include "QUnit.hpp"
#include "truss_test.h"

void TrussTest::test_truss_one()
{
    Truss truss;
    truss.getData();
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();

    QUNIT_IS_EQUAL(10, truss.members());
}
