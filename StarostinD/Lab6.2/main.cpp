#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class Player;
class Computer;
class Human;
class Game;

class Player {
protected:
	int length = 0;
	int number[10] = {-1,-1,-1,-1,-1,-1,-1,-1,-1,-1};
public:
	Player() = default;
	virtual void new_game(int len) = 0;
};

class Human: public Player{
private:
	void check_number_length(long long num) const {
		int check_length = 0;
		long long num_copy = num;
		while (num_copy) {
			num_copy /= 10;
			++check_length;
		}
		if (check_length != length) {
			throw invalid_argument("Error! The length of the number must be equal to the entered length.(" + to_string(length) + ")\n");
		}
	}
	friend  Computer;
public:
	Human(int len) {
		new_game(len);
	}
	void new_game(int len) override {
		if (len > 10 || len < 1) {
			throw out_of_range("Error! Length must be in range [1;10]\n");
		}
		length = len;
	}
	void new_number(long long num) {
		check_number_length(num);
		for (int i = 0; i < 10; ++i) {
			number[i] = -1;
		}
		for (int i = length - 1; i >= 0; --i) {
			int t = num % 10;
			num /= 10;
			if (number[t] == -1) {
				number[t] = i;
			}
			else {
				throw invalid_argument("Error! The number entered has the same digits");
			}
		}
	}
};

class Computer: public Player {
public:
	Computer(int len) {
		new_game(len);
	}
	void new_game(int len) override {
		if (len > 10 || len < 1) {
			throw out_of_range("Error! Length must be in range [1;10]\n");
		}
		length = len;
		for (int i = 0; i < 10; ++i) {
			number[i] = -1;
		}
		int id = 1 + rand() % 9;
		number[id] = 0;
		for (int i = 1; i < len; ++i) {
			while (number[id] != -1) {
				id = rand() % 10;
			}
			number[id] = i;
		}
	}
	void compare(int& bulls, int& cows, const Human& obj) {
		cows = bulls = 0;
		for (int i = 0; i <= 9; ++i) {
			if (number[i] != -1 && obj.number[i] != -1 && number[i] == obj.number[i]) {
				++bulls;
			}
			else if (number[i] != -1 && obj.number[i] != -1) {
				++cows;
			}
		}
	}

};

class Game {
private:
	Human player;
	Computer computer;
	int length;
	int attempts_;
	int bulls_, cows_;
	bool result;
public:
	Game(int len) : player(len), computer(len), length(len), attempts_(0), bulls_(0), cows_(0), result(false) {};
	void new_game(int len) {
		length = len;
		attempts_ = bulls_ = cows_ = 0;
		result = false;
		player.new_game(len);
		computer.new_game(len);
	}
	void guess(long long num) {
		++attempts_;
		player.new_number(num);
		computer.compare(bulls_, cows_, player);
		if (bulls_ == length) {
			result = true;
		}
	}
	int cows() const {
		return cows_;
	}
	int bulls() const {
		return bulls_;
	}
	bool win() const {
		return result;
	}
	int attempts() const {
		return attempts_;
	}
};


int main() {
	srand(time(NULL));
	cout << "This is a game of bulls and cows.";
	bool exit = false;
	Game g(1);
	try {
		do {
			cout << "\nEnter the length of the number: ";
			int length;
			cin >> length;
			g.new_game(length);
			cout << "\nLet's start.\n";
			while (!g.win()) {
				cout << "Guess the number: ";
				long long number;
				cin >> number;
				try {
					g.guess(number);
					cout << "\nBulls: " << g.bulls() << "; Cows: " << g.cows() << endl;
					if (!g.win()) {
						cout << "Try again\n";
					}
				}
				catch (exception e) {
					cerr << e.what() << '\n';
				}
			}
			cout << "\nYou win!!! Number of attempts: " << g.attempts();
			cout << "\nWant to play again? (Enter 0 for NO and any other number for YES): ";
			cin >> exit;
		} while (exit);
	}
	catch (exception e) {
		cerr << e.what();
	}
	cout << "\nGoodbye!\n";
	return 0;
}