#include <iostream>
#include <fstream>
#include <string> //Для std::getline()
#include <Windows.h> //Для корректного отображения русских слов
#define default_size_dictionary 5


class dictionary
{
	std::string* english_words;
	std::string* russian_words;
	int now_size_dictionary; //[0;max_size_dictionary]
	int max_size_dictionary;

	void word_not_found(std::string word)
	{
		int choice = -1;
		std::cout << "<" << word << ">" << " is not in the dictionary." << std::endl << "Do you want to add a word to the dictionary? (Write 1)" << std::endl << "" << "Do you want to skip a word? (Write something)" << std::endl;
		while (1)
		{
			std::cout << "Enter: " << std::endl;
			std::cin >> choice;
			if (choice == 1)
			{
				std::string rus_word, eng_word;
				std::cout << "Enter the Russian word: " << std::endl;
				std::cin >> rus_word;
				std::cout << "Enter the English word: " << std::endl;
				std::cin >> eng_word;
				add_words(rus_word, eng_word);
				break;
			}
			else
			{
				std::cout << "The word was skipped." << std::endl;
				break;
			}
		}
	}

public:

	dictionary() //По умолчанию
	{
		now_size_dictionary = 0;
		max_size_dictionary = default_size_dictionary;
		english_words = new std::string[default_size_dictionary];
		russian_words = new std::string[default_size_dictionary];
	}

	dictionary(int amount_words) //Сами задаём размер словаря
	{
		if (amount_words <= 0)
		{
			std::cout << "Incorrect value for the dictionary size.The dictionary size will be set by default." << std::endl;
			amount_words = default_size_dictionary;
		}
		now_size_dictionary = 0;
		max_size_dictionary = amount_words;
		english_words = new std::string[amount_words];
		russian_words = new std::string[amount_words];
	}

	dictionary(int amount_words, const dictionary& other_obj) //Конструктор копирования словаря other_obj в данный словарь.
	{
		if (amount_words <= 0)
		{
			std::cout << "Incorrect value for the dictionary size.The dictionary size will be set by default." << std::endl;
			amount_words = default_size_dictionary;
		}
		now_size_dictionary = 0;
		max_size_dictionary = amount_words;
		english_words = new std::string[amount_words];
		russian_words = new std::string[amount_words];

		if (other_obj.now_size_dictionary > max_size_dictionary)
		{
			while (now_size_dictionary < max_size_dictionary)
			{
				english_words[now_size_dictionary] = other_obj.english_words[now_size_dictionary];
				russian_words[now_size_dictionary] = other_obj.russian_words[now_size_dictionary];
				now_size_dictionary += 1;
			}
			std::cout << "<" << now_size_dictionary << "> words were copied into the dictionary." << std::endl; //Потому что размер копируемого словаря больше данного.
		}
		else if (other_obj.now_size_dictionary <= max_size_dictionary)
		{
			while (now_size_dictionary < other_obj.now_size_dictionary)
			{
				english_words[now_size_dictionary] = other_obj.english_words[now_size_dictionary];
				russian_words[now_size_dictionary] = other_obj.russian_words[now_size_dictionary];
				now_size_dictionary += 1;
			}
			std::cout << "The dictionary has been copied." << std::endl;
		}
	}

	void add_words(std::string rus_word, std::string eng_word)
	{
		if (now_size_dictionary < max_size_dictionary)
		{
			russian_words[now_size_dictionary] = rus_word;
			english_words[now_size_dictionary] = eng_word;

			now_size_dictionary += 1;

			std::cout << "<" << eng_word << "> - <" << rus_word << "> has been added to the dictionary." << std::endl;
		}
		else
		{
			std::cout << "The dictionary is full. Size: " << max_size_dictionary << std::endl;
		}
	}

	void change_translation(std::string word)
	{
		int count = 0;
		std::string new_translation;
		while (count < now_size_dictionary)
		{
			if (english_words[count] == word)
			{
				std::cout << "Enter a new translation of the word <" << word << ">: " << std::endl;
				std::cin >> new_translation;
				russian_words[count] = new_translation;
				std::cout << "The translation has been changed." << std::endl;
				count = -1;
				break;
			}

			else if (russian_words[count] == word)
			{
				std::cout << "Enter a new translation of the word <" << word << ">: " << std::endl;
				std::cin >> new_translation;
				english_words[count] = new_translation;
				std::cout << "The translation has been changed." << std::endl;
				count = -1;
				break;
			}

			else
			{
				count += 1;
			}
		}
		if (count != -1)
		{
			word_not_found(word);
		}
	}

