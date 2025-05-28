#include <iostream>
#include <string>
#include "BigNum.h"
using namespace std;


int main()
{
    cout << (2 | (0 >> (64 - 6))) << endl;
    BigNum n1 = BigNum(UINT32_MAX) + 1;
    BigNum n2 = 10;
    BigNum n3 = n2 * n1;
    cout << n3 << endl;
    cout << n3 * n2 << endl;

    cout << n3 / 30 << endl;

}

