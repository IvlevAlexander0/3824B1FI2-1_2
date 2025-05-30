#include <iostream>
#include <map>
#include <string>
#include <stdexcept>
#include <iomanip>

using namespace std;

class Deposit {
public:
    enum Term { THREE_MONTHS = 3, SIX_MONTHS = 6, ONE_YEAR = 12, TWO_YEARS = 24, THREE_YEARS = 36 };

private:
    string accountNumber;
    string ownerName;
    double salaryAccountBalance;
    double depositAmount;
    double interestRate;
    Term term;
    bool isActive;
    int monthsElapsed;

public:
    Deposit()
        : accountNumber(""), ownerName(""), salaryAccountBalance(0.0),
        depositAmount(0.0), interestRate(0.0), term(ONE_YEAR),
        isActive(false), monthsElapsed(0) {}

    Deposit(string accNum, string name, double balance)
        : accountNumber(accNum), ownerName(name), salaryAccountBalance(balance),
        depositAmount(0), interestRate(0), term(ONE_YEAR), isActive(false), monthsElapsed(0) {}

    bool authorize(const string& accNum, const string& password) {
        return accNum == accountNumber;
    }

    void showAvailableDeposits() {
        cout << "Available deposites for " << salaryAccountBalance << " rub:\n";
        if (salaryAccountBalance < 100000) {
            cout << "1. 3 months: 5%\n";
            cout << "2. 6 months: 5.5%\n";
            cout << "3. 1 year: 6%\n";
            cout << "4. 2 years: 6.5%\n";
            cout << "5. 3 years: 7%\n";
        }
        else if (salaryAccountBalance < 500000) {
            cout << "1. 3 months: 5.5%\n";
            cout << "2. 6 months: 6%\n";
            cout << "3. 1 год: 6.5%\n";
            cout << "4. 2 years: 7%\n";
            cout << "5. 3 years: 7.5%\n";
        }
        else if (salaryAccountBalance < 1000000) {
            cout << "1. 3 months: 6%\n";
            cout << "2. 6 months: 6.5%\n";
            cout << "3. 1 year: 7%\n";
            cout << "4. 2 years: 7.5%\n";
            cout << "5. 3 years: 8%\n";
        }
        else {
            cout << "1. 3 months: 6.5%\n";
            cout << "2. 6 months: 7%\n";
            cout << "3. 1 year: 7.5%\n";
            cout << "4. 2 years: 8%\n";
            cout << "5. 3 years: 8.5%\n";
        }
    }


    void openDeposit(double amount, Term t) {
        if (amount > salaryAccountBalance) {
            throw runtime_error("Not enough money on salary balance");
        }
        if (isActive) {
            throw runtime_error("Deposit is open");
        }

        depositAmount = amount;
        term = t;
        salaryAccountBalance -= amount;

        switch (term) {
        case THREE_MONTHS:
            interestRate = (salaryAccountBalance < 100000) ? 0.05 : (salaryAccountBalance < 500000) ? 0.055 : (salaryAccountBalance < 1000000) ? 0.06 : 0.065;
            break;
        case SIX_MONTHS:
            interestRate = (salaryAccountBalance < 100000) ? 0.055 : (salaryAccountBalance < 500000) ? 0.06 : (salaryAccountBalance < 1000000) ? 0.065 : 0.07;
            break;
        case ONE_YEAR:
            interestRate = (salaryAccountBalance < 100000) ? 0.06 : (salaryAccountBalance < 500000) ? 0.065 : (salaryAccountBalance < 1000000) ? 0.07 : 0.075;
            break;
        case TWO_YEARS:
            interestRate = (salaryAccountBalance < 100000) ? 0.065 : (salaryAccountBalance < 500000) ? 0.07 : (salaryAccountBalance < 1000000) ? 0.075 : 0.08;
            break;
        case THREE_YEARS:
            interestRate = (salaryAccountBalance < 100000) ? 0.07 : (salaryAccountBalance < 500000) ? 0.075 : (salaryAccountBalance < 1000000) ? 0.08 : 0.085;
            break;
        default: throw runtime_error("Wrong period");
        }

        isActive = true;
        monthsElapsed = 0;

        cout << "Deposit open of " << depositAmount << " rub for " << term << " months with " << interestRate * 100 << "%\n";
    }

