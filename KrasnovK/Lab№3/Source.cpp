#include <iostream>
#include <functional>

using namespace std;

class IntegralCalculator {
private:
    double a; // lower
    double b; // upper
    int n; // otrezki
    std::function<double(double)> func;
    enum Method { LEFT, RIGHT, MID } method;

public:
    IntegralCalculator() : a(0), b(0), n(1), method(LEFT) {}

    void setFunction(std::function<double(double)> f) {
        func = f;
    }

    void setLimits(double lower, double upper) {
        if (lower >= upper) {
            throw invalid_argument("errror, upper > lower");
        }
        a = lower;
        b = upper;
    }

    pair<double, double> getLimits() const {
        return make_pair(a, b);
    }

    void setSegments(int segments) {
        if (segments <= 0) {
            throw invalid_argument("error, > 0");
        }
        n = segments;
    }

    void setMethod(const string& methodName) {
        if (methodName == "left") {
            method = LEFT;
        }
        else if (methodName == "right") {
            method = RIGHT;
        }
        else if (methodName == "mid") {
            method = MID;
        }
        else {
            throw invalid_argument("error, left/right/mid");
        }
    }

    double calculate() const {
        double h = (b - a) / n;
        double result = 0.0;

        switch (method) {
        case LEFT:
            for (int i = 0; i < n; ++i) {
                result += func(a + i * h);
            }
            break;

        case RIGHT:
            for (int i = 1; i <= n; ++i) {
                result += func(a + i * h);
            }
            break;

        case MID:
            for (int i = 0; i < n; ++i) {
                result += func(a + (i + 0.5) * h);
            }
            break;
        }

        return result * h;
    }

    void result() const {
        cout << "result: " << calculate() << endl;
    }
};

int main() {
    IntegralCalculator calculator;
    calculator.setFunction([](double x) { return x * x; }); // x^2

    double lowerLimit, upperLimit;
    int otrezki;
    string metod;

    cout << "lower: ";
    cin >> lowerLimit;
    cout << "upper: ";
    cin >> upperLimit;
    cout << "n otrzkov: ";
    cin >> otrezki;
    cout << "metod (left/right/mid): ";
    cin >> metod;

    calculator.setLimits(lowerLimit, upperLimit);
    calculator.setSegments(otrezki);
    calculator.setMethod(metod);

    calculator.result();

    return 0;
}