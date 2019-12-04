#include "Demo.h"

using std::cout;
using std::cin;
using std::string;
using std::vector;

void Demo::start() {
	system("CLS");
	cout << "****************** MENU ******************" << endl;
	cout << "You are in demonstration mode. N = "<< N << endl;
	cout << "Make your choise:" << endl;
	cout << "0 - set N" << endl;
	cout << "1 - Test 1 task ( +, -, *, /, ^(-1) )" << endl;
	cout << "2 - Test 2 task ( ^ )" << endl;
	cout << "3 - Test 3 task ( ... )" << endl;
	cout << "4 - Test 4 task ( sqrt() )" << endl;
	cout << "5 - Test 5 task ( ... )" << endl;
	cout << "6 - Test 6 task ( ... )" << endl;
	cout << "7 - Test 7 task ( ... )" << endl;
	cout << "8 - Test 8 task ( ... )" << endl;
	cout << "9 - Test 9 task ( ... )" << endl;
	cout << "10 - Test 10 task ( ... )" << endl;

	cout << "   - Exit" << endl;

	int ind = 0;
	cin >> ind;
	switch (ind)
	{
	case 0:
		cin >> N;
		start();
		break;
	case 1:
		test1();
		break;
	case 2:
		test2();
		break;
	case 3:
		test3();
		break;
	case 4:
		test4();
		break;
	case 5:
		test5();
		break;
	case 6:
		test6();
		break;
	case 7:
		test7();
		break;
	case 8:
		test8();
		break;
	case 9:
		test9();
		break;
	case 10:
		test10();
		break;
	default:
		break;
	}
	return;
}

void Demo::test1() {
	
	system("CLS");
	cout << "****************** TASK 1 ******************" << endl;
	cout << "You are in TASK1 mode. N = " << N << endl;
	cout << "Make your choise:" << endl;
	cout << "0 - a^(-1)" << endl;
	cout << "1 - a + b" << endl;
	cout << "2 - a - b" << endl;
	cout << "3 - a * b" << endl;
	cout << "4 - a / b" << endl;
	cout << "  - menu" << endl;

	
	cout << "input a = ";
	BigNumber a = get_number();

	int ind = 0;
	cin >> ind;
	switch (ind)
	{
	case 0:
	{
		cout << endl << "a^(-1) = ";
		BigNumber res = a.inverse();
		res.printBigNumber();
		cin.get();
		test1();
	}break;
		
	case 1:
	{
		cout << "input b = ";
		BigNumber b = get_number();
		BigNumber res = (a+b);
		cout << endl << "a + b = ";
		res.printBigNumber();
		cin.get();
		test1();
	}break;
		
	case 2:
	{
		cout << "input b = ";
		BigNumber b = get_number();
		BigNumber res = (a - b);
		cout << endl << "a - b = ";
		res.printBigNumber();
		cin.get();
		test1();
	}break;
	case 3:
	{
		cout << "input b = ";
		BigNumber b = get_number();
		cout << endl << "a * b = ";
		BigNumber res = (a*b);
		res.printBigNumber();
		cin.get();
		test1();
	}break;
	case 4:
	{
		cout << "input b = ";
		BigNumber b = get_number();
		cout << endl << "a / b = ";
		BigNumber res = (a / b);
		res.printBigNumber();
		cin.get();
		test1();
	}break;
	default:
		start();
		break;
	}
	return;
}

int Demo::random_int(int max) {
	static std::random_device rd;
	static std::mt19937 gen(rd());
	std::uniform_int_distribution<> dis(0, max);
	return dis(gen);
};

BigNumber Demo::random_number(int length) {
	BigNumber res("0", N);
	vector<int> chunk;
	BigNumber ten("10", N);
	for (int i = 0; i < length; i++) {
		int rand = random_int(9);
		chunk.push_back(rand);
	}
	res.setChunks(chunk);

	return res;
}

BigNumber Demo::get_number() {
	string a;
	cin >> a;
	BigNumber res(a,N);
	return res;
}