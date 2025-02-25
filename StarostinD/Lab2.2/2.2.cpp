#include <iostream>
#include <limits>
#include <cmath>
using namespace std;

class Polynomial {
	int degree;
	int next_degree;
	double poly[13]{ 0 };
public:
	Polynomial() : degree(INT_MIN), next_degree(INT_MIN) {};
	Polynomial(double zero): next_degree(0) {
		if (zero != 0) {
			poly[0] = zero;
			degree = 0;
		}
		else {
			cout << "Error! The leading coefficient of polynomial can't be equal 0\n";
			poly[0] = zero;
			degree = INT_MIN;
		}

	}
	Polynomial(int size, const double src[]): next_degree(0), degree(0) {
		--size;
		if (size < 0 || size > 12) {
			cout << "Error! Minimim degree - 0, maximum degree - 12\n";
			exit(0);
		}
		bool flag = true;
		degree = size;
		for (int i = size; i >= 0; --i) {
			if (flag && src[i] != 0) {
				degree = i;
				flag = false;
			}
			poly[i] = src[i];
		}
		flag = true;
		for (int i = degree - 1; flag && i >= 0; --i) {
			if (src[i] != 0) {
				next_degree = i;
				flag = false;
			}
		}
		if (degree == 0 && poly[degree] == 0) {
			cout << "Error! The leading coefficient of polynomial can't be equal 0\n";
			degree = INT_MIN;
		}
	}
	Polynomial(const Polynomial& copy) {
		degree = copy.degree;
		next_degree = copy.next_degree;
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
		else if (id == 0 && c == 0 && degree <= 0) {
			cout << "Error! The leading coefficient of polynomial can't be equal 0\n";
			degree = INT_MIN;
		}
		else if (id == degree && c == 0 && next_degree == 0 && poly[next_degree] == 0) {
			cout << "Error! The leading coefficient of polynomial can't be equal 0\n";
			degree = INT_MIN;
		}
		else if (id == degree && c == 0) {
			poly[id] = c;
			degree = next_degree;
			int flag = true;
			for (int i = degree - 1; flag && i >= 0; --i) {
				if (poly[i] != 0) {
					next_degree = i;
					flag = false;
				}
			}
		}
		else {
			poly[id] = c;
			if (id > degree) {
				next_degree = degree;
				degree = id;
			}
		}
	}
	double value(double x) const {
		double val = poly[0];
		double m = 1;
		for (int i = 1; i <= degree; ++i) {
			m *= x;
			val += m * poly[i];
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
			if (P[i] != 0) {
				if (i != deg && P[i] < 0 && P[i] != -1) {
					out << "\b\b- " << abs(P[i]) << "x^" << i << " + ";;
				}
				else if (P[i] != 1 && P[i] != -1) {
					out << P[i] << "x^" << i << " + ";
				}
				else if (P[i] == 1) {
					out << "x^" << i << " + ";
				}
				else if (P[i] == -1) {
					out << "\b\b- x^" << i << " + ";
				}
			}
		}
		if (P[0] != 0) {
			if (P[0] < 0) {
				out << "\b\b- " << abs(P[0]) << ')';
			}
			else {
				out << P[0] << ')';
			}
		}
		else {
			out << "\b\b \b\b)";
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
	return a + (-b);
}
Polynomial operator*(const Polynomial& a, const Polynomial& b) {
	if (a.degree < 0 || b.degree < 0) {
		return Polynomial(0);
	}
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
	Polynomial zero(0);
	cout << zero << ' ' << zero.get_degree() << endl; // (0) -2147483648
	cout << zero * f << ' ' << (zero * f).get_degree() << endl; // (0) -2147483648
	cout << zero + 1 << ' ' << (zero + 1).get_degree() << endl; // (0) -2147483648
	cout << f << ' ' << f[0] << ' ' << f[1] << ' ' << f[2] << ' ' << f[3] << ' ' << f.get_degree()  << " value(2) = " << f.value(2) << endl; // (x^2 + x^1 + 1) 1 1 1 0 2 value(1) = 3
	f.set_coef(2, 12.5);
	cout << f << " value(2) = " << f.value(2) << ' ' << f.get_degree() << endl; // (12.5x^2 + x^1 + 1) value(1) = 14.5
	f.set_coef(4, 4);
	cout << f << ' ' << f.get_degree() << endl; // (4x^4 + 12.5x^2 + x^1 + 1) 4
	f.set_coef(4, 0);
	cout << f << ' ' << f.get_degree() << endl; // (12.5x^2 + x^1 + 1) 2
	double cf2[]{ 1, 3, 3, 6, 13, 6, 7, 2 };
	Polynomial f2(sizeof(cf2) / sizeof(double), cf2);
	cout << f2 << " f2.value(sqrt(13)) =  " << f2.value(sqrt(13)) << ' ' << f2.get_degree() << endl; // (2x^7 + 7x^6 + 6x^5 + 13x^4 + 6x^3 + 3x^2 + 3x^1 + 1) f2.value(sqrt(13)) =  37406.9
	f2.set_degree(1);
	cout << f2 << " f2.value(sqrt(13)) =  " << f2.value(sqrt(13)) << ' ' << f2.get_degree() << endl; // (3x^1 + 1) f2.value(sqrt(13)) =  11.8167
	f2.set_coef(2, 2), f2.set_coef(3, 4);
	Polynomial f2_derivatives[5]{ f2 };
	for (int i = 1; i < 5; ++i) {
		f2_derivatives[i] = (f2_derivatives[i - 1]).derivative();
	}
	for (int i = 0; i < 5; ++i) {
		cout << f2_derivatives[i] << " | " << f2_derivatives[i].get_degree() << " | "; // (4x^3 + 2x^2 + 3x^1 + 1) | 3 | (12x^2 + 4x^1 + 3) | 2 | (24x^1 + 4) | 1 | (24) | 0 | (0) | -2147483648 |
	}
	cout.put('\n');
	cout << 15 + f2_derivatives[1] << ' ' << -f << ' ' << f2_derivatives[1] - f2 - 15 << ' ' << 15 + (-f2_derivatives[1]) << '\n'; // (12x^2 + 4x^1 + 18) (-12.5x^2 - x^1 - 1) (-4x^3 + 10x^2 + x^1 - 13) (-12x^2 - 4x^1 + 12)
	f2.set_coef(2, 3);
	double c3[2]{ 1, 1 };
	double c4[2]{ -1, 1 };
	cout << Polynomial(2, c3) * Polynomial(2, c4) << ' ' << Polynomial(2, c3) * Polynomial(2, c4) * f2 << '\n'; // (x^2 -1) (3x^4 + 3x^3 -2x^2 -3x^1 -1)
 	return 0;
}