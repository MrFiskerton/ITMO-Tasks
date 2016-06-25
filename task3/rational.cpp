//Mr.Fiskerton//
#include "rational.h"
#include <stdexcept>

rational::rational() {
	numerator = 0;
	denominator = 1;
}

rational::rational(int newNum) {
	numerator = newNum;
	denominator = 1;
}

rational::rational(int newNum, int newDenom) {
	if (newDenom == 0) { throw std::invalid_argument("[ERROR] rational-constructor: Devision by zero\n"); }
	numerator = newNum;
	denominator = newDenom;
	simplify();
}

int rational::getNum() const {
	return numerator;
}

int rational::getDenom() const {
	return denominator;
}

int rational::gcd (int a, int b) {
	return b ? gcd (b, a % b) : a;
}

int rational::lcm(int a, int b) {
    return a / gcd(a, b) * b;
}


void rational::simplify() {
    int t = gcd(numerator, denominator);
    numerator /= t;
    denominator /= t;
}


rational rational::operator+(rational const &operand) const {
    int t = lcm(operand.denominator, denominator);
    return rational(numerator * t / denominator + operand.numerator * t / operand.denominator, t);
}

rational rational::operator-(rational const &operand) const {
    int t = lcm(operand.denominator, denominator);
    return rational(numerator * t / denominator - operand.numerator * t / operand.denominator, t);
}


rational rational::operator*(rational const &operand) const {
    return rational(numerator * operand.numerator, denominator * operand.denominator);
}

rational rational::operator/(rational const &operand) const {
    return rational(numerator * operand.denominator, denominator * operand.numerator);
}
