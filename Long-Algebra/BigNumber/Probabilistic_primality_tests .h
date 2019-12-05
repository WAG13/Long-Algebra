#ifndef LONGALGEBRA_PROBABILISTIC_PRIMALITY_TESTS_H
#define LONGALGEBRA_PROBABILISTIC_PRIMALITY_TESTS_H
#include "BigNumber.h"

/*
*  №10
*  @brief Probabilistic primality Phermat's and Solovay–Strassen's tests.
 *  Returns "true" if the number is prime.
*  @author Totskyi Alexander
*/

/* *
*  @brief Decimal expansion of the pow.
*  Requires for modular exponentation.
*/
vector<BigNumber> binaryPows(BigNumber x) //decimal expansion
{
    vector<BigNumber> v;
    BigNumber zero = BigNumber("0");
    BigNumber two = BigNumber("2");
    while (x > zero)
    {
        v.push_back(x % two);
        x = x / two;
    }
    return v;
}

/* *
*  @brief Modular exponentiation.
*/
BigNumber modularExp(BigNumber a, BigNumber k, BigNumber n, vector<BigNumber> pows)
{
    BigNumber zero = BigNumber("0");
    BigNumber one = BigNumber("1");
    BigNumber two = BigNumber("2");
    BigNumber b = one;
    if (k==zero) return b;
    BigNumber A = a;
    if (pows[0]==one)
        b = a;
    for(int i = 1; i < pows.size(); i++)
    {
        A = (A*A) % n;
        if(pows[i]==one)
            b = (A * b) % n;
    }
    return b;
}
/* *
*  @brief Calculation of Jacobian number.
*/
BigNumber jacobianNumber(BigNumber a, BigNumber n)
{
    BigNumber zero = BigNumber("0");
    BigNumber one = BigNumber("1");
    BigNumber two = BigNumber("2");
    BigNumber three = BigNumber("3");
    BigNumber four = BigNumber("4");
    BigNumber five = BigNumber("5");
    BigNumber eight = BigNumber("8");
    if (a == zero)
        return zero;// (0/n) = 0
    BigNumber ans = one;
    if (a == one)
        return ans; // (1/n) = 1
    while (a>zero)
    {
        if (zero > a)
        {
            a = -a;// (a/n) = (-a/n)*(-1/n) - property of Lacobian symbol
            if (n % four == three)
                ans = -ans;// (-1/n) = -1 if n = 3 (mod 4)
        }
        while (a % two == zero)
        {
            a = a / two;
            if ((n % eight == three) || (n % eight == five))
                ans = -ans;
        }
        std::swap(a, n);
        if (((a % four) == three) && ((n % four) == three))
            ans = -ans;
        a = a % n;
        if (a > (n / two))
            a = a - n;
    }
    if (n == one)
        return ans;
    return zero;
}

bool solovayStrassenAlgorithm(BigNumber p, int iterations)
{
    BigNumber zero = BigNumber("0");
    BigNumber one = BigNumber("1");
    BigNumber two = BigNumber("2");
    if (two > p)
        return false;
    if ((p != two) && ((p % two) == zero))
        return false;
    for (int i = 0; i < iterations; i++)
    {
        int a = rand() % (27) +2;
        string new_str = to_string(a);
        BigNumber A(new_str);
        BigNumber r = modularExp(A, (p - one) / two, p, binaryPows((p - one) / two));
        if((r!=one) && (r!=p-one))
            return false;
        if (r==p-one)
            r=one;
        BigNumber jacobian = jacobianNumber(A, p);
        if (r % p != jacobian && jacobian !=zero && r%p!=-jacobian)
            return false;
    }
    return true;
}
/* *
* @brief Calculation of Fermat's liitle theorem.
* a^(p-1) = 1 (mod p)
*/
bool fermatAlgorithm(BigNumber p, int iterations)
{
    BigNumber one = BigNumber("1");
    for(int i=0; i < iterations; i++)
    {
        int a = rand() % (30-1) + 1;
        string new_str = to_string(a);
        BigNumber A(new_str);
        BigNumber r = modularExp(A, p - one, p, binaryPows(p - one));
        if(r !=one) return false;
    }
    return true;
}

#endif //LONGALGEBRA_PROBABILISTIC_PRIMALITY_TESTS_H
