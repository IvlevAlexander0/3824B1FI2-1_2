#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <array>
#include <algorithm>
#include <cctype>
using namespace std;

class Goods {
private:
	string code;
	string name;
	double price;
	unsigned int discount;
public:
	Goods() : code("----"), name(""), price(0), discount(0) {};
	Goods(string c, string n, double p, int disc) {
		name = n;
		try {
			set_code(c);
		}
		catch (string e) {
			code = "----";
			cerr << e << " Code set to \"----\".(" << name << ")\n";
		}
		try {
			set_price(p);
		}
		catch (string e) {
			price = 0;
			cerr << e << " Price set to 0.(" << name << ")\n";
		}
		try {
			set_discount(disc);
		}
		catch (string e) {
			discount = 0;
			cerr << e << " Discount set to 0.(" << name << ")\n";
		}
	}
	void set_code(string c) {
		if (c.length() != 4) {
			throw(string("Code length must be equal to 4."));
		}
		code = c;
	}
	string get_code() {
		return code;
	}
	void set_name(string n) {
		name = n;
	}
	string get_name() {
		return name;
	}
	void set_price(int p) {
		if (p <= 0) {
			throw(string("Price must be greater than 0."));
		}
		price = p;
	}
	unsigned int get_price() {
		return price;
	}
	void set_discount(int disc) {
		if (disc < 1 || disc > 50) {
			throw(string("Discount must be in the range from 1 to 50."));
		}
		discount = disc;
	}
	unsigned int get_discount() {
		return discount;
	}
	friend bool operator<(const Goods&, const Goods&);
};

bool operator<(const Goods& x, const Goods& y) {
	return x.code < y.code;
}

class Store {
protected:
	vector<Goods> goods;
public:
	Store() {};
	Store(const Store& src) : goods(src.goods) {};
	Store(const vector<Goods>& goods) : goods(goods) {};
	void add(Goods t) {
		vector<Goods>::iterator it = upper_bound(goods.begin(), goods.end(), t);
		if (it != goods.end() && it->get_code() == t.get_code()) {
			throw(string("Product with this code already exists."));
		}
		goods.insert(it, t);
	}
};

bool cmp(const array<string, 5> x, const array<string, 5> y) {
	return x[0] < y[0];
}

