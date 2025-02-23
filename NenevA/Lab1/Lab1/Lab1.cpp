#include <iostream>
using namespace std;

class Rational {

private:
    int numerator;
    int denominator;

    int calculate_GCD(int a, int b) {
        while (b != 0) {
            int temp = b;
            b = a % b;
            a = temp;
        }
        return a;
    }

    void reduction() {
        int Gcd = calculate_GCD(numerator, denominator);
        numerator /= Gcd;
        denominator /= Gcd;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

public:
    Rational(int num = 0, int denom = 1) : numerator(num), denominator(denom) {
        if (denominator == 0) {
            cout << "Denominator can't equal zero.";
            exit(0);
        }
        reduction();
    }

    Rational operator+(const Rational& other) const {
        return Rational(numerator * other.denominator + other.numerator * denominator, denominator * other.denominator);
    }

    Rational operator-(const Rational& other) const {
        return Rational(numerator * other.denominator - other.numerator * denominator, denominator * other.denominator);
    }

    Rational operator*(const Rational& other) const {
        return Rational(numerator * other.numerator, denominator * other.denominator);
    }

    Rational operator/(const Rational& other) const {
        if (other.numerator == 0) {
            cout << "Division by zero can't be done.";
            exit(0);
        }
        return Rational(numerator * other.denominator, denominator * other.numerator);
    }


    friend ostream& operator<<(ostream& os, const Rational& r) {
        os << r.numerator;
        if (r.denominator != 1) {
            os << "/" << r.denominator;
        }
        return os;
    }
};

int main() {
    Rational r1(6, 10);
    Rational r2(3, 4);

    cout << "r1 = " << r1 << endl;
    cout << "r2 = " << r2 << endl;

    cout << "r1 + r2 = " << r1 + r2 << endl;
    cout << "r1 - r2 = " << r1 - r2 << endl;
    cout << "r1 * r2 = " << r1 * r2 << endl;
    cout << "r1 / r2 = " << r1 / r2 << endl;

    return 0;
}