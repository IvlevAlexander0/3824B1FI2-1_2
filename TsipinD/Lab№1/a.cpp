#include <iostream>
#include <string>

using namespace std;

class Length_Converter {
private:
    double meters;
    double feet = 3.28084;
    double yard = 1.09361;

public:
    Length_Converter() {
        meters = 0.0;
    }
    Length_Converter(double value) {
        meters = value;
    }

    
    void SetInMeters(double value) {
        meters = value;
    }

    double GetInMeters() const {
        return meters;
    }

    double GetInFeets() const {
        return meters * feet;
    }

    double GetInYards() const {
        return meters * yard;
    }

    void Print() const {
        cout << "Current length:\n";
        cout << " - Meters: " << meters << endl;
        cout << " - Feets: " << GetInFeets() << endl;
        cout << " - Yards: " << GetInYards() << endl;
    }
};

int main() {
    Length_Converter converter;

    converter.SetInMeters(10.0);
    converter.Print();

    cout << "\n\nLength in feet: " << converter.GetInFeets() << endl;

    return 0;
}