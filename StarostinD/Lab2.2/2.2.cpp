#include <iostream>
#include <cmath>
using namespace std;

class Polynomial {
	int degree;
	double poly[13]{ 0 };
public:
	Polynomial() : degree(0) {};
	Polynomial(int zero) {
		degree = 0;
		poly[0] = zero;
	}
	Polynomial(double zero) {
		degree = 0;
		poly[0] = zero;
	}
	Polynomial(int deg, const double src[]) {
		--deg;
		if (deg < 0 || deg > 12) {
			cout << "Error! Minimim degree - 0, maximum degree - 12\n";
			exit(0);
		}
		degree = deg;
		for (int i = 0; i <= deg; ++i) {
			poly[i] = src[i];
		}
	}
	Polynomial(const Polynomial& copy) {
		degree = copy.degree;
		for (int i = 0; i <= copy.degree; ++i) {
			poly[i] = copy.poly[i];
		}
	}
	void set_degree(int deg) {
		if (deg < 0 || deg > 12) {
			cout << "Error! Minimim degree - 0, maximum degree - 12\n";
			exit(0);
		}
		degree = deg;
		if (poly[deg] == 0) {
			poly[deg] = 1;
		}
		for (int i = deg + 1; i <= 12; ++i) {
			poly[i] = 0;
		}
	}
	int get_degree() const{
		return degree;
	}
	void set_coef(int id, double c) {
		if (id < 0 || id > 12) {
			cout << "Error! Minimim degree - 0, maximum degree - 12\n";
		}
		else {
			poly[id] = c;
			degree = max(degree, id);
		}
	}
	double value(double x) const {
		double val = 0;
		for (int i = 0; i <= degree; ++i) {
			val += pow(x, i) * poly[i];
		}
		return val;
	}
	Polynomial derivative() const{
		Polynomial der;
		for (int i = 1; i <= degree; ++i) {
			der.set_coef(i - 1, i * poly[i]);
		}
		return der;
	}
	const double& operator[](int id) const{
		if (id >= 0 && id <= 12) {
			return poly[id];
		}
		else {
			cout << "Error! Minimim degree - 0, maximum degree - 12\n";
			exit(0);
		}
	}
	friend ostream& operator<<(ostream& out, const Polynomial& P);
	friend Polynomial operator+(const Polynomial& a, const Polynomial& b);
	friend Polynomial operator-(const Polynomial& a,const Polynomial& b);
	friend Polynomial operator*(const Polynomial& a, const Polynomial& b);
	Polynomial& operator=(const Polynomial& eq) {
		for (int i = 0; i <= 12; ++i) {
			poly[i] = eq[i];
		}
		degree = eq.degree;
		return *this;
	}
	Polynomial operator-() const{
		Polynomial result;
		for (int i = 0; i <= degree; ++i) {
			result.poly[i] = -poly[i];
		}
		result.degree = degree;
		return result;
	}
};
ostream& operator<<(ostream& out, const Polynomial& P) {
	int deg = P.degree;
	if (P.degree > 0) {
		out << '(';
		for (int i = deg; i > 0; --i) {
			if (P[i] != 0 && P[i] != 1) {
				if (i != deg && P[i] < 0) {
					out << "\b\b";
				}
				out << P[i] << "x^" << i << " + ";
			}
			else if (P[i] == 1) {
				if (i != deg && P[i] < 0) {
					out << "\b\b";
				}
				out << "x^" << i << " + ";
			}
		}
		if (P[0] != 0) {
			if (P[0] < 0) {
				out << "\b\b";
			}
			out << P[0] << ')';
		}
		else {
			out << "\b\b\b)";
		}
	}
	else {
		out << '(' << P[0] << ')';
	}
	return out;
}
Polynomial operator+(const Polynomial& a, const Polynomial& b) {
	Polynomial result;
	int deg = 0;
	int m = max(a.degree, b.degree);
	for (int i = 0; i <= m; ++i) {
		result.poly[i] = a.poly[i] + b.poly[i];
		if (result.poly[i]) {
			deg = i;
		}
	}
	result.degree = deg;
	return result;
}
Polynomial operator-(const Polynomial& a, const Polynomial& b) {
	Polynomial result;
	int deg = 0;
	int m = max(a.degree, b.degree);
	for (int i = 0; i <= m; ++i) {
		result.poly[i] = a.poly[i] - b.poly[i];
		if (result.poly[i]) {
			deg = i;
		}
	}
	result.degree = deg;
	return result;
}
Polynomial operator*(const Polynomial& a, const Polynomial& b) {
	if (a.degree + b.degree > 12) {
		cout << "Error! The sum of the degrees of the arguments for this operation must be less than 13\n";
		exit(0);
	}
	Polynomial result;
	int deg = a.degree + b.degree;
	result.degree = deg;
	for (int i = 0; i <= a.degree; ++i) {
		for (int j = 0; j <= b.degree; ++j) {
			result.poly[i + j] += a.poly[i] * b.poly[j];
		}
	}
	return result;
}

int main() {
	double cf[]{ 1, 1, 1 };
	Polynomial f(sizeof(cf) / sizeof(double), cf);
	cout << f << ' ' << f[0] << ' ' << f[1] << ' ' << f[2] << ' ' << f[3] << ' ' << f.get_degree()  << " value(1) = " << f.value(1) << endl; // (x^2 + x^1 + 1) 1 1 1 0 2 value(1) = 3
	f.set_coef(2, 12.5);
	cout << f << " value(1) = " << f.value(1) << endl; // (12.5x^2 + x^1 + 1) value(1) = 14.5
	f.set_coef(4, 4);
	cout << f << ' ' << f.get_degree() << endl; // (4x^4 + 12.5x^2 + x^1 + 1) 4
	double cf2[]{ 1, 3, 3, 6, 13, 6, 7, 2 };
	Polynomial f2(sizeof(cf2) / sizeof(double), cf2);
	cout << f2 << " f2.value(sqrt(13)) =  " << f2.value(sqrt(13)) << endl; // (2x^7 + 7x^6 + 6x^5 + 13x^4 + 6x^3 + 3x^2 + 3x^1 + 1) f2.value(sqrt(13)) =  37406.9
	f2.set_degree(1);
	cout << f2 << " f2.value(sqrt(13)) =  " << f2.value(sqrt(13)) << endl; // (3x^1 + 1) f2.value(sqrt(13)) =  11.8167
	Polynomial f2_d = f2.derivative();
	cout << f2 << ' ' << f2_d << ' ' << f2_d.derivative() << endl; // (3x^1 + 1) (3) (0)
	cout << 15 + f2_d<< ' ' << -f << ' ' << f2_d - f2 - 15 << ' ' << 15 + (-f2_d) << '\n'; // (18) (-4x^4 -12.5x^2 -1x^1 -1) (-3x^1 -13) (12)
	f2.set_coef(2, 3);
	double c3[2]{ 1, 1 };
	double c4[2]{ -1, 1 };
	cout << Polynomial(2, c3) * Polynomial(2, c4) << ' ' << Polynomial(2, c3) * Polynomial(2, c4) * f2 << '\n'; // (x^2 -1) (3x^4 + 3x^3 -2x^2 -3x^1 -1)
 	return 0;
}