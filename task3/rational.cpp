//Mr.Fiskerton//
#include "rational.h"

rational::rational(int newNum) {
	sign = sign(newNum);
	numerator = abs(newNum);
	denominator = 1;
}

rational::rational(int newNum, int newDenom) {
	if (newDenom == 0) { throw invalid_argument("[ERROR] rational-constructor: Devision by zero\n"); }
	sign = (!( sign(newNum) ^ sign(newDenom) )) ? true : false; 
	numerator = abs(newNum);
	denominator = abs(newDenom);
	simplify(numerator, denominator);
}

rational::rational(bool newSign, int newNum, int newDenom) {
	if (newDenom == 0) { throw invalid_argument("[ERROR] rational-constructor: Devision by zero\n"); }
	sign = newSign;
	numerator = abs(newNum);
	denominator = abs(newDenom);
	simplify(numerator, denominator);
}

int rational::getNum() const {
	return numerator;
}
	
int rational::getDenom() const {
	return denominator;
}
	
rational rational::operator +(rational const &operand) const {
	int nok = operand.denominator * denominator / gcd(operand.denominator, denominator);
	int num = numerator * (nok / denominator) + operand.numerator * (nok / operand.denominator), 
		denom = nok;
	simplify(num, denom);	
	return rational(num, denom);
}
	
rational rational::operator -(rational const &operand) const {
	int nok = denominator * operand.denominator / gcd(denominator, operand.denominator);
	int num = numerator * (nok / denominator) - 
			  	operand.numerator * (nok / operand.denominator), 
		denom = nok;
	simplify(num, denom);
	return rational(num, denom);
}
	
rational rational::operator *(rational const &operand) const {
	int num = numerator * operand.numerator, 
		denom = denominator * operand.denominator;
	simplify(num, denom);
	if(!(sign ^ operand.sign)){ num*=-1; }
	return rational(num, denom);
}
	
rational rational::operator /(rational const &operand) const {
	int num = numerator * operand.denominator, 
		denom = denominator * operand.numerator;
	simplify(num, denom);
	return rational( (!(sign ^ operand.sign) ), num, denom);
}

int rational::gcd (int a, int b) {
	return b ? gcd (b, a % b) : a;
}

void rational::simplify(int &n, int &denominator) {
	int g = gcd(n, denominator);
	while(g != 1) {
		n = n / g;
		denominator = denominator / g;
		g = gcd(n, denominator);
	}
}

void rational::abs(int &a){
	a *= sign(a) ? 1 : -1;
}

bool rational::sign(int a){
	return a >= 0;
}
