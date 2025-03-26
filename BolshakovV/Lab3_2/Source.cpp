#include <iostream>
#include <clocale>
#include <fstream>
#include <string>
#include <Windows.h>


class dictionary {
private:


	int size;
	std::string* eng_words;
	std::string* rus_words;
	int INC;

	void choise() {
		std::cout << "\nThe word is not found" << std::endl;
		int choise;
		std::cout << "Do you want to add a word to the dictionary?" << std::endl;
		std::cout << "1 - yes, 2 - no" << std::endl;

		int flag = 0;
		do {
			flag = 1;
			std::cin >> choise;
			if (std::cin.fail() || (choise < 1 || choise>2)) {
				std::cout << "Error. Please enter the correct value" << std::endl;
				flag = 0;
			}
			std::cin.clear();
			while (std::cin.get() != '\n') {};

		} while (flag == 0);

		if (choise == 1) {
			std::cout << "Enter the word in Russian and it's English translation" << std::endl;
			std::string eng;
			std::string rus;
			std::cout << "The word in Russian: ";
			getline(std::cin, rus);
			std::cout << "\n";
			std::cout << "English translation: ";
			getline(std::cin, eng);
			add_word(rus, eng);
		}
	}


	void mass_2() {
		INC *= 2;
		std::string* new_eng_words = new std::string[INC];
		std::string* new_rus_words = new std::string[INC];

		for (int i = 0; i < size; i++) {
			new_eng_words[i] = eng_words[i];
			new_rus_words[i] = rus_words[i];
		}
		delete[]eng_words;
		delete[]rus_words;

		eng_words = new_eng_words;
		rus_words = new_rus_words;
	}


public:
	dictionary() : size(0), INC(5) {
		eng_words = new std::string[INC];
		rus_words = new std::string[INC];
	}

	dictionary(const dictionary& dict) {
		size = dict.size;
		INC = dict.INC;

		delete[]eng_words;
		delete[]rus_words;


		eng_words = new std::string[INC];
		rus_words = new std::string[INC];

		for (int i = 0; i < size; i++) {
			eng_words[i] = dict.eng_words[i];
			rus_words[i] = dict.rus_words[i];
		}
	}

	~dictionary() {
		delete[]eng_words;
		delete[]rus_words;
		eng_words = NULL;
		rus_words = NULL;
	}

	void add_word(const std::string& RUS, const std::string& ENG) {//пункт 1
		if (size >= INC) {
			mass_2();
		}

		rus_words[size] = RUS;
		eng_words[size] = ENG;

		size++;


	}

	void change_translation(const std::string& old_ENG, const std::string& new_translation) {//пункт 2
		int flag = 0;
		for (int i = 0; i < size; i++) {
			if (eng_words[i] == old_ENG) {
				rus_words[i] = new_translation;
				flag = 1;
			}
			else if (size == 0) {
				std::cout << "The dictinary is empty" << std::endl;
			}
		}
		if (flag == 0) {
			choise();

		}

	}

	void translation_rus(const std::string& ENG) {//пункт 3
		int flag = 0;

		if (size == 0) {
			std::cout << "The dictinary is empty" << std::endl; // словарь пуст
		}

		for (int i = 0; i < size; i++) {
			if (eng_words[i] == ENG) {
				std::cout << "Translation into Russian: " << rus_words[i] << std::endl;
				flag = 1;
			}
		}

		if (flag == 0) {
			choise();
		}
	}

	void translation_eng(const std::string& RUS) { //пункт 4

		int flag = 0;

		if (size == 0) {
			std::cout << "The dictinary is empty" << std::endl; // словарь пуст
		}

		for (int i = 0; i < size; i++) {
			if (rus_words[i] == RUS) {
				std::cout << "English translation: " << eng_words[i] << std::endl;
				flag = 1;
			}
		}

		if (flag == 0) {
			choise();
		}
	}


	void print_size() const { //пункт 5
		std::cout << "The number of words in the dictionary: " << size << std::endl;
	}

	void save_the_dictionary(const std::string& file) { //пункт 6
		std::ofstream fout(file, std::ios::out);

		if (fout.is_open()) {
			for (int i = 0; i < size; i++) {
				fout << rus_words[i] << " " << eng_words[i] << std::endl;
			}
		}
		else {
			std::cout << "Error. The file could not be opened" << std::endl;
		}
		fout.close();
	}

	void dictionary_output(const std::string& file1) { //пункт 7
		std::ifstream fin;
		std::string line;
		fin.open(file1);
		if (fin.is_open()) {
			while (std::getline(fin, line)) {

				int len = line.size();
				std::string rus1;
				std::string eng1;

				bool isRussian = 1;

				int i;
				for (i = 0; i < len; i++) {
					if (line[i] >= 'А' && line[i] <= 'я' || line[i] == ' ') {
						rus1 += line[i];
					}

					if ((line[i] >= 'A' && line[i] <= 'Z') || (line[i] >= 'a' && line[i] <= 'z')) {
						break;
					}
				}

				while (i < len) {
					eng1 += line[i];
					++i;
				}


				rus1.pop_back(); // удалили последний пробел в строке из русских слов 

				add_word(rus1, eng1);
			}
		}
		else {
			std::cout << "Error" << std::endl;
		}
		fin.close();
	}

	//очистка файла (в задании не было)
	void clear_file(const std::string& filename) {
		std::ofstream file(filename, std::ios::trunc);
		if (file.is_open()) {
			file.close();
		}
		else {
			std::cout << "Error" << std::endl;
		}
	}


};



int main() {

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	setlocale(LC_ALL, "RUS");
	dictionary dict;


	dict.add_word("яблоко", "apple");
	dict.add_word("книга", "book");
	dict.add_word("дом", "house");
	dict.add_word("родной город", "hometown");
	dict.add_word("кот", "cat");
	dict.add_word("мяч", "ball");

	std::cout << "Translate (dict): " << std::endl;

	dict.translation_rus("apple");
	dict.translation_eng("книга");
	dict.translation_rus("book");

	dict.change_translation("book", "книжка"); //изменение перевода слова

	dict.translation_rus("book");
	dict.translation_rus("ball");
	dict.translation_eng("родной город");
	dict.print_size();

	std::cout << "\n\nTranslate (dict_2): " << std::endl;
	dictionary dict_2(dict);
	dict_2.print_size();
	dict_2.translation_rus("book");
	dict_2.translation_rus("hometown");

	dict.save_the_dictionary("Dictinary_01.txt");


	//считывание строк из файла, добавление нового слова (строки) в словарь, сохранение словаря

	/*dict.dictionary_output("Dictinary_01.txt");
	dict.print_size();
	dict.translation_rus("apple");
	dict.translation_rus("book");
	dict.translation_rus("ball");
	dict.translation_rus("Hello World");
	dict.translation_rus("Hello World");
	dict.save_the_dictionary("Dictinary_01.txt"); */


	//считывание строк из файла, проверка на корректность считывания строки

	/*dict.dictionary_output("Dictinary_01.txt");
	dict.print_size();
	dict.translation_rus("apple");
	dict.translation_rus("book");
	dict.translation_rus("Hello World"); */



	//dict.clear_file("Dictinary_01.txt"); 




	return 0;
}