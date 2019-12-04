#include <iostream>
#include "../1/BigNumber.h"
#include "ElipticCurve.h"
#include "Point.h"

using namespace std;

void checkCaseExponentiation (ElipticCurve curve, const string& deg, Point& a) {
    BigNumber degree = BigNumber(deg);
    Point aInDegree = curve.exponentiation(a, degree);
    cout << "Point (" << a.getX() << "," << a.getY() << ") in degree " << degree << ":"<< endl;
    cout << aInDegree.getX() << " " << aInDegree.getY() << endl;
}

//check out this literature. It will help a lot:
//https://studref.com/403745/informatika/algoritmy_osnove_ellipticheskih_krivyh
//https://people.cs.nctu.edu.tw/~rjchen/ECC2012S/Elliptic%20Curves%20Number%20Theory%20And%20Cryptography%202n.pdf
int main() {
	Point a = Point(BigNumber("13"), BigNumber("7"));
	Point b = Point(BigNumber("3"), BigNumber("10"));

	//A=1,B=1,N=23
	ElipticCurve curve = ElipticCurve(BigNumber("1"), BigNumber("1"), BigNumber("23"));

	Point sumAB = curve.addPoints(a, b);

	cout << "Sum two points (13,7) and (3,10)" << endl;
	cout << sumAB.getX() << " " << sumAB.getY() << endl;

	Point minusA = curve.getInversePoint(a);
	cout << "Get -a" << endl;
	cout << minusA.getX() << " " << minusA.getY() << endl;

	Point infinitePoint = curve.addPoints(a, minusA);
	cout << "Infinite point" << endl;
	cout << infinitePoint.getX() << " " << infinitePoint.getY()<<endl;

	cout << "Check if point is infinite" << endl;
	cout << infinitePoint.isInfinitePoint() << endl;

    //-----------------------------------------------
    checkCaseExponentiation(curve, "2", a);
    checkCaseExponentiation(curve, "5", a);
    checkCaseExponentiation(curve, "7", a);
    checkCaseExponentiation(curve, "70000000000001", a);

    curve = ElipticCurve(BigNumber("3"), BigNumber("5"), BigNumber("7"));
    a = Point(BigNumber("6"), BigNumber("6"));
    checkCaseExponentiation(curve, "20", a);

    curve = ElipticCurve(BigNumber("234"), BigNumber("464"), BigNumber("109"));
    a = Point(BigNumber("77"), BigNumber("50"));
    checkCaseExponentiation(curve, "44", a);

    return 0;
}
