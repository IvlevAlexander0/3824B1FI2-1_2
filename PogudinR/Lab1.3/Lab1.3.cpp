#include <iostream>
#include <iomanip>
using namespace std;

class Time {
private:
    int hours, minutes, seconds;

    void normalize() {
        if (seconds >= 60) {
            minutes += seconds / 60;
            seconds %= 60;
        }
        else if (seconds < 0) {
            minutes -= (abs(seconds) + 59) / 60;
            seconds = (seconds % 60 + 60) % 60;
        }
        if (minutes >= 60) {
            hours += minutes / 60;
            minutes %= 60;
        }
        else if (minutes < 0) {
            hours -= (abs(minutes) + 59) / 60;
            minutes = (minutes % 60 + 60) % 60;
        }
        hours = (hours % 24 + 24) % 24;
    }

public:
    Time(int h = 0, int m = 0, int s = 0) {
        if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
            cout << "Error: Invalid time values! Setting to default (00:00:00)." << endl;
            hours = 0; minutes = 0; seconds = 0;
        }
        else {
            hours = h;
            minutes = m;
            seconds = s;
            normalize();
        }
    }

    void setTime(int h, int m, int s) {
        if (h < 0 || h > 23 || m < 0 || m > 59 || s < 0 || s > 59) {
            cout << "Error: Invalid time values!" << endl;
            return;
        }
        hours = h;
        minutes = m;
        seconds = s;
        normalize();
    }

    void getTime() const {
        cout << setfill('0') << setw(2) << hours << ":"
            << setw(2) << minutes << ":"
            << setw(2) << seconds << endl;
    }

    Time difference(const Time& other) const {
        int totalSec1 = hours * 3600 + minutes * 60 + seconds;
        int totalSec2 = other.hours * 3600 + other.minutes * 60 + other.seconds;
        int diff = abs(totalSec1 - totalSec2);
        return Time(diff / 3600, (diff % 3600) / 60, diff % 60);
    }

    void shift(int h, int m, int s) {
        hours += h;
        minutes += m;
        seconds += s;
        normalize();
    }

    void display() const {
        getTime();
    }
};

int main() {
    int h, m, s;

    cout << "Enter time 1 (hours minutes seconds): ";
    cin >> h >> m >> s;
    Time t1(h, m, s);

    cout << "Enter time 2 (hours minutes seconds): ";
    cin >> h >> m >> s;
    Time t2(h, m, s);

    cout << "Initial Time 1: ";
    t1.display();
    cout << "Initial Time 2: ";
    t2.display();

    Time diff = t1.difference(t2);
    cout << "Difference: ";
    diff.display();

    cout << "Enter time shift (hours minutes seconds): ";
    cin >> h >> m >> s;
    t1.shift(h, m, s);
    cout << "Time 1 after shift: ";
    t1.display();

    return 0;
}