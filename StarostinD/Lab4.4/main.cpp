#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
using namespace std;

class Contact;
class Contacts;
struct MyError;
bool check(const Contact& x, const Contact& y);

class Contact {
private:
	friend bool check(const Contact& x, const Contact& y);
	friend Contacts;
	string name[3];
	long long phone;
	int DOB[3];
	bool favorite;
public:
	Contact(string surn, string n, string patr, long long p, int day, int month, int year, bool fav) : phone{ p }, favorite{ fav } {
		name[0] = surn, name[1] = n, name[2] = patr;
		DOB[0] = day, DOB[1] = month, DOB[2] = year;
	}

};
bool check(const Contact& x, const Contact& y) {
	if (x.name[0] == y.name[0]) {
		if (x.name[1] == y.name[1]) {
			return x.name[2] < y.name[2];
		}
		return x.name[1] < y.name[1];
	}
	return x.name[0] < y.name[0];
}
struct MyError {
	string str;
	MyError(const string str_) : str(str_) {};
};
class Contacts {
private:
	vector<Contact> book;
	size_t cur;
	size_t size;
	bool find(long long phone) {
		for (int i = 0; i < size; ++i) {
			if(book[i].phone == phone) {
				cur = i;
				return true;
			}
		}
		return false;
	}
	bool find(const string& fullname) {
		string tmp;
		for (int i = 0; i < size; ++i) {
			tmp = book[i].name[0] + ' ' + book[i].name[1] + ' ' + book[i].name[2];
			if (tmp == fullname) {
				cur = i;
				return true;
			}
		}
		return false;
	}
public:
	Contacts() : book(), cur(0), size(0) {};
	Contacts(const Contacts& copy) : book(copy.book), cur(0), size(copy.size) {};
	Contacts(const vector<Contact>& bk) : book(bk), cur(0), size(bk.size()) {};
	void add(const Contact a) {
		bool b1 = find(a.name[0] + ' ' + a.name[1] + ' ' + a.name[2]);
		bool b2 = find(a.phone);
		if (!b1 && !b2) {
			book.push_back(a);
			sort(book.begin(), book.end(), check);
			++size;
			cur = 0;
		}
		else if(b1) {
			throw(MyError("Contact " + a.name[0] + ' ' + a.name[1] + ' ' + a.name[2] + " already exists"));
		}
		else {
			throw(MyError("Contact with phone " + to_string(a.phone) + " already exists"));
		}
	}
	void choose(const string& fullname) {
		if (!find(fullname)) {
			cur = 0;
			throw(MyError(fullname + " Not found"));
		}
	}
	void choose(long long phone) {
		if (!find(phone)) {
			cur = 0;
			throw(MyError(to_string(phone) + " Not found"));
		}
	}
	void remove() {
		auto it = book.begin() + cur;
		book.erase(it);
		--size;
	}
	void set_name(string fullname) {
		if (!find(fullname)) {
			size_t pos1 = 0, pos2 = 0;
			for (int i = 0; i < 3; ++i) {
				pos2 = fullname.find(" ", pos1);
				book[cur].name[i] = fullname.substr(pos1, pos2 - pos1);
				pos1 = pos2 + 1;
			}
			sort(book.begin(), book.end(), check);
			find(fullname);
		}
		else {
			throw(MyError("Contact " + fullname + " already exists"));
		}
	}
	void set_phone(long long phone) {
		if (!find(phone)) {
			book[cur].phone = phone;
		}
		else {
			throw(MyError("Contact with phone" + to_string(phone) + " already exists"));
		}
	}
	void set_DOB(int day, int month, int year) {
		book[cur].DOB[0] = day;
		book[cur].DOB[1] = month;
		book[cur].DOB[2] = year;
	}
	size_t get_size() const {
		return size;
	}
	void get_contacts() const {
		int i = 1;
		for (Contact x : book) {
			cout << i++ << ") " << x.name[0] << ' ' << x.name[1] << ' ' << x.name[2] << ' ' << x.phone << ' ' << x.DOB[0] << '.'
				 << x.DOB[1] << '.' << x.DOB[2] << '\n';
		}
	}
	void get_contacts(const char ch) const {
		int i = 1;
		cout << (char)toupper(ch) << ":\n";
		for (Contact x : book) {
			if(x.name[0][0] == toupper(ch))
				cout << i++ << ") " << x.name[0] << ' ' << x.name[1] << ' ' << x.name[2] << ' ' << x.phone << ' ' << x.DOB[0] << '.'
				     << x.DOB[1] << '.' << x.DOB[2] << '\n';
		}
	}
	void chosen() const {
		cout << book[cur].name[0] << ' ' << book[cur].name[1] << ' ' << book[cur].name[2] << ' ' << book[cur].phone << ' '
			 << book[cur].DOB[0] << '.' << book[cur].DOB[1] << '.' << book[cur].DOB[2] << '\n';
	}
	void get_favorite() const{
		int i = 1;
		for (Contact x : book) {
			if (x.favorite == true) {
				cout << i++ << ") " << x.name[0] << ' ' << x.name[1] << ' ' << x.name[2] << ' ' << x.phone << ' ' << x.DOB[0] << '.'
					 << x.DOB[1] << '.' << x.DOB[2] << '\n';
			}
		}
	}
	bool is_favorite() const {
		return book[cur].favorite;
	}
	void make_favorite() {
		book[cur].favorite = true;
	}
	void remove_favorite() {
		book[cur].favorite = false;
	}
	void save(ofstream& out) const {
		if (out.is_open()) {
			for (Contact x : book) {
				for (int i = 0; i < 3; ++i) {
					out << x.name[i] << ' ';
				}
				out << x.phone << ' ';
				for (int i = 0; i < 3; ++i) {
					out << x.DOB[i] << ' ';
				}
				out << x.favorite << '\n';
			}
		}
		else {
			throw(MyError("The file is closed"));
		}
	}
	void read(ifstream& in) {
		if (in.is_open()) {
			while(!in.eof()) {
				string line;
				getline(in, line);
				size_t pos1 = 0, pos2 = 0;
				string tname[3];
				long long tphone;
				int tDOB[3]{ 0 };
				bool tfav;
				for (int i = 0; i < 3; ++i) {
					pos2 = line.find(" ", pos1);
					tname[i] = line.substr(pos1, pos2 - pos1);
					pos1 = pos2 + 1;
				}
				pos2 = line.find(" ", pos1);
				tphone = stoll(line.substr(pos1, pos2 - pos1));
				pos1 = pos2 + 1;
				for (int i = 0; i < 3; ++i) {
					pos2 = line.find(" ", pos1);
					tDOB[i] = stoi(line.substr(pos1, pos2 - pos1));
					pos1 = pos2 + 1;
				}
				pos2 = line.find(" ", pos1);
				tfav = stoi(line.substr(pos1, pos2 - pos1));
				pos1 = pos2 + 1;
				try {
					add(Contact(tname[0], tname[1], tname[2], tphone, tDOB[0], tDOB[1], tDOB[2], tfav));
				}
				catch (const MyError& Err) {
					cout << Err.str << '\n';
				}
			}
		}
		else {
			throw(MyError("The file is closed"));
		}
	}
};

int main() {
	Contacts book;
	ifstream txt("cnt.txt");
	book.read(txt);
	book.get_contacts();
	cout << "\nFavorite:\n";
	book.get_favorite();
	cout << endl;
	book.add(Contact("Pavlov", "Maksim", "Sergeevich", 79204129870, 18, 10, 1998, 1));
	book.add(Contact("Petrov", "Roman", "Konstantinovich", 79154239570, 10, 07, 1973, 0));
	book.get_contacts();
	cout << '\n';
	book.get_contacts('P');
	txt.close();
	ofstream txt1("contacts.txt");
	book.save(txt1);
	cout << "\nSize is: " << book.get_size() << endl;
	book.choose(13235648);
	cout << "Found: ";
	book.chosen();
	book.set_name("Edward Euanthe Lehtinen");
	cout << "Changed contact: ";
	book.chosen();
	cout << endl;
	book.get_contacts();
	try {
		book.choose(111);
	}
	catch (const MyError& er) {
		cerr << "\nError! " << er.str << '\n';
	}
	txt1.close();
	return 0;
}
