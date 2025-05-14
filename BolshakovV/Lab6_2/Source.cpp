#include <iostream>
#include <random>
#include <string>

class Computer {

private:

	bool proverka_duplicate(const std::string& s, char c) const {
		for (char ch : s) {
			if (c == ch) {
				return true;
			}
		}
		return false;
	}

	int min(int n1, int n2) const {
		return n1 >= n2 ? n2 : n1;
	}

public:

	Computer() {}

	std::string generation_number(int n) const {
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<int>dist(0, 9);
		int len = 0;
		std::string chislo;
		int z;
		char z1;
		do {
			z = dist(gen);
			//если первая цифра 0, то пропускаем
			if (len == 0 && z == 0) {
				continue;
			}

			z1 = z + '0';

			if (proverka_duplicate(chislo, z1)) {
				continue;
			}

			chislo += z1;
			len++;

		} while (len != n);

		std::cout << "Stroka (pc): " << chislo << std::endl; //нужна для проверки в main (вывод сгенерированного компьютером числа)

		return chislo;
	}

	int result(const std::string& s1, const std::string& s2) const {
		if (s1.size() != s2.size()) {
			std::cout << "Error: Strings must be the same length." << std::endl;
			return 1;
		}

		int count_bull = 0;
		int count_cow = 0;
		int count_s1[10] = { 0 };
		int count_s2[10] = { 0 };

		int len = s1.size();

		for (int i = 0; i < len; ++i) {
			if (s1[i] == s2[i]) {
				count_bull++;
			}
			else {
				count_s1[s1[i] - '0']++;
				count_s2[s2[i] - '0']++;
			}
		}

		for (int i = 0; i < 10; ++i) {
			count_cow += min(count_s1[i], count_s2[i]);
		}

		if (count_bull == len) {
			std::cout << "You win!!!" << std::endl;
			return 0;
		}
		else {
			std::cout << "Count cow = " << count_cow << std::endl;
			std::cout << "Count bull = " << count_bull << std::endl;
			return 1;
		}

	}


};

class Player {

private:

	bool proverka_duplicate(const std::string& s) const {
		int size = s.size();
		for (int i = 0; i < size - 1; i++) {
			for (int j = i + 1; j < size; j++) {
				if (s[i] == s[j]) {
					return true;
				}
			}
		}
		return false;

	}

	int proverka_number(const std::string& s) const {
		for (char c : s) {
			if (c < '0' || c>'9') {
				std::cout << "Error. Please enter the correct value (A space is also an incorrect value)" //пробел -  тоже ошибка 
					<< std::endl;
				return 1;
			}
		}
		return 0;
	}

	int to_number(const std::string& s) const {
		int number = 0;
		for (char c : s) {
			number = number * 10 + (c - '0');
		}
		return number;
	}

public:
	Player() {}

	int choose_lenght() const {
		std::string str;
		std::cout << "The minimum number length is 2: ";
		int flag = 1;
		do {
			std::getline(std::cin, str);
			flag = 0;
			if (proverka_number(str)) {
				flag = 1;
			}
			else if (str == "0") {
				std::cout << "Error. The length cannot be 0" << std::endl;
				flag = 1;
			}
			else if (str == "1") {
				std::cout << "Error. It is not interesting to play with the length of a number equal to 1!" << std::endl;
				flag = 1;

			}
		} while (flag);

		int len = to_number(str);

		return len;

	}

	std::string enter_number(int len) const {
		int flag = 1;
		std::string str;

		do {
			std::getline(std::cin, str);
			flag = 0;

			if (str.size() != len) {
				std::cout << "Incorrect number length" << std::endl;
				flag = 1;

			}

			if (proverka_number(str)) {
				flag = 1;
			}

			if (str[0] == '0') {
				std::cout << "Error. A number cannot start with 0" << std::endl;
				flag = 1;
			}

			if (proverka_duplicate(str)) {
				std::cout << "Error. There are duplicate numbers" << std::endl;
				flag = 1;

			}

		} while (flag);

		return str;
	}
};

class Game {
private:
	Computer computer;
	Player player;
	std::string str_man;
	std::string str_pc;
	int len;

public:
	Game(std::string s1 = "", std::string s2 = "", int l = 0) : str_man(s1), str_pc(s2), len(l) {

	}

	void enter_lenght() {
		std::cout << "Choose the length of the number. ";
		len = player.choose_lenght();
	}

	void gen_number() {

		str_pc = computer.generation_number(len);
	}

	void attempt() {
		std::cout << "Enter a number with non-repeating digits (the length of the number is " << len << ")" << std::endl;
		str_man = player.enter_number(len);
	}
	int Result() {
		int res = computer.result(str_man, str_pc);
		return res;
	}

};

std::string ent(const std::string& l, const std::string& r) {
	std::string mode;
	int flag = 1;
	do {
		std::getline(std::cin, mode);
		flag = 0;
		if (mode != l && mode != r) {
			std::cout << "Error. Please enter the correct value" << std::endl;
			flag = 1;
		}
	} while (flag);
	return mode;
}

int main() {

	Game game;

	std::string mode;

	std::cout << "Please select the mode: 1 - start the game, 2 - end the game" << std::endl;

	int flag2 = 1;
	mode = ent("1", "2");
	int number = mode[0] - '0'; //перевели строку в int

	switch (number) {
	case 1:

		game.enter_lenght();
		game.gen_number();

		do {

			std::string mode2;

			std::cout << "Please select the mode: 1 - make an attempt, 2 - end the game" << std::endl;
			mode2 = ent("1", "2");

			int number2 = mode2[0] - '0'; //перевели строку в int

			switch (number2) {
			case 1:

				game.attempt();

				flag2 = game.Result();

				break;

			case 2:
				std::cout << "Thanks for playing!" << std::endl;
				flag2 = 0;
				break;

			}

		} while (flag2);

		break;

	case 2:
		std::cout << "Thanks for playing!" << std::endl;
		break;
	}

	return 0;
}