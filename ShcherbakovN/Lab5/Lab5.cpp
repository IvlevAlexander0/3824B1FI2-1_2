#include <iostream>
#include <vector>
#include <cmath> //Функция std::floor(n), возвращающая наибольшее целое значение, не превышающее n, где n - с плавающей запятой или целое число.

struct DepositRate
{
public:
    std::string info;
    double threeMonth;
    double sixMonth;
    double oneYear;
    double twoYear;
    double threeYear;

    double get_interest_rate_for_deposit_term(int _count_months) //Метод, возвращающий поле, которое будет соответствовать в векторе кокнкретной процентной ставке.
    {
        if (_count_months == 3)
        {
            return threeMonth;
        }
        else if (_count_months == 6)
        {
            return sixMonth;
        }
        else if (_count_months == 12)
        {
            return oneYear;
        }
        else if (_count_months == 24)
        {
            return twoYear;
        }
        else if (_count_months == 36)
        {
            return threeYear;
        }
        else
        {
            return -1.0;
        }
    }
};

class Person
{
private:
    std::string name;
    std::string surname;
    std::string patronymic; //Фамилия
public:
    Person(): name{ "" }, surname{ "" }, patronymic{ "" } {}
    ~Person() {}

    void set_name(std::string _name)
    {
        name = _name;
    }

    void set_surname(std::string _surname)
    {
        surname = _surname;
    }

    void set_patronymic(std::string _patronymic)
    {
        patronymic = _patronymic;
    }

    std::string get_name() const
    {
        return name;
    }

    std::string get_surname() const
    {
        return surname;
    }

    std::string get_patronymic() const
    {
        return patronymic;
    }
};

class Deposit_info
{
private:
    int amount; // Сумма депозита.
    int term; // Срок депозита в месяцах.
    int now_term; //Сколько прошло месяцев с момента открытия депозита.
    double rate; //Процентная ставка депозита.
    int accumulated_interest; // Накопленные проценты(сумма).
    bool is_open; //Открыт ли депозит у клиента.

public:
    Deposit_info(): amount{0}, term{0}, now_term{0}, rate{0.0}, accumulated_interest{0}, is_open{false} {}
    ~Deposit_info() {}

    int get_amount() const
    {
        return amount;
    }

    int get_term() const
    {
        return term;
    }

    int get_now_term() const
    {
        return now_term;
    }

    double get_rate() const
    {
        return rate;
    }

    int get_accumulated_interest() const
    {
        return accumulated_interest;
    }

    bool get_is_open() const
    {
        return is_open;
    }

    void set_amount(int _amount)
    {
        amount = _amount;
    }

    void set_term(int _term)
    {
        term = _term;
    }

    void set_now_term(int _now_term)
    {
        now_term = _now_term;
    }

    void set_rate(double _rate)
    {
        rate = _rate;
    }

    void set_accumulated_interest(int _accumulated_interest)
    {
        accumulated_interest = _accumulated_interest;
    }

    void set_is_open(bool _is_open)
    {
        is_open = _is_open;
    }
};

class Client
{
private:
    std::string salary_account; //Номер зарплатного счёта
    int amount_salary_account; //Сумма на зарплатном счету (в рублях, без копеек)
    std::string password; //Пароль (произвольная строка, выбранная пользователем, с длиной больше 3 символов)

public:
    Person person; //ФИО
    Deposit_info deposit_info; //Информация о депозите

    Client(): salary_account{""}, amount_salary_account{0}, password{""} {}
    ~Client() {}

    std::string get_salary_account() const
    {
        return salary_account;
    }

    int get_amount_salary_account() const
    {
        return amount_salary_account;
    }

    std::string get_password() const
    {
        return password;
    }

    void set_salary_account(std::string _salary_account)
    {
        salary_account = _salary_account;
    }

    void set_amount_salary_account(int amount)
    {
        amount_salary_account = amount;
    }

