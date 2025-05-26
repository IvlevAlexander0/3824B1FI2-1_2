#include <iostream>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <stdexcept>
// измения: 
// добавил максимально кол-во записей (100, для примера) и минимальную температуру
// добавил проверку на ввод ниже минимальной температуры (Set Observation)
// добавил проверку на ввод данных времени (is ValidDate для дня+месяца, отдельно для часов и отдельно для месяцев см ниже в комментариях int main()
// добавил проверку на ввод даты на первых наблюдений (isBeforeFirstObservationDate)
// изменил запись с 12 до 24 часов (начанию с 1го часа т.к 24=0 и это будет накладываться на последующие/предыдущие дни)
using namespace std; 

const int FIXED_YEAR = 2025;
const int MAX_OBSERVATIONS = 100;
const double ABSOLUTE_ZERO = -273.15;

struct DateTime {
    int day;
    int month;
    int hour;

    bool operator<(const DateTime& other) const {
        if (month != other.month) return month < other.month;
        if (day != other.day) return day < other.day;
        return hour < other.hour;
    }
};

class Thermometer {
private:
    DateTime observations[MAX_OBSERVATIONS];
    double temperatures[MAX_OBSERVATIONS];
    int count;

public:
    Thermometer() : count(0) {}

    void setObservation(int day, int month, int hour, double temperature) {
        if (count >= MAX_OBSERVATIONS) {
            throw runtime_error("Maximum number of observations reached");
        }
        if (temperature < ABSOLUTE_ZERO) {
            throw runtime_error("Temperature cannot be below absolute zero");
        }
        observations[count] = { day, month, hour };
        temperatures[count] = temperature;
        count++;
    }

    double getObservation(int day, int month, int hour) const {
        for (int i = 0; i < count; ++i) {
            if (observations[i].day == day && observations[i].month == month && observations[i].hour == hour) {
                return temperatures[i];
            }
        }
        throw runtime_error("Observation not found");
    }

    void saveToFile(const string& filename = "data.txt") const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("Error opening file to write");
        file << "Дата и время, Температура\n";
        for (int i = 0; i < count; ++i) {
            const DateTime& dt = observations[i];
            double temp = temperatures[i];
            file << dt.day << "/" << dt.month << "/" << FIXED_YEAR << " " << dt.hour << ":00,"
                << fixed << setprecision(2) << temp << "\n";
        }
        file.close();
    }

    void loadFromFile(const string& filename = "data.txt") {
        ifstream file(filename);
        if (!file.is_open()) throw runtime_error("Attention delete data.txt before next try!");
        string line;
        getline(file, line);
        while (getline(file, line)) {
            int day, month, hour;
            double temperature;
            if (sscanf_s(line.c_str(), "%d/%d/%d %d:00,%lf", &day, &month, &hour, &temperature) != 4) {
                throw runtime_error("Error while reading");
            }
            setObservation(day, month, hour, temperature);
        }
        file.close();
    }

    void getFirstObservationDate(int& day, int& month) const {
        if (count == 0) throw runtime_error("No observations");
        day = observations[0].day;
        month = observations[0].month;
    }


    bool isValidDate(int day, int month) const { 
        if (month < 1 || month > 12 || day < 1 || day > 31) return false;
        if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;
        if (month == 2) {
            if (day > 29) return false;
            if (day == 29 && !((FIXED_YEAR % 4 == 0 && FIXED_YEAR % 100 != 0) || (FIXED_YEAR % 400 == 0))) return false;
        }
        return true;
    }

    bool isBeforeFirstObservationDate(int day, int month) const { // проверка даты с началом наблюдений
        if (month < observations[0].month) return false;
        if (month = observations[0].month & day < observations[0].day) return false;
        return true;
    }

    bool isBeforeFirstObservationDate(int month) const { // перегрузка только для месяца
        if (month < observations[0].month) return false;
        return true;
    }

    void setSeriesObservations(int day, int month) {
        if (!isValidDate(day, month)) {
            throw runtime_error("Invalid date");
        }
        for (int hour = 1; hour <= 24; ++hour) { // теперь 24
            double temperature;

            cout << "Enter temperature for " << day << "/" << month << "/" << FIXED_YEAR << " " << hour << ":00: ";
            cin >> temperature;

            if (count > 0 && (observations[count - 1].day < day || (observations[count - 1].day == day && observations[count - 1].month < month))) {
                throw runtime_error("Cannot enter observations for a date earlier than the first observation");
            }

            setObservation(day, month, hour, temperature);
        }
    }

    double calculateAverageTemperature(int day, int month) const {
        double sum = 0;
        int countTemp = 0;
        for (int i = 0; i < count; ++i) {
            const DateTime& dt = observations[i];
            double temp = temperatures[i];
            if (dt.day == day && dt.month == month) {
                sum += temp;
                countTemp++;
            }
        }
        if (countTemp == 0) throw runtime_error("No observations for this date");
        return sum / countTemp;
    }

    double calculateMonthlyAverage(int month) const {
        double sum = 0;
        int countTemp = 0;
        for (int i = 0; i < count; ++i) {
            const DateTime& dt = observations[i];
            double temp = temperatures[i];
            if (dt.month == month) {
                sum += temp;
                countTemp++;
            }
        }
        if (countTemp == 0) throw runtime_error("No observations for this month");
        return sum / countTemp;
    }

    double calculateDailyOrNightlyAverage(int month, bool isDaytime) const {
        double sum = 0;
        int countTemp = 0;
        for (int i = 0; i < count; ++i) {
            const DateTime& dt = observations[i];
            double temp = temperatures[i];
            if (dt.month == month && ((isDaytime && dt.hour >= 6 && dt.hour < 18) || (!isDaytime && (dt.hour < 6 || dt.hour >= 18)))) {
                sum += temp;
                countTemp++;
            }
        }
        if (countTemp == 0) throw runtime_error("No observations for this month");
        return sum / countTemp;
    }
};

