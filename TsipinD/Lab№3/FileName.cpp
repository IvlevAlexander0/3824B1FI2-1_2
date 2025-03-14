#define _USE_MATH_DEFINES 
#include <iostream>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std; 

class TaylorSeries {
private:
    string currentFunction;
    int numberOfTerms;
    double Point;

public:

    double taylor_arcsin(double x, int terms) const {
        if (x < -1.0 || x > 1.0) {
            return NAN;
        }

        double result = x;
        double term = x;

        for (int n = 1; n < terms; ++n) {

            term *= (x * x) * (2 * n - 1) * (2 * n - 1) / (2 * n * (2 * n + 1));
            result += term;
        }

        return result;
    }

    double taylor_arccos(double x, int terms) const {
        if (x < -1.0 || x > 1.0) {
            return NAN;
        }

        return M_PI / 2 - taylor_arcsin(x, terms);
    }

    double taylor_ln(double x, int terms) const {
        if (x < -1.0 || x > 1.0) {
            return NAN;
        }
        if (x <= -1.0) {
            return NAN;
        }

        double result = 0;
        double term = x;

        for (int n = 1; n <= terms; ++n) {
            result += term / n;
            term *= -x;
        }

        return result;
    }
    TaylorSeries() : currentFunction("arcsin"), numberOfTerms(5), Point(0) {}

    void setCurrentFunction(const string& function) {
        currentFunction = function;
    }

    string getCurrentFunction() const {
        return currentFunction;
    }

    void setNumberOfTerms(int terms) {
        numberOfTerms = terms;
    }

    int getNumberOfTerms() const {
        return numberOfTerms;
    }

    void setPoint(double point) {
        Point = point;
    }

    double getPoint() const {
        return Point;
    }

    string getSeriesFormula() const {
        if (currentFunction == "arcsin") {
            return "arcsin(x) = x + (1/6)x^3 + (3/40)x^5 + ...";
        }
        else if (currentFunction == "arccos") {
            return "arccos(x) = pi/2 - x - (1/6)x^3 - (3/40)x^5 - ...";
        }
        else if (currentFunction == "ln") {
            return "ln(1+x) = x - (1/2)x^2 + (1/3)x^3 - ...";
        }
        return "Unknown function";
    }

    double getValue(double x = NAN) const {
        if (isnan(x)) {
            x = Point;
        }
        if (currentFunction == "arcsin") {
            return taylor_arcsin(x, numberOfTerms);
        }
        else if (currentFunction == "arccos") {
            return taylor_arccos(x, numberOfTerms);
        }
        else if (currentFunction == "ln") {
            return taylor_ln(x, numberOfTerms);
        }
        return 0;
    }

    double getDeviation(double x = NAN) const {
        if (isnan(x)) {
            x = Point;
        }
        double seriesValue = getValue();
        double referenceValue;
        if (currentFunction == "arcsin") {
            referenceValue = asin(x);
        }
        else if (currentFunction == "arccos") {
            referenceValue = acos(x);
        }
        else if (currentFunction == "ln") {
            referenceValue = log(1 + x);
        }
        else {
            referenceValue = 0;
        }
        return seriesValue - referenceValue;
    }
};

int main() {
    string list[] = { "arcsin","arccos","ln" };

    TaylorSeries series;
    series.setNumberOfTerms(5);
    double x = 0.3;
    series.setPoint(x);
    for (size_t i = 0; i < 3; ++i) {
        series.setCurrentFunction(list[i]);
        cout << "Current Function: " << series.getCurrentFunction() << endl;
        cout << "Series Formula: " << series.getSeriesFormula() << endl;

        cout << "Series Value at x=" << defaultfloat << x << ": " << fixed << setprecision(8) << series.getValue() << endl;
        cout << "Deviation at x=" << defaultfloat << x << ": " << fixed << setprecision(8) << series.getDeviation() << std::endl;

        cout << "--------------------------------------------------------------------------" << endl;

    };

    return 0;
}