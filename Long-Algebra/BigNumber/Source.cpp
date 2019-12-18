#include "BigNumber.h"
#include <iostream>
#include <string>

BigNumber test_case_1(){
	BigNumber cur("122", "2001");
	std::cout << "122 ^ 54573 mod 2001\n";
	std::cout << "Expected value: " << 296<<'\n';
	return (cur ^ (BigNumber("54573", "0")));
}

BigNumber test_case_2(){
	BigNumber cur("13", "23");
	std::cout << "13 ^ 426 mod 23\n";
	std::cout << "Expected value: " << 2 << '\n';
	return (cur ^ (BigNumber("426", "0")));
}

BigNumber test_case_3(){
	BigNumber cur("543", "563");
	std::cout << "543 ^ 493 mod 563\n";
	std::cout << "Expected value: " << 330 << '\n';
	return (cur ^ (BigNumber("493", "0")));
}

BigNumber test_case_4(){
	BigNumber cur("9", "7");
	std::cout << "9 ^ 12 mod 7\n";
	std::cout << "Expected value: " << 1 << '\n';
	return (cur ^ (BigNumber("12", "0")));
}

BigNumber test_case_5(){
	BigNumber cur("394", "598");
	std::cout << "394 ^ 293 mod 598\n";
	std::cout << "Expected value: " << 140 << '\n';
	return (cur ^ (BigNumber("293", "0")));
}

int main() {
	BigNumber temp("0");
	temp = test_case_1();
	std::cout << "Current value: " << temp << "\n\n";
	temp = test_case_2();
	std::cout << "Current value: " << temp << "\n\n";
	temp = test_case_3();
	std::cout << "Current value: " << temp << "\n\n";
	temp = test_case_4();
	std::cout << "Current value: " << temp << "\n\n";
	temp = test_case_5();
	std::cout << "Current value: " << temp << "\n\n";
}