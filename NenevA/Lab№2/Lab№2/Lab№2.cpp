#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cctype>
#include <unordered_set>

using namespace std;

class String {
private:
    char* data;
    size_t length;

public:
    // Конструктор
    String() : data(new char[1]), length(0) {
        data[0] = '\0';
    }

    // Конструктор
    String(const char* str) : length(strlen(str)) {
        data = new char[length + 1];
        strcpy(data, str);
    }

    // Конструктор копирования
    String(const String& other) : length(other.length) {
        data = new char[length + 1];
        strcpy(data, other.data);
    }

    // Деструктор
    ~String() {
        delete[] data;
    }

    // Присваивание
    String& operator=(const String& other) {
        if (this != &other) {
            delete[] data;
            length = other.length;
            data = new char[length + 1];
            strcpy(data, other.data);
        }
        return *this;
    }

    // 1) Задать строку
    void setString(const char* str) {
        delete[] data;
        length = strlen(str);
        data = new char[length + 1];
        strcpy(data, str);
    }

    // 2) Узнать длину
    size_t getLength() const {
        return length;
    }

    // 3) Узнать символ по индексу
    char getCharAt(size_t index) const {
        if (index >= length) {
            cerr << "Index out of bounds" << endl;
            return '\0';
        }
        return data[index];
    }

    // 4) Изменить символ по индексу
    void setCharAt(size_t index, char ch) {
        if (index >= length) {
            cerr << "Index out of bounds" << endl;
            return;
        }
        data[index] = ch;
    }

    // 5) Подстрока
    String substring(size_t start, size_t end) const {
        if (start > end || end > length) {
            cerr << "Invalid substring range" << endl;
            return String();
        }
        char* subData = new char[end - start + 1];
        strncpy(subData, data + start, end - start);
        subData[end - start] = '\0';
        String result(subData);
        delete[] subData;
        return result;
    }

    // 6) Палиндром
    bool isPalindrome() const {
        int left = 0;
        int right = getLength() - 1;

        while (left < right) {
            while (left < right && isspace(data[left])) {
                left++;
            }
            while (left < right && isspace(data[right])) {
                right--;
            }
            if (tolower(data[left]) != tolower(data[right])) {
                return false;
            }
            left++;
            right--;
        }
        return true;
    }

    // 7) Уникальные латинские буквы через последовательность символов
    size_t countUniqueLatinChars() const {
        unordered_set<char> uniqueChars;
        for (size_t i = 0; i < length; ++i) {
            char ch = tolower(data[i]);
            if ((ch >= 'a' && ch <= 'z')) {
                uniqueChars.insert(ch);
            }
        }
        return uniqueChars.size();
    }

    // Вывести строку
    void print() const {
        cout << data << endl;
    }
};

int main() {
    String str("A Toyota");
    str.print();
    cout << "Length = " << str.getLength() << endl;
    cout << "Character at index 5 is " << str.getCharAt(5) << endl;

    str.print();
    String subStr = str.substring(0, 5);
    subStr.print();

    cout << (str.isPalindrome() ? "Is a palindrome" : "Not a palindrome") << endl;
    str.setCharAt(5, '-');
    str.print();

    cout << "Unique Latin letters = " << str.countUniqueLatinChars() << endl;
    return 0;
}