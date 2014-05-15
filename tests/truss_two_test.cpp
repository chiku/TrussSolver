#include "../vendor/cmatrix/src/matrix.h"
#include "QUnit.hpp"

#include "../include/truss.h"
#include "truss_test.h"

void TrussTest::test_truss_two()
{
    Truss truss;
    truss.getData("data/truss2.dat");
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();

    QUNIT_IS_EQUAL(truss.members(), 5);

    cmatrix::Matrix<double> expectedUglobal(8, 1);
    expectedUglobal( 0, 0) = 0.0000;
    expectedUglobal( 1, 0) = 0.0000;
    expectedUglobal( 2, 0) = 0.0000;
    expectedUglobal( 3, 0) = 0.5558;
    expectedUglobal( 4, 0) = 0.0000;
    expectedUglobal( 5, 0) = 0.5372;
    expectedUglobal( 6, 0) = 0.0000;
    expectedUglobal( 7, 0) = 0.0000;
    QUNIT_IS_TRUE(truss.uglobal.equalWithTolerance(expectedUglobal, 0.0005));

    cmatrix::Matrix<double> expectedLocalForce_0(4, 1);
    expectedLocalForce_0(0, 0) = -27.7915;
    expectedLocalForce_0(1, 0) = -48.1377;
    expectedLocalForce_0(2, 0) =  27.7915;
    expectedLocalForce_0(3, 0) =  48.1377;
    QUNIT_IS_TRUE(truss.locforce[0].equalWithTolerance(expectedLocalForce_0, 0.0005));

    cmatrix::Matrix<double> expectedLocalForce_1(4, 1);
    expectedLocalForce_1(0, 0) = -46.5255;
    expectedLocalForce_1(1, 0) = -26.8623;
    expectedLocalForce_1(2, 0) =  46.5255;
    expectedLocalForce_1(3, 0) =  26.8623;
    QUNIT_IS_TRUE(truss.locforce[1].equalWithTolerance(expectedLocalForce_1, 0.0005));

    cmatrix::Matrix<double> expectedLocalForce_2(4, 1);
    expectedLocalForce_2(0, 0) =  0.0000;
    expectedLocalForce_2(1, 0) =  3.7246;
    expectedLocalForce_2(2, 0) =  0.0000;
    expectedLocalForce_2(3, 0) = -3.7246;
    QUNIT_IS_TRUE(truss.locforce[2].equalWithTolerance(expectedLocalForce_2, 0.0005));

    cmatrix::Matrix<double> expectedLocalForce_3(4, 1);
    expectedLocalForce_3(0, 0) = -27.7915;
    expectedLocalForce_3(1, 0) =  48.1377;
    expectedLocalForce_3(2, 0) =  27.7915 ;
    expectedLocalForce_3(3, 0) = -48.1377;
    QUNIT_IS_TRUE(truss.locforce[3].equalWithTolerance(expectedLocalForce_3, 0.0005));

    cmatrix::Matrix<double> expectedLocalForce_4(4, 1);
    expectedLocalForce_4(0, 0) = -46.5255;
    expectedLocalForce_4(1, 0) =  26.8623;
    expectedLocalForce_4(2, 0) =  46.5255;
    expectedLocalForce_4(3, 0) = -26.8623;
    QUNIT_IS_TRUE(truss.locforce[4].equalWithTolerance(expectedLocalForce_4, 0.0005));
}
