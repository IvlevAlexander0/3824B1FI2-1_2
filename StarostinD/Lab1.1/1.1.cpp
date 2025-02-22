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
	void SetFrac(int p_, int q_) {
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
	void SetFrac(double a) {
		int c = 1;
		while (ceil(a * c) - a * c > 0.0000001) {
			c++;
		}
		p = ceil(a * c);
		q = c;
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
	Rational(int a) {
		p = a;
		q = 1;
	}
	Rational(double a) {
		int c = 1;
		while (ceil(a * c) - a * c > 0.0000001) {
			c++;
		}
		p = ceil(a * c);
		q = c;
	}
	friend Rational operator+(const Rational& a, const Rational& b);
	friend Rational operator-(const Rational& a, const Rational& b);
	friend Rational operator*(const Rational& a, const Rational& b);
	friend Rational operator/(const Rational& a, const Rational& b);
	friend ostream& operator<<(ostream& out, const Rational& a);
};

Rational operator+(const Rational& a, const Rational& b) {
	return Rational(a.p * b.q + b.p * a.q, a.q * b.q);
}

Rational operator-(const Rational& a, const Rational& b) {
	return Rational(a.p * b.q - b.p * a.q, a.q * b.q);
}

Rational operator*(const Rational& a, const Rational& b) {
	return Rational(a.p * b.p, a.q * b.q);
}

Rational operator/(const Rational& a, const Rational& b) {
	return Rational(a.p * b.q, a.q * b.p);
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
	Rational a(2, 3), b(52, 25);
	int n = 5;
	cout << "Inicialisation constructor: " << a << ' ' << b << '\n'; // Inicialisation constructor: 2/3 52/25
	cout << "Rational and Rational: " << a + b << ' ' << a - b << ' ' << a * b << ' ' << a / b << '\n'; // Rational and Rational: 206/75 -106/75 104/75 25/78
	cout << "Rational and integer: " << a + n << ' ' << a - n << ' ' << a * n << ' ' << a / n << '\n'; // Rational and integer: 17/3 -13/3 10/3 2/15
	cout << "Integer and Rational: " << n + a << ' ' << n - a << ' ' << n * a << ' ' << n / a << '\n'; // Integer and Rational: 17/3 13/3 10/3 15/2
	Rational c;
	cout << "Default constuctor: " << c << '\n'; // Default constuctor: 1/1
	Rational ca(a);
	cout << "Copy constructor: " << ca << '\n'; // Copy constructor: 2/3
	Rational zero(0, 12);
	Rational zero2(0, 123);
	cout << "Zero in numerator: " << zero << ". Multiplication by zero Rational: " << a * zero << '\n'; // Zero in numerator: 0. Multiplication by zero Rational: 0
	//Rational e(13, 0); // Error! Division by 0
	//cout << "Division by zero Rational" << n / zero << ' '; // Error! Division by 0
	//cout << a / zero << '\n'; // Error! Division by 0
	//cout << "Division by zero integer" << a / 0; // Error! Division by 0
	cout << "Operations with zero Rationals: " << zero + zero2 << ' ' << zero - zero2 << ' ' << zero * zero2 << '\n'; // Operations with zero Rationals: 0 0 0
	//cout << zero / zero2; // Error! Division by 0
	ca.SetFrac(9, 33);
	cout << ".SetFrac(9, 33): " << ca << '\n'; // .SetFrac: 3/11
	//ca.SetFraq(1, 0); // Error! Division by 0
	Rational stwo{ sqrt(2) };
	cout << "Rational and double " << Rational(1.0 / 137) << ' ' << stwo << ' ' << stwo + a << '\n'; // Rational and double 1/137 13250218/9369319 58489292/28107957
	cout << a - stwo << ' ' << stwo * a << ' ' << a / stwo; // -21012016/28107957 26500436/28107957 9369319/19875327
}