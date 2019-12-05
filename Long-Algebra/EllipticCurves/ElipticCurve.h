#pragma once
#include "Point.h"
#include "../BigNumber/BigNumber.h"
#include "BigLinkedList.h"
#include <limits>


class ElipticCurve {
private:
	BigNumber A;
	BigNumber B;
	BigNumber N;

	Point getPointWithN(Point    point);
public:
	ElipticCurve(BigNumber A, BigNumber B, BigNumber N):A(A),B(B),N(N) {
		//set N in case user haven't done it
		this->A.setN(N.to_string());
		this->B.setN(N.to_string());

		BigNumber discriminant = BigNumber("16",N.to_string()) * (BigNumber("4",N.to_string()) * A*A*A + BigNumber("27",N.to_string()) * B*B);
		if (discriminant == BigNumber("0",N.to_string())) {
			throw new std::invalid_argument("Discriminant cannot be equal 0");
		}
	}
	BigNumber getPointOrder(Point init_point);
	Point getNewPointForOrderFinding(BigNumber* currX);
	BigNumber getOrderOfGroup();
	vector<BigNumber*> getDividers(BigNumber& lcm);
    Point exponentiation (Point a, BigNumber& k); //Point A in degree k

	BigNumber getA();
	BigNumber getB();
	BigNumber getN();

	Point addPoints(Point a, Point b);
	Point getInversePoint(Point a);
	bool isPointOnCurve(Point a);

};

BigNumber ElipticCurve::getB() {
	return B;
}

BigNumber ElipticCurve::getA() {
	return A;
}

BigNumber ElipticCurve::getN() {
	return N;
}

/**
* 13
* @determining the point order
* Dmytro Pashchenko
*/
BigNumber ElipticCurve::getPointOrder(Point init_point) {
	if (init_point.isInfinitePoint()) return BigNumber("1");

	BigNumber degree = N + BigNumber("1");
	Point q = exponentiation(init_point, degree);
	BigNumber m("1");
	// m > root^4(N)
	while (N >= (m ^ BigNumber("4"))) m = m + BigNumber("1");

	// storing all x-coordinates of (j * P) to list, j = 1...m 
	BigLinkedList<std::pair<BigNumber, BigNumber>> baby_steps;
	Point last_value = init_point;
	for (BigNumber i = BigNumber("1"); m >= i; i = i + BigNumber("1")) {
		baby_steps.push_back(std::pair<BigNumber, BigNumber>{last_value.getX(), i});
		last_value = addPoints(last_value, init_point);
	}

	degree = BigNumber("2") * m;
	Point giant_step = exponentiation(init_point, degree);
	Point temp_point = giant_step;
	BigNumber first_index = -m;
	Point match_point = exponentiation(giant_step, first_index);
	bool match = false;
	BigNumber match_index("0");
	bool negative = false;

	//comparing points (x-coordinates) by giant steps and baby steps, seek for matching
	BigNumber i = -m;
	for (; m >= i; i = i + BigNumber("1")) {
		match_point = addPoints(q, temp_point);
		for (BigNumber j = BigNumber("0"); m >= j; j = j + BigNumber("1")) {
			if (match_point.getX() == baby_steps.get(j).first || match_point.getX() == -baby_steps.get(j).first) {
				match = true;
				match_index = j;
				if (match_point.getX() == -baby_steps.get(j).first) negative = true;
				break;
			}
		}
		if (match) break;
		temp_point = addPoints(temp_point, giant_step);
	}

	//similar points, different degrees -> (degree1 - degree2) * P = 0
	BigNumber order_candidate = N + BigNumber("1") + BigNumber("2") * m * i;
	if (negative) order_candidate = order_candidate + match_index;
	else order_candidate = order_candidate - match_index;

	vector<BigNumber> factors;
	BigNumber temp("0");
	bool minimal_order = true;

	//searching for the minimal degree, if M:q and q * P = 0 -> M = q, repeat; otherwise M is the order of P
	while (true) {
		factors = order_candidate.factorize_pollard().base;
		for (BigNumber &div : factors) {
			if (exponentiation(init_point, div) == Point::getInfinitePoint()) {
				order_candidate = div;
				minimal_order = false;
				break;
			}
		}
		if (minimal_order) break;
		minimal_order = true;
	}

	return order_candidate;
}

