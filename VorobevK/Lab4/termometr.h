#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <fstream>


using std;


char months[12][12] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
int days[12] = { 0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334 };

class DateTime {
public:
	int unit;
	DateTime() { unit = 0; }
	DateTime(int unit_) : unit{ unit_ } {}
	DateTime(int hour, int day, int month) {
		unit = hour + day * 24 + days[month - 1] * 24;
	}
	int month() {
		int month = 12;
		for (int i = 0; i < 12; i++) {
			if (days[i] >= unit / 24) {
				month = i;
				break;
			}
		}
		return month;
	}
	int day() {
		return (unit - days[month() - 1]*24) / 24;
	}
	int hour() {
		return unit % 24;
	}
};
bool operator < (DateTime dt1, DateTime dt2) {
	return dt1.unit < dt2.unit;
}

bool operator == (DateTime dt1, DateTime dt2) {
	return dt1.unit == dt2.unit;
}

ostream& operator << (ostream& out, DateTime date_time) {
	int month = date_time.month();
	int day = date_time.day();
	int hour = date_time.unit % 24;
	out <<hour<<' ' << day << ' ' << months[month - 1];
	return out;
}

class Record {
public:
	int temperature;
	DateTime date_time;
	Record() : temperature{0}, date_time{ 0 } {}
	Record(DateTime dt_, int t = 0) :date_time{dt_}, temperature{t} {}
};

class termometr {
	vector<Record> records;
	DateTime start_dt;
	int lower_bound(Record record) {
		int r = records.size() - 1;
		int l = 0;
		int t = (l + r) / 2;
		while (l <= r) {
			if (records[t].date_time < record.date_time) {
				l = t + 1;
			}
			else if (record.date_time < records[t].date_time) {
				r = t - 1;
			}
			else {
				return t;
			}
			t = (l + r) / 2;
		}
		return t;
	}
	int binsearch(Record record) {
		int lb = lower_bound(record); 
		if (lb > 0 && lb < records.size() && records[lb].date_time == record.date_time)
			return lb;
		else
			return -1;
	}
public:
	termometr() {}
	void set_start_dt(DateTime dt) {
		start_dt = dt;
	}
	DateTime get_start_dt() {
		return start_dt;
	}
	void set_record(Record record) {
		if (records.size() == 0) {
			records.push_back(record);
		}
		else {
			int lb = lower_bound(record);
			if (lb > 0 && lb < records.size() && records[lb].date_time == record.date_time)
				records[lb] = record;
			else
				records.insert(records.begin() + lb+1, record);
		}
	}
	int get_tempreture() {
		int ind = binsearch(Record(start_dt));

		if (ind != -1) {
			return records[ind].temperature;
		}
		else {
			throw "Not registered record at this time";
		}
	}
	void set_series_of_records(vector<int> temperatures) {
		for (int i = 0; start_dt.unit +i < 365*24 && i < temperatures.size(); i++) {
			set_record(Record(DateTime(start_dt.unit+i), temperatures[i]));
		}
	}
	double get_average_temperature_for_day() {
		int sum = 0;
		int count;
		DateTime start_day = DateTime(0, start_dt.day(), start_dt.month());
		int start = lower_bound(Record(DateTime(0, start_dt.day(), start_dt.month())));
		int end = lower_bound(Record(DateTime(0, start_dt.day()+1, start_dt.month())))+1;
		
		count = end - start;
		for (int i = start; i < end; i++) {
			sum += records[i].temperature;
		}
		if (count != 0) return (double)sum / count;
		else return 0;
	}
	double get_average_temperature_for_month() {
		int sum = 0;
		int count = 0;
		int start = lower_bound(Record(DateTime(0, 0, start_dt.month())));
		int end;
		if (start_dt.month() != 12) {
			end = lower_bound(Record(DateTime(0, 0, start_dt.month()+1)))+1;
		}
		else{
			end = records.size();
		}
		count = end - start;
		for (int i = start; i < end; i++) {
			sum += records[i].temperature;
		}
		if (count != 0) return (double)sum / count;
		else return 0;
	}
	double get_average_temperature() {
		int sum = 0;
		int count = 0;
		
		for (int i = 0; i < records.size(); i++) {
			sum += records[i].temperature;
		}
		if (records.size() != 0) return (double)sum / count;
		else return 0;
	}
	double get_average_temperature_month_for_day() {
		int sum = 0;
		int count = 0;
		int start = lower_bound(Record(DateTime(0, 0, start_dt.month())));
		int end;
		if (start_dt.month() != 12) {
			end = lower_bound(Record(DateTime(0, 0, start_dt.month() + 1))) + 1;
		}
		else {
			end = records.size();
		}
		count = end - start;
		for (int i = start; i < end; i++) {
			if (records[i].date_time.hour() > 8 && records[i].date_time.hour() < 22) {
				sum += records[i].temperature;
			}
		}
		if (count != 0) return (double)sum / count;
		else return 0;
	}
	double get_average_temperature_month_for_night() {
		int sum = 0;
		int count = 0;
		int start = lower_bound(Record(DateTime(0, 0, start_dt.month())));
		int end;
		if (start_dt.month() != 12) {
			end = lower_bound(Record(DateTime(0, 0, start_dt.month() + 1))) + 1;
		}
		else {
			end = records.size();
		}
		count = end - start;
		for (int i = start; i < end; i++) {
			if (records[i].date_time.hour() < 8 && records[i].date_time.hour() > 22) {
				sum += records[i].temperature;
				count++;
			}
		}
		if (count != 0) return (double)sum / count;
		else return 0;
	}
	void save_to_file(string file) {
		ofstream out;
		out.open(file);
		if (out.is_open()) {
			for (int i = 0; i < records.size(); ++i) {
				out << records[i].date_time.unit << ' ' << records[i].temperature;
			}
		}
		out.close();
	}
	void read_from_file(string file) {
		records = vector<Record>(0);
		ifstream in(file);
		if (in.is_open()) {
			int dt;
			int temp;
			while (in >> dt >> temp) {
				records.push_back(Record(dt, temp));
			}
		}
	}
};