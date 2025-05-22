#include <iostream>
#include <cmath>

using namespace std;

class Polynom {
private:
    double coefficients[13];
    int degree;

public:
    Polynom() : degree(0) {
        for (int i = 0; i < 13; ++i) {
            coefficients[i] = 0.0;
        }
    }

    Polynom(int n) : degree(n) {
        if (n < 0 || n > 12) {
            throw out_of_range("stepen 0-12");
        }
        for (int i = 0; i <= n; ++i) {
            coefficients[i] = 0.0;
        }
        if (n > 0) {
            coefficients[n] = 1.0;
        }
    }

    ~Polynom() {}

    Polynom& operator=(const Polynom& other) {
        if (this != &other) {
            degree = other.degree;
            for (int i = 0; i <= degree; ++i) {
                coefficients[i] = other.coefficients[i];
            }
        }
        return *this;
    }

    void setDegree(int n) {
        if (n < 0 || n > 12) {
            throw out_of_range("stepen 0-12");
        }
        degree = n;
        for (int i = 0; i <= n; ++i) {
            coefficients[i] = 0.0;
        }
        if (n > 0) {
            coefficients[n] = 1.0;
        }
    }

    void setCoefficient(int index, double value) {
        if (index < 0 || index > degree) {
            throw out_of_range("index out of range");
        }
        coefficients[index] = value;
        if (index == degree && value == 0.0 && degree > 0) {
            degree--;
        }
    }

    int getDegree() const {
        return degree;
    }

    double getCoefficient(int index) const {
        if (index < 0 || index > degree) {
            throw out_of_range("index out of range");
        }
        return coefficients[index];
    }

    double v_x(double x) const {
        double result = coefficients[degree];
        for (int i = degree - 1; i >= 0; --i) {
            result = result * x + coefficients[i];
            return result; // sxema gornera
        }
    }

    Polynom proizvodnaya() const {
        if (degree == 0) {
            return Polynom(0);
        }
        Polynom deriv(degree - 1);
        for (int i = 1; i <= degree; ++i) {
            deriv.setCoefficient(i - 1, coefficients[i] * i);
        }
        return deriv;
    }

    friend std::ostream& operator<<(ostream& os, const Polynom& poly) {
        for (int i = poly.degree; i >= 0; --i) {
            os << poly.coefficients[i] << "x^" << i;
            if (i > 0) {
                os << " + ";
            }
        }
        return os;
    }
};

int main() {
    int degree;
    cout << "polinom degree: ";
    cin >> degree;
    Polynom p(degree);

    for (int i = 0; i <= degree; ++i) {
        double coeff;
        cout << "coeff x^" << i << ": ";
        cin >> coeff;
        p.setCoefficient(i, coeff);
    }

    cout << "Polinom: " << p << endl;
    cout << "polinom degree " << p.getDegree() << endl;
    cout << "polinom(x): " << p.v_x(2) << endl;
    Polynom deriv = p.proizvodnaya();
    cout << "proizvodnaya: " << deriv << endl;

    return 0;
}
