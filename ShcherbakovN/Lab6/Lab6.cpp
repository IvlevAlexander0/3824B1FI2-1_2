#include <iostream>
#include <string> //Для функции std::to_string(), которая преобразует тип в строку.

class Number_check //Класс, который хранит информацию о том, какие цифры входят в число. Хранит информацию о повторении или неповторении цифр в числе. Используется для поддержки класса Human.
{
private:
    bool acceptable; //Допустимость числа по повторению цифр.
    int arr_digits[10]; //Массив, который хранит информацию о количество цифр в числе (индекс массива - цифра в числе).

public:

    Number_check() : acceptable{ true }
    {
        for (int i = 0; i < 10; ++i)
        {
            arr_digits[i] = 0;
        }
    }
    ~Number_check() {}

    void set_acceptable(bool result) //result - false или true. Задать допустимости числа.
    {
        acceptable = result;
    }

    bool get_acceptable() const //Получить допустимость числа.
    {
        return acceptable;
    }

    void reset() //Обнулить данные.
    {
        acceptable = true;
        for (int i = 0; i < 10; ++i)
        {
            arr_digits[i] = 0;
        }
    }

    void update(int digit) //digit - цифра числа. Метод Запоминает количество цифр в числе.
    {
        arr_digits[digit] += 1;

        for (int i = 0; i < 10; ++i) //Проверка на повторение цифр.
        {
            if (arr_digits[i] > 1)
            {
                acceptable = false;
                break;
            }
        }
    }
};

class Computer //Класс для генерации загадываемое числа заданной длины. Хранит информацию о данном числе. Используется для поддержки класса Bulls_and_cows.
{
private:

    int computer_n; //Количество цифр в загадываемом числе(без повторений, то есть 1 <= n <= 10).
    std::string computer_number; //Загаданное компьютером число.

public:

    Computer() : computer_n{ 0 }, computer_number{ "" } {}
    ~Computer() {}

    void set_computer_n(int _computer_n) //_computer_n - количество цифр в загадываемом числе(без повторений, то есть 1 <= n <= 10). Задать количество цифр в загадываемом числе.
    {
        computer_n = _computer_n;
    }

    int get_computer_n() const //Получить количество цифр в загаданном числе.
    {
        return computer_n;
    }

    std::string get_computer_number() const //Получить загаданное число.
    {
        return computer_number;
    }

    void generate_random_number() //Генерация загадываемого числа с неповторяющимися цифрами.
    {
        int num = 0, index = 0;
        computer_number = ""; // Обнуление прошло загаданного числа.
        int _arr[10] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        for (int i = 9, n = computer_n; n > 0; --i, --n) //Алгоритм перемешения рандомно выбираемых цифр в конец массива и рандомная выборка из остальных цифр.
        {
            index = rand() % (i + 1);
            if (_arr[index] == 0 && i == 9 && computer_n != 1) //Если первый символ числа, длина которого больше единицы, ноль, то цикл возвращается к началу.
            {
                i += 1;
                n += 1;
                continue;
            }
            num = _arr[index];
            _arr[index] = _arr[i];
            _arr[i] = num;
            computer_number.append(std::to_string(num)); //Метод append() добавляет в конец строки другую строку.
        }
    }
};

class Human //Класс для обработки числа-попытки. Хранит информацию о числе-попытке. Используется для поддержки класса Bulls_and_cows.
{
private:

    int human_n; //Количество цифр в числе-попытке(без повторений, то есть 1 <= n <= 10).
    std::string human_number; //Число-попытка.
    Number_check human_check; //Информация о цифрах в числе-попытке.

public:

    Human() : human_n{ 0 }, human_number{ "" } {}
    ~Human() {}

    void reset() //Обнулить данные о числе-попытке.
    {
        human_n = 0;
        human_number = "";
        human_check.reset();
    }

    void initialization(std::string _human_number) //_human_number - число-попытка. Внести данные о числе-попытке.
    {
        human_n = (int)_human_number.length();
        human_number = _human_number;
        for (int i = 0; i < human_n; ++i)
        {
            human_check.update(_human_number[i] - 48); //-48, так как _human_number возвращает код символа.
        }
    }

    bool get_human_number_acceptable() const //Узнать допустимость числа-попытки(по повторению цифр в числе-попытке).
    {
        return human_check.get_acceptable();
    }

};

class Bulls_and_cows //Основной класс игры «Быки и коровы».
{
private:

    Computer computer; //Загаданное компьютером число.
    Human human; // Число-попытка.
    int bulls; //Сколько цифр угадано без совпадения с их позициями в загаданном числе(то есть количество коров).
    int cows; //Сколько цифр угадано вплоть до позиции в загаданном числе(то есть количество быков).

