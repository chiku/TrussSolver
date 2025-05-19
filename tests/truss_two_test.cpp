#include "cmatrix/src/matrix.h"
#include "truss.h"

#include "doctest/doctest.h"


TEST_CASE("Truss 2")
{
    Truss truss;
    truss.getData(read_truss_file("data/truss2.dat"));
    truss.findKLocal();
    truss.findKGlobal();
    truss.condense();
    truss.solve();

    REQUIRE(truss.members() == 5);

    cmatrix::Matrix<double> expectedUglobal(8, 1);
    expectedUglobal( 0, 0) = 0.0000;
    expectedUglobal( 1, 0) = 0.0000;
    expectedUglobal( 2, 0) = 0.0000;
    expectedUglobal( 3, 0) = 0.5558;
    expectedUglobal( 4, 0) = 0.0000;
    expectedUglobal( 5, 0) = 0.5372;
    expectedUglobal( 6, 0) = 0.0000;
    expectedUglobal( 7, 0) = 0.0000;
    CHECK_MESSAGE(truss.uglobal.equalWithTolerance(expectedUglobal, 0.0005), "actual\n",  truss.uglobal, "expected\n", expectedUglobal);

    cmatrix::Matrix<double> expectedLocalForce_0(4, 1);
    expectedLocalForce_0(0, 0) = -27.7915;
    expectedLocalForce_0(1, 0) = -48.1377;
    expectedLocalForce_0(2, 0) =  27.7915;
    expectedLocalForce_0(3, 0) =  48.1377;
    CHECK_MESSAGE(truss.locforce[0].equalWithTolerance(expectedLocalForce_0, 0.0005), "actual\n",  truss.locforce[0], "expected\n", expectedLocalForce_0);

    cmatrix::Matrix<double> expectedLocalForce_1(4, 1);
    expectedLocalForce_1(0, 0) = -46.5255;
    expectedLocalForce_1(1, 0) = -26.8623;
    expectedLocalForce_1(2, 0) =  46.5255;
    expectedLocalForce_1(3, 0) =  26.8623;
    CHECK_MESSAGE(truss.locforce[1].equalWithTolerance(expectedLocalForce_1, 0.0005), "actual\n",  truss.locforce[1], "expected\n", expectedLocalForce_1);

    cmatrix::Matrix<double> expectedLocalForce_2(4, 1);
    expectedLocalForce_2(0, 0) =  0.0000;
    expectedLocalForce_2(1, 0) =  3.7246;
    expectedLocalForce_2(2, 0) =  0.0000;
    expectedLocalForce_2(3, 0) = -3.7246;
    CHECK_MESSAGE(truss.locforce[2].equalWithTolerance(expectedLocalForce_2, 0.0005), "actual\n",  truss.locforce[2], "expected\n", expectedLocalForce_2);

    cmatrix::Matrix<double> expectedLocalForce_3(4, 1);
    expectedLocalForce_3(0, 0) = -27.7915;
    expectedLocalForce_3(1, 0) =  48.1377;
    expectedLocalForce_3(2, 0) =  27.7915 ;
    expectedLocalForce_3(3, 0) = -48.1377;
    CHECK_MESSAGE(truss.locforce[3].equalWithTolerance(expectedLocalForce_3, 0.0005), "actual\n",  truss.locforce[3], "expected\n", expectedLocalForce_3);

    cmatrix::Matrix<double> expectedLocalForce_4(4, 1);
    expectedLocalForce_4(0, 0) = -46.5255;
    expectedLocalForce_4(1, 0) =  26.8623;
    expectedLocalForce_4(2, 0) =  46.5255;
    expectedLocalForce_4(3, 0) = -26.8623;
    CHECK_MESSAGE(truss.locforce[4].equalWithTolerance(expectedLocalForce_4, 0.0005), "actual\n",  truss.locforce[4], "expected\n", expectedLocalForce_4);
}
