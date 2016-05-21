#pragma once

class rational {
	public:
		rational(int);
		rational(int, int);
		rational(bool, int, int);
		int getNum() const;
		int getDenom() const;
		rational operator +(rational const &operand) const;
		rational operator -(rational const &operand) const;
		rational operator *(rational const &operand) const;
		rational operator /(rational const &operand) const;

	private:
		unsigned int num;
		unsigned int denom;
		bool sign;//1->"+"  0-> "-" 
		static int gcd (int, int);
		static void simplify(int&, int&);
		static void abs(int&);
		static bool sign(int);
};