	void find_translation_english_word(std::string eng_word)
	{
		int count = 0;
		while (count < now_size_dictionary)
		{
			if (english_words[count] == eng_word)
			{
				std::cout << "Translation <" << eng_word << ">:<" << russian_words[count] << ">." << std::endl;
				count = -1;
				break;
			}
			else
			{
				count += 1;
			}
		}
		if (count != -1)
		{
			word_not_found(eng_word);
		}
	}

	void find_translation_russian_word(std::string rus_word)
	{
		int count = 0;
		while (count < now_size_dictionary)
		{
			if (russian_words[count] == rus_word)
			{
				std::cout << "Translation <" << rus_word << ">:<" << english_words[count] << ">." << std::endl;
				count = -1;
				break;
			}
			else
			{
				count += 1;
			}
		}
		if (count != -1)
		{
			word_not_found(rus_word);
		}
	}

	void print_dictionary_size() const
	{
		std::cout << "The current number of words in the dictionary: <" << now_size_dictionary << ">." << std::endl;
	}

	void save_to_file() const
	{
		std::ofstream fout; //Создаём поток для записи
		fout.open("dictionary.txt"); //Открываем файл
		int count = 0;

		while (count < now_size_dictionary)
		{
			if (count == 0)
			{
				fout << english_words[count] <<  ";";
				fout << russian_words[count];
				count += 1;
			}
			else
			{
				fout << std::endl << english_words[count] << ";";
				fout << russian_words[count];
				count += 1;
			}
		}

		fout.close(); //Закрываем файл
		std::cout << "The dictionary has been saved to a file." << std::endl;
	}

	void read_from_file()
	{
		while (now_size_dictionary != 0) //Очищаем словарь от слов
		{
			english_words[now_size_dictionary] = "";
			russian_words[now_size_dictionary] = "";

			now_size_dictionary -= 1;
		}


		std::ifstream fin; //Создаём поток для чтения
		fin.open("dictionary.txt"); //Открываем файл

		if (fin.is_open()) //is_open если файл открыт, то возвращает true (иначе - false)
		{
			while (fin.eof() != true && now_size_dictionary < max_size_dictionary) //fin.eof() вернёт true, если будет попытка чтения за пределами конца файла(то есть пока не будет конец файла). Иначе false
			{
				std::getline(fin, english_words[now_size_dictionary], ';'); //getline(<ПОТОК>, <СТРОКА, куда сохраняется>, <РАЗДЕЛИТЕЛЬ(символ), после которых прекращается чтение>)
				std::getline(fin, russian_words[now_size_dictionary], '\n');
				now_size_dictionary += 1;
			}
		}

		fin.close(); //Закрываем файл
		std::cout << "The dictionary has been read from the file. <" << now_size_dictionary << "> words were read into the dictionary." << std::endl;
	}


	void print_dictionary() const //Печать всего словаря.
	{
		int count = 0;
		std::cout << "------------------------------" << std::endl;
		while (count < now_size_dictionary)
		{
			std::cout << "English: <" << english_words[count] << ">; Russian: <" << russian_words[count] << ">." << std::endl;
			count += 1;
		}
		std::cout << "------------------------------" << std::endl;
	}


	~dictionary() //Очищаем память
	{
		delete[] english_words;
		delete[] russian_words;
	}
};

int main()
{
	SetConsoleCP(1251); // Ввод с консоли в кодировке 1251.
	SetConsoleOutputCP(1251); // Вывод на консоль в кодировке 1251. Нужно только будет изменить шрифт консоли на Lucida Console или Consolas.

	dictionary test1(8);
	test1.add_words("Солнце", "Sun");
	test1.add_words("Кошка", "Cat");
	test1.add_words("Книга", "Book");
	test1.add_words("Число", "Number");

	test1.print_dictionary();

	test1.change_translation("Число");
	test1.change_translation("Sun");
	test1.change_translation("Привет");

	test1.print_dictionary();

	test1.find_translation_english_word("Cat");
	test1.find_translation_russian_word("Книга");
	test1.find_translation_russian_word("Телефон");

	test1.print_dictionary();

	test1.print_dictionary_size();

	test1.save_to_file();

	std::cout << "====================" << std::endl;

	dictionary test2(10);

	test2.read_from_file();

	test2.print_dictionary();
	test2.print_dictionary_size();

	std::cout << "====================" << std::endl;

	dictionary test3(7, test1);
	test3.print_dictionary();
}