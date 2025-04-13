#include <iostream>
#include <string>
#include <cmath> // Для использования pow

void default_func(double a) {
    std::cout << "It's a " << __func__ << " function." << std::endl;
}

void print_a(double a) {
    std::cout << "It's a " << __func__ << " function." << std::endl;
    std::cout << a << std::endl;
}

void square(double a) {
    std::cout << "It's a " << __func__ << " function." << std::endl;
    std::cout << a * a << std::endl;
}

void cube(double a) {
    std::cout << "It's a " << __func__ << " function." << std::endl;
    std::cout << pow(a, 3) << std::endl;
}

class option {
public:
    std::string name;
    void (*function)(double a);

    option() : name("None"), function(default_func) {}

    option(std::string name_) : name(name_), function(default_func) {}

    option(std::string name_, void (*function_)(double a)) : name(name_), function(function_) {}

    ~option() {}
};

std::ostream& operator<<(std::ostream& stream, const option& Option) {
    stream << "Option - " << Option.name << "." << std::endl;
    return stream;
}

class menu {
public:
    int n;
    int rememberance = -1;
    option* options = nullptr;

    menu(){
        n = 0;
        options = nullptr;
    }

    menu(int n_) :
        n(n_), options(nullptr) {
        if (n_ > 0) {
            options = new option[n_];
            for (int i = 0; i < n_; i++) {
                options[i];
            }
        }
        else {
            throw std::invalid_argument("Bad size.");
        }
    }

    int get_num_com() const {
        return n;
    }

    void set_num_com(int n_) {
        if (n_ > 0) {
            int old_n = n;
            n = n_;
            option* new_options = new option[n];
            for (int i = 0; i < std::min(old_n, n); i++) {
                new_options[i] = options[i];
            }
            delete[] options;
            options = new_options;
        }
        else {
            std::cout << "Not valid argument." << std::endl;
        }
    }

    void set_option(int itoe, const std::string& name, void (*function_)(double a)) {
        if (itoe < 0 || itoe >= n) {
            std::cout << "Invalid index." << std::endl;
        }
        else {
            options[itoe] = option(name, function_);
        }
    }

    void do_option(int itoe) {
        if (itoe < 0 || itoe >= n) {
            std::cout << "Invalid argument." << std::endl;
        }
        else {
            std::cout << "You have chosen option " << itoe + 1 << "." << std::endl;
            std::cout << options[itoe];
            std::cout << "Input the argument of function: ";
            double a;
            std::cin >> a;
            options[itoe].function(a);
            rememberance = itoe;
        }
    }

    int get_rememberance() const {
        return rememberance;
    }
    ~menu() {
        delete[] options;
    }
};

std::ostream& operator<<(std::ostream& stream, const menu& Menu) {
    stream << "Menu" << std::endl;
    for (int i = 0; i < Menu.n; i++) {
        stream << i + 1 << " - " << Menu.options[i];
    }
    return stream;
}

int main() {
    menu Menu(3);
    std::cout << Menu;
    Menu.set_option(2, "Square", square);
    std::cout << Menu;
    std::cout << "Enter option of menu: ";
    int itoe;
    std::cin >> itoe;
    Menu.do_option(itoe);
    return 0;
}
