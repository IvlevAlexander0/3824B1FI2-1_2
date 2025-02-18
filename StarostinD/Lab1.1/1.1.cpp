#include <iostream>
#include <cmath>
using namespace std;

class Rational {
	int p;
	int q;
	int Gcd(int a, int b) {
		if (b == 0) {
			return a;
		}
		if (a < b) {
			a += b;
			b = a - b;
			a -= b;
		}
		return Gcd(b, a % b);
	}
public:
	void SetFraq(int p_, int q_) {
		if (p_ == 0 && q_ != 0) {
			p = 0, q = 1;
		}
		else if (q_ == 0) {
			cout << "Error! Division by 0";
			exit(0);
		}
		else {
			int gcd = Gcd(abs(p_), abs(q_));
			p_ /= gcd;
			q_ /= gcd;
			if (q_ < 0) {
				q_ *= -1;
				p_ *= -1;
			}
			p = p_;
			q = q_;
		}
	}
	Rational() {
		p = 1, q = 1;
	}
	Rational(int p_, int q_) {
		if (p_ == 0 && q_ != 0) {
			p = 0, q = 1;
		}
		else if (q_ == 0) {
			cout << "Error! Division by 0";
			exit(0);
		}
		else {
			int gcd = Gcd(abs(p_), abs(q_));
			p_ /= gcd;
			q_ /= gcd;
			if (q_ < 0) {
				q_ *= -1;
				p_ *= -1;
			}
			p = p_;
			q = q_;
		}
	}
	Rational(const Rational& other): p(other.p), q(other.q) {};
	friend Rational operator+(const Rational& a, const Rational& b);
	friend Rational operator+(const Rational& a, int b);
	friend Rational operator+(int a, const Rational& b);
	friend Rational operator-(const Rational& a, const Rational& b);
	friend Rational operator-(const Rational& a, int b);
	friend Rational operator-(int a, const Rational& b);
	friend Rational operator*(const Rational& a, const Rational& b);
	friend Rational operator*(const Rational& a, int b);
	friend Rational operator*(int a, const Rational& b);
	friend Rational operator/(const Rational& a, const Rational& b);
	friend Rational operator/(const Rational& a, int b);
	friend Rational operator/(int a, const Rational& b);
	friend ostream& operator<<(ostream& out, const Rational& a);
};

Rational operator+(const Rational& a, const Rational& b) {
	return Rational(a.p * b.q + b.p * a.q, a.q * b.q);
}
Rational operator+(const Rational& a, int b) {
	return Rational(a.p + b * a.q, a.q);
}
Rational operator+(int a, const Rational& b) {
	return Rational(b.p + a * b.q, b.q);
}

Rational operator-(const Rational& a, const Rational& b) {
	return Rational(a.p * b.q - b.p * a.q, a.q * b.q);
}
Rational operator-(const Rational& a, int b) {
	return Rational(a.p - b * a.q, a.q);
}
Rational operator-(int a, const Rational& b) {
	return Rational(a * b.q - b.p, b.q);
}

Rational operator*(const Rational& a, const Rational& b) {
	return Rational(a.p * b.p, a.q * b.q);
}
Rational operator*(const Rational& a, int b) {
	return Rational(a.p * b, a.q);
}
Rational operator*(int a, const Rational& b) {
	return Rational(a * b.p, b.q);
}

Rational operator/(const Rational& a, const Rational& b) {
	return Rational(a.p * b.q, a.q * b.p);
}
Rational operator/(const Rational& a, int b) {
	return Rational(a.p, a.q * b);
}
Rational operator/(int a, const Rational& b) {
	return Rational(a * b.q, b.p);
}

ostream& operator<<(ostream& out, const Rational& a) {
	if (a.p == 0) {
		return out << 0;
	}
	else {
		return out << a.p << '/' << a.q;
	}
}


int main() {
}