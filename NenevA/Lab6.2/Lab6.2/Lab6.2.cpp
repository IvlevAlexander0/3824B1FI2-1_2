#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

class Player {
public:
    virtual string makeGuess() = 0;
};

class HumanPlayer : public Player {
public:
    string makeGuess() override {
        string guess;
        cout << "Try to guess my number: ";
        cin >> guess;
        return guess;
    }
};

class ComputerPlayer {
public:
    string generateSecretNumber(int length) {
        string digits = "0123456789";
        string number;
        bool used[10] = { false };

        int ind = 1 + rand() % 9;
        used[ind] = true;
        number += digits[ind];

        while (number.length() < length) {
            int index = rand() % 10;
            if (!used[index]) {
                used[index] = true;
                number += digits[index];
            }
        }

        return number;
    }
};

class Game {
private:
    ComputerPlayer computer;
    Player* human;
    string secretNumber;
    int numberLength;

    bool isValidGuess(const string& guess) {
        if (guess.length() != numberLength) {
            return false;
        }
        bool used[10] = { false };
        for (char c : guess) {
            if (!isdigit(c) || used[c - '0']) {
                return false;
            }
            used[c - '0'] = true;
        }
        return true;
    }

public:
    Game(int length, Player* player) : human(player), numberLength(length) {
        srand(time(NULL));
        secretNumber = computer.generateSecretNumber(length);
    }

    void play() {
        cout << "I guessed a number with " << numberLength << " different dijits" << endl;

        while (true) {
            string guess = human->makeGuess();

            if (!isValidGuess(guess)) {
                cout << "Incorrect input! Enter a number with " << numberLength << " different dijits instead!" << endl;
                continue;
            }
            if (guess[0] == '0') {
                cout << "Incorrect input! Enter a number that doesn't start with 0 instead!" << endl;
                continue;
            }
            int bulls = 0;
            int cows = 0;

            for (int i = 0; i < numberLength; ++i) {
                if (guess[i] == secretNumber[i]) {
                    bulls++;
                }
                else {
                    for (int j = 0; j < numberLength; ++j) {
                        if (guess[i] == secretNumber[j]) {
                            if (i != j) {
                                cows++;
                                break;
                            }
                        }
                    }
                }
            }

            cout << "Bulls: " << bulls << ", Cows: " << cows << endl;

            if (bulls == numberLength) {
                cout << "You've guessed!" << endl;
                break;
            }
        }
    }
};

int main() {
    int length;
    cout << "Enter number's length (n): ";
    cin >> length;

    if (length < 1 || length > 10) {
        cout << "Number's length must be in range [1, 10] as there're only 10 different dijits." << endl;
        return 1;
    }

    HumanPlayer humanPlayer;
    Game game(length, &humanPlayer);
    game.play();

    return 0;
}
