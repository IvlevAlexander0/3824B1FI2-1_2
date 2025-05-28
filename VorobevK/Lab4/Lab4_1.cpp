
#include <iostream>
#include "termometr.h"

using std::cout;
using std::endl;

int main()
{
    termometr term;
    term.set_start_dt(DateTime(10, 5, 10));
    term.set_series_of_records({ 10, 12, 13, 13, 11, 9, 6, 3, 0 });
    cout << term.get_average_temperature_month_for_day() << endl;
  //  term.set_record(Record(DateTime(18, 6, 10), 20));
    cout << term.get_average_temperature_for_month() << endl;
    cout << term.get_average_temperature_for_day() << endl;

}
