#include <iostream>
#include <iomanip>

using namespace std;

class WeightConverter {
private:
    double weightKg;

public:
    WeightConverter() : weightKg(0.0) {}
    WeightConverter(double kg) : weightKg(kg) {}

    void setWeight(double kg) {
        weightKg = kg;
    }
    double Kg() const {
        return weightKg;
    }
    double Pounds() const {
        return weightKg * 2.20462;
    }
    double Ounces() const {
        return weightKg * 32.1507;
    }
    friend ostream& operator<<(ostream& os, const WeightConverter& Wc) {
        os << fixed << setprecision(2);
        os << "Weight: " << Wc.Pounds() << " pounds, " << Wc.Ounces() << " ounces";
        return os;
    }
};

int main() {
    WeightConverter wc;

    double vvod;
    cin >> vvod;
    wc.setWeight(vvod);

    cout << "In kg: " << wc.Kg() << endl;
    cout << wc << endl;

    return 0;
}