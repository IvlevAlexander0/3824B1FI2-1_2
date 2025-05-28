#include <iostream>
#include "Tab.h"

double some_func(int x) {
    return (double(x) / 3) * x;
}

int main()
{
    Tabulator<int, double> tab = Tabulator<int, double>();
    tab.set_func(some_func);
    tab.set_range(2, 10);
    tab.set_count(4);
    vector<double> res = tab.tabulate();
    for (double i : res) {
        std::cout << i << std::endl;
    }
    ofstream file;
    file.open("results.txt");
    tab.tabulate_and_save({ file });
    file.close();
}
