#include <iostream>
#include <cmath>

using namespace std;

class Polynomial
{
private:

    int deg;
    double coefficients[13];

public:

    Polynomial()
    {
        deg = 2;
        set_coefficients();
    }

    void set_deg(int _deg)
    {
        deg = _deg;
    }

    void set_coefficients()
    {
        for (int i = deg; i >= 0; --i)
        {
            cout << "Enter the coefficient x^" << i << ": ";
            cin >> coefficients[i];
            cout << endl;
        }
    }

    int get_deg()
    {
        return deg;
    }

    double get_one_coefficient(int _num)
    {
        return coefficients[_num];
    }

    double get_value_polynomial(double _value)
    {
        double res = 0.0;
        for (int i = 0; i < deg + 1; ++i)
        {
            res += pow(_value, i) * coefficients[i];
        }
        return res;
    }

    void print_polynomial()
    {
        for (int i = deg; i >= 0; --i)
        {
            if (i == deg && i != 0)
            {
                if (coefficients[i] == 0.0)
                {
                    cout << "This coefficient should not be zero. Otherwise, this polynomial will not be of degree " << deg << "!" << endl;
                    i += 1;
                    set_coefficients();
                    continue;
                }
                else if (coefficients[i] < 0.0)
                {
                    cout << showpos << coefficients[i] << "*x^" << noshowpos << i;
                    continue;
                }
                else if (coefficients[i] > 0.0)
                {
                    cout << coefficients[i] << "*x^" << i;
                    continue;
                }
            }
            else if (coefficients[i] == 0)
            {
                continue;
            }
            else if (i == 0)
            {
                if (coefficients[i] != 0)
                {
                    if (deg != 0)
                    {
                        cout << showpos << coefficients[i] << noshowpos;
                        continue;
                    }
                    else if (deg == 0)
                    {
                        cout << coefficients[i];
                        continue;
                    }
                }
                else
                {
                    continue;
                }
            }
            else
            {
                cout << showpos << coefficients[i] << "*x^" << noshowpos << i;
                continue;
            }
        }
        cout << endl;
    }

    void get_derivative()
    {
        int _deg = deg;
        double _coefficients[13] = { 0 };
        for (int i = 0; i < deg + 1; ++i)
        {
            _coefficients[i] = coefficients[i];
        }

        for (int i = 0; i != deg; ++i)
        {
            coefficients[i] = coefficients[i + 1] * (i + 1);
        }
        deg -= 1;
        print_polynomial();

        for (int i = 0; i < deg + 1; ++i)
        {
            coefficients[i] = _coefficients[i];
        }
        deg = _deg;
    }
    ~Polynomial(){}
};

int main()
{
    Polynomial my_p;

    my_p.print_polynomial();

    my_p.set_deg(1);

    my_p.set_coefficients();

    my_p.print_polynomial();

    cout << my_p.get_deg() << endl;

    cout << my_p.get_one_coefficient(1) << endl;

    cout << my_p.get_value_polynomial(1) << endl;

    my_p.get_derivative();

}