    void set_password(std::string _password)
    {
        password = _password;
    }
};

class Processing_center
{
protected:
    std::vector<Client> database;

    Processing_center() {}
    ~Processing_center() {}

    int add_client(std::string _salary_account, int _amount_salary_account, std::string _password, std::string _name, std::string _surname, std::string _patronymic)
    {
        Client now_client;
        if (_salary_account.length() == 4 && _salary_account != "0000")
        {
            for (size_t i = 0; i < 4; ++i)
            {
                if (isdigit(_salary_account[i]) == 0) //isdigit(n) проверяет, является ли символ n цифрой от '0' до '9'
                {
                    return -1;
                }
            }
        }
        else
        {
            return -1;
        }
        if (_amount_salary_account < 0)
        {
            return -2;
        }
        if (_password.length() < 4)
        {
            return -3;
        }
        now_client.set_salary_account(_salary_account);
        now_client.set_amount_salary_account(_amount_salary_account);
        now_client.set_password(_password);

        now_client.person.set_name(_name);
        now_client.person.set_surname(_surname);
        now_client.person.set_patronymic(_patronymic);

        database.push_back(now_client); //push_back(n) - добавляет в вектор элемент n.
        return 0;
    }
};

class Deposit: protected Processing_center //Проценты за каждый месяц одни и те же. То есть к телу дупозита не добавляются суммы для дальейшего расчёта, расчёт ведётся от начальной суммы депозита.
{
private:
    int position_in_database;
    bool is_login;
    std::vector<DepositRate> deposit_rates{
        {"Interest rates up to 100 thousand", 5.0, 5.5, 6.0, 6.2, 6.5}, //До 100 тысяч рублей.
        {"Interest rates from 100 thousand to 500 thousand", 5.5, 6.0, 6.6, 6.8, 7.0}, //От 100 до 500 тысяч  рублей.
        {"Interest rates from 500 thousand to 1 million", 6.0, 6.3, 6.9, 7.2, 7.5}, //От 500 тысяч до 1 млн рублей.
        {"Interest rates more than 1 million", 6.5, 6.8, 7.3, 7.5, 7.8}  //Более 1 млн рублей.
    };

    int calculating_percentages_month(int _deposit_amount, double _deposit_rate) //Сумма на депозите, процентная ставка.
    {
        return (int)floor((_deposit_amount * (_deposit_rate / 100)) / 12);
    }

    int get_vailable_deposits_rates(int _amount_salary_account) const //Служебный метод. Возвращает индекс соответствующий определенному набору процентных ставок в векторе.
    {
        if (_amount_salary_account < 100000)
        {
            return 0;
        }
        else if (_amount_salary_account >= 100000 && _amount_salary_account < 500000)
        {
            return 1;
        }
        else if (_amount_salary_account >= 500000 && _amount_salary_account < 1000000)
        {
            return 2;
        }
        else if (_amount_salary_account >= 1000000)
        {
            return 3;
        }

    }

    void print_login_client() const //Служебный метод. Выводит ФИО текущего, авторизованного клиента.
    {
        std::cout << "Client: <" << database[position_in_database].person.get_name() << " " << database[position_in_database].person.get_surname() << " " << database[position_in_database].person.get_patronymic() << ">";
    }

    bool check_login_client() const //Служебный метод. Проверяет авторизован ли клиент.
    {
        if (is_login)
        {
            return true;
        }
        else
        {
            std::cout << "Authorization is required." << std::endl;
            return false;
        }
    }
public:
    Deposit() : is_login{ false }, position_in_database{-1} {}
    ~Deposit() {}