    void checkDeposit() const {
        if (!isActive) {
            cout << "Deposit not opened\n";
        }
        else {
            cout << fixed << setprecision(2);
            cout << "Deposit balance: " << depositAmount + calculateInterest() << " rub\n";
        }
    }

    void withdrawInterest() {
        if (!isActive) {
            throw runtime_error("Deposit not opened");
        }
        double interest = calculateInterest();
        depositAmount -= interest;
        salaryAccountBalance += interest;
        monthsElapsed++;
        cout << "Interest withdraw: " << interest << " rub\n";
    }

    void plusMonth() {
        if (isActive) {
            monthsElapsed++;
            cout << "Time skiped on 1 month\n";
        }
        else {
            throw runtime_error("Deposite not opened");
        }
    }

    void closeDeposit() {
        if (!isActive || monthsElapsed < term) {
            throw runtime_error("U can't close deposit until end of period");
        }
        double totalAmount = depositAmount + calculateInterest();
        salaryAccountBalance += totalAmount;
        isActive = false;
        depositAmount = 0;
        cout << "Deposit closed. Money transfered to salary balance: " << totalAmount << " rub\n";
    }

private:
    double calculateInterest() const {
        return depositAmount * interestRate / 12 * (monthsElapsed + 1);
    }
};

class ProcessingCenter {
private:
    map<string, tuple<string, double, string>> clients; // номер - фио, баланс, пароль
    map<string, Deposit> deposits; // номер - депозит

public:
    void addClient(const string& accountNumber, const string& ownerName, double balance, const string& password) {
        clients[accountNumber] = make_tuple(ownerName, balance, password);
    }

    Deposit& getDeposit(const string& accountNumber) {
        return deposits[accountNumber];
    }

    void createDeposit(const string& accountNumber) {
        auto it = clients.find(accountNumber);
        if (it == clients.end()) throw runtime_error("Client not found");

        Deposit deposit(accountNumber, get<0>(it->second), get<1>(it->second));
        deposits[accountNumber] = deposit;
    }

    bool authorizeClient(const string& accountNumber, const string& password) {
        auto it = clients.find(accountNumber);
        if (it != clients.end()) {
            return get<2>(it->second) == password;
        }
        return false;
    }

    void showClientDeposits(const string& accountNumber) {
        auto it = deposits.find(accountNumber);
        if (it != deposits.end()) {
            it->second.checkDeposit();
        }
        else {
            cout << "Client has no opened deposites\n";
        }
    }

    void showSalaryAccountBalance(const string& accountNumber) {
        auto it = clients.find(accountNumber);
        if (it != clients.end()) {
            cout << fixed << setprecision(2);
            cout << "Client salary balance: " << get<0>(it->second)
                << ": " << get<1>(it->second) << " rub\n";
        }
        else {
            cout << "Client not found\n";
        }
    }
};

void displayMenu() {
    cout << "-------------------\n"
        << "Menu:\n"
        << "1 Add client\n"
        << "2 Open deposit\n"
        << "3 Check deposit\n"
        << "4 Wisdraw %\n"
        << "5 Close deposit\n"
        << "6 Show salary balance\n" // необязательная функция для проверки счёта вывода
        << "7 (godmod) month skip\n"
        << "0 EXIT\n"
        << "Choose num: ";
}

