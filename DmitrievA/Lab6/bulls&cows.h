#pragma once
#include <iostream>
#include <random>
#include <string>

using std::cout;
using std::cin;
using std::istream;
using std::ostream;
using std::string;
using std::endl;

class Generator {
	std::mt19937 engine;
	Generator() {
		std::random_device dev;
		Generator::engine = std::mt19937(dev());
	}
public:
	static Generator* Instance() {
		static Generator instance;
		return &instance;
	}

	string getnumbers(int count) {
		if (count < 1 || count > 10) {
			throw "Number must be between 1 and 10";
		}
		bool cross_out[10] = {};
		for (int i = 0; i < 10; i++) {
			cross_out[i] = false;
		}
		string s = string(count, '0');
		for (int i = 0; i < count; i++) {
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, 9 - i);
			int num = dist(engine);
			int j;
			for (j = 0; cross_out[j] || num > 0;) {
				num -= 1 - cross_out[j];
				j++;
			}
			s[i] = j + '0';
			cross_out[j] = true;
		}
		return s;
	}
};


bool check_for_unique_digits(string s) {
	for (int i = 0; i < s.size()-1; i++) {
		if (s[i] <= '9' && s[i] >= '0') {
			for (int j = i + 1; j < s.size(); j++) {
				if (s[i] == s[j]) {
					return false;
				}
			}
		}
		else{
			return false;
		}
	}
	return true;
}


class Game {
	istream& in;
	ostream& out;
public:
	Game(istream& in_ = cin, ostream& out_ = cout) : in{ in_ }, out{ out_ } {}

	void start_game(bool with_restart = false) {
		bool want_restart = false;
		do{
			this->guessing_process();
			bool incorrect = false;
			char c;
			if (with_restart) {
				out << "Do you want restart? Y/N" << endl;
				do {
					if (incorrect) { out << "Please, enter Y or N"; }
					cin >> c;
					incorrect = true;
				} while (c != 'Y' && c != 'N');
				if (c == 'Y') want_restart = true;
				else want_restart = false;
			}
		} while (with_restart && want_restart);
	}
	void guessing_process() {
		out << "Input len of number: ";
		bool incorrect = false;
		int n;
		do {
			if (incorrect) out << "number must be between 1 and 10(inclusive)";
			in >> n;
			incorrect = true;
		} while (n < 1 || n > 10);
		string num = Generator::Instance()->getnumbers(n);
		string input;
		int try_count = 0;
		while (input != num) {
			out << "Input number" << endl;
			in >> input;
			if (input.size() != n) { out << "wrong len. Try again" << endl; continue; }
			if (!check_for_unique_digits(input)) { out << "Input number with unique digits" << endl; continue; };
			int cows = 0;
			int buls = 0;
			for (int i = 0; i < n; i++) {
				if (num[i] == input[i]) {
					buls++;
					continue;
				}
				for (int j = 0; j < n; j++) {
					if (input[i] == num[j]) {
						cows++;
						break;
					}
				}
			}
			out << "bulls: " << buls << "\t cows: " << cows << endl;
			try_count++;
		}
		out << "You gueess the number! Try count: " << try_count << endl;
	}
};