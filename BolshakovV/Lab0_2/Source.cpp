#include <iostream>
#include <cstring>
#include <iomanip>
#include <cmath>
#include <climits>

class TIME {

private:
	int hour;
	int minute;
	int second;

	void normal() {
		if (second < 0) {

			int total_seconds = minute * 60 + second;
			minute = total_seconds / 60;
			second = total_seconds % 60;

		}
		if (minute < 0) {

			int total_minutes = hour * 60 + minute;
			hour = total_minutes / 60;
			minute = total_minutes % 60;

		}
		if (minute == 0 && second < 0) {
			second = 0;
		}
		if (second >= 60) {
			minute += second / 60;
			second %= 60;
		}
		if (minute >= 60) {
			hour += minute / 60;
			minute %= 60;
		}
		if (hour >= 24) {
			hour = 0;
		}
		if (hour < 0) {
			hour = 0;
		}
	}

	int proverka(const std::string& str, int l_value, int r_value) {
		int chislo;
		int flag = 1;
		do {
			flag = 0;
			std::cout << str;
			std::cin >> chislo;
			if (std::cin.fail() || (chislo<l_value || chislo>r_value)) {
				std::cout << "Error. Please enter the correct value" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
				flag = 1;
			}
		} while (flag == 1);
		return chislo;
	}

public:
	TIME(int hour_a = 0, int minute_a = 0, int second_a = 0) {
		hour = hour_a;
		minute = minute_a;
		second = second_a;
	}

	void print() {
		std::cout << hour << " h " << minute << " m " << second << " s" << std::endl;
	}
	void set_the_time() {

		hour = proverka("Hour (0 - 23): ", 0, 23);
		minute = proverka("Minute (min = - (hour*60)): ", -(hour * 60), INT_MAX);
		second = proverka("Second (min = - (minute * 60)): ", -(minute * 60), INT_MAX);



		normal();
	}
	void shift() {
		int h, m, s;


		int b = -hour;
		int b1 = 23 - hour;

		h = proverka("Shift_hour (min = - hour, max = 23 - hour): ", b, b1);
		hour += h;

		int a = -(hour * 60);
		int a1 = 23 * 60 - hour * 60;
		m = proverka("Shift_minute (min = - (new_hour*60), max = 23*60 - new_hour*60) : ", a, a1);
		minute += m;
		s = proverka("Shift_second: ", INT_MIN, INT_MAX);
		second += s;


		normal();
	}
	void difference_time(TIME* time2) {
		int sett_time = hour * 3600 + minute * 60 + second;
		int sett_time2 = time2->hour * 3600 + time2->minute * 60 + time2->second;

		int diff = fabs(sett_time - sett_time2);
		int diff_hour = diff / 3600;
		int ost1 = (diff - diff_hour * 3600);
		int diff_minute = ost1 / 60;
		int diff_second = ost1 - diff_minute * 60;
		std::cout << "Time difference: " << diff_hour << " hour " << diff_minute << " minute " << diff_second << " second" << std::endl;
	}

};

int main() {
	TIME original;
	TIME t2;
	int h, m, s;

	int mode;

	int f2 = 0;

	do {
		std::cout << std::endl;
		std::cout << "Please select the operating mode of the program: " << std::endl;
		std::cout << "1 - set the time;" << std::endl;
		std::cout << "2 - find out the time;" << std::endl;
		std::cout << "3 - find out the difference between the set and preset time;" << std::endl;
		std::cout << "4 - shift the time by a preset offset" << std::endl;
		std::cout << "5 - end the program" << std::endl;
		std::cout << std::endl;

		int flag = 1;
		do {
			flag = 0;
			std::cin >> mode;
			if (std::cin.fail() || (mode < 1 || mode>5)) {
				std::cout << "Error. Please enter the correct value" << std::endl;
				std::cin.clear();
				while (std::cin.get() != '\n') {}
				flag = 1;
			}

		} while (flag == 1);

		switch (mode) {
		case 1:
			std::cout << "Please enter the time in the format: h hours, m minutes, s seconds." << std::endl;


			original.set_the_time();
			break;
		case 2:
			std::cout << "Time: " << std::endl;
			original.print();
			break;
		case 3:
			std::cout << "Please enter the time number 2 (enter the time in the format: h hours, m minutes, s seconds)" << std::endl;

			t2.set_the_time();
			original.difference_time(&t2);
			break;
		case 4:
			std::cout << "Please enter how much you want to change the time (enter the time in the format: h hours, m minutes, s seconds)" << std::endl;

			original.shift();
			break;
		case 5:
			f2 = 1;
			break;
		}
	} while (f2 == 0);

	return 0;
}