    int set_number_of_digits_to_generate_computer_number(std::string _str) //_str - количество цифр в загадываемом числе(без повторений, то есть 1 <= n <= 10). Метод проверяет _str на все необходимые ограничения(по условию задания) и генерирует число с неповторяющимися цифрами, которых _str штук. 
    {
        int n_length = (int)_str.length();
        for (int i = 0; i < n_length; ++i)
        {
            if (!(std::isdigit(_str[i])))
            {
                return -2; //Не все цифры.
            }
        }
        int _n = std::stoi(_str); //stoi() - преобразует строку в тип int.
        if (_n > 0 && _n < 11)
        {
            computer.set_computer_n(_n);
            computer.generate_random_number();

            //std::cout << computer.get_computer_number() << std::endl; //Вывод загаданного числа (для проверки).
            return 0; //Всё хорошо.
        }
        else
        {
            return -1; //Длина числа не подходит.
        }
    }

    int human_try_guess(std::string _str) //_str - число-попытка. Метод проверяет _str на все необходимые ограничения(по условию задания) и сравнивает с загаданным числом, сохраняя количество "быков" и "коров".
    {
        int str_length = (int)_str.length();
        if (str_length > 0 && str_length < 11)
        {
            for (int i = 0; i < str_length; ++i)
            {
                if (!(std::isdigit(_str[i]))) //std::isdigit() - проверяет, является ли заданный символ десятичной цифрой (от 0 до 9).
                {
                    return -2; //Не все цифры.
                }
            }

            if (str_length == computer.get_computer_n())
            {
                human.initialization(_str);
                if (human.get_human_number_acceptable())
                {
                    if ((_str[0] != '0' && str_length > 1) || str_length == 1)
                    {
                        if (cows != 0 || bulls != 0)
                        {
                            bulls = 0;
                            cows = 0;
                        }
                        std::string computer_number = computer.get_computer_number();
                        for (int i = 0; i < str_length; ++i)
                        {
                            if (_str[i] == computer_number[i])
                            {
                                bulls += 1;
                            }
                            else
                            {
                                for (int j = 0; j < str_length; ++j)
                                {
                                    if (_str[i] == computer_number[j])
                                    {
                                        cows += 1;
                                    }
                                }
                            }
                        }

                        human.reset();
                        return 0; //Всё хорошо.
                    }
                    else
                    {
                        human.reset();
                        return -5; //Число (длина которого больше 1) не должно начинаться с нуля.
                    }
                }
                else 
                {
                    human.reset();
                    return -4; //Цифры в числе повторяются.
                }
            }
            else
            {
                return -3; //Длина загаданного числа не совпадает с длиной числа-попытки.
            }
        }
        else
        {
            return -1; //Длина числа не подходит.
        }
    }

public:

    Bulls_and_cows() : bulls{ 0 }, cows{ 0 } {}
    ~Bulls_and_cows() {}

    void start_game() //Основной метод. Запускает игру  «Быки и коровы».
    {
        std::string _str = "";
        while (1)
        {
            while (1)
            {
                std::cout << "Choose the length of the number being guessed with non-repeating digits (i.e. from 1 to 10): " << std::endl;
                _str = "";
                std::getline(std::cin, _str); //std::getline() - позволяет считывать целые строки текста из потока ввода и сохранять их в строковой переменной.

                if (set_number_of_digits_to_generate_computer_number(_str) == 0)
                {
                    break;
                }
                else
                {
                    std::cout << "Incorrect length of the number being guessed." << std::endl;
                }
            }

            while (1)
            {
                while (1)
                {
                    std::cout << "Try to guess the hidden number: " << std::endl;
                    _str = "";
                    std::getline(std::cin, _str); //std::getline() - позволяет считывать целые строки текста из потока ввода и сохранять их в строковой переменной.
                    int result = human_try_guess(_str);
                    if (result == -1)
                    {
                        std::cout << "The length of the entered number is not suitable (the length must be from 1 to 10 digits)." << std::endl;
                    }
                    else if (result == -2)
                    {
                        std::cout << "The entered value is not a number." << std::endl;
                    }
                    else if (result == -3)
                    {
                        std::cout << "The length of the number does not match the length of the hidden number." << std::endl;
                    }
                    else if (result == -4)
                    {
                        std::cout << "The digits in the number should not be repeated." << std::endl;
                    }
                    else if (result == -5)
                    {
                        std::cout << "The number must not start from zero." << std::endl;
                    }
                    else if (result == 0)
                    {
                        break;
                    }
                }

                std::cout << "The result of the attempt: <" << bulls << "> bulls and <" << cows << "> cows." << std::endl;
                if (bulls == computer.get_computer_n())
                {
                    std::cout << "The hidden number has been successfully guessed! The hidden number: <" << computer.get_computer_number() << ">." << std::endl;
                    break;
                }
            }

            std::cout << "================================================================================" << std::endl;
            std::cout << "Do you want to play with a new number? Enter something." << std::endl;
            std::cout << "Do you want to end the game? Enter <End>." << std::endl;
            std::cout << "Your decision: " << std::endl;
            
            _str = "";
            std::getline(std::cin, _str); //std::getline() - позволяет считывать целые строки текста из потока ввода и сохранять их в строковой переменной.
            std::cout << "================================================================================" << std::endl;

            if (_str == "End")
            {
                std::cout << "The game is over." << std::endl;
                break;
            }
        }     
    }
};

int main()
{
    srand(time(NULL));
    Bulls_and_cows game;

    game.start_game();
}