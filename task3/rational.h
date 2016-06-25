#pragma once

class rational {
	public:
		rational();
		rational(int);
		rational(int, int);
		int getNum() const;
		int getDenom() const;
		rational operator +(rational const &operand) const;
		rational operator -(rational const &operand) const;
		rational operator *(rational const &operand) const;
		rational operator /(rational const &operand) const;

	private:
		int numerator;
		int denominator;
		void simplify();
		//int lcm(int, int);
		//int gcd (int, int);
};
