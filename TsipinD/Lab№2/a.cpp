#include <iostream>

using namespace std;
const size_t MAX_LENGTH = 40;

class String {
    char data[MAX_LENGTH + 1];
    int length;

public:
    String() {
        data[0] = '\0';
        length = 0;
    }
    String(char* str) {
        length = 0;
        while (str[length] != '\0' && length < MAX_LENGTH) {
            data[length] = str[length];
            ++length;
        }
        data[length] = '\0';
    }


    void SetString(char* str) {
        length = 0;
        while (str[length] != '\0' && length < MAX_LENGTH) {
            data[length] = str[length];
            ++length;
        }
        data[length] = '\0';
    }

    double GetLength() {
        return length;
    }

    char GetCharOnIndex(int index) {
        if (index < length)
            return data[index];
        else return '\0';
    }

    void SetCharOnIndex(char ch, int index) {
        if (index < length)
            data[index] = ch;
    }

    String GetSubstring(int start, int end) {
        if (start < length && end <= length && start < end) {
            String res;
            for (size_t i = start; i < end; i++) {
                res.data[i - start] = data[i];
            }
            res.data[end - start] = '\0';
            res.length = end - start;
            return res;
        }
        return String();
    }

    void PrintString() const {
        cout << "Your string: " << data << endl;
    }

    bool GetIsPalindrome() {
        for (size_t i = 0; i < length / 2; i++) {
            if (data[i] != data[length - 1 - i])
                return false;
        }
        return true;
    }

    size_t GetLatinCharCount() {
        size_t count = 0;
        bool unique[26] = { false };
        for (size_t i = 0; i < length; i++) {
            if (data[i] >= 'a' && data[i] <= 'z') {
                unique[data[i] - 'a'] = true;  
            }
            if (data[i] >= 'A' && data[i] <= 'Z') {
                unique[data[i] - 'A'] = true;
            }
        }
        for (size_t i = 0; i < 26; i++) {
            if (unique[i] == true)
                count++;
        }
        return count;
    }
};

int main() {
    String my_string;
    char str[] = "HelloWorld!";
    my_string.SetString(str);
    my_string.SetCharOnIndex('M', 5);
    my_string = my_string.GetSubstring(5, 11);
    my_string.PrintString();
    size_t count = my_string.GetLatinCharCount();
    cout << "Latin chars: " << count << endl;
    cout <<"Is it a palindrome: "<< my_string.GetIsPalindrome() << endl << endl;
    char str2[] = "gorod dorog";
    my_string.SetString(str2);
    my_string.PrintString();
    cout << "Is it a palindrome: " << my_string.GetIsPalindrome() << endl;
    return 0;
}