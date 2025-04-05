#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class date {
public:
	int month;
	int day;
	int year;
	bool visoc;
	date() :
		month(1), day(1), year(2000), visoc(true) {
	};
	date(int month_, int day_, int year_) :
		month(), day(), year() {
		if (month_ < 1 || month_ > 12) {
			cout << "Invalid month. Setting to default (1, January)." << endl;
			month = 1;
		}
		else {
			month = month_;
		}
		if (year_ < 0){
			cout << "Invalid year. Setting to default (2000 year)." << endl;
			year = 2000;
			visoc = true;
		} 
		else {
			year = year_;
			if (year % 4 == 0) {
				visoc = true;
			}
			else
			{
				visoc = false;
			}
		}
		if (day_ < 1 || day_ > 31) {
			cout << "Invalid day. Setting to default (1 day of month)." << endl;
			day = 1;
		}
		else
		{
			if (month == 2) {
				if (visoc && day_ > 29) {
					cout << "Invalid day. Setting to default (1 day of month)." << endl;
					day = 1;
				}
				else
				{
					if (day > 28) {
						cout << "Invalid day. Setting to default (1 day of month)." << endl;
						day = 1;
					}
				}
			}
			else {
				if ((month % 2 == 0) && (day > 30)) {
					cout << "Invalid day. Setting to default (1 day of month)." << endl;
					day = 1;
				}
				else {
					day = day_;
				}
			}
		}
	};
	bool operator<(const date& Date) const {
		if (year < Date.year) {
			true;
		}
		else {
			if (year == Date.year) {
				if (month < Date.month) {
					return true;
				}
				else {
					if (month == Date.month) {
						if (day < Date.day) {
							return true;
						}
						else {
							return false;
						}
					}
					else {
						return false;
					}
				}
			}
			else {
				return false;
			}
		}
	}
	bool operator==(const date& Date) {
		if (year == Date.year) {
			if (month == Date.year) {
				if (day == Date.day) {
					return true;
				}
			}
		}
		return false;
	}
	~date() {};
};
ostream& operator<<(ostream& stream, const date& Date) {
	if (Date.month < 10) {
		stream << Date.day << ".0" << Date.month << "." << Date.year << "." << endl;
	}
	else {
		stream << Date.day << "." << Date.month << "." << Date.year << "." << endl;
	}
	return stream;
}
struct returning
{
	int stepss;
	date dates;
};
ostream& operator<<(ostream& stream, returning returni) {
	stream << returni.stepss << " steps were made on " << returni.dates << endl;
	return stream;
}
int get_month_code(date wh) {
	if (wh.visoc) {
		if (wh.month == 1 || wh.month == 4 || wh.month == 7) {
			return 0;
		}
		if (wh.month == 2 || wh.month == 8) {
			return 3;
		}
		if (wh.month == 3 || wh.month == 11) {
			return 4;
		}
		if (wh.month == 5) {
			return 2;
		}
		if (wh.month == 6) {
			return 5;
		}
		if (wh.month == 9 || wh.month == 12) {
			return 6;
		}
		if (wh.month == 10) {
			return 1;
		}
	}
	else {
		if (wh.month == 4 || wh.month == 7) {
			return 0;
		}
		if (wh.month == 8) {
			return 3;
		}
		if (wh.month == 3 || wh.month == 11 || wh.month == 2) {
			return 4;
		}
		if (wh.month == 5) {
			return 2;
		}
		if (wh.month == 6) {
			return 5;
		}
		if (wh.month == 9 || wh.month == 12) {
			return 6;
		}
		if (wh.month == 10 || wh.month == 1) {
			return 1;
		}
	}
}
int get_year_code(date wh) {
	int code = floor((wh.year % 100) / 4) + wh.year % 100;
	return code + 6;
}
int get_day_of_week(date wh) {
	int day, codem, codey;
	codem = get_month_code(wh);
	codey = get_year_code(wh);
	day = wh.day;
	int day_w = day + codem + codey;
	day_w = (day_w % 7 + 6) % 7;
	if (day_w == 0) {
		return 7;
	}
	else {
		return day_w; //Работает для дней недели с 2000 до 2100 годов.
	}
}

