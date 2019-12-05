#include "Demo.h"

void Demo::start() {
	system("CLS");
	cout << "****************** MENU ******************" << endl;
	cout << "You are in demonstration mode. N = "<< N << endl;
	cout << "Make your choise:" << endl;
	cout << "0 - set N" << endl;
	cout << "1 - Test 1 task ( +, -, *, /, ^(-1) )" << endl;
	cout << "2 - Test 2 task ( ^ )" << endl;
	cout << "3 - Test 3 task ( factorization )" << endl;
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

/**
 * This function tests the factorization algorithms. Naive and Pollard Rho algorithms.
 *
 * @author Vitaliy Datsiuk
 */
void Demo::test3() {

    BigNumber p1("97","997");
    BigNumber p2("995","997");
    BigNumber p3("901","997");
    BigNumber p4("201","997");
    BigNumber p5("247","997");
    BigNumber p6("13","997");
    BigNumber p7("1","997");
    BigNumber p8("601","997");
    BigNumber p9("599","997");
    BigNumber p10("597","997");
    BigNumber p11("3","997");
    BigNumber p12("489","997");
    BigNumber p13("5","997");
    BigNumber p14("95","997");
    BigNumber p15("167","997");
    BigNumber p16("705","997");
    BigNumber p17("671","997");
    BigNumber p18("421","997");
    BigNumber p19("423","997");
    BigNumber p20("11","997");
    BigNumber p21("77","997");
    BigNumber p22("727","997");





    factorization a = p1.factorize_pollard();
    a.print();
    cout << endl;
    a = p2.factorize_pollard();
    a.print();
    cout << endl;
    a = p3.factorize_pollard();
    a.print();
    cout << endl;
    a = p4.factorize_pollard();
    a.print();
    cout << endl;
    a = p5.factorize_pollard();
    a.print();
    cout << endl;
    a = p6.factorize_pollard();
    a.print();
    cout << endl;
    a = p7.factorize_pollard();
    a.print();
    cout << endl;
    a = p8.factorize_pollard();
    a.print();
    cout << endl;
    a = p9.factorize_pollard();
    a.print();
    cout << endl;
    a = p10.factorize_pollard();
    a.print();
    cout << endl;
    a = p11.factorize_pollard();
    a.print();
    cout << endl;
    a = p12.factorize_pollard();
    a.print();
    cout << endl;
    a = p13.factorize_pollard();
    a.print();
    cout << endl;
    a = p14.factorize_pollard();
    a.print();
    cout << endl;
    a = p15.factorize_pollard();
    a.print();
    cout << endl;
    a = p16.factorize_pollard();
    a.print();
    cout << endl;
    a = p17.factorize_pollard();
    a.print();
    cout << endl;
    a = p18.factorize_pollard();
    a.print();
    cout << endl;
    a = p19.factorize_naive();
    a.print();
    cout << endl;
    a = p20.factorize_naive();
    a.print();
    cout << endl;
    a = p21.factorize_naive();
    a.print();
    cout << endl;
    a = p22.factorize_naive();
    a.print();
    cout << endl;
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