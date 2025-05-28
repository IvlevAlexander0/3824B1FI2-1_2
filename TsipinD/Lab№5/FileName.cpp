#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool isDigits4(const string& s) {
    if (s.length() != 4) return false;
    for (char c : s) {
        if (c < '0' || c > '9') {
            return false;
        }
    }
    return true;
}


bool isValidCardNumber(const string& card) {
    if (!isDigits4(card))
        return false;
    if (card < "0001" || card > "9999")
        return false;
    return true;
}

bool isValidPin(const string& pin) {
    if (!isDigits4(pin))
        return false;
    if (pin < "0000" || pin > "9999")
        return false;
    return true;
}

struct Denomination {
    int value;
    int count;
};

class Client {
public:
    string cardNumber;
    string fullName;
    int balance;
    string pin;
    bool isBlocked;

    Client(string cardNum, string name, int initialBalance, string pinCode)
        : cardNumber(cardNum), fullName(name), balance(initialBalance), pin(pinCode), isBlocked(false) {
    }
};

class ProcessingCenter {
private:
    vector<Client> clients;
public:
    void addClient(const Client& client) {
        if (!isValidCardNumber(client.cardNumber)) {
            cout << "Error: Incorrect card number or card format: " << client.cardNumber << endl;
            return;
        }
        if (!isValidPin(client.pin)) {
            cout << "Error: Incorrect PIN-code format: " << client.pin << endl;
            return;
        }
        clients.push_back(client);
    }

    Client* findClient(const string& cardNumber) {
        for (Client& client : clients) {
            if (client.cardNumber == cardNumber) {
                return &client;
            }
        }
        return nullptr;
    }

    bool checkPin(const string& cardNumber, const string& pin) {
        Client* client = findClient(cardNumber);
        return client && !client->isBlocked && (client->pin == pin);
    }

    void blockCard(const string& cardNumber) {
        if (Client* client = findClient(cardNumber)) {
            client->isBlocked = true;
            cout << "The card " << cardNumber << " is blocked!" << endl;
        }
    }
};

class ATM {
private:
    Denomination denominations[6] = {
        {5000, 1600}, {2000, 1600}, {1000, 1600},
        {500, 1600}, {200, 1600}, {100, 1600}
    };
    ProcessingCenter& processingCenter;
    Client* currentClient = nullptr;
    int wrongPinAttempts = 0;

    int findDenominationIndex(int value) {
        for (int i = 0; i < 6; ++i) {
            if (denominations[i].value == value) {
                return i;
            }
        }
        return -1;
    }

public:
    ATM(ProcessingCenter& pc) : processingCenter(pc) {}

    bool acceptCard(const string& cardNumber) {
        if (!isValidCardNumber(cardNumber)) {
            cout << "Error: Incorrect card number!" << endl;
            return false;
        }
        currentClient = processingCenter.findClient(cardNumber);
        wrongPinAttempts = 0;
        if (!currentClient || currentClient->isBlocked) {
            cout << "No data!" << endl;
            return false;
        }
        return true;
    }

    bool verifyPin(const string& pin) {
        if (!currentClient)
            return false;
        if (!isValidPin(pin)) {
            cout << "Error: Incorrect PIN-code!" << endl;
            return false;
        }
        if (currentClient->pin == pin) {
            wrongPinAttempts = 0;
            return true;
        }
        if (++wrongPinAttempts >= 3) {
            processingCenter.blockCard(currentClient->cardNumber);
        }
        cout << "Error: Incorrect PIN-code!"<< endl;
        return false;
    }

    void showBalance() const {
        if (currentClient) {
            cout << "Client: " << currentClient->fullName << endl;
            cout << "Balance: " << currentClient->balance << " rubles.\n";
        }
    }

    bool takeCash(int amount) {
        if (!currentClient || amount <= 0 || amount > currentClient->balance) {
            return false;
        }
        vector<pair<int, int>> PayOut;
        int tempCounts[6];
        for (int i = 0; i < 6; ++i) {
            tempCounts[i] = denominations[i].count;
        }
        int remaining = amount;
        for (int i = 0; i < 6 && remaining > 0; ++i) {
            int possible = min(remaining / denominations[i].value, tempCounts[i]);
            possible = min(possible, 40);
            if (possible > 0) {
                PayOut.emplace_back(denominations[i].value, possible);
                remaining -= denominations[i].value * possible;
                tempCounts[i] -= possible;
            }
        }
        if (remaining == 0) {
            currentClient->balance -= amount;
            for (int i = 0; i < 6; ++i) {
                denominations[i].count = tempCounts[i];
            }
            return true;
        }
        return false;
    }

    bool depositCash(const vector<pair<int, int>>& payment) {
        if (!currentClient || payment.empty()) return false;
        int total = 0;
        for (const pair<int, int>& note : payment) {
            const int value = note.first;
            const int count = note.second;
            const int id = findDenominationIndex(value);
            if (id == -1 || count <= 0 || count > 40 || denominations[id].count + count > 2000) {
                return false;
            }
            total += value * count;
        }
        currentClient->balance += total;
        for (const pair<int, int>& note : payment) {
            denominations[findDenominationIndex(note.first)].count += note.second;
        }
        return true;
    }

    void returnCard() {
        if (currentClient) {
            cout << "The card " << currentClient->cardNumber << " was returned\n";
            currentClient = nullptr;
        }
    }
};

int main() {
    ProcessingCenter center;
    // корректные данные
    center.addClient({ "0001", "Jesse Pinkman", 50000, "1111" });
    center.addClient({ "0002", "Walter White", 100000, "9999" });

    // некорректные данные
    center.addClient({ "123", "Bad Guy", 50000, "9999" });     // Ошибка карты
    center.addClient({ "0009", "Bad Pin", 50000, "abcd" });    // Ошибка пина

    ATM atm(center);

    cout << '\n' << '\n';

    if (atm.acceptCard("0001") && atm.verifyPin("1111")) {
        atm.showBalance();
        atm.takeCash(3700);
        atm.showBalance();
        atm.depositCash({ {500, 5}, {1000, 2} });
        atm.showBalance();
        atm.returnCard();
    }
    cout << '\n' << '\n';
    // Тест ошибок пина:
    if (atm.acceptCard("0002")) {
        atm.verifyPin("qwer");
        atm.verifyPin("1000");
        atm.verifyPin("9999");
        atm.returnCard();
    }
    return 0;
}