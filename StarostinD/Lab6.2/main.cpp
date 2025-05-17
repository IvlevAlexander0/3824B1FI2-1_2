#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class Game {
private:
	int length;
	vector<int> number;
	int attempts;
	int bulls_ = 0, cows_ = 0;
	const vector<int> digits = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
	bool result = false;
public:
	Game() : Game(4) {};
	Game(int len) {
		new_game(len);
	}
	void new_game(int len) {
		if (len > 10 || len < 1) {
			throw out_of_range("Error! Length must be in range [1;10]\n");
		}
		length = len;
		for (int i = 0; i < 10; ++i) {
			number.push_back(-1);
		}
		attempts = 0;
		bulls_ = 0, cows_ = 0;
		result = false;
		int id = 1 + rand() % 9;
		number[id] = 0;
		for (int i = 1; i < len; ++i) {
			while (number[id] != -1) {
				id = rand() % 10;
			}
			number[id] = i;
		}
	}
	void guess(int n) {
		cows_ = bulls_ = 0;
		if (!int(n / pow(10, length - 1))) {
			throw invalid_argument("Error! The argument must be an " + to_string(length) + "-digit number.");
		}
		attempts++;
		vector<int> p_num(length), copy_num = number;
		for (int i = length - 1; i >= 0; --i) {
			p_num[i] = n % 10;
			n /= 10;
		}
		for (int i = 0; i < length; ++i) {
			if (copy_num[p_num[i]] == i) {
				bulls_++;
				copy_num[p_num[i]] = -1;
			}
		}
		if (bulls_ == length) {
			result = true;
			cows_ = 0;
			return;
		}
		for (int i = 0; i < length; ++i) {
			if (copy_num[p_num[i]] >= 0) {
				cows_++;
			}
		}
	}
	int cows() {
		return cows_;
	}
	int bulls() {
		return bulls_;
	}
	bool win() {
		return result;
	}
};

class Player {

};

class Computer {

};

int main() {
	cout << "This is a game of bulls and cows.";
	bool exit = false;
	try {
		do {
			cout << "\nEnter the length of the number : ";
			int length;
			cin >> length;
			Game g(length);
			cout << "\nLet's start.\n";
			while (!g.win()) {
				cout << "Guess the number: ";
				int number;
				cin >> number;
				try {
					g.guess(number);
				}
				catch (exception e) {
					cerr << e.what() << '\n';
				}
				cout << "\nBulls: " << g.bulls() << "; Cows: " << g.cows() << endl;
				if (!g.win()) {
					cout << "Try again\n";
				}
			}
			cout << "\nYou win!!!\nWant to play again?(Enter 1 for YES and 0 for NO): ";
			cin >> exit;
		} while (exit);
	}
	catch (exception e) {
		cerr << e.what();
	}
}