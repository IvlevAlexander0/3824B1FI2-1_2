#include <iostream>

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
            if (coefficients[deg] == 0)
            {
                cout << "This coefficient should not be zero. Otherwise, this polynomial will not be of degree " << deg << "!" << endl;
                i += 1;
                continue;
            }
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
        double res = 0.0, value_x_deg = 1.0;
        for (int i = 0; i < deg + 1; ++i)
        {
            res += value_x_deg * coefficients[i];
            value_x_deg *= _value;
        }
        return res;
    }

    void print_polynomial() const //const - метод сможет только "читать" поля
    {
        for (int i = deg; i >= 0; --i)
        {
            if (i == deg && i != 0)
            {
                if (coefficients[i] < 0.0)
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

    void get_derivative() const //const - метод сможет только "читать" поля
    {
        int _deg = deg;
        double _coefficients[13] = { 0 };
        
        for (int i = 0; i != deg; ++i)
        {
            _coefficients[i] = coefficients[i + 1] * (i + 1);
        }
        _deg -= 1;
        
        if (deg == 0)
        {
            cout << "0";
        }
        
        for (int i = _deg; i >= 0; --i)
        {
            if (i == _deg && i != 0)
            {
                if (_coefficients[i] < 0.0)
                {
                    cout << showpos << _coefficients[i] << "*x^" << noshowpos << i;
                    continue;
                }
                else if (_coefficients[i] > 0.0)
                {
                    cout << _coefficients[i] << "*x^" << i;
                    continue;
                }
            }
            else if (_coefficients[i] == 0)
            {
                continue;
            }
            else if (i == 0)
            {
                if (_coefficients[i] != 0)
                {
                    if (deg != 0)
                    {
                        cout << showpos << _coefficients[i] << noshowpos;
                        continue;
                    }
                    else if (_deg == 0)
                    {
                        cout << _coefficients[i];
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
                cout << showpos << _coefficients[i] << "*x^" << noshowpos << i;
                continue;
            }
        }
        cout << endl;
    }
    ~Polynomial(){}
};

int main()
{
    Polynomial my_p;

    my_p.print_polynomial();

    my_p.set_deg(3);

    my_p.set_coefficients();

    my_p.print_polynomial();

    cout << "get_deg: " << my_p.get_deg() << endl;

    cout << "get_one_coefficient: " << my_p.get_one_coefficient(0) << endl;

    cout << "get_value_polynomial: " << my_p.get_value_polynomial(2) << endl;

    my_p.get_derivative();

}