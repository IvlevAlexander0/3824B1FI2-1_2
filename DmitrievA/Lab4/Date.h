#pragma once
#include <ostream>
#include <string>
#include <limits>
#include <iostream>
#include <string>

using std::string;
using std::to_string;

char months[12][12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November","December" };

enum Months {
	January,
	February,
	March,
	April,
	May,
	June,
	july,
	August,
	September,
	October,
	November,
	December
};

char days[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };

bool is_year_leap(unsigned int year) {
	return year % 4 == 0 && (year % 100 != 0 || year % 400 == 0);
}

class DeltaDate {
public:
	int days, months, years;
	DeltaDate() { days = 0; months = 0; years = 0; }
	DeltaDate(int days_, int months_, int years_) : days{ days_ }, months{ months_ }, years{ years_ } {}

};
std::ostream& operator << (std::ostream& stream, const DeltaDate& ddate) {
	stream << ddate.days << " " << ddate.months << " " << ddate.years;
	return stream;
}

class Date;

std::ostream& operator << (std::ostream& stream, const Date& date);

class Date {
	char day, month; // month from 1 to 12
	unsigned int year;
public:
	Date() { day = 1; month = 1; year = 1; }
	Date(char day_, char month_, unsigned int year_) : day{ day_ }, month{ month_ }, year{ year_ } {
		if (month < 1 || month > 12 || day_ < 1 || (month == 2 && day_ > 28 + is_year_leap(year_)) || day_ > days[month - 1]) {
			std::cout << "wrong day or month. Set default data";
			day = 1; month = 1; year = 1;
			return;
		}
		day = day_;
		month = month_;
		year = year_;
	}
	Date(const Date& date_) : day{ date_.day }, month{ date_.month }, year{ date_.year } {}
	friend std::ostream& operator << (std::ostream& stream, const Date& date);
	Date operator +(const DeltaDate& ddate) {
		Date cdate = Date(*this);
		DeltaDate cddate = DeltaDate(ddate);
		if (cddate.years < 0 && cdate.year < -cddate.years) {
			std::cout << "Can't move to negative year. returning default value" << std::endl;
			return Date();
		}
		cdate.year += cddate.years;
		while (cddate.days > 365 + is_year_leap(cdate.year)) {
			cddate.days -= 365 + is_year_leap(cdate.year);
			if (cdate.year == UINT_MAX) {
				std::cout << "Max year achived. returning default value" << std::endl;
				return Date();
			}
			cdate.year += 1;
		}
		while (-cddate.days > 365 + is_year_leap(cdate.year)) {
			cddate.days += 365 + is_year_leap(cdate.year);
			if (cddate.years == 1) {
				std::cout << "Can't move to negative year. returning default value" << std::endl;
				return Date();
			}
			cdate.year -= 1;
		}
		if (cddate.months > 12) {
			if (UINT_MAX - (cddate.months / 12) < cdate.year) {
				std::cout << "Max year achived. returning default value" << std::endl;
				return Date();
			}
			cdate.year += (cddate.months / 12);
			cddate.months = cddate.months % 12;
		}
		if (-cddate.months > 12) {
			if (cddate.months / 12 > cddate.years) {
				std::cout << "Can't move to negative year. returning default value" << std::endl;
				return Date();
			}
			cdate.year -= cddate.months / 12;
			cddate.months = -((-cddate.months) % 12);
		}
		while (cddate.days > days[cdate.month - 1] || (cdate.month == 2 && cddate.days > 28 + is_year_leap(cdate.year))) {
			if (cdate.month == 2) {
				cddate.days -= 28 + is_year_leap(cdate.year);
			}
			else {
				cddate.days -= days[cdate.month - 1];
			}
			if (cdate.month == 12) {
				cdate.month = 1;
				if (cdate.year == UINT_MAX) {
					std::cout << "Max year achived. returning default value" << std::endl;
					return Date();
				}
				cdate.year += 1;
			}
			else {
				cdate.month += 1;
			}
		}
		while (-cddate.days > days[cdate.month - 1] || (cdate.month == 2 && -cddate.days > 28 + is_year_leap(cdate.year))) {
			if (cdate.month == 2) {
				cddate.days += 28 + is_year_leap(cdate.year);
			}
			else {
				cddate.days += days[cdate.month - 1];
			}
			if (cdate.month == 1) {
				cdate.month = 12;
				if (cddate.years == 1) {
					std::cout << "Can't move to negative year. returning default value" << std::endl;
					return Date();
				}
				cdate.year -= 1;
			}
			else {
				cdate.month -= 1;
			}
		}
		if (cdate.month + cddate.months > 12) {
			if (cdate.year == UINT_MAX) {
				std::cout << "Max year achived. returning default value" << std::endl;
				return Date();
			}
			++cdate.year;
			cdate.month = (cdate.month + cddate.months) % 12;
		}
		else if (cdate.month + cddate.months < 1) {
			if (cddate.years == 1) {
				std::cout << "Can't move to negative year. returning default value" << std::endl;
				return Date();
			}
			--cdate.year;
			cdate.month = 12 - (cdate.month + cddate.months);
		}
		else {
			cdate.month += cddate.months;
		}
		if (((cdate.day + cddate.days) > days[cdate.month - 1]) || (cdate.month == 2 && cddate.days > 28 + is_year_leap(cdate.year))) {
			if (cdate.month == 12) {
				cdate.month = 1;
				if (cdate.year == UINT_MAX) {
					std::cout << "Max year achived. returning default value" << std::endl;
					return Date();
				}
				++cdate.year;
			}
			else {
				++cdate.month;
				if (cdate.month == 2) {
					cdate.day = 28 + is_year_leap(cdate.year) + cdate.day + cddate.days;
				}
			}
		}
		else if (cdate.day + cddate.days < 1) {
			if (cdate.month == 1) {
				if (cddate.years == 1) {
					std::cout << "Can't move to negative year. returning default value" << std::endl;
					return Date();
				}
				--cdate.year;
				cdate.month = 12;
				cdate.day = 31 + cdate.day + cddate.days;
			}
			else {
				--cdate.month;
				if (cdate.month == 2) {
					cdate.day = 28 + is_year_leap(cdate.year) + cdate.day + cddate.days;
				}
			}

		}
		else {
			cdate.day = cddate.days + cdate.day;
		}
		return cdate;
	}
	DeltaDate operator - (const Date& date) {
		return DeltaDate(day - date.day, month - date.month, year - date.year);
	}
	Date(string s) {
		size_t num = 0;
		int f = 1;
		for (char i : s) {
			if (i == '.') {
				switch (f)
				{
				case 1:
					year = num;
					num = 0;
					f = 2;
					break;
				case 2:
					month = num;
					num = 0;
					f = 3;
					break;
				}
			}
			else {
				num *= 10;
				num += i - '0';
			}
		}
		day = num;
	}
	bool operator < (Date d) const {
		if (year != d.year) {
			return year < d.year;
		}
		if (month != d.month) {
			return month < d.month;
		}
		return day < d.day;
	}
	string to_file() {
		string s;
		s.append(to_string(year));
		s.append(".");
		s.append(to_string(month));
		s.append(".");
		s.append(to_string(day));
		return s;
	}
	bool operator == (const Date& d2) const {
		return year == d2.year && month == d2.month && day == d2.day;
	}
};

std::ostream& operator << (std::ostream& stream, const Date& date) {
	stream << (int)date.day << " " << months[date.month - 1] << " " << date.year;
	return stream;
}
