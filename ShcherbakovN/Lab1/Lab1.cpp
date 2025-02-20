#include <iostream>
using namespace std;


class temp_conv 
{
private:
    double temp;
public:
    temp_conv()
    {
        temp = 30.0;
    }
    void set_celsius(double t_c)
    {
        temp = t_c;
    }
    double get_celsius()
    {
        return temp;
    }
    double get_kelvin()
    {
        double t_k;
        t_k = temp + 273.15;
        return t_k;
    }
    double get_fahrenheit()
    {
        double t_f;
        t_f = 32.0 + (temp * 1.8);
        return t_f;
    }
};

int main()
{
    temp_conv my_temp;
    cout << my_temp.get_celsius() << endl;
    cout << my_temp.get_kelvin() << endl;
    cout << my_temp.get_fahrenheit() << endl;
    double new_temp;
    cin >> new_temp;
    my_temp.set_celsius(new_temp);
    cout << my_temp.get_celsius() << endl;
    cout << my_temp.get_kelvin() << endl;
    cout << my_temp.get_fahrenheit() << endl;
}