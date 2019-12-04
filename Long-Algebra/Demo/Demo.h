#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <stdio.h>
#include <stdlib.h>
#include "../BigNumber/BigNumber.h"
#include "../EllipticCurves/ElipticCurve.h"

class Demo
{
public:
	string N;
	Demo(string n) { N = n; };
	~Demo() {};
	void start();
protected:
	void test1();
	void test2() {};
	void test3() {};
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