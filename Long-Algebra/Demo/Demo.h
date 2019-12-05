#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include "../BigNumber/BigNumber.h"
//#include "../EllipticCurves/ElipticCurve.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::vector;

class Demo
{
private:
	string N;
public:
	Demo(string n) { N = n; };
	~Demo() {};
	void start();
protected:
	void test1();
	void test2() {};

    /**
     * This function tests the factorization algorithms. Naive and Pollard Rho algorithms.
     *
     * @author Vitaliy Datsiuk
     */
	void test3();
	void test4() {};
	void test5() {};
	void test6() {};
	void test7() {};
	void test8() {};
	void test9() {};
	void test10() {};
	void test12() {};
	void test13() {};
	void test14() {};
	void test15() {};
	void test16() {};

	int random_int(int length);
	BigNumber random_number(int length);
	BigNumber get_number();
};