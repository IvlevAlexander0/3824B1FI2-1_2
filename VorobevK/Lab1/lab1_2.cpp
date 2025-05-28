#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <cmath>
#include <ctime>
using namespace std;
class lengths{
    public:
    double meters,t;
    lengths(double a):meters{a}{};
    void set(double a){
        meters = a;
    };
    void get(){
        std::cout << meters << "\n";
    };
    void getfeet(){
        t=meters*3.28;
        std::cout << t << "\n";
    };
    void getyards(){
        t=meters*1.09;
        std::cout << t << "\n";
    };
};
int main(){
    lengths a = lengths(105);
    a.set(110);
    a.get();
    a.getfeet();
    a.getyards();
    return 0;
}