#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <iomanip>
#include <string>
#include <utility>
#include <stdexcept>

using namespace std;

const int FIXED_YEAR = 2025;

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
    map<DateTime, double> observations;

public:
    void setObservation(int day, int month, int hour, double temperature) {
        DateTime dt = { day, month, hour };
        observations[dt] = temperature;
    }

    double getObservation(int day, int month, int hour) const {
        DateTime dt = { day, month, hour };
        auto it = observations.find(dt);
        if (it != observations.end()) {
            return it->second;
        }
        else {
            throw runtime_error("error not found obs");
        }
    }

    void saveToFile(const string& filename = "data.txt") const {
        ofstream file(filename);
        if (!file.is_open()) throw runtime_error("error not open file to write");

        file << "Дата и время, Температура\n";
        for (auto it = observations.begin(); it != observations.end(); ++it) {
            const DateTime& dt = it->first;
            double temp = it->second;
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
                throw runtime_error("error while reading");
            }
            setObservation(day, month, hour, temperature);
        }

        file.close();
    }

    pair<int, int> getFirstObservationDate() const {
        if (observations.empty()) throw runtime_error("No obs");
        auto it = observations.begin();
        return { it->first.day, it->first.month };
    }

    void setSeriesObservations(int day, int month) {
        for (int hour = 1; hour <= 12; ++hour) {
            double temperature;
            cout << "Enter temperature for " << day << "/" << month << "/" << FIXED_YEAR << " " << hour << ":00: ";
            cin >> temperature;
            setObservation(day, month, hour, temperature);
        }
    }

    double calculateAverageTemperature(int day, int month) const {
        double sum = 0;
        int count = 0;

        for (auto it = observations.begin(); it != observations.end(); ++it) {
            const DateTime& dt = it->first;
            double temp = it->second;
            if (dt.day == day && dt.month == month) {
                sum += temp;
                count++;
            }
        }

        if (count == 0) throw runtime_error("net nabludeniy for date");
        return sum / count;
    }

    double calculateMonthlyAverage(int month) const {
        double sum = 0;
        int count = 0;

        for (auto it = observations.begin(); it != observations.end(); ++it) {
            const DateTime& dt = it->first;
            double temp = it->second;
            if (dt.month == month) {
                sum += temp;
                count++;
            }
        }

        if (count == 0) throw runtime_error("net nabludeniy for month");
        return sum / count;
    }

    double calculateDailyOrNightlyAverage(int month, bool isDaytime) const {
        double sum = 0;
        int count = 0;
        for (auto it = observations.begin(); it != observations.end(); ++it) {
            const DateTime& dt = it->first;
            double temp = it->second;
            if (dt.month == month && ((isDaytime && dt.hour >= 6 && dt.hour < 18) || (!isDaytime && (dt.hour < 6 || dt.hour >= 18)))) {
                sum += temp;
                count++;
            }
        }

        if (count == 0) throw runtime_error("net nabludeniy for month");
        return sum / count;
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
        cout << "\nMenu:\n";
        cout << "1 Show date and time of start observation\n";
        cout << "2 Add/change observation for day\n";
        cout << "3 Show temperature of observation\n";
        cout << "4 Enter all observations\n";
        cout << "5 Average temperature for date\n";
        cout << "6 Average temperature for month\n";
        cout << "7 Average day or night temperature for month\n";
        cout << "8 Save to file\n";
        cout << "9 EXIT\n";

        int choice;
        cin >> choice;

        try {
            switch (choice) {
            case 1: {
                pair<int, int> firstDate = thermometer.getFirstObservationDate();
                cout << "1st date of observations: " << firstDate.first << "/" << firstDate.second << "/" << FIXED_YEAR << endl;
                break;
            }
            case 2: {
                int day, month, hour;
                double temperature;
                cout << "enter date (day month): ";
                cin >> day >> month;
                cout << "hour(1-12): ";
                cin >> hour;
                cout << "enter temperature: ";
                cin >> temperature;
                thermometer.setObservation(day, month, hour, temperature);
                break;
            }
            case 3: {
                int day, month, hour;
                cout << "enter date (day month): ";
                cin >> day >> month;
                cout << "hour(1-12): ";
                cin >> hour;
                double temp = thermometer.getObservation(day, month, hour);
                cout << "temperature: " << temp << endl;
                break;
            }
            case 4: {
                int day, month;
                cout << "enter date (day month): ";
                cin >> day >> month;
                thermometer.setSeriesObservations(day, month);
                break;
            }
            case 5: {
                int day, month;
                cout << "enter date (day month): ";
                cin >> day >> month;
                double avgTemp = thermometer.calculateAverageTemperature(day, month);
                cout << "Average temperature: " << avgTemp << endl;
                break;
            }
            case 6: {
                int month;
                cout << "enter month: ";
                cin >> month;
                double avgTemp = thermometer.calculateMonthlyAverage(month);
                cout << "Average temperature for month: " << avgTemp << endl;
                break;
            }
            case 7: {
                int month;
                bool isDaytime;
                cout << "enter month: ";
                cin >> month;
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