int main() {
    Thermometer thermometer;

    try {
        thermometer.loadFromFile();
    }
    catch (const runtime_error& e) {
        cout << e.what() << endl;
    }

    while (true) {
        cout << "\nMenu:\n"
            << "1 Show date and time of start observation\n"
            << "2 Add/change observation for day\n"
            << "3 Show temperature of observation\n"
            << "4 Enter all observations\n"
            << "5 Average temperature for date\n"
            << "6 Average temperature for month\n"
            << "7 Average day or night temperature for month\n"
            << "8 Save to file\n"
            << "9 EXIT\n"
            << "Choose num: ";

        int choice;
        cin >> choice;

        try {
            switch (choice) {
            case 1: {
                int firstDay, firstMonth;
                thermometer.getFirstObservationDate(firstDay, firstMonth);
                cout << "1st date of observations: " << firstDay << "/" << firstMonth << "/" << FIXED_YEAR << endl;
                break;
            }
            case 2: {
                int day, month, hour;
                double temperature;
                cout << "enter date (day month): ";
                cin >> day >> month;
                if (!thermometer.isValidDate(day, month) || !thermometer.isBeforeFirstObservationDate(day, month)) {
                    cout << "Invalid date or before first observation!" << endl;
                    break;
                }
                cout << "hour(0-24): ";
                cin >> hour;
                if (hour < 1 || hour > 24) { // решил не создавать метод, а обойтись просто if (по идее, затраты на обработку + - те же)
                    cout << "Invalid hour!" << endl;
                    break;
                }
                cout << "enter temperature: ";
                cin >> temperature;
                thermometer.setObservation(day, month, hour, temperature);
                break;
            }
            case 3: {
                int day, month, hour;
                cout << "enter date (day month): ";
                cin >> day >> month;
                if (!thermometer.isValidDate(day, month) || !thermometer.isBeforeFirstObservationDate(day, month)) {
                    cout << "Invalid date or before first observation!" << endl;
                    break;
                }
                cout << "hour(0-24): ";
                cin >> hour;
                cin >> hour;
                if (hour < 1 || hour > 24) { // решил не создавать метод, а обойтись просто if (по идее, затраты на обработку + - те же)
                    cout << "Invalid hour!" << endl;
                    break;
                }
                double temp = thermometer.getObservation(day, month, hour);
                cout << "temperature: " << temp << endl;
                break;
            }
            case 4: {
                int day, month;
                cout << "enter date (day month): ";
                cin >> day >> month;
                if (!thermometer.isValidDate(day, month) || !thermometer.isBeforeFirstObservationDate(day, month)) {
                    cout << "Invalid date or before first observation!" << endl;
                    break;
                }
                thermometer.setSeriesObservations(day, month);
                break;
            }
            case 5: {
                int day, month;
                cout << "enter date (day month): ";
                cin >> day >> month;
                if (!thermometer.isValidDate(day, month) || !thermometer.isBeforeFirstObservationDate(day, month)) {
                    cout << "Invalid date or before first observation!" << endl;
                    break;
                }
                double avgTemp = thermometer.calculateAverageTemperature(day, month);
                cout << "Average temperature: " << avgTemp << endl;
                break;
            }
            case 6: {
                int month;
                cout << "enter month: ";
                cin >> month;
                if (month < 1 || month > 12 || !thermometer.isBeforeFirstObservationDate(month)) { // также как и с hour решил не создавать метод или перегрузку на isValidDate для одной переменной и обошёлся простым if
                    cout << "Invalid date or before first observation!" << endl;
                    break;
                }
                double avgTemp = thermometer.calculateMonthlyAverage(month);
                cout << "Average temperature for month: " << avgTemp << endl;
                break;
            }
            case 7: {
                int month;
                bool isDaytime;
                cout << "enter month: ";
                cin >> month;
                if (month < 1 || month > 12 || !thermometer.isBeforeFirstObservationDate(month)) { // как и в case 6
                    cout << "Invalid date or before first observation!" << endl;
                    break;
                }
                cout << "day temperature? (1 - yes, 0 - no): ";
                cin >> isDaytime;
                double avgTemp = thermometer.calculateDailyOrNightlyAverage(month, isDaytime);
                cout << "Average temperature: " << avgTemp << endl;
                break;
            }
            case 8: {
                thermometer.saveToFile();
                cout << "File data.txt was created" << endl;
                break;
            }
            case 9:
                return 0;
            default:
                cout << "wrong option" << endl;
            }
        }
        catch (const runtime_error& e) {
            cout << e.what() << endl;
        }
    }

    return 0;
}