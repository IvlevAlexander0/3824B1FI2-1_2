#include <fstream>
#include <iostream>
#include <string>
#define INITIAL_DATA_CONST -400.0
#define DEFAULT_TEMPERATURE -300.0

std::string list_months[12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
int list_days_in_months[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
std::string list_days[31] = { "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23", "24", "25", "26", "27", "28", "29", "30", "31" };
std::string list_hours[24] = { "00", "01", "02", "03", "04", "05", "06", "07", "08", "09", "10", "11", "12", "13", "14", "15", "16", "17", "18", "19", "20", "21", "22", "23" };

class Date
{
private:
    int day;
    int month;
    int year;
    double time_period[24]; //[00:00;23:00]. Сюда записывается температура в градусах Цельсия. По умолчанию инициализируется -300.0(так как такой температуры не существует).
public:
    Date() : day{ -1 }, month{ -1 }, year{ -1 }
    {
        for (size_t i = 0; i < 24; ++i)
        {
            time_period[i] = DEFAULT_TEMPERATURE;
        }
    }
    Date(int _day, int _month, int _year) 
    {
        if (_month < 13 && _month > 0 && _day <= list_days_in_months[_month - 1] && _day > 0 && _year > 0)
        {
            day = _day;
            month = _month;
            year = _year;
        }
        else
        {
            std::cout << "Invalid parameters. Default initialization is performed." << std::endl;
            day = -1;
            month = -1;
            year = -1;
        }
        for (size_t i = 0; i < 24; ++i)
        {
            time_period[i] = DEFAULT_TEMPERATURE;
        }
    }

    void reset_date() //Сборс даты до значений по умолчанию
    {
        day = -1;
        month = -1;
        year = -1;
        for (size_t i = 0; i < 24; ++i)
        {
            time_period[i] = DEFAULT_TEMPERATURE;
        }
    }

    void set_date(int _day, int _month, int _year) //Устанавливает конкретную дату (без температуры).
    {
        if (_month < 13 && _month > 0 && _day <= list_days_in_months[_month - 1] && _day > 0 && _year > 0)
        {
            day = _day;
            month = _month;
            year = _year;
        }
        else
        {
            std::cout << "Invalid parameters." << std::endl;
        }
    }
    void set_date_temperature(int _hour, double _value) //Устанавливает конкретную температуру или температуру по умолчанию/температуру инициализирующую.
    {
        if (_hour < 24 && _hour >= 0 && (_value > -273.15 || _value == INITIAL_DATA_CONST || _value == DEFAULT_TEMPERATURE))
        {
            time_period[_hour] = _value;
        }
        else
        {
            std::cout << "Invalid parameters." << std::endl;
        }
    }

    int get_date_day() const
    {
        return day;
    }
    int get_date_month() const
    {
        return month;
    }
    int get_date_year() const
    {
        return year;
    }
    double get_date_temperature(int _hour) const
    {
        return time_period[_hour];
    }

    ~Date(){}
};

class Thermometer
{
private:
    Date initializing_date;
    Date* list_of_monitoring = new Date[365];

    int get_index_observation(int _day, int _month, int _year, int _hour) const
    {
        int delta_day = initializing_date.get_date_day() - _day;
        int delta_month = initializing_date.get_date_month() - _month;
        int delta_year = initializing_date.get_date_year() - _year;
        int initializing_date_hour = 0;
        while (initializing_date.get_date_temperature(initializing_date_hour) != INITIAL_DATA_CONST && initializing_date_hour != 24)
        {
            initializing_date_hour += 1;
        }
        int delta_hour = initializing_date_hour - _hour;

        //Ограничение снизу.
        if ((delta_year > 0) || (delta_year == 0 && delta_month > 0) || (delta_year == 0 && delta_month == 0 && delta_day > 0) || (delta_year == 0 && delta_month == 0 && delta_day == 0 && delta_hour > 0))
        {
            //std::cout << "An attempt to set an observation outside the range (calendar year)." << std::endl;
            return -1;
        }

        int initializing_date_number_in_year = initializing_date.get_date_day();
        for (int i = initializing_date.get_date_month() - 1; i > 0; --i)
        {
            initializing_date_number_in_year += list_days_in_months[i - 1];
        }
        //std::cout << initializing_date_number_in_year << std::endl;
        int observation_date_number_in_year = _day;
        for (int i = _month - 1; i > 0; --i)
        {
            observation_date_number_in_year += list_days_in_months[i - 1];
        }
        //std::cout << observation_date_number_in_year << std::endl;

        int delta_dates = observation_date_number_in_year - initializing_date_number_in_year;

        //Ограничение сверху.
        if (((delta_dates == 0) && ((initializing_date.get_date_year() + 1) == _year) && (initializing_date_hour <= _hour))
            || ((delta_dates == 0) && ((initializing_date.get_date_year() + 1) < _year)) || ((delta_dates > 0) && ((initializing_date.get_date_year() + 1) <= _year)))
        {
            //std::cout << "An attempt to set an observation outside the range (calendar year)." << std::endl;
            return -1;
        }

        int date_index = 0;
        if (delta_dates < 0)
        {
            date_index = (365 - initializing_date_number_in_year) + observation_date_number_in_year;
        }
        else if (delta_dates > 0)
        {
            date_index = delta_dates;
        }
        else if (delta_dates == 0)
        {
            if (initializing_date.get_date_year() == _year)
            {
                date_index = 0;
            }
            else if ((initializing_date.get_date_year() + 1) == _year)
            {
                date_index = 364;
            }
        }

        return date_index;
    }

    void print_observation(int _day, int _month, int _year, int _hour, double _temperature) const
    {
        std::cout << "<" << list_days[_day - 1] << "." << list_months[_month - 1] << "." << _year << "> : <" << list_hours[_hour] << ":00> : <" << _temperature << " C>";
    }
public:
    Thermometer()
    {
        initializing_date.set_date(1, 1, 2025);
        initializing_date.set_date_temperature(0, INITIAL_DATA_CONST);
    }

    Thermometer(int _day, int _month, int _year, int _time)
    {
        if (_month < 13 && _month > 0 && _day <= list_days_in_months[_month - 1] && _day > 0 && _year > 0 && _time < 24 && _time >= 0)
        {
            initializing_date.set_date(_day, _month, _year);
            initializing_date.set_date_temperature(_time, INITIAL_DATA_CONST);
        }
        else
        {
            initializing_date.set_date(1, 1, 2025);
            initializing_date.set_date_temperature(0, INITIAL_DATA_CONST);
            std::cout << "Invalid parameters. Default initialization is performed." << std::endl;
        }
    }

    ~Thermometer()
    {
        delete[] list_of_monitoring;
    }

    int set_initializing_date(int _day, int _month, int _year, int _time)
    {
        if (_month < 13 && _month > 0 && _day <= list_days_in_months[_month - 1] && _day > 0 && _year > 0 && _time < 24 && _time > 0)
        {
            int i = 0;
            while (initializing_date.get_date_temperature(i) != INITIAL_DATA_CONST && i != 24)
            {
                i += 1;
            }
            //Запрет на установку новой начальной даты раньше предыдущей.
            if ((initializing_date.get_date_year() < _year) || (initializing_date.get_date_year() == _year && initializing_date.get_date_month() < _month)
                || (initializing_date.get_date_year() == _year && initializing_date.get_date_month() == _month && initializing_date.get_date_day() < _day) ||
                (initializing_date.get_date_year() == _year && initializing_date.get_date_month() == _month && initializing_date.get_date_day() == _day && i < _time))
            {
                initializing_date.reset_date();
            }
            else
            {
                std::cout << "An attempt to shift the initializing date to a value earlier than the current one(or by the current one). The initializing date has not been changed." << std::endl;
                return -1;
            }
            initializing_date.set_date(_day, _month, _year);
            initializing_date.set_date_temperature(_time, INITIAL_DATA_CONST);
            for (size_t i = 0; i < 365; ++i)
            {
                list_of_monitoring[i].reset_date();
            }
            list_of_monitoring[0].set_date(_day, _month, _year);
            list_of_monitoring[0].set_date_temperature(_time, DEFAULT_TEMPERATURE);
        }
        else
        {
            std::cout << "Invalid parameters." << std::endl;
        }
        return 0;
    }

    void get_initializing_date() const
    {
        int i = 0;
        while (initializing_date.get_date_temperature(i) != INITIAL_DATA_CONST && i != 24)
        {
            i += 1;
        }
        if (initializing_date.get_date_temperature(i) == INITIAL_DATA_CONST)
        {
            std::cout << "<Initializing_date> : <" << list_days[initializing_date.get_date_day() - 1] << "." << list_months[initializing_date.get_date_month() - 1] << "." << initializing_date.get_date_year() << "> : <" << i << ":00>" << std::endl;
        }
    }

    int set_observation(int _day, int _month, int _year, int _hour, double _temperature)
    {
        int date_index = get_index_observation(_day, _month, _year, _hour);
        if (date_index != -1)
        {
            list_of_monitoring[date_index].set_date(_day, _month, _year);
            list_of_monitoring[date_index].set_date_temperature(_hour, _temperature);
        }
        else
        {
            std::cout << "An attempt to set an observation outside the range (calendar year)." << std::endl;
        }

        return 0;
    }

    void get_observation_temperature(int _day, int _month, int _year, int _hour) const
    {
        int date_index = get_index_observation(_day, _month, _year, _hour);
        if (date_index != -1)
        {
            if (list_of_monitoring[date_index].get_date_temperature(_hour) == DEFAULT_TEMPERATURE)
            {
                std::cout << "This observation does not exist." << std::endl;
            }
            else
            {
                print_observation(_day, _month, _year, _hour, list_of_monitoring[date_index].get_date_temperature(_hour));
                std::cout << std::endl;
            }
        }
        else
        {
            std::cout << "An attempt to get an observation outside the range (calendar year)." << std::endl;
        }
    }

    void set_series_observations(int _day, int _month, int _year)
    {
        double temperature = 0.0, count = 0.0;
        for (int i = 0; i < 24; ++i)
        {
            if (get_index_observation(_day, _month, _year, i) != -1)
            {
                std::cout << "Enter temperature for <" << list_hours[i] << ":00> :";
                std::cin >> temperature;
                if (temperature == INITIAL_DATA_CONST || temperature == DEFAULT_TEMPERATURE)
                {
                    i -= 1;
                    std::cout << "Invalid parameters." << std::endl;
                    continue;
                }
                set_observation(_day, _month, _year, i, temperature);
                count += 1;
            }
            else
            {
                if (count == 0.0)
                {
                    std::cout << "An attempt to set an observation outside the range (calendar year)." << std::endl;
                }
                continue;
            }
        }
    }

    double get_average_temperature_date(int _day, int _month, int _year) const
    {
        double average_temperature = 0.0, extra = 0.0, count = 0.0;
        int date_index = 0;
        int i = 0;
        for (i = 0; i < 24; ++i)
        {
            date_index = get_index_observation(_day, _month, _year, i);

            if (date_index != -1)
            {
                break;
            }
        }

        if (date_index == -1)
        {
            std::cout << "An attempt to take the temperature from a date that is outside the range (calendar year)." << std::endl;
            return -1.0;
        }

        for (int j = i; j < 24; ++j)
        {

            extra = list_of_monitoring[date_index].get_date_temperature(j);
            //std::cout << extra << std::endl;
            if (extra != DEFAULT_TEMPERATURE)
            {
                average_temperature += extra;
                count += 1;
            }
            else
            {
                continue;
            }
        }
        if (count == 0.0)
        {
            std::cout << "No observations were made on this date." << std::endl;
            return -1.0;
        }
        else
        {
            average_temperature = average_temperature / count;
        }
        std::cout << "Average temperature for the date <" << list_days[_day - 1] << "." << list_months[_month - 1] << "." << _year << "> : <" << average_temperature << " C>" << std::endl;
        return average_temperature;
    }

    double get_average_temperature_all() const
    {
        double average_temperature = 0.0, count = 0.0, extra = 0.0;
        for (int i = 0; i < 365; ++i)
        {
            for (int j = 0; j < 24; ++j)
            {
                extra = list_of_monitoring[i].get_date_temperature(j);
                //std::cout << extra << std::endl;
                if (extra != DEFAULT_TEMPERATURE)
                {
                    average_temperature += extra;
                    count += 1;
                }
                else
                {
                    continue;
                }
            }
        }
        if (count == 0.0)
        {
            std::cout << "No observations were made during the calendar year." << std::endl;
            return -1.0;
        }
        else
        {
            average_temperature = average_temperature / count;
        }
        std::cout << "Average temperature for a calendar year : <" << average_temperature << " C>" << std::endl;
        return average_temperature;
    }

    double get_average_temperature_month(int _month, int _year) const
    {
        double average_temperature = 0.0, extra = 0.0, count = 0.0;
        int date_index = 0;
        int i = 0, j = 1;
        for (j = 1; j < list_days_in_months[_month - 1] + 1; ++j)
        {
            for (i = 0; i < 24; ++i)
            {
                date_index = get_index_observation(j, _month, _year, i);

                if (date_index != -1)
                {
                    break;
                }
            }
            if (date_index != -1)
            {
                break;
            }
        }

        if (date_index == -1)
        {
            std::cout << "An attempt to take the temperature from a date that is outside the range (calendar year)." << std::endl;
            return -1.0;
        }


        int k = i;
        for (int l = j; l < list_days_in_months[_month - 1] + 1; ++l)
        {
            date_index = get_index_observation(l, _month, _year, k);
            for (; k < 24; ++k)
            {
                extra = list_of_monitoring[date_index].get_date_temperature(k);

                if (extra != DEFAULT_TEMPERATURE)
                {
                    average_temperature += extra;
                    count += 1;
                }
                else
                {
                    continue;
                }
            }
            k = 0;
        }

        if (count == 0.0)
        {
            std::cout << "No observations were made on this month." << std::endl;
            return -1.0;
        }
        else
        {
            average_temperature = average_temperature / count;
        }
        std::cout << "Average temperature for the month <" << list_months[_month - 1] << "." << _year << "> : <" << average_temperature << " C>" << std::endl;
        return average_temperature;
    }

    double get_average_daytime_or_nighttime_temperature_month(int _month, int _year, std::string _time) const //_time: "day" - день [06:00 - 18:00], "night" - ночь [00:00 - 05:00, 19:00 - 23:00].
    {
        double average_temperature = 0.0, extra = 0.0, count = 0.0;
        int date_index = 0;
        int i = 0, j = 1;
        for (j = 1; j < list_days_in_months[_month - 1] + 1; ++j)
        {
            for (i = 0; i < 24; ++i)
            {
                date_index = get_index_observation(j, _month, _year, i);

                if (date_index != -1)
                {
                    break;
                }
            }
            if (date_index != -1)
            {
                break;
            }
        }

        if (date_index == -1)
        {
            std::cout << "An attempt to take the temperature from a date that is outside the range (calendar year)." << std::endl;
            return -1.0;
        }


        int k = i;
        if (_time == "day")
        {
            for (int l = j; l < list_days_in_months[_month - 1] + 1; ++l)
            {
                date_index = get_index_observation(l, _month, _year, k);
                for (; k < 24; ++k)
                {
                    if ((k > 5) && (k < 19))
                    {
                        extra = list_of_monitoring[date_index].get_date_temperature(k);

                        if (extra != DEFAULT_TEMPERATURE)
                        {
                            average_temperature += extra;
                            count += 1;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                k = 0;
            }
        }
        else if (_time == "night")
        {
            for (int l = j; l < list_days_in_months[_month - 1] + 1; ++l)
            {
                date_index = get_index_observation(l, _month, _year, k);
                for (; k < 24; ++k)
                {
                    if ((k < 6) || (k > 18))
                    {
                        extra = list_of_monitoring[date_index].get_date_temperature(k);

                        if (extra != DEFAULT_TEMPERATURE)
                        {
                            average_temperature += extra;
                            count += 1;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
                k = 0;
            }
        }
        else
        {
            std::cout << "Invalid parameters." << std::endl;
            return -1.0;
        }
       

        if (count == 0.0)
        {
            std::cout << "No observations were made on this month." << std::endl;
            return -1.0;
        }
        else
        {
            average_temperature = average_temperature / count;
        }

        if (_time == "day")
        {
            std::cout << "Average monthly daytime temperature <" << list_months[_month - 1] << "." << _year << "> : <" << average_temperature << " C>" << std::endl;
        }
        else if (_time == "night")
        {
            std::cout << "Average monthly nighttime temperature <" << list_months[_month - 1] << "." << _year << "> : <" << average_temperature << " C>" << std::endl;
        }

        return average_temperature;

    }

    void save_to_file() const
    {
        std::ofstream fout; //Создаём поток для записи.
        fout.open("observations.txt"); //Открываем файл.
        int count = 0, extra = 0;

        while (count < 365)
        {
            for (int i = 0; i < 24; ++i)
            {
                if (list_of_monitoring[count].get_date_temperature(i) != DEFAULT_TEMPERATURE)
                {
                    fout << list_days[list_of_monitoring[count].get_date_day() - 1] << "." << list_months[list_of_monitoring[count].get_date_month() - 1] << "." << list_of_monitoring[count].get_date_year() << "|" << list_hours[i] << ":00|" << list_of_monitoring[count].get_date_temperature(i) << " C";
                    fout << std::endl;
                    extra += 1;
                }

            }
            count += 1;
        }


        fout.close(); //Закрываем файл.
        if (extra != 0)
        {
            std::cout << "Observations are saved to a file." << std::endl;
        }
        else
        {
            std::cout << "The list of observations is empty." << std::endl;
        }
    }

    void read_from_file()
    {
        //Очистка старого списка наблюдений.
        for (size_t i = 0; i < 365; ++i)
        {
            list_of_monitoring[i].reset_date();
        }
        
        std::ifstream fin; //Создаём поток для чтения.
        fin.open("observations.txt"); //Открываем файл.

        int count = 0;
        if (fin.is_open()) //is_open если файл открыт, то возвращает true (иначе - false).
        {
            int day = -1, month = -1, year = -1, hour = -1;
            double temperature = DEFAULT_TEMPERATURE;
            std::string str_extra;
            while (fin.eof() != true && count < 365) //fin.eof() вернёт true, если будет попытка чтения за пределами конца файла(то есть пока не будет конец файла). Иначе false.
            {
                std::getline(fin, str_extra, '.'); //getline(<ПОТОК>, <СТРОКА, куда сохраняется>, <РАЗДЕЛИТЕЛЬ(символ), после которых прекращается чтение>).
                if (fin.eof() != true)
                {
                    day = std::stoi(str_extra); //Перевод в integer.
                    //std::cout << str_extra << ";" << day << std::endl;

                    std::getline(fin, str_extra, '.');
                    for (int j = 0; j < 12; ++j)
                    {
                        if (str_extra == list_months[j])
                        {
                            month = j + 1;
                            break;
                        }
                    }
                    //std::cout << str_extra << ";" << month << std::endl;

                    std::getline(fin, str_extra, '|');
                    year = std::stoi(str_extra);
                    //std::cout << str_extra << ";" << year << std::endl;

                    std::getline(fin, str_extra, ':');
                    hour = std::stoi(str_extra);
                    //std::cout << str_extra << ";" << hour << std::endl;

                    std::getline(fin, str_extra, '|');
                    std::getline(fin, str_extra, ' ');
                    temperature = std::stod(str_extra); //Перевод в double.
                    //std::cout << str_extra << ";" << temperature << std::endl;

                    std::getline(fin, str_extra, '\n');

                    //std::cout << "---" << std::endl;

                    set_observation(day, month, year, hour, temperature);
                    count += 1;
                }
            }
        }

        fin.close(); //Закрываем файл
        if (count != 0)
        {
            std::cout << "The observations were read." << std::endl;
        }
        else
        {
            std::cout << "The file is empty." << std::endl;
        }
    }

    void print_all_observations()
    {
        int count = 0, extra = 0;

        std::cout << "=====<ALL OBSERVATIONS>=====" << std::endl;

        while (count < 365)
        {
            for (int i = 0; i < 24; ++i)
            {
                if (list_of_monitoring[count].get_date_temperature(i) != DEFAULT_TEMPERATURE)
                {
                    std::cout << "<" << list_days[list_of_monitoring[count].get_date_day() - 1] << "." << list_months[list_of_monitoring[count].get_date_month() - 1] << "." << list_of_monitoring[count].get_date_year() << "> : <" << list_hours[i] << ":00> : <" << list_of_monitoring[count].get_date_temperature(i) << " C>";
                    std::cout << std::endl;
                    extra += 1;
                }

            }
            count += 1;
        }
        if (extra == 0)
        {
            std::cout << "The list of observations is empty." << std::endl;
        }
    }
};

int main()
{
    Thermometer test1;
    test1.get_initializing_date();
    test1.print_all_observations();

    std::cout << "----------" << std::endl;

    test1.set_initializing_date(23, 4, 2025, 9);
    test1.get_initializing_date();

    std::cout << "----------" << std::endl;

    test1.set_observation(19, 3, 2023, 5, -3); // Выход за пределы
    test1.set_observation(25, 6, 2025, 17, 24);
    test1.set_observation(7, 9, 2025, 11, 7);
    test1.set_observation(16, 9, 2025, 0, -4);
    test1.set_observation(18, 8, 2025, 8, 12);
    test1.set_observation(3, 1, 2026, 22, -19);
    test1.set_observation(22, 5, 2026, 8, 9); // Выход за пределы

    std::cout << "----------" << std::endl;

    test1.set_series_observations(9, 8, 2025);

    std::cout << "----------" << std::endl;

    test1.get_average_temperature_date(9, 8, 2025);
    test1.get_average_temperature_month(9, 2025);
    test1.get_average_temperature_all();

    std::cout << "----------" << std::endl;

    test1.get_average_daytime_or_nighttime_temperature_month(8, 2025, "day");
    test1.get_average_daytime_or_nighttime_temperature_month(8, 2025, "night");

    std::cout << "----------" << std::endl;

    test1.save_to_file();

    test1.set_initializing_date(1, 5, 2025, 14);
    test1.print_all_observations(); //Список пуст
    
    std::cout << "----------" << std::endl;

    test1.read_from_file();
    test1.print_all_observations();
}