    void print_info_login_client() const //Метод для проверки значений для данного клиента.
    {
        if (check_login_client())
        {
            print_login_client();
            std::cout << std::endl;
            std::cout << "Salary account number <" << database[position_in_database].get_salary_account() << ">" << std::endl;
            std::cout << "Amount in the salary account <" << database[position_in_database].get_amount_salary_account() << " Rub>" << std::endl;
            std::cout << "Password <" << database[position_in_database].get_password() << ">" << std::endl;
            if (database[position_in_database].deposit_info.get_is_open())
            {
                std::cout << "Deposit amount: <" << database[position_in_database].deposit_info.get_amount() << " Rub>" << std::endl;
                std::cout << "Deposit period: <" << database[position_in_database].deposit_info.get_term() << " Months>" << std::endl;
                std::cout << "Deposit rate: <" << database[position_in_database].deposit_info.get_rate() << " %> per year" << std::endl;
                std::cout << "The percentage amount of the deposit: <" << database[position_in_database].deposit_info.get_accumulated_interest() << " Rub> for <" << database[position_in_database].deposit_info.get_now_term() << " Months>" << std::endl;
            }
            else
            {
                std::cout << "This client does not have an open deposit." << std::endl;
            }
        }
    }

    void add_client_in_database(std::string _salary_account, int _amount_salary_account, std::string _password, std::string _name, std::string _surname, std::string _patronymic) //Добавляет клиента в базу данных клиентов.
    {
        int result = add_client(_salary_account, _amount_salary_account, _password, _name, _surname, _patronymic);
        if (result == -1)
        {
            std::cout << "The client has not been added to the database. Invalid salary_account." << std::endl;
        }
        else if (result == -2)
        {
            std::cout << "The client has not been added to the database. Invalid amount_salary_account." << std::endl;
        }
        else if (result == -3)
        {
            std::cout << "The client has not been added to the database. Invalid password." << std::endl;
        }
        else
        {
            std::cout << "The client has been added to the database." << std::endl;
        }
    }

    int login_client(std::string _salary_account, std::string _password) //Авторизовывает клиента.
    {
        if (database.empty() != true) //empty() проверяет пустой ли вектор(пустой - true, иначе false).
        {
            for (int i = 0; i < database.size(); ++i) //size() - возвращает количество элементов в векторе.
            {
                if (database[i].get_salary_account() == _salary_account)
                {
                    if (database[i].get_password() == _password)
                    {
                        position_in_database = i;
                        is_login = true;
                        print_login_client();
                        std::cout << " is logged in." << std::endl;
                        return 0;
                    }
                    else
                    {
                        std::cout << "Invalid password." << std::endl;
                        return -1;
                    }
                }
            }
            std::cout << "The client was not found." << std::endl;
            return -1;
        }
        else
        {
            std::cout << "Database is empty." << std::endl;
            return -1;
        }
    }

    void show_info_available_deposit() const //Показывает доступные процентные ставки по депозиту.
    {
        if (check_login_client())
        {
            int index = get_vailable_deposits_rates(database[position_in_database].get_amount_salary_account());
            print_login_client();
            for (int i = 0; i < index + 1; ++i)
            {
                std::cout << std::endl << deposit_rates[i].info << ": " << deposit_rates[i].threeMonth << "% - 3 Months, " << deposit_rates[i].sixMonth << "% - 6 Months, " << deposit_rates[i].oneYear << "% - 12 Months(1 Year), " << deposit_rates[i].twoYear << "% - 24 Months(2 Years), " << deposit_rates[i].threeYear << "% - 36 Months(3 Years)." << std::endl;
            }
        }
    }

    void сheck_is_open_deposit() const //Проверяет, наличие открытого депозита.
    {
        if (check_login_client())
        {
            print_login_client();
            std::cout << std::endl;
            if (database[position_in_database].deposit_info.get_is_open())
            {
                std::cout << "This client has an open deposit for a period of <" << database[position_in_database].deposit_info.get_term() << " Months> for the amount of <" << database[position_in_database].deposit_info.get_amount();
                std::cout << " Rub> of <" << database[position_in_database].deposit_info.get_rate() << " %> per year" << std::endl;
            }
            else
            {  
                std::cout << "This client does not have an open deposit." << std::endl;
            }
        }
    }

