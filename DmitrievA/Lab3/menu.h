#pragma once
#include <string>
#include <stdlib.h>
#include <iostream>

using std::string;
using std::ostream;
using std::cout;
using std::endl;

void default_function(double a) {}


class MenuItem {
public:
	void (*function) (double);
	string name;
	MenuItem() : name{ "" }, function{ default_function } {}
	MenuItem(void (*function_) (double), string name_) : function{ function_ }, name{ name_ } {}
	MenuItem(const MenuItem& mi) {
		name = mi.name;
		function = mi.function;
	}
};

ostream& operator << (ostream& out, MenuItem mi) {
	out << mi.name;
	return out;
}

class Menu;

ostream& operator << (ostream& out, Menu m);

class Menu {
public:
	MenuItem* items = nullptr;
	size_t capacity;
	size_t last_pick = -1;
	Menu() : capacity{ 0 }, items{ nullptr } {};//Добавить конструкторов и дефолтных пунктов меню
	Menu(size_t capacity_) :capacity{ capacity_ } {
		items = new MenuItem[capacity];
	}
	Menu(size_t capacity_, MenuItem* items_) {
		capacity = capacity_;
		items = new MenuItem[capacity];
		for (int i = 0; i < capacity; i++) {
			items[i] = items_[i];
		}
	}
	Menu(const Menu& menu_) {
		capacity = menu_.capacity;
		delete items;
		items = new MenuItem[capacity];
		for (size_t i = 0; i < capacity; i++) {
			items[i] = menu_.items[i];
		}
	}
	void set_commands_count(size_t count) {
		if (capacity != 0 && items != nullptr) {
			MenuItem* items2 = new MenuItem[count];
			for (size_t i = 0; i < capacity; i++) {
				items2[i] = items[i];
			}
			for (size_t i = capacity; i < count; i++) {
				items2[i] = MenuItem();
			}
			delete items;
			items = items2;
		}
		else {
			items = new MenuItem[count];
		}
		capacity = count;
	}
	size_t get_count() {
		return capacity;
	}
	void set_menu_item(size_t index, string name, void (*function_) (double)) {
		if (index < capacity) {
			items[index] = MenuItem(function_, name);
		}
		else {
			cout << "index more than capacity" << endl;
		}
	}
	void set_menu_item(size_t index, MenuItem mi) {
		if(index < capacity) {
			items[index] = mi;
		}
		else {
			cout << "index more than capacity" << endl;
		}
	}
	void print_menu(ostream& out = cout) {
		out << *this;
	}
	void execute_menu(ostream& out = cout, std::istream& in = std::cin) {
		out << "Choose item from menu:" << endl;
		out << *this;
		size_t inp;
		bool flag = false;
		do {
			if (flag) out << "input number between 1 and " << capacity << endl;
			in >> inp;
			flag = true;
		} while (inp == 0 ||inp > capacity);
		out << "You choose " << items[inp-1]<< endl;
		out << "Input argument(double): ";
		double arg;
		in >> arg;
		items[inp-1].function(arg);
		last_pick = inp;
	}
	size_t get_last_pick() {
		return last_pick;
	}
	friend ostream& operator << (ostream& out, Menu m);
};

ostream& operator << (ostream& out, Menu m) {
	for (size_t i = 0; i < m.capacity; i++) {
		out << i+1 << "." << m.items[i].name << endl;
	}
	return out;
}