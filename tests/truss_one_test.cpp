#include "cmatrix/src/matrix.h"
#include "truss.h"

#include "doctest/doctest.h"


TEST_CASE("Truss 1")
{
    Truss truss;
    truss.getData(read_truss_file("data/truss1.dat"));
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();

    REQUIRE(truss.members() == 10);

    cmatrix::Matrix<double> expectedUglobal(12, 1);
    expectedUglobal( 0, 0) =  0.9420;
    expectedUglobal( 1, 0) =  4.2168;
    expectedUglobal( 2, 0) = -1.0580;
    expectedUglobal( 3, 0) =  4.3773;
    expectedUglobal( 4, 0) =  0.7815;
    expectedUglobal( 5, 0) =  1.8604;
    expectedUglobal( 6, 0) = -0.8185;
    expectedUglobal( 7, 0) =  2.0024;
    expectedUglobal( 8, 0) =  0.0000;
    expectedUglobal( 9, 0) =  0.0000;
    expectedUglobal(10, 0) =  0.0000;
    expectedUglobal(11, 0) =  0.0000;
    CHECK_MESSAGE(truss.uglobal.equalWithTolerance(expectedUglobal, 0.0005), "actual\n",  truss.uglobal, "expected\n", expectedUglobal);

    cmatrix::Matrix<double> expectedLocalForce_0(4, 1);
    expectedLocalForce_0(0, 0) =   0.0000;
    expectedLocalForce_0(1, 0) = -40.1246;
    expectedLocalForce_0(2, 0) =   0.0000;
    expectedLocalForce_0(3, 0) =  40.1246;
    CHECK_MESSAGE(truss.locforce[0].equalWithTolerance(expectedLocalForce_0, 0.0005), "actual\n",  truss.locforce[0], "expected\n", expectedLocalForce_0);

    cmatrix::Matrix<double> expectedLocalForce_1(4, 1);
    expectedLocalForce_1(0, 0) =  40.1246;
    expectedLocalForce_1(1, 0) =   0.0000;
    expectedLocalForce_1(2, 0) = -40.1246;
    expectedLocalForce_1(3, 0) =   0.0000;
    CHECK_MESSAGE(truss.locforce[1].equalWithTolerance(expectedLocalForce_1, 0.0005), "actual\n",  truss.locforce[1], "expected\n", expectedLocalForce_1);

    cmatrix::Matrix<double> expectedLocalForce_2(4, 1);
    expectedLocalForce_2(0, 0) = -40.1246;
    expectedLocalForce_2(1, 0) =  40.1246;
    expectedLocalForce_2(2, 0) =  40.1246;
    expectedLocalForce_2(3, 0) = -40.1246;
    CHECK_MESSAGE(truss.locforce[2].equalWithTolerance(expectedLocalForce_2, 0.0005), "actual\n",  truss.locforce[2], "expected\n", expectedLocalForce_2);

    cmatrix::Matrix<double> expectedLocalForce_3(4, 1);
    expectedLocalForce_3(0, 0) =  59.8754;
    expectedLocalForce_3(1, 0) =  59.8754;
    expectedLocalForce_3(2, 0) = -59.8754;
    expectedLocalForce_3(3, 0) = -59.8754;
    CHECK_MESSAGE(truss.locforce[3].equalWithTolerance(expectedLocalForce_3, 0.0005), "actual\n",  truss.locforce[3], "expected\n", expectedLocalForce_3);

    cmatrix::Matrix<double> expectedLocalForce_4(4, 1);
    expectedLocalForce_4(0, 0) = -59.8754;
    expectedLocalForce_4(1, 0) =   0.0000;
    expectedLocalForce_4(2, 0) =  59.8754;
    expectedLocalForce_4(3, 0) =   0.0000;
    CHECK_MESSAGE(truss.locforce[4].equalWithTolerance(expectedLocalForce_4, 0.0005), "actual\n",  truss.locforce[4], "expected\n", expectedLocalForce_4);

    cmatrix::Matrix<double> expectedLocalForce_5(4, 1);
    expectedLocalForce_5(0, 0) =   0.0000;
    expectedLocalForce_5(1, 0) = -35.4896;
    expectedLocalForce_5(2, 0) =   0.0000;
    expectedLocalForce_5(3, 0) =  35.4896;
    CHECK_MESSAGE(truss.locforce[5].equalWithTolerance(expectedLocalForce_5, 0.0005), "actual\n",  truss.locforce[5], "expected\n", expectedLocalForce_5);

    cmatrix::Matrix<double> expectedLocalForce_6(4, 1);
    expectedLocalForce_6(0, 0) =  195.3650;
    expectedLocalForce_6(1, 0) =    0.0000;
    expectedLocalForce_6(2, 0) = -195.3650;
    expectedLocalForce_6(3, 0) =    0.0000;
    CHECK_MESSAGE(truss.locforce[6].equalWithTolerance(expectedLocalForce_6, 0.0005), "actual\n",  truss.locforce[6], "expected\n", expectedLocalForce_6);

    cmatrix::Matrix<double> expectedLocalForce_7(4, 1);
    expectedLocalForce_7(0, 0) = -95.3650;
    expectedLocalForce_7(1, 0) =  95.3650;
    expectedLocalForce_7(2, 0) =  95.3650;
    expectedLocalForce_7(3, 0) = -95.3650;
    CHECK_MESSAGE(truss.locforce[7].equalWithTolerance(expectedLocalForce_7, 0.0005), "actual\n",  truss.locforce[7], "expected\n", expectedLocalForce_7);

    cmatrix::Matrix<double> expectedLocalForce_8(4, 1);
    expectedLocalForce_8(0, 0) =  104.6350;
    expectedLocalForce_8(1, 0) =  104.6350;
    expectedLocalForce_8(2, 0) = -104.6350;
    expectedLocalForce_8(3, 0) = -104.6350;
    CHECK_MESSAGE(truss.locforce[8].equalWithTolerance(expectedLocalForce_8, 0.0005), "actual\n",  truss.locforce[8], "expected\n", expectedLocalForce_8);

    cmatrix::Matrix<double> expectedLocalForce_9(4, 1);
    expectedLocalForce_9(0, 0) = -204.6350;
    expectedLocalForce_9(1, 0) =    0.0000;
    expectedLocalForce_9(2, 0) =  204.6350;
    expectedLocalForce_9(3, 0) =    0.0000;
    CHECK_MESSAGE(truss.locforce[9].equalWithTolerance(expectedLocalForce_9, 0.0005), "actual\n",  truss.locforce[9], "expected\n", expectedLocalForce_9);
}