    void open_deposit(int _deposit_amount, double _deposit_term_months) //Открывает депозит на данную сумму на данный срок(в месяцах).
    {
        if (check_login_client())
        {
            print_login_client();
            std::cout << std::endl;
            if (database[position_in_database].deposit_info.get_is_open())
            {
                std::cout << "The client already has an open deposit." << std::endl;
            }
            else
            {
                if (_deposit_amount < database[position_in_database].get_amount_salary_account())
                {
                    int index = get_vailable_deposits_rates(_deposit_amount);
                    double individual_deposit_rate = deposit_rates[index].get_interest_rate_for_deposit_term(_deposit_term_months);
                    if (individual_deposit_rate != -1.0) //Используется обычное сравнение, так как точность чисел одна и та же(задана вручную).
                    {
                        database[position_in_database].deposit_info.set_is_open(true);
                        database[position_in_database].deposit_info.set_amount(_deposit_amount);
                        database[position_in_database].set_amount_salary_account(database[position_in_database].get_amount_salary_account() - _deposit_amount);
                        database[position_in_database].deposit_info.set_term(_deposit_term_months);
                        database[position_in_database].deposit_info.set_rate(individual_deposit_rate);

                        std::cout << "Deposit was opened for this client for a period of <" << database[position_in_database].deposit_info.get_term() << " Months> for the amount of <" << database[position_in_database].deposit_info.get_amount();
                        std::cout << " Rub> of <" << database[position_in_database].deposit_info.get_rate() << " %> per year" << std::endl;
                    }
                    else
                    {
                        std::cout << "Invalid deposit period. Check the available deposits for this client." << std::endl;
                    }
                }
                else
                {
                    std::cout << "Invalid deposit amount. There are not enough funds to open a deposit for this amount." << std::endl;
                }
            }
        }
    }

    void show_status_deposit() const //Выводит информацию по депозиту клиента.
    {
        if (check_login_client())
        {
            print_login_client();
            std::cout << std::endl;
            if (database[position_in_database].deposit_info.get_is_open())
            {
                std::cout << "Deposit amount: <" << database[position_in_database].deposit_info.get_amount() << " Rub>" << std::endl;
                std::cout << "Deposit period: <" << database[position_in_database].deposit_info.get_term() << " Months>" << std::endl;
                std::cout << "Deposit rate: <" << database[position_in_database].deposit_info.get_rate() << " %> per year" << std::endl;
                std::cout << "The percentage amount of the deposit: <" << database[position_in_database].deposit_info.get_accumulated_interest() << " Rub> for <" << database[position_in_database].deposit_info.get_now_term() << " Months>" << std::endl;
            }
            else
            {
                std::cout << "This client does not have an open deposit." << std::endl;
            }
        }
    }

    void output_accumulated_interest() //Производит снятие накопленных процентов с депозита на зарплатный счёт клиента.
    {
        if (check_login_client())
        {
            print_login_client();
            std::cout << std::endl;
            if (database[position_in_database].deposit_info.get_is_open())
            {
                database[position_in_database].set_amount_salary_account(database[position_in_database].get_amount_salary_account() + database[position_in_database].deposit_info.get_accumulated_interest());
                database[position_in_database].deposit_info.set_accumulated_interest(0);
                std::cout << "The percentage amount was transferred to the client's salary account." << std::endl;
            }
            else
            {
                std::cout << "This client does not have an open deposit." << std::endl;
            }
        }
    }