class calculation {
public:
	date when;
	int hour_inter_s;
	int minute_inter_s;
	int hour_inter_e;
	int minute_inter_e;
	int duration_minutes;
	int steps;
	calculation() :
		when(), hour_inter_s(-1), minute_inter_s(-1), hour_inter_e(-1), minute_inter_e(-1), duration_minutes(-1), steps(0) {
	};
	calculation(date when_) :
		when(when_), duration_minutes(-1), steps(0) {
		while (duration_minutes < 0) {
			hour_inter_e = -1;
			hour_inter_s = -1;
			minute_inter_e = -1;
			minute_inter_s = -1;
			while (hour_inter_s < 0 || hour_inter_s > 23) {
				cout << "Enter the starting hour: ";
				cin >> hour_inter_s;
				if (hour_inter_s < 0 || hour_inter_s > 23) {
					cout << "Invalid hour. Enter again." << endl;
				}
			}
			while (minute_inter_s < 0 || minute_inter_s > 59) {
				cout << "Enter the starting minute: ";
				cin >> minute_inter_s;
				if (minute_inter_s < 0 || minute_inter_s > 59) {
					cout << "Invalid minute. Enter again." << endl;
				}
			}
			while (hour_inter_e < 0 || hour_inter_e > 23) {
				cout << "Enter the ending hour: ";
				cin >> hour_inter_e;
				if (hour_inter_e < 0 || hour_inter_e > 23) {
					cout << "Invalid hour. Enter again." << endl;
				}
			}
			while (minute_inter_e < 0 || minute_inter_e > 59) {
				cout << "Enter the ending minute: ";
				cin >> minute_inter_e;
				if (minute_inter_e < 0 || minute_inter_e > 59) {
					cout << "Invalid minute. Enter again." << endl;
				}
			}
			duration_minutes = (hour_inter_e * 60 + minute_inter_e) - hour_inter_s * 60 - minute_inter_s;
			if (duration_minutes < 0) {
				cout << "Invalid interval. Input times again." << endl;
			}
		};
		steps = duration_minutes * 105; //Беру среднее значение 105 шагов в минуту.
	};
	calculation(date when_, int hour_inter_e_, int hour_inter_s_, int minute_inter_e_, int minute_inter_s_) :
		when(when_), duration_minutes(0), steps(0) {
		hour_inter_e = -1;
		hour_inter_s = -1;
		minute_inter_e = -1;
		minute_inter_s = -1;
		if (hour_inter_s_ < 0 || hour_inter_s_ > 23) {
			cout << "Invalid starting hour. Setting to default (0)." << endl;
			hour_inter_s = 0;
		}
		else {
			hour_inter_s = hour_inter_s_;
		}
		if (minute_inter_s_ < 0 || minute_inter_s_ > 59) {
			cout << "Invalid starting minute. Setting to default (0)." << endl;
			minute_inter_s = 0;
		}
		else {
			minute_inter_s = minute_inter_s_;
		}
		if (hour_inter_e_ < 0 || hour_inter_e_ > 23 || hour_inter_e_ < hour_inter_s) {
			cout << "Invalid ending hour. Setting to starting one." << endl;
			hour_inter_e = hour_inter_s;
		}
		else {
			hour_inter_e = hour_inter_e_;
		}
		if (minute_inter_e_ < 0 || minute_inter_e_ > 59 || ((hour_inter_e == hour_inter_s) && (minute_inter_e_ < minute_inter_s))) {
			cout << "Invalid ending minute. Setting to starting one." << endl;
			minute_inter_e = minute_inter_s;
		}
		else {
			minute_inter_e = minute_inter_e_;
		}
		duration_minutes = hour_inter_e * 60 + minute_inter_e - (hour_inter_s * 60 + minute_inter_s);
		steps = duration_minutes * 105;
	}
	date get_date() {
		return when;
	}
	int get_steps() {
		return steps;
	}
	~calculation() {};
};
ostream& operator<<(ostream& stream, calculation Calculation) {
	stream << "A calculation made on: " << Calculation.when;
	if (Calculation.minute_inter_s < 10) {
		stream << "Starting time - " << Calculation.hour_inter_s << ":0" << Calculation.minute_inter_s << endl;
	}
	else {
		stream << "Starting time - " << Calculation.hour_inter_s << ":" << Calculation.minute_inter_s << endl;
	}
	if (Calculation.minute_inter_e < 10) {
		stream << "Ending time - " << Calculation.hour_inter_e << ":0" << Calculation.minute_inter_e << endl;
	}
	else {
		stream << "Ending time - " << Calculation.hour_inter_e << ":" << Calculation.minute_inter_e << endl;
	}
	stream << "Steps made that day: " << Calculation.steps << "." << endl;
	stream << "--------" << endl;
	return stream;
}
class step_o_meter {
public:
	date start_of_calc;
	calculation* calcs = nullptr;
	int n = 0;
	step_o_meter() :
		start_of_calc(), calcs(), n() {
	};
	step_o_meter(date date_) :
		start_of_calc(date_), calcs(nullptr), n() {
	};
	void set_date_start(date Date) {
		start_of_calc = Date;
	}
	date get_date_start() {
		return start_of_calc;
	}
	void set_calc(date when_) {
		if (when_<start_of_calc) {
			cout << "Invalid date. Start of calculations was later than this date." << endl;
		}
		else {
			if (calcs != nullptr) {
				bool exist = false;
				for (int i = 0; i < n; i++) {
					if (calcs[i].when == when_) {
						cout << "There's already existing calculation. Rewrite? (1 for yes, 0 for no)." << endl;
						bool choice;
						cin >> choice;
						if (choice) {
							calcs[i] = calculation(when_);
						}
						exist = true;
					}
				}
				if (not(exist)) {
					calculation* new_calcs = new calculation[++n];
					for (int i = 0; i < n; i++) {
						if (i == n - 1) {
							new_calcs[i] = calculation(when_);
						}
						else {
							new_calcs[i] = calcs[i];
						}
					}
					delete[] calcs;
					calcs = new_calcs;
				}
			}
			else {
				calculation* new_calcs = new calculation[++n];
				for (int i = 0; i < n; i++) {
					if (i == n - 1) {
						new_calcs[i] = calculation(when_);
					}
					else {
						new_calcs[i] = calcs[i];
					}
				}
				delete[] calcs;
				calcs = new_calcs;
			}
		}
	}
	void set_calc_file(date when_, int hour_e, int hour_s, int min_e, int min_s) {
		if (when_ < start_of_calc) {
			cout << "Invalid date. Start of calculations was later than this date." << endl;
		}
		else {
			if (calcs != nullptr) {
				bool exist = false;
				for (int i = 0; i < n; i++) {
					if (calcs[i].when == when_) {
						cout << "There's already existing calculation. Rewrite? (1 for yes, 0 for no)." << endl;
						bool choice;
						cin >> choice;
						if (choice) {
							calcs[i] = calculation(when_, hour_e, hour_s, min_e, min_s);
						}
						exist = true;
					}
				}
				if (not(exist)) {
					calculation* new_calcs = new calculation[++n];
					for (int i = 0; i < n; i++) {
						if (i == n - 1) {
							new_calcs[i] = calculation(when_, hour_e, hour_s, min_e, min_s);
						}
						else {
							new_calcs[i] = calcs[i];
						}
					}
					delete[] calcs;
					calcs = new_calcs;
				}
				
			}
			else {
				calculation* new_calcs = new calculation[++n];
				for (int i = 0; i < n; i++) {
					if (i == n - 1) {
						new_calcs[i] = calculation(when_, hour_e, hour_s, min_e, min_s);
					}
				}
				delete[] calcs;
				calcs = new_calcs;
			}
		}
	}
	calculation get_calc(date when_) {
		bool flag = true;
		for (int i = 0; i < n; i++) {
			if (calcs[i].when == when_) {
				cout << calcs[i];
				flag = false;
			}
		}
		if (flag) {
			cout << "No calcs on this date." << endl;
			throw invalid_argument("Bad date.");
		}
	}
	double get_mid_steps_on_month(int month_) {
		int count = 0;
		int over_steps = 0;
		for (int i = 0; i < n; i++) {
			if (calcs[i].when.month == month_) {
				count++;
				over_steps += calcs[i].steps;
			}
		}
		return over_steps / count;
	}
	double get_mid_steps() {
		int count = 0;
		int over_steps = 0;
		for (int i = 0; i < n; i++) {
			over_steps += calcs[i].steps;
			cout << over_steps << "||" << calcs[i].steps << endl;
			count++;
		}
		return over_steps / count;
	}
	double get_mid_steps_on_weekday(int weekday) {
		int count = 0;
		int over_steps = 0;
		if (weekday < 1 || weekday > 7) {
			cout << "Invalid week of day. Setting to 0." << endl;
			return 0;
		}
		else {
			for (int i = 0; i < n; i++) {
				if (weekday == get_day_of_week(calcs[i].when)) {
					count++;
					over_steps += calcs[i].steps;
				}
			}
			return over_steps / count;
		}
	}
	returning max_on_month(int month) {
		int max_one = 0;
		date ret_date;
		for (int i = 0; i < n; i++) {
			if (calcs[i].when.month == month) {
				if (calcs[i].steps >= max_one) {
					max_one = calcs[i].steps;
					ret_date = calcs[i].when;
				}
			}
		}
		return returning{ max_one, ret_date };
	}
	returning max_on_all() {
		int max_one = 0;
		date ret_date;
		for (int i = 0; i < n; i++) {
			if (calcs[i].steps >= max_one) {
				max_one = calcs[i].steps;
				ret_date = calcs[i].when;
			}
		}
		return returning{ max_one, ret_date };
	}
	void save_in_file(string filename) {
		ofstream out;
		out.open(filename);
		if (out.is_open()) {
			for (int i = 0; i < n; i++) {
				out << calcs[i] << endl;
			}
		}
		else {
			cout << "File is not open." << endl;
		}
		out.close();
	}
	void read_file(string filename) {
		ifstream in;
		in.open(filename);
		string num;
		string num_1;
		int hour_e = 0;
		int hour_s = 0;
		int minute_e = 0;
		int minute_s = 0;
		int month = 0;
		int day = 0;
		int year = 0;
		int count = 0;
		date dates;
		if (in.is_open()) {
			while (in >> num) {
				++count;
				if (count == 5) {
					int itoe = 0;
					int count_1 = 0;
					int length = int(num.length());
					for (int i = 0; i < length; i++) {
						if (num[i] == '.') {
							if (count_1 == 0) {
								day = stoi(num.substr(itoe, i));
								itoe = i + 1;
								count_1++;
							}
							else {
								if (count_1 == 1) {
									month = stoi(num.substr(itoe, i-itoe));
									count_1++;
									itoe = i + 1;
								}
								else {
									year = stoi(num.substr(itoe, i - itoe));
									dates = date(month, day, year);
								}
							}
						}
					}
				}
				if (count == 9) {
					int length = int(num.length());
					for (int i = 0; i < length; i++) {
						if (num[i] == ':') {
							hour_s = stoi(num.substr(0, i));
							minute_s = stoi(num.substr(++i, length-i));
							break;
						}
					}
				}
				if (count == 13) {
					int length = int(num.length());
					for (int i = 0; i < length; i++) {
						if (num[i] == ':') {
							hour_e = stoi(num.substr(0, i));
							minute_e = stoi(num.substr(++i, length - i));
							break;
						}
					}
				}
				if (num == "--------") {
					count = 0;
					set_calc_file(dates, hour_e, hour_s, minute_e, minute_s);
					cout << calculation(dates, hour_e, hour_s, minute_e, minute_s);
				}
			}
		}
		else {
			cout << "File is not open." << endl;
		}
		in.close();
	}
	~step_o_meter() {
		delete[] calcs;
	};
};

int main() {
	string filename = "steps.txt";
	date start(3, 10, 2014);
	date another(3, 11, 2014);
	step_o_meter stepings(start);
	/*stepings.set_calc(start);
	stepings.save_in_file(filename);
	stepings.set_calc(another);
	stepings.save_in_file(filename);*/
	stepings.read_file(filename);
	cout << stepings.get_mid_steps() << endl;
	cout << stepings.get_mid_steps_on_weekday(7) << endl;
	cout << stepings.max_on_all();

}