// Returns order of a group
BigNumber ElipticCurve::getOrderOfGroup()
{
    bool orderFound = false;
    // line 5 initiallized and used 17 line variable in this algorithm
    // https://en.wikipedia.org/wiki/Counting_points_on_elliptic_curves#Baby-step_giant-step
    BigNumber L("1");
    BigNumber one("1");
    BigNumber currPointOrder("1");
    Point currPoint("0", "0");
    BigNumber currX("0");
    while (!orderFound)
    {
        currPoint = getNewPointForOrderFinding(&currX);
        L = L.lcm(L, getPointOrder(currPoint));
        vector<BigNumber> dividers = L.factorize_naive().base;
        if (dividers.size() <= 1)
        {
            orderFound = true;
            if (dividers.size() == 1)
                return dividers[0];
            else
            {
                cout << endl << "Error while counting group order" << endl;
                return BigNumber("0");
            }
        }
        currX = currX + one;
    }
    return BigNumber("0");
}



Point ElipticCurve::getNewPointForOrderFinding(BigNumber* currX)
{
    BigNumber one("1");
    while (true)
    {
        BigNumber Sqrt((*currX)^BigNumber("3")+A*(*currX)+B);
        vector<BigNumber> root = Sqrt.sqrt();//= sqr(currX*currX*currX+A*currX+B);
        if (root.size()!=0)
            return Point(*currX, root[0]);
        *currX = *currX + one;
    }
}

/**
*@brief adds two points a and b
*@return sum of two points a and b.
*@throw invalid_argument if one of the points is not on the curve
*/
Point ElipticCurve::addPoints(Point a, Point b) {
	a = getPointWithN(a);
	b = getPointWithN(b);

	if (a.isInfinitePoint())
		return b;

	if (b.isInfinitePoint())
		return a;

	if (!isPointOnCurve(a) || !isPointOnCurve(b)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	//A+(-A)=O
	if (a == getInversePoint(b)) {
		return Point::getInfinitePoint();
	}

	BigNumber lambda("0",N.to_string());
	if (a.getX() == b.getX()) {
		//lambda=(3*a^2+A)/(2*y1) mod N
		lambda = (BigNumber("3",N.to_string()) * a.getX()*a.getX() + A)/ (BigNumber("2",N.to_string()) * a.getY());
	}
	else {
		//lambda=(y2-y1)/(x2-x1) mod N
		lambda = (b.getY() - a.getY())/ (b.getX() - a.getX());
	}

	//x=lambda*lambda-x1-x2 mod N
	BigNumber x = lambda*lambda - a.getX() - b.getX();
	//y=lambda*(x1-x)-y1
	BigNumber y = lambda * (a.getX() - x) - a.getY();

	return Point(x, y);
}

/**
*@return inverse point
*@throw invalid_argument if point is not on the curve
*/
Point ElipticCurve::getInversePoint(Point a) {
	a = getPointWithN(a);

	if (!isPointOnCurve(a)) {
		throw new std::invalid_argument("Some of the points are not on the curve");
	}

	return Point(a.getX(),-a.getY());
}

/**
*@brief checks if point is on curve
*@return true if point is on the curve, otherwise false
*/
bool ElipticCurve::isPointOnCurve(Point a) {
	a = getPointWithN(a);

	BigNumber k = a.getY()*a.getY();
	if (a.getY()*a.getY() != a.getX()*a.getX()*a.getX() + A * a.getX() + B)
		return false;
	if (a.getX() >= N || a.getY()>=N)
		return false;

	return true;
}

/**
*@brief sets N to the coordinates of the point
*@return point with correct N
*This function is created to allow users pass points without setting N to their coordinates.
*/
Point ElipticCurve::getPointWithN(Point point) {
    if (point.isInfinitePoint())
        return Point::getInfinitePoint();
	BigNumber x = point.getX();
	x.setN(N.to_string());
	BigNumber y = point.getY();
	y.setN(N.to_string());
	return Point(x, y);
}

/**
 * #16
 * @brief Point on the elliptic curve exponentiation implemented in this function
 * @return new Point on this curve (or infinite point)
 */
Point ElipticCurve::exponentiation (Point a, BigNumber& k) { //Point A in degree k

    if (!(k >= BigNumber("0"))) {
        throw std::invalid_argument("Degree cannot be lower then 0");
    }

    //k = k % (A point order);
    if (k == BigNumber("0")) {return Point::getInfinitePoint();}

    Point b = Point::getInfinitePoint();

    while (k != BigNumber("0")) {
        if (k % BigNumber("2") == BigNumber("0")) {
            k = k / BigNumber("2");
            a = addPoints(a,a);
        } else {
            k = k - BigNumber("1");
            b = addPoints(b,a);
        }
    }

    return b;
}