    void close_deposit() //Закрывает депозит клиента.
    {
        if (check_login_client())
        {
            print_login_client();
            std::cout << std::endl;
            if (database[position_in_database].deposit_info.get_is_open())
            {
                if (database[position_in_database].deposit_info.get_term() == database[position_in_database].deposit_info.get_now_term())
                {
                    database[position_in_database].set_amount_salary_account(database[position_in_database].get_amount_salary_account() + database[position_in_database].deposit_info.get_accumulated_interest() + database[position_in_database].deposit_info.get_amount());
                    database[position_in_database].deposit_info.set_accumulated_interest(0);
                    database[position_in_database].deposit_info.set_amount(0);
                    database[position_in_database].deposit_info.set_term(0);
                    database[position_in_database].deposit_info.set_now_term(0);
                    database[position_in_database].deposit_info.set_rate(0.0);
                    database[position_in_database].deposit_info.set_is_open(false);
                    std::cout << "The deposit has been successfully closed." << std::endl;
                }
                else
                {
                    std::cout << "The deposit cannot be closed. The deposit period is not over yet." << std::endl;
                }
            }
            else
            {
                std::cout << "This client does not have an open deposit." << std::endl;
            }
        }
    }

    void fast_forward_several_months(int _months) //"Перемотка времени" на нескоько месяцев вперёд.
    {
        if (database.empty() != true) //empty() проверяет пустой ли вектор(пустой - true, иначе false).
        {
            for (int i = 0; i < database.size(); ++i)
            {
                if (database[i].deposit_info.get_is_open())
                {
                    for (int j = 0; j < _months; ++j)
                    {
                        if (database[i].deposit_info.get_now_term() < database[i].deposit_info.get_term())
                        {
                            database[i].deposit_info.set_now_term(database[i].deposit_info.get_now_term() + 1);
                            database[i].deposit_info.set_accumulated_interest(database[i].deposit_info.get_accumulated_interest() + calculating_percentages_month(database[i].deposit_info.get_amount(), database[i].deposit_info.get_rate()));
                        }
                        else
                        {
                            break;
                        }
                    }
                }
            }
            std::cout << "The rewinding of time to <" << _months << "> months ahead has been completed." << std::endl;
        }
        else
        {
            std::cout << "Database is empty." << std::endl;
        }
    }
};

int main()
{
    Deposit test;
    test.add_client_in_database("7436", 576934, "kfie402j5", "Nikita", "Shcherbakov", "Andreevich");
    std::cout << "====================" << std::endl;

    test.login_client("7436", "j92h5"); //Попытка авторизироваться с неверным паролем.
    test.login_client("7436", "kfie402j5");
    std::cout << "====================" << std::endl;

    test.print_info_login_client();
    std::cout << "====================" << std::endl;

    test.show_info_available_deposit();
    std::cout << "====================" << std::endl;

    test.сheck_is_open_deposit();
    std::cout << "====================" << std::endl;

    test.open_deposit(356965, 12);
    std::cout << "====================" << std::endl;

    test.сheck_is_open_deposit();
    std::cout << "====================" << std::endl;

    test.open_deposit(10000, 3); //Попытка открыть второй депозит.
    std::cout << "====================" << std::endl;

    test.show_status_deposit();
    std::cout << "====================" << std::endl;

    test.fast_forward_several_months(3); //Перемотка времени на 3 месяц.
    std::cout << "====================" << std::endl;

    test.show_status_deposit();
    std::cout << "====================" << std::endl;

    test.close_deposit(); //Попытка закрыть депозит до окончания его срока.
    std::cout << "====================" << std::endl;

    test.print_info_login_client();
    std::cout << "====================" << std::endl;

    test.output_accumulated_interest();
    std::cout << "====================" << std::endl;

    test.print_info_login_client();
    std::cout << "====================" << std::endl;

    test.fast_forward_several_months(10); //Перемотка времени на 10 месяц.
    std::cout << "====================" << std::endl;

    test.show_status_deposit();
    std::cout << "====================" << std::endl;

    test.print_info_login_client();
    std::cout << "====================" << std::endl;

    test.close_deposit();
    std::cout << "====================" << std::endl;

    test.show_status_deposit();
    std::cout << "====================" << std::endl;

    test.print_info_login_client();
    std::cout << "====================" << std::endl;
}