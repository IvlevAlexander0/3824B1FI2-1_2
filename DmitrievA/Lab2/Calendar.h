#pragma once
#include <ostream>
#include <string>
#include <iostream>

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
			if (cdate.year == UINT32_MAX) {
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
		while (cddate.months > 12) {
			cddate.months -= 12;
			if (cdate.year == UINT32_MAX) {
				std::cout << "Max year achived. returning default value" << std::endl;
				return Date();
			}
			cdate.year += 1;
		}
		while (-cddate.months > 12) {
			cddate.months += 12;
			if (cddate.years == 1) {
				std::cout << "Can't move to negative year. returning default value" << std::endl;
				return Date();
			}
			cdate.year -= 1;
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
				if (cdate.year == UINT32_MAX) {
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
			if (cdate.year == UINT32_MAX) {
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
		if (cdate.day + cddate.days > days[cdate.month - 1] || (cdate.month == 2 && cddate.days > 28 + is_year_leap(cdate.year))) {
			if (cdate.month == 12) {
				cdate.month = 1;
				if (cdate.year == UINT32_MAX) {
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
};

std::ostream& operator << (std::ostream& stream, const Date& date) {
	stream << (int)date.day << " " << months[date.month - 1] << " " << date.year;
	return stream;
}


class Event {
public:
	std::string name;
	Date date;
	Event() { name = ""; date = Date(); }
	Event(std::string name_, Date date_) : name{ name_ }, date{ date_ } {}
};

std::ostream& operator << (std::ostream& stream, const Event& event) {
	stream << "Event: " << event.name << ".\nPlanned on " << event.date;
	return stream;
}

class Calendar;

std::ostream& operator << (std::ostream& stream, const Calendar& calendar);

class Calendar {
	Event events[30];
	int count;
public:
	Calendar() { count = 0; }
	Calendar(Event events_[], size_t len) {
		for (int i = 0; i < len && i < 30; i++) {
			events[i] = events_[i];
		}
		count = len < 30 ? len : 30;
	}
	Calendar(const Calendar& calendar_) {
		for (int i = 0; i < calendar_.count; i++) {
			events[i] = calendar_.events[i];
		}
		count = calendar_.count;
	}
	void AddEvent(Event event) {
		if (count >= 30) {
			std::cout << "Not enouth capacyty in calendar" << std::endl;
			return;
		}
		events[count] = event;
		++count;
	}
	void AddEvent(std::string name, Date date) {
		AddEvent(Event(name, date));
	}
	void AddEvent(std::string name, char day = 1, char month = 1, int year = 1) {
		AddEvent(name, Date(day, month, year));
	}
	Event GetEvent(size_t index) {
		if (index > count - 1) {
			return Event();
		}
		return events[index];
	}
	Date GetDateOfEvent(size_t index) {
		if (index > count - 1) {
			return Date();
		}
		return events[index].date;
	}
	DeltaDate GetDistance(size_t index, const Date& date) {
		Date event_date = GetDateOfEvent(index);
		return event_date - date;
	}
	void CreateNewFromOld(size_t index, const DeltaDate& ddate) {
		Event old_event = GetEvent(index);
		Event event = Event(old_event.name, old_event.date + ddate);
		AddEvent(event);
	}
	friend std::ostream& operator << (std::ostream& stream, const Calendar& calendar);
};

std::ostream& operator << (std::ostream& stream, const Calendar& calendar) {
	for (int i = 0; i < calendar.count; i++) {
		stream << calendar.events[i] << std::endl;
	}
	return stream;
}
