#include "../vendor/cmatrix/matrix/matrix.h"
#include "../vendor/qunit/QUnit.hpp"

#include "../include/truss.h"
#include "truss_test.h"

void TrussTest::test_truss_three()
{
    Truss truss;
    truss.getData("data/truss3.dat");
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();

    QUNIT_IS_EQUAL(truss.members(), 13);

    CMatrix::Matrix<double> expectedUglobal(16, 1);
    expectedUglobal( 0, 0) =    0.0000;
    expectedUglobal( 1, 0) =    0.0000;
    expectedUglobal( 2, 0) =   11.0000;
    expectedUglobal( 3, 0) =  191.8333;
    expectedUglobal( 4, 0) =   22.0000;
    expectedUglobal( 5, 0) =  353.3333;
    expectedUglobal( 6, 0) =   11.0000;
    expectedUglobal( 7, 0) =  280.8333;
    expectedUglobal( 8, 0) =    0.0000;
    expectedUglobal( 9, 0) =    0.0000;
    expectedUglobal(10, 0) =  -53.1406;
    expectedUglobal(11, 0) =  182.8333;
    expectedUglobal(12, 0) =   16.8594;
    expectedUglobal(13, 0) =  353.3333;
    expectedUglobal(14, 0) =   86.8594;
    expectedUglobal(15, 0) =  253.8333;
    QUNIT_IS_TRUE(truss.uglobal.equalWithTolerance(expectedUglobal, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_0(4, 1);
    expectedLocalForce_0(0, 0) = -9.1667;
    expectedLocalForce_0(1, 0) =  0.0000;
    expectedLocalForce_0(2, 0) =  9.1667;
    expectedLocalForce_0(3, 0) =  0.0000;
    QUNIT_IS_TRUE(truss.locforce[0].equalWithTolerance(expectedLocalForce_0, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_1(4, 1);
    expectedLocalForce_1(0, 0) = -35.8333;
    expectedLocalForce_1(1, 0) = -26.8750;
    expectedLocalForce_1(2, 0) =  35.8333;
    expectedLocalForce_1(3, 0) =  26.8750;
    QUNIT_IS_TRUE(truss.locforce[1].equalWithTolerance(expectedLocalForce_1, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_2(4, 1);
    expectedLocalForce_2(0, 0) = -9.1667;
    expectedLocalForce_2(1, 0) =  0.0000;
    expectedLocalForce_2(2, 0) =  9.1667;
    expectedLocalForce_2(3, 0) =  0.0000;
    QUNIT_IS_TRUE(truss.locforce[2].equalWithTolerance(expectedLocalForce_2, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_3(4, 1);
    expectedLocalForce_3(0, 0) =   0.0000;
    expectedLocalForce_3(1, 0) =  10.0000;
    expectedLocalForce_3(2, 0) =   0.0000;
    expectedLocalForce_3(3, 0) = -10.0000;
    QUNIT_IS_TRUE(truss.locforce[3].equalWithTolerance(expectedLocalForce_3, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_4(4, 1);
    expectedLocalForce_4(0, 0) =  9.1667;
    expectedLocalForce_4(1, 0) =  0.0000;
    expectedLocalForce_4(2, 0) = -9.1667;
    expectedLocalForce_4(3, 0) =  0.0000;
    QUNIT_IS_TRUE(truss.locforce[4].equalWithTolerance(expectedLocalForce_4, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_5(4, 1);
    expectedLocalForce_5(0, 0) = -22.5000;
    expectedLocalForce_5(1, 0) =  16.8750;
    expectedLocalForce_5(2, 0) =  22.5000;
    expectedLocalForce_5(3, 0) = -16.8750;
    QUNIT_IS_TRUE(truss.locforce[5].equalWithTolerance(expectedLocalForce_5, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_6(4, 1);
    expectedLocalForce_6(0, 0) = 0.0000;
    expectedLocalForce_6(1, 0) = 0.0000;
    expectedLocalForce_6(2, 0) = 0.0000;
    expectedLocalForce_6(3, 0) = 0.0000;
    QUNIT_IS_TRUE(truss.locforce[6].equalWithTolerance(expectedLocalForce_6, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_7(4, 1);
    expectedLocalForce_7(0, 0) =  4.1667;
    expectedLocalForce_7(1, 0) =  3.1250;
    expectedLocalForce_7(2, 0) = -4.1667;
    expectedLocalForce_7(3, 0) = -3.1250;
    QUNIT_IS_TRUE(truss.locforce[7].equalWithTolerance(expectedLocalForce_7, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_8(4, 1);
    expectedLocalForce_8(0, 0) =  9.1667;
    expectedLocalForce_8(1, 0) =  0.0000;
    expectedLocalForce_8(2, 0) = -9.1667;
    expectedLocalForce_8(3, 0) =  0.0000;
    QUNIT_IS_TRUE(truss.locforce[8].equalWithTolerance(expectedLocalForce_8, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_9(4, 1);
    expectedLocalForce_9(0, 0) =   0.0000;
    expectedLocalForce_9(1, 0) =  30.0000;
    expectedLocalForce_9(2, 0) =   0.0000;
    expectedLocalForce_9(3, 0) = -30.0000;
    QUNIT_IS_TRUE(truss.locforce[9].equalWithTolerance(expectedLocalForce_9, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_10(4, 1);
    expectedLocalForce_10(0, 0) =  44.1667;
    expectedLocalForce_10(1, 0) = -33.1250;
    expectedLocalForce_10(2, 0) = -44.1667;
    expectedLocalForce_10(3, 0) =  33.1250;
    QUNIT_IS_TRUE(truss.locforce[10].equalWithTolerance(expectedLocalForce_10, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_11(4, 1);
    expectedLocalForce_11(0, 0) = -58.3333;
    expectedLocalForce_11(1, 0) =   0.0000;
    expectedLocalForce_11(2, 0) =  58.3333;
    expectedLocalForce_11(3, 0) =   0.0000;
    QUNIT_IS_TRUE(truss.locforce[11].equalWithTolerance(expectedLocalForce_11, 0.0005));

    CMatrix::Matrix<double> expectedLocalForce_12(4, 1);
    expectedLocalForce_12(0, 0) = -58.3333;
    expectedLocalForce_12(1, 0) =   0.0000;
    expectedLocalForce_12(2, 0) =  58.3333;
    expectedLocalForce_12(3, 0) =   0.0000;
    QUNIT_IS_TRUE(truss.locforce[12].equalWithTolerance(expectedLocalForce_12, 0.0005));
}
