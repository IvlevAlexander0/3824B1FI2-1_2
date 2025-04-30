#include <iostream>
#include <vector>
#include <functional>
#include <string>

using namespace std;

class Menu {
private:
    struct MenuItem {
        string name;
        function<void(double)> action;
    };

    vector<MenuItem> items;
    int lastSelectedIndex;

public:
    // Конструктор
    Menu() : lastSelectedIndex(-1) {}

    //Деструктор
    ~Menu() {}

    //1) Задать число команд
    void setNumCommands(int num) {
        if (num >= 0) {
            items.resize(num);
        }
    }

    //2) Узнать число команд
    int getNumCommands() const {
        return items.size();
    }

    //3) Создать команду
    void setCommand(int index, const string& name, function<void(double)> action) {
        if (index >= 0 && index < items.size()) {
            items[index].name = name;
            items[index].action = action;
        }
    }

    //4) Вывести меню
    void displayMenu() const {
        cout << "Menu:" << endl;
        for (size_t i = 0; i < items.size(); ++i) {
            cout << i + 1 << ". " << items[i].name << endl;
        }
        cout << "Enter your choice: ";
    }

    //5) Выбор команды
    void selectCommand() {
        int choice;
        double argument;

        displayMenu();
        cin >> choice;

        if (choice >= 1 && choice <= static_cast<int>(items.size())) {
            lastSelectedIndex = choice - 1;
            cout << "You've selected: " << items[lastSelectedIndex].name << endl;
            cout << "Enter the function's argument: ";
            cin >> argument;
            items[lastSelectedIndex].action(argument);
        }
        else {
            cout << "Invalid choice!" << endl;
        }
    }

    //6) Вернуть номер последнего выбранного пункта меню
    int getLastSelectedIndex() const {
        return lastSelectedIndex;
    }
};

void Arg(double x) {
    cout << "Action was executed with an argument: " << x << endl;
}

int main() {
    Menu menu;
    menu.setNumCommands(3);
    menu.setCommand(0, "Command 1", Arg);
    menu.setCommand(1, "Command 2", Arg);
    menu.setCommand(2, "Command 3", Arg);

    menu.selectCommand();

    cout << "Last selected command index: " << menu.getLastSelectedIndex() << endl;

    return 0;
}