// Lab3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "menu.h"
#include <math.h>

void print_square(double a) {
    std::cout << a * a;
}

void print_sqrt(double a) {
    std::cout << sqrt(a);
}

int main()
{
    MenuItem i1 = MenuItem(print_sqrt, "Root");
    MenuItem i2 = MenuItem(print_square, "Square");
    Menu m = Menu(3);
    m.set_menu_item(0, i1);
    m.set_menu_item(1, i2);
    std::cout << m <<std::endl;
    m.execute_menu();
}

