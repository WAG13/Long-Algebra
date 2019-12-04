#include <iostream>
#include "BigNumber.h"
#include "Probabilistic_primality_tests .h"

int main()
{
    const int iterations = 10;
	BigNumber n1("101");
    BigNumber n2("101");
    bool first = solovayStrassenAlgorithm(n1, iterations);
    bool second = solovayStrassenAlgorithm(n2, iterations);
    cout<< std::boolalpha;
    cout << first << " " << second;
	n1.printBigNumber();
	n2.printBigNumber();
}