class Cash_desk : public Store {
private:
	vector<array<string, 5>> check; // [1]наименование - [2]стоимость за единицу – [3]количество – [4]общая стоимость за товар
	vector<Goods>::iterator it;
	bool changed = 1;
	void last() {
		changed = 0;
		size_t size = check.size() + 1;
		check.resize(size);
		check.back()[0] = "CODE"; // обозначение итога
		unsigned int sum1 = 0, sum2 =0;
		for (int i = 0; i < size - 1; ++i) {
			sum1 += stoi(check[i][3]) * stoi(check[i][2]);
		}
		check.back()[1] = "total cost: " + to_string(sum1) + " rub";
		for (int i = 0; i < size - 1; ++i) {
			sum2 += stoi(check[i][4]);
		}
		check.back()[3] = "to be paid: " + to_string(sum2) + " rub";
		check.back()[2] = "total discount: " + to_string((unsigned int(100 - (sum2 * 100.0) / sum1)));
	}
public:
	Cash_desk(const vector<Goods>& goods) : Store(goods) {};
	Cash_desk(const Store& src) : Store(src) {};
	void scan(string code) {
		if (code.length() != 4) {
			throw(string("Code length must be equal to 4."));
		}
		vector<Goods>::iterator t = lower_bound(goods.begin(), goods.end(), Goods(code, "", 1, 1));
		if (t == goods.end() || t->get_code() != code) {
			throw(string("Not found.(" + code + ")"));
		}
		else {
			it = t;
		}
	}
	string about() {
		return string("Code: " + it->get_code() + ", Name: " + it->get_name() + ", Price: " + to_string(it->get_price())
			+ ", Discount: " + to_string(it->get_discount()));
	}
	void add_to_check() {
		const array<string, 5> t{ it->get_code() };
		changed = 1;
		vector<array<string, 5>>::iterator search = lower_bound(check.begin(), check.end(),t, cmp);
		if (search == check.end() || (*search)[0] != it->get_code()) {
			if (check.size() == 0 || check.back()[0] != "CODE") {
				check.resize(check.size() + 1);
				check.back()[0] = it->get_code();
				check.back()[1] = it->get_name();
				check.back()[2] = to_string(it->get_price()) + " rub";
				check.back()[3] = "1";
				check.back()[4] = to_string(unsigned int(it->get_price() * (1 - it->get_discount() / 100.0))) + " rub";
			}
			else {
				check.back()[0] = it->get_code();
				check.back()[1] = it->get_name();
				check.back()[4] = check.back()[2] = to_string(unsigned int(1 - it->get_price() * (it->get_discount() / 100.0))) + " rub";
				check.back()[3] = "1";
			}
		}
		else {
			unsigned int num = stoi((*search)[3]) + 1;
			(*search)[3] = to_string(num);
			(*search)[4] = to_string(unsigned int((num * it->get_price()) * (1 - it->get_discount() / 100.0))) + " rub";
		}
	}
	void delete_from_check() {
		const array<string, 5> t{ it->get_code() };
		changed = 1;
		vector<array<string, 5>>::iterator search = lower_bound(check.begin(), check.end(), t, cmp);
		if (search == check.end() || (*search)[0] != it->get_code()) {
			throw(string("Not found.(" + it->get_code() + ")"));
		}
		else if((*search)[3] == "1") {
			check.erase(search);
		}
		else {
			unsigned int num = stoi((*search)[3]) - 1;
			(*search)[3] = to_string(num);
			(*search)[4] = to_string(unsigned int((num * it->get_price()) * (1 - it->get_discount() / 100.0))) + " rub";
		}
	}
	string form() {
		if (check.size() < 1 || (check.size() == 1 && check[0][0] == "CODE")) {
			throw(string("Not enough goods"));
		}
		string fin_check = "CHECK:\n";
		if (changed) {
			last();
		}
		for (size_t i = 0, size = check.size(); i < size - 1; ++i) {
			fin_check += to_string(i + 1) + ") ";
			for (size_t j = 1; j < 5; ++j) {
				fin_check += check[i][j] + "-";
			}
			fin_check.back() = '\n';
		}
		fin_check += "________________________________\n";
		for (int i = 0; i < 4; i++) {
			fin_check += check.back()[i] + " ";
		}
		return fin_check;
	}
	unsigned int sum() {
		if (changed) {
			last();
		}
		int sum = 0, order = 1;
		bool flag = 0;
		for (int i = check.back()[3].size(); i >= 0; --i) {
			if (isdigit(check.back()[3][i])) {
				flag = 1;
				sum += (check.back()[3][i] - '0') * order;
				order *= 10;
			}
			else if (flag) {
				break;
			}
		}
		return sum;
	}
};

int main() {
	Goods t("0001", "First", 100, 1);
	Store st;
	st.add(t);
	st.add(Goods("0002", "Second", 12, 23));
	st.add(Goods("0003", "Third", 232, 12));
	for (int i = 4; i < 10000; ++i) {
		string name = "     ";
		name[0] = 'A' + (rand() % ('Z' - 'A'));
		for (int j = 1; j < 5; ++j) {
			name[j] = 'a' + (rand() % ('z' - 'a'));
		}
		if (i < 10) {
			st.add(Goods("000" + to_string(i), name, 1 + rand() % 10000, i + 3));
		}
		else if(i < 100){
			st.add(Goods("00" + to_string(i), name, 1 + rand() % 10000, 1 + rand() % 50));
		}
		else if (i < 1000) {
			st.add(Goods("0" + to_string(i), name, 1 + rand() % 10000, 1 + rand() % 50));
		}
		else if (i < 10000) {
			st.add(Goods(to_string(i), name, 1 + rand() % 10000, 1 + rand() % 50));
		}
	}
	Cash_desk ca(st);
	ca.scan("0002");
	cout << ca.about() << '\n';
	ca.scan("0003");
	cout << ca.about() << '\n';
	string str("\n");
	while (str != "q") {
		try {
			cin >> str;
			if (str != "q") {
				ca.scan(str);
				ca.add_to_check();
				cout << ca.about() << '\n';
			}
		}
		catch (string err) {
			cerr << err << '\n';
		}
	}
	string s;
	try {
		s = ca.form();
		cout << endl << s << endl;
	}
	catch (string err) {
		cerr << err << '\n';
	}
	cout << ca.sum() << endl;
	return 0;
}