int main() {
    ProcessingCenter pc;

    while (true) {
        displayMenu();

        int choice;
        cin >> choice;

        switch (choice) {
        case 1: { // добавить акк
            string accountNumber, ownerName, password;
            double balance;

            cout << "\nEnter account number: ";
            cin >> accountNumber;

            cout << "Client name: ";
            cin.ignore();
            getline(cin, ownerName);

            cout << "Enter balance: ";
            cin >> balance;

            cout << "Enter password: ";
            cin >> password;

            pc.addClient(accountNumber, ownerName, balance, password);
            pc.createDeposit(accountNumber);
            break;
        }

        case 2: { // открыть депозит
            string accountNumber, password;
            cout << "\nEnter account number for deposit: ";
            cin >> accountNumber;

            cout << "Enter password: ";
            cin >> password;

            if (!pc.authorizeClient(accountNumber, password)) {
                cout << "Wrong number or password\n";
                break;
            }

            try {
                Deposit& deposit = pc.getDeposit(accountNumber);
                deposit.showAvailableDeposits();

                double depositAmount;
                int termChoice;

                cout << "\n--------------------\n" << "ENTER DEPOSITE AMOUNT (rub): ";
                cin >> depositAmount;

                cout << "Choose term:\n1 - 3 months\n2 - 6 months\n3 - 1 year\n4 - 2 years\n5 - 3 years\nEnter: ";
                cin >> termChoice;

                Deposit::Term term;
                switch (termChoice) {
                case 1: term = Deposit::THREE_MONTHS; break;
                case 2: term = Deposit::SIX_MONTHS; break;
                case 3: term = Deposit::ONE_YEAR; break;
                case 4: term = Deposit::TWO_YEARS; break;
                case 5: term = Deposit::THREE_YEARS; break;
                default:
                    cout << "Wrong term\n";
                    continue;
                }

                deposit.openDeposit(depositAmount, term);
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }

        case 3: { // проверить депозит
            string accountNumber, password;
            cout << "\nEnter account number of deposit: ";
            cin >> accountNumber;

            cout << "Enter password: ";
            cin >> password;

            if (!pc.authorizeClient(accountNumber, password)) {
                cout << "Wrong number or password\n";
                break;
            }

            pc.showClientDeposits(accountNumber);
            break;
        }

        case 4: { // снять проценты
            string accountNumber, password;
            cout << "\nEnter account number to wisdraw %: ";
            cin >> accountNumber;

            cout << "Enter password: ";
            cin >> password;

            if (!pc.authorizeClient(accountNumber, password)) {
                cout << "Wrong number or password\n";
                break;
            }

            try {
                     Deposit & deposit = pc.getDeposit(accountNumber);
                     deposit.withdrawInterest();
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }

        case 5: { // закрыть депозит
            string accountNumber, password;
            cout << "\nEnter account number to deposit: ";
            cin >> accountNumber;

            cout << "Enter password: ";
            cin >> password;

            if (!pc.authorizeClient(accountNumber, password)) {
                cout << "Wrong number or password\n";
                break;
            }

            try {
                Deposit& deposit = pc.getDeposit(accountNumber);
                deposit.closeDeposit();
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }

        case 6: { // Показать баланс зарплатного счета клиента
            string accountNumber, password;
            cout << "\nEnter account number: ";
            cin >> accountNumber;

            cout << "Enter password: ";
            cin >> password;

            if (!pc.authorizeClient(accountNumber, password)) {
                cout << "Wrong number or password\n";
                break;
            }

            pc.showSalaryAccountBalance(accountNumber);
            break;
        }

        case 7: { // увеличить время на один месяц
            string accountNumber, password;
            cout << "\nEnter account number: ";
            cin >> accountNumber;

            cout << "Enter password: ";
            cin >> password;

            if (!pc.authorizeClient(accountNumber, password)) {
                cout << "Wrong number or password\n";
                break;
            }

            try {
                Deposit& deposit = pc.getDeposit(accountNumber);
                deposit.plusMonth();
            }
            catch (const runtime_error& e) {
                cout << e.what() << endl;
            }
            break;
        }

        case 0: // выход
            cout << "exiting...\n";
            return 0;

        default:
            cout << "wrong num\n";
            break;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return 0;
}