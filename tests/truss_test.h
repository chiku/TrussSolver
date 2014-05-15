#include <iostream>

#include "QUnit.hpp"

#ifndef __TRUSS_SOLVER_TEST__
#define __TRUSS_SOLVER_TEST__

class TrussTest
{
public:
    TrussTest(std::ostream &out, int verboseLevel = QUnit::verbose) : qunit(out, verboseLevel) { }

    int run()
    {
        test_truss_one();
        test_truss_two();
        test_truss_three();

        return qunit.errors();
    }

private:
    QUnit::UnitTest qunit;

    void test_truss_one();
    void test_truss_two();
    void test_truss_three();

};

#endif
