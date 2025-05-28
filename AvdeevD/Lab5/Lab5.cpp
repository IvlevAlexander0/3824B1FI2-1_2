#include <iostream>

using namespace std;

class fio {
public:
	string first_name;
	string last_name;
	string patronymic;
	fio() {
		first_name = "_";
		last_name = "_";
		patronymic = "_";
	};
	fio(string first, string last, string patr) {
		first_name = first;
		last_name = last;
		patronymic = patr;
	};
	void create_name() {
		cout << "Please, tell us some information.\nName: ";
		cin >> first_name;
		cout << "Last name: ";
		cin >> last_name;
		cout << "Patronymic if capable, if not just put _: ";
		cin >> patronymic;
	}
	~fio() {};
};

ostream& operator<<(ostream& stream, const fio& Fio) {
	stream << "First name - " << Fio.first_name << "." << endl;
	stream << "Last name - " << Fio.last_name << "." << endl;
	stream << "Patronymic - " << Fio.patronymic << "." << endl;
	return stream;
}

struct sat {
	int seat = 0;
	int railcar_num = 0;
	bool upper = false;
};

class ticket {
public:
	int date;
	fio name;
	int train_num;
	sat seat;
	bool moscow;
	ticket() {
		date = 0;
		name.first_name = "_";
		name.last_name = "_";
		name.patronymic = "_";
		train_num = 0;
		seat;
		moscow = false;
	}
	ticket(int date_, fio fio_, int train_num_, sat seat_, bool moscow_) {
		date = date_;
		name = fio_;
		seat = seat_;
		train_num = train_num_;
		moscow = moscow_;
	}
	~ticket() {};
};
ostream& operator<<(ostream& stream, const ticket& Ticket) {
	stream << "Date of departing - " << Ticket.date << "." << endl;
	stream << "Number of train - " << Ticket.train_num << "." << endl;
	stream << "Number of railcar - " << Ticket.seat.railcar_num << "." << endl;
	if (Ticket.seat.upper) {
		stream << "Upper seat " << Ticket.seat.seat << "." << endl;
	}
	else {
		stream << "Lower seat " << Ticket.seat.seat << "." << endl;
	}
	stream << Ticket.name;
	if (Ticket.moscow) {
		stream << "Departing in Moscow, arriving in Nizhniy Novgorod." << endl;
	}
	else {
		stream << "Departing in Nizhniy Novgorod, arriving in Moscow." << endl;
	}
	return stream;
}

bool check_full(bool* arr, size_t size) {//true если заняты все
	for (size_t i = 0; i < size; i++) {
		if (!(arr[i])) {
			return false;
		}
	}
	return true;
}
bool check_seat(bool* arr, size_t itoe) {
	if (arr[itoe]) {
		return true;
	}
	return false;
}

bool check_day(int month, int day) {//Если true, то дня не существует
	if (day < 1 || day > 31) {
		return true;
	}
	if (month % 2 == 0) {
		if (month == 2) {
			if (day > 28) {
				return true;
			}
		}
		else {
			if (day > 30) {
				return true;
			}
		}
	}
	return false;
}

class railcar {
public:
	int type;
	railcar() {
		type = 0;
	};
	railcar(int type_) :
		type(type_){};
	~railcar() {};

};
class lastochka : public railcar {
public:
	bool seats[100];
	int free_seats;
	lastochka() :railcar() {
		free_seats = 100;
		for (int i = 0; i < 100; i++) {
			seats[i] = 0;
		}
	}
	lastochka(int type_) : railcar(type_) {
		free_seats = 100;
		for (int i = 0; i < 100; i++) {
			seats[i] = 0;
		}
	}
	void get_free_seat() {
		int count = 0;
		for (int i = 0; i < 100; i++) {
			if (!(seats[i])) {
				count++;
			}
		}
		free_seats = count;
	}
	~lastochka() {
	}
};
class plac : public railcar {
public:
	bool upper[27] { 0 };
	bool lower[27] { 0 };
	int free_upper;
	int free_lower;
	plac() :railcar() {
		free_upper = 27;
		free_lower = 27;
		for (int i = 0; i < 27; i++) {
			upper[i] = 0;
			lower[i] = 0;
		}
	}
	plac(int type_) : railcar(type_) {
		free_upper = 27;
		free_lower = 27;
		for (int i = 0; i < 27; i++) {
			upper[i] = 0;
			lower[i] = 0;
		}
	}
	void get_free_seat_lower() {
		int count = 0;
		for (int i = 0; i < 27; i++) {
			if (!(lower[i])) {
				count++;
			}
		}
		free_lower = count;
	}
	void get_free_seat_upper() {
		int count = 0;
		for (int i = 0; i < 27; i++) {
			if (!(upper[i])) {
				count++;
			}
		}
		free_upper = count;
	}
	~plac() {
	}
};
class kupe : public railcar {
public:
	bool upper[18] { 0 };
	bool lower[18] { 0 };
	int free_upper;
	int free_lower;
	kupe() :railcar() {
		free_upper = 18;
		free_lower = 18;
		for (int i = 0; i < 18; i++) {
			upper[i] = 0;
			lower[i] = 0;
		}
	}
	kupe(int type_) : railcar(type_) {
		free_upper = 18;
		free_lower = 18;
		for (int i = 0; i < 18; i++) {
			upper[i] = 0;
			lower[i] = 0;
		}
	}
	void get_free_seat_lower() {
		int count = 0;
		for (int i = 0; i < 18; i++) {
			if (!(lower[i])) {
				count++;
			}
		}
		free_lower = count;
	}
	void get_free_seat_upper() {
		int count = 0;
		for (int i = 0; i < 18; i++) {
			if (!(upper[i])) {
				count++;
			}
		}
		free_upper = count;
	}
	~kupe() {
	}
};
class svcar : public railcar {
public:
	bool seats[18]{ 0 };
	int free_seats;
	svcar() :railcar() {
		free_seats = 18;
		for (int i = 0; i < 18; i++) {
			seats[i] = 0;
		}
	}
	svcar(int type_) :railcar(type_) {
		free_seats = 18;
		for (int i = 0; i < 18; i++) {
			seats[i] = 0;
		}
	}
	void get_free_seat() {
		int count = 0;
		for (int i = 0; i < 18; i++) {
			if (!(seats[i])) {
				count++;
			}
		}
		free_seats = count;
	}
	~svcar() {
	}
};

class train {
public:
	int num;
	bool moscow;
	train() {
		num = 0;
		moscow = false;
	}
	train(int num_, bool moscow_) {
		num = num_;
		moscow = moscow_;
	}
	~train() {};
};
class lastoch : public train {
public:
	lastochka rcars[8];
	lastoch() : train() {
		for (int i = 0; i < 8; i++) {
			rcars[i] = lastochka(i);
		}
	}
	lastoch(int num_, bool moscow_) : train(num_, moscow_) {
		num = num_;
		moscow = moscow_;
		for (int i = 0; i < 8; i++) {
			rcars[i] = lastochka(i);
		}
	}
	int over_free_seats() {
		int count = 0;
		for (int i = 0; i < 8; i++) {
			rcars[i].get_free_seat();
			count += rcars[i].free_seats;
		}
		return count;
	}
	~lastoch() {
	}
};
class firm : public train {
public:
	svcar svs[2];
	kupe kupes[6];
	plac placs[4];
	firm():train() {
		for (int i = 0; i < 6; i++) {
			if (i<2) {
				svs[i] = svcar(i + 1);
				kupes[i] = kupe(i+7);
				placs[i] = plac(i+3);
			}
			else {
				if (i < 4) {
					kupes[i] = kupe(i + 7);
					placs[i] = plac(i+3);
				}
				else {
					kupes[i] = kupe(i + 7);
				}
			}
		}
	}
	firm(int num_, bool moscow_) :train(num_, moscow_) {
		num = num_;
		moscow = moscow_;
		for (int i = 0; i < 6; i++) {
			kupes[i] = kupe(i + 7);
			if (i < 4) {
				if (i < 2) {
					svs[i] = svcar(i + 1);
				}
				placs[i] = plac(i + 3);
			}
		}
	}
	int over_free_seats_upper() {
		int count = 0;
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				placs[i].get_free_seat_upper();
				count += placs[i].free_upper;
			}
			kupes[i].get_free_seat_upper();
			count += kupes[i].free_upper;
		}
		return count;
	}
	int over_free_seats_lower() {
		int count = 0;
		for (int i = 0; i < 6; i++) {
			if (i < 4) {
				if (i < 2) {
					svs[i].get_free_seat();
					count += svs[i].free_seats;
				}
				placs[i].get_free_seat_lower();
				count += placs[i].free_lower;
			}
			kupes[i].get_free_seat_lower();
			count += kupes[i].free_lower;
		}
		return count;
	}
	~firm() {
	}
};
class fast :public train {
public:
	kupe kupes[4];
	plac placs[8];
	fast() : train() {
		for (int i = 0; i < 8; i++) {
			placs[i] = plac(i + 5);
			if (i < 4) {
				kupes[i] = kupe(i + 1);
			}
		}
	}
	fast(int num_, bool moscow_) : train(num_, moscow_) {
		num = num_;
		moscow = moscow_;
		for (int i = 0; i < 8; i++) {
			placs[i] = plac(i + 5);
			if (i < 4) {
				kupes[i] = kupe(i + 1);
			}
		}
	}
	int over_free_seats_upper() {
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if (i < 4) {
				kupes[i].get_free_seat_upper();
				count += kupes[i].free_upper;
			}
			placs[i].get_free_seat_upper();
			count += placs[i].free_upper;

		}
		return count;
	}
	int over_free_seats_lower() {
		int count = 0;
		for (int i = 0; i < 8; i++) {
			if (i < 4) {
				kupes[i].get_free_seat_lower();
				count += kupes[i].free_lower;

			}
			placs[i].get_free_seat_lower();
			count += placs[i].free_lower;

		}
		return count;
	}
	~fast() {
	}
};

class railroad {
public:
	int num_tick;
	ticket* tickets;
	lastoch lastochki[6];
	firm firmen[2];
	fast fastone[2];
	int trains[10]{ 0 };
	railroad() {
		num_tick = 0;
		tickets = nullptr;
		for (int i = 0; i < 6; i++) {
			if (i < 2) {
				firmen[i] = firm(5 + i, i%2);
				fastone[i] = fast(50 + i, i%2);
			}
			lastochki[i] = lastoch(10 + i, i % 2);
		}
		for (int i = 0; i < 6; i++) {
			trains[i + 4] = lastochki[i].num;
			if (i < 2) {
				trains[i] = firmen[i].num;
				trains[i + 2] = fastone[i].num;
			}
		}
	}
	void new_ticket(ticket Ticket) {
		ticket* tickets1 = new ticket[num_tick + 1];
		if (tickets != nullptr) {
			for (int i = 0; i < num_tick; i++) {
				tickets1[i] = tickets[i];
			}
		}
		tickets1[num_tick] = Ticket;
		delete[] tickets;
		tickets = tickets1;
		num_tick++;
		for (int i = 0; i < 6; i++) {
			if (i < 2) {
				if (Ticket.train_num == fastone[i].num) {
					if (Ticket.seat.railcar_num > 4) {
						for (int j = 0; j < 8; j++) {
							if (j == Ticket.seat.railcar_num - 5) {
								if (Ticket.seat.upper) {
									fastone[i].placs[j].upper[Ticket.seat.seat] = true;
									return;
								}
								else {
									fastone[i].placs[j].lower[Ticket.seat.seat] = true;
									return;
								}
							}
						}
					}
					else {
						for (int j = 0; j < 4;j++) {
							if (j == Ticket.seat.railcar_num - 1) {
								if (Ticket.seat.upper){
									fastone[i].kupes[j].upper[Ticket.seat.seat] = true;
									return;
								}
								else {
									fastone[i].kupes[j].lower[Ticket.seat.seat] = true;
									return;
								}
							}
						}
					}
				} 
				if (Ticket.train_num == firmen[i].num) {
					if (Ticket.seat.railcar_num < 3) {
						if (Ticket.seat.railcar_num == 1) {
							firmen[i].svs[0].seats[Ticket.seat.seat] = true;
							return;
						}
						else {
							firmen[i].svs[1].seats[Ticket.seat.seat] = true;
							return;
						}
					}
					else if (Ticket.seat.railcar_num < 7) {
						for (int j = 0; j < 4; j++) {
							if (j == Ticket.seat.railcar_num - 3) {
								if (Ticket.seat.upper) {
									firmen[i].placs[j].upper[Ticket.seat.seat] = true;
									return;
								}
								else {
									firmen[i].placs[j].lower[Ticket.seat.seat] = true;
									return;
								}
							}
						}
					}
					else {
						for (int j = 0; j < 6; j++) {
							if (j == Ticket.seat.railcar_num - 7) {
								if (Ticket.seat.upper) {
									firmen[i].kupes[j].upper[Ticket.seat.seat] = true;
									return;
								}
								else {
									firmen[i].kupes[j].lower[Ticket.seat.seat] = true;
									return;
								}
							}
						}
					}
				}

			}
			if (Ticket.train_num == lastochki[i].num) {
				for (int j = 0; j < 8; j++) {
					if (j == Ticket.seat.railcar_num-1) {
						lastochki[i].rcars[j].seats[Ticket.seat.seat] = true;
					}
				}
			}

		}
	}
	~railroad() {
		if (num_tick > 0) {
			delete[] tickets;
		}
	}
};

class kassa {
public:
	railroad Rail;
	string name;
	string last_name;
	string otchestvo;
	int data;
	int train_num;
	int railcar_num;
	int railcar_type;
	int train_type;
	int itoe;
	int caritoe;
	fio* fios = nullptr;
	int amout;
	int amolt;
	int amot;
	int countoft;
	int over_price;
	sat* reserved_seats;
	int realized_seats;
	bool got_data;
	bool mosca;
	kassa() {
		Rail = railroad();
		name = "_";
		last_name = "_";
		otchestvo = "_";
		data = 0;
		train_num = -1;
		railcar_num = -1;
		railcar_type = -1;
		train_type = -1;
		itoe = -1;
		caritoe = -1;
		fios = nullptr;
		amout = 0;
		amolt = 0;
		amot = 0;
		countoft = 0;
		over_price = 0;
		reserved_seats = nullptr;
		realized_seats = 0;
		got_data = false;
		mosca = false;
	}
	kassa(railroad rail) {
		Rail = rail;
		name = "_";
		last_name = "_";
		otchestvo = "_";
		data = 0;
		train_num = -1;
		railcar_num = -1;
		railcar_type = -1;
		train_type = -1;
		itoe = -1;
		caritoe = -1;
		fios = nullptr;
		amout = 0;
		amolt = 0;
		amot = 0;
		countoft = 0;
		over_price = 0;
		reserved_seats = nullptr;
		realized_seats = 0;
		got_data = false;
		mosca = false;
	}
	void get_data() {
		if (got_data) {
			cout << "You have already inputed data. Please deny your order to input a new data." << endl;
			return;
		}
		bool flag = false;
		//дата
		cout << "We'll need you to enter some information about your order. Let's start with date." << endl;
		do {
			cout << "Date (only 30 days from now on): ";
			cin >> data;
			if (data < 0 || data > 30) {
				cout << "Invalid date." << endl;
				flag = true;
			}
			else {
				flag = false;
			}
		} while (flag);
		cout << "Available trains: " << endl;
		for (int i = 0; i < 10; i++) {
			if (i < 2) {
				cout << "    Branded train - " << Rail.trains[i] << "." << endl;
				cout << "	 The starting point of train is - ";
				if (Rail.firmen[i].moscow) {
					cout << "Moscow." << endl;
				}
				else {
					cout << "Nizhniy Novgorod." << endl;
				}
			}
			else if (i < 4) {
				cout << "    Express train - " << Rail.trains[i] << "." << endl;
				cout << "	 The starting point of train is - ";
				if (Rail.fastone[i-2].moscow) {
					cout << "Moscow." << endl;
				}
				else {
					cout << "Nizhniy Novgorod." << endl;
				}
			}
			else {
				cout << "    Lastochka - " << Rail.trains[i] << "." << endl;
				cout << "	 The starting point of train is - ";
				if (Rail.lastochki[i-4].moscow) {
					cout << "Moscow." << endl;
				}
				else {
					cout << "Nizhniy Novgorod." << endl;
				}
			}
		}
		//поезд
		do {
			cout << "Train number: ";
			cin >> train_num;
			flag = true;
			for (int i = 0; i < 10; i++) {
				if (train_num == Rail.trains[i]) {
					if (i < 2) {
						train_type = 0; //фирменный
						if (train_num == Rail.firmen[0].num) {
							itoe = 0;
						}
						else {
							itoe = 1;
						}
						mosca = Rail.firmen[itoe].moscow;
					}
					else if (i < 4) {
						train_type = 1; //скорый поезд
						if (train_num == Rail.fastone[0].num) {
							itoe = 0;
						}
						else {
							itoe = 1;
						}
						mosca = Rail.fastone[itoe].moscow;
					}
					else {
						train_type = 3; //ласточка
						for (int j = 0; j < 6; j++) {
							if (train_num == Rail.lastochki[i].num) {
								itoe = i;
							}
						}
						mosca = Rail.lastochki[itoe].moscow;
					}
					flag = false;
				}
			}
			if (flag) {
				cout << "Invalid train number." << endl;
			}
		} while (flag);
		cout << "Keep in mind, that the amount of names you'll need to input will be the same\nas the amount of tickets you choose." << endl;
		//тип вагона и кол-во билетов
		switch (train_type)
		{
		case 0:
			do {
				cout << "Railcar type (0 for reserved seat, 1 for coupe and 2 for sv): ";
				cin >> railcar_type;
				if (railcar_type < 0 || railcar_type > 2) {
					cout << "Invalid type." << endl;
					flag = true;
				}
				else {
					flag = false;
				}
			} while (flag);
			switch (railcar_type)
			{
			case 0:
				do {
					cout << "Amount of upper seat tickets: ";
					cin >> amout;
					int free_th = 0;
					for (int i = 0; i < 4; i++) {
						Rail.firmen[itoe].placs[i].get_free_seat_upper();
						free_th += Rail.firmen[itoe].placs[i].free_upper;
					}
					if (amout < 0 || amout > free_th) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amout;
					}
				} while (flag);
				do {
					cout << "Amount of lower seat tickets: ";
					cin >> amolt;
					int free_th = 0;
					for (int i = 0; i < 4; i++) {
						Rail.firmen[itoe].placs[i].get_free_seat_lower();
						free_th += Rail.firmen[itoe].placs[i].free_lower;
					}
					if (amolt < 0 || amolt > free_th) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amolt;
					}
				} while (flag);
				break;
			case 1:
				do {
					cout << "Amount of upper seat tickets: ";
					cin >> amout;
					int free_th = 0;
					for (int i = 0; i < 6;i++) {
						Rail.firmen[itoe].kupes[i].get_free_seat_upper();
						free_th += Rail.firmen[itoe].kupes[i].free_upper;
					}
					if (amout < 0 || amout > free_th) {
						cout << "Invalid amount or too much." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amout;
					}
				} while (flag);
				do {
					cout << "Amount of lower seat tickets: ";
					cin >> amolt;
					int free_th = 0;
					for (int i = 0; i < 6;i++) {
						Rail.firmen[itoe].kupes[i].get_free_seat_lower();
						free_th += Rail.firmen[itoe].kupes[i].free_lower;
					}
					if (amolt < 0 || amolt > free_th) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amolt;
					}
				} while (flag);
				break;
			case 2:
				do {
					cout << "Amount of tickets: ";
					cin >> amot;
					int free_th = 0;
					for (int i = 0; i < 2; i++) {
						Rail.firmen[itoe].svs[i].get_free_seat();
						free_th += Rail.firmen[itoe].svs[i].free_seats;
					}
					if (amot < 0 || amot > 18) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amot;
					}
				} while (flag);
				break;
			default:
				break;
			}
			break;
		case 1:
			cout << "Railcar type (0 for reserved seat and 1 for coupe): ";
			cin >> railcar_type;
			if (railcar_type < 0 || railcar_type > 1) {
				cout << "Invalid type." << endl;
				flag = true;
			}
			else {
				flag = false;
			}
			switch (train_type)
			{
			default:
				break;
			}
			switch (railcar_type)
			{
			case 0:
				do {
					cout << "Amount of upper seat tickets: ";
					cin >> amout;
					int free_th = 0;
					for (int i = 0; i < 8; i++) {
						Rail.fastone[itoe].placs[i].get_free_seat_upper();
						free_th += Rail.fastone[itoe].placs[i].free_upper;
					}
					if (amout < 0 || amout > free_th) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amout;
					}
				} while (flag);
				do {
					cout << "Amount of lower seat tickets: ";
					cin >> amolt;
					int free_th = 0;
					for (int i = 0; i < 8; i++) {
						Rail.fastone[itoe].placs[i].get_free_seat_lower();
						free_th += Rail.fastone[itoe].placs[i].free_lower;
					}
					if (amolt < 0 || amolt > free_th) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amolt;
					}
				} while (flag);
				break;
			case 1:
				do {
					cout << "Amount of upper seat tickets: ";
					cin >> amout;
					int free_th = 0;
					for (int i = 0; i < 4;i++) {
						Rail.fastone[itoe].kupes[i].get_free_seat_upper();
						free_th += Rail.fastone[itoe].kupes[i].free_upper;
					}
					if (amout < 0 || amout > free_th) {
						cout << "Invalid amount or too much." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amout;
					}
				} while (flag);
				do {
					cout << "Amount of lower seat tickets: ";
					cin >> amolt;
					int free_th = 0;
					for (int i = 0; i < 4;i++) {
						Rail.fastone[itoe].kupes[i].get_free_seat_lower();
						free_th += Rail.fastone[itoe].kupes[i].free_lower;
					}
					if (amolt < 0 || amolt > free_th) {
						cout << "Invalid amount." << endl;
						flag = true;
					}
					else {
						flag = false;
						countoft += amolt;
					}
				} while (flag);
				break;
			default:
				break;
			}
			break;
		default:
			do {
				cout << "Amount of tickets: ";
				cin >> amot;
				int free_th = Rail.lastochki[itoe].over_free_seats();
				if (amot < 0 || amot > free_th) {
					flag = true;
					cout << "Invalid amount." << endl;
				}
				else {
					flag = false;
					countoft += amot;
				}
			} while (flag);
			break;
		}
		//ФИО пассажиров
		delete[] fios;
		fios = new fio[countoft];
		for (int i = 0; i < countoft; i++) {
			fios[i].create_name();
		}
		delete[] reserved_seats;
		reserved_seats = new sat[countoft];
		got_data = true;
	}
	void check_seats() {
		switch (train_type)
		{
		case 0:
			cout << Rail.firmen[itoe].num << " branded train." << endl;
			switch (railcar_type)
			{
			case 0:
				for (int i = 0; i < 4; i++) {
					cout << i + 3 << " railcar is reserves seat railcar:" << endl;
					for (int j = 0; j < 27; j++) {
						cout << j + 1 << " upper seat is ";
						if (Rail.firmen[itoe].placs[i].upper[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
						cout << j + 1 << " lower seat is ";
						if (Rail.firmen[itoe].placs[i].lower[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
					}
				}
				break;
			case 1:
				for (int i = 0; i < 6; i++) {
					cout << i + 7 << " railcar is coupe railcar: " << endl;
					for (int j = 0; j < 18; j++) {
						cout << j + 1 << " upper seat is ";
						if (Rail.firmen[itoe].kupes[i].upper[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
						cout << j + 1 << " lower seat is ";
						if (Rail.firmen[itoe].kupes[i].lower[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
					}
				}
				break;
			default:
				for (int i = 0; i < 2; i++) {
					cout << i + 1 << " railcar  is sv railcar: " << endl;
					for (int j = 0; j < 18; j++) {
						cout << j + 1 << " seat is ";
						if (Rail.firmen[itoe].svs[i].seats[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
					}
				}
				break;
			}
			break;
		case 1:
			cout << Rail.fastone[itoe].num << " fast train." << endl;
			switch (railcar_type)
			{
			case 0:
				for (int i = 0; i < 8; i++) {
					cout << i + 5 << " railcar is reserves seat railcar:" << endl;
					for (int j = 0; j < 27; j++) {
						cout << j + 1 << " upper seat is ";
						if (Rail.fastone[itoe].placs[i].upper[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
						cout << j + 1 << " lower seat is ";
						if (Rail.fastone[itoe].placs[i].lower[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
					}
				}
				break;
			default:
				for (int i = 0; i < 4; i++) {
					cout << i + 1 << " railcar is coupe railcar: " << endl;
					for (int j = 0; j < 18; j++) {
						cout << j + 1 << " upper seat is ";
						if (Rail.fastone[itoe].kupes[i].upper[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
						cout << j + 1 << " lower seat is ";
						if (Rail.fastone[itoe].kupes[i].lower[j]) {
							cout << "taken." << endl;
						}
						else {
							cout << "free." << endl;
						}
					}
				}
				break;
			}
			break;
		case 3:
			cout << Rail.lastochki[itoe].num << " lastochka." << endl;
			for (int i = 0; i < 8; i++) {
				cout << i + 1 << " railcar:" << endl;
				for (int j = 0; j < 100; j++) {
					cout << "	" << j + 1 << "seat is ";
					if (Rail.lastochki[itoe].rcars[i].seats[j]) {
						cout << "taken." << endl;
					}
					else {
						cout << "free." << endl;
					}
				}
			}
			break;
		default:
			cout << "We don't have your preferences about your train and railcar. \nGive us them and then we'll tell wich seats is free." << endl;
			break;
		}
	}
	void reserv_seats() {
		if (countoft < 1) {
			cout << "You have not chosen at least one seat or you try to reserve more than you wanted." << endl;
			return;
		}
		bool flag = false;
		switch (train_type) {
		case 0:
			switch (railcar_type)
			{
			case 0:
				cout << "Available to see reserved seat railcars: " << endl;
				for (int i = 0; i < 4; i++) {
					cout << "\t" << i + 3 << " railcar." << endl;
				}
				while (countoft > 0) {
					do {
						cout << "Input the number of railcar where you want to reserve the seats: ";
						cin >> railcar_num;
						caritoe = railcar_num - 3;
						if (railcar_num < 3 || railcar_num > 6) {
							cout << "Invalid number of railcar." << endl;
							flag = true;
						}
						else if (Rail.firmen[itoe].placs[caritoe].free_lower + Rail.firmen[itoe].placs[caritoe].free_upper == 0) {
							flag = true;
							cout << "This railcar is already full. Choose another." << endl;
						}
						else {
							flag = false;
						}
					} while (flag);
					for (int i = 0; i < min(amout, Rail.firmen[itoe].placs[caritoe].free_upper); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat >> 27) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if (!(Rail.firmen[itoe].placs[caritoe].upper[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat-1;
								realized_seats++;
								countoft--;
								Rail.firmen[itoe].placs[caritoe].upper[seat - 1] = true;
							}
						} while (flag);
					}
					amout -= Rail.firmen[itoe].placs[caritoe].free_upper;
					Rail.firmen[itoe].placs[caritoe].get_free_seat_upper();
					for (int i = 0; i < min(amolt, Rail.firmen[itoe].placs[caritoe].free_lower); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat > 27) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if ((Rail.firmen[itoe].placs[caritoe].lower[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat-1;
								realized_seats++;
								countoft--;
								Rail.firmen[itoe].placs[caritoe].lower[seat - 1] = true;
							}
						} while (flag);
					}
					amolt -= Rail.firmen[itoe].placs[caritoe].free_lower;
					Rail.firmen[itoe].placs[caritoe].get_free_seat_lower();
				}
				break;
			case 1:
				cout << "Available to see coupe railcars: ";
				for (int i = 0; i < 6; i++) {
					cout << "\t" << i + 7 << " railcar." << endl;
				}
				while (countoft > 0) {
					do {
						cout << "Input the number of railcar where you want to reserve the seats: ";
						cin >> railcar_num;
						caritoe = railcar_num - 7;
						if (railcar_num < 7 || railcar_num > 12) {
							cout << "Invalid number of railcar." << endl;
							flag = true;
						}
						else if (Rail.firmen[itoe].kupes[caritoe].free_lower + Rail.firmen[itoe].kupes[caritoe].free_upper == 0) {
							flag = true;
							cout << "This railcar is already full. Choose another." << endl;
						}
						else {
							flag = false;
						}
					} while (flag);
					for (int i = 0; i < min(amout, Rail.firmen[itoe].kupes[caritoe].free_upper); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat >> 18) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if (Rail.firmen[itoe].kupes[caritoe].upper[seat - 1]) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat-1;
								realized_seats++;
								countoft--;
								Rail.firmen[itoe].kupes[caritoe].upper[seat - 1] = true;
							}
						} while (flag);
					}
					amout -= Rail.firmen[itoe].kupes[caritoe].free_upper;
					Rail.firmen[itoe].kupes[caritoe].get_free_seat_upper();
					for (int i = 0; i < min(amolt, Rail.firmen[itoe].kupes[caritoe].free_lower); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat > 18) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if ((Rail.firmen[itoe].kupes[caritoe].lower[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat-1;
								realized_seats++;
								countoft--;
								Rail.firmen[itoe].kupes[caritoe].lower[seat - 1] = true;
							}
						} while (flag);
					}
					amolt -= Rail.firmen[itoe].kupes[caritoe].free_lower;
					Rail.firmen[itoe].kupes[caritoe].get_free_seat_lower();
				}
				break;
			case 2:
				cout << "Available to see sv railcars: ";
				for (int i = 0; i < 2;i++) {
					cout << "\t" << i + 1 << " railcar." << endl;
				}
				while (countoft > 0) {
					do {
						cout << "Input the number of railcar where you want to reserve the seats: ";
						cin >> railcar_num;
						caritoe = railcar_num - 1;
						if (railcar_num < 1 || railcar_num > 2) {
							cout << "Invalid number of railcar." << endl;
							flag = true;
						}
						else if (Rail.firmen[itoe].svs[caritoe].free_seats == 0) {
							flag = true;
							cout << "This railcar is already full. Choose another." << endl;
						}
						else {
							flag = false;
						}
					} while (flag);
					for (int i = 0; i < min(amot, Rail.firmen[itoe].svs[caritoe].free_seats); i++) {
						int seat;
						do {
							cout << "Choose the seat: ";
							cin >> seat;
							if (seat < 1 || seat > 18) {
								cout << "Invalid seat." << endl;
								flag = true;
							}
							else if (!(Rail.firmen[itoe].svs[caritoe].seats[seat-1])) {
								cout << "The seat is taken." << endl;
								flag = true;
							}
							else {
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat - 1;
								realized_seats++;
								countoft--;
								Rail.firmen[itoe].svs[caritoe].seats[seat - 1] = true;
							}
						} while (flag);
					}
				}
				break;
			default:
				break;
			}
			break;
		case 1:
			switch (railcar_type)
			{
			case 1:
				cout << "Available to see coupe railcars: " << endl;
				for (int i = 0; i < 4; i++) {
					cout << "\t" << i + 1 << " railcar." << endl;
				}
				while (countoft > 0) {
					do {
						cout << "Input the number of railcar where you want to reserve the seats: ";
						cin >> railcar_num;
						caritoe = railcar_num - 1;
						if (railcar_num < 1 || railcar_num > 4) {
							cout << "Invalid number of railcar." << endl;
							flag = true;
						}
						else if (Rail.fastone[itoe].kupes[caritoe].free_lower + Rail.fastone[itoe].kupes[caritoe].free_upper == 0) {
							flag = true;
							cout << "This railcar is already full. Choose another." << endl;
						}
						else {
							flag = false;
						}
					} while (flag);
					for (int i = 0; i < min(amout, Rail.fastone[itoe].kupes[caritoe].free_upper); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat >> 18) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if ((Rail.fastone[itoe].kupes[caritoe].upper[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat - 1;
								reserved_seats[realized_seats].upper = true;
								realized_seats++;
								countoft--;
								Rail.fastone[itoe].kupes[caritoe].upper[seat - 1] = true;
							}
						} while (flag);
					}
					amout -= Rail.fastone[itoe].kupes[caritoe].free_upper;
					Rail.fastone[itoe].kupes[caritoe].get_free_seat_upper();
					for (int i = 0; i < min(amolt, Rail.fastone[itoe].kupes[caritoe].free_lower); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat > 18) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if ((Rail.fastone[itoe].kupes[caritoe].lower[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat - 1;
								reserved_seats[realized_seats].upper = false;
								realized_seats++;
								countoft--;
								Rail.fastone[itoe].kupes[caritoe].lower[seat - 1] = true;
							}
						} while (flag);
					}
					amolt -= Rail.fastone[itoe].kupes[caritoe].free_lower;
					Rail.fastone[itoe].kupes[caritoe].get_free_seat_lower();
				}
				break;
			case 0:
				cout << "Available to see reserved seat railcars: ";
				for (int i = 0; i < 8; i++) {
					cout << "\t" << i + 5 << " railcar." << endl;
				}
				while (countoft > 0) {
					do {
						cout << "Input the number of railcar where you want to reserve the seats: ";
						cin >> railcar_num;
						caritoe = railcar_num - 5;
						if (railcar_num < 5 || railcar_num > 12) {
							cout << "Invalid number of railcar." << endl;
							flag = true;
						}
						else if (Rail.fastone[itoe].placs[caritoe].free_lower + Rail.fastone[itoe].placs[caritoe].free_upper == 0) {
							flag = true;
							cout << "This railcar is already full. Choose another." << endl;
						}
						else {
							flag = false;
						}
					} while (flag);
					for (int i = 0; i < min(amout, Rail.fastone[itoe].placs[caritoe].free_upper); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat >> 27) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if ((Rail.fastone[itoe].placs[caritoe].upper[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat - 1;
								realized_seats++;
								countoft--;
								Rail.fastone[itoe].placs[caritoe].upper[seat - 1] = true;
							}
						} while (flag);
					}
					amout -= Rail.fastone[itoe].placs[caritoe].free_upper;
					Rail.fastone[itoe].placs[caritoe].get_free_seat_upper();
					for (int i = 0; i < min(amolt, Rail.fastone[itoe].placs[caritoe].free_lower); i++) {
						int seat;
						do {
							cout << "Choose the seat to reserve: ";
							cin >> seat;
							if (seat < 1 || seat > 27) {
								flag = true;
								cout << "Invalid seat." << endl;
							}
							else if ((Rail.fastone[itoe].placs[caritoe].lower[seat - 1])) {
								flag = true;
								cout << "This seat is taken." << endl;
							}
							else {
								flag = false;
								reserved_seats[realized_seats].railcar_num = railcar_num;
								reserved_seats[realized_seats].seat = seat - 1;
								realized_seats++;
								countoft--;
								Rail.fastone[itoe].placs[caritoe].lower[seat - 1] = true;
							}
						} while (flag);
					}
					amolt -= Rail.fastone[itoe].placs[caritoe].free_lower;
					Rail.fastone[itoe].placs[caritoe].get_free_seat_lower();
				}
				break;
			default:
				break;
			}
			break;
		case 3:
			cout << "Available to see railcars: " << endl;
			for (int i = 0; i < 8; i++) {
				cout << "\t" << i + 1 << " railcar." << endl;
			}
			while (countoft > 0) {		
				do {
					cout << "Input the number of railcar where you want to reserve the seats: ";
					cin >> railcar_num;
					caritoe = railcar_num - 1;
					if (railcar_num < 1 || railcar_num > 8) {
						cout << "Invalid number of railcar." << endl;
						flag = true;
					}
					else if (Rail.lastochki[itoe].rcars[caritoe].free_seats == 0) {
						cout << "This railcar is already full. Choose another." << endl;
						flag = true;
					}
					else {
						flag = false;
					}
				} while (flag);
				for (int i = 0; i < min(amot, Rail.lastochki[itoe].rcars[caritoe].free_seats); i++) {
					int seat;
					do {
						cout << "Choose the seat to reserve: ";
						cin >> seat;
						if (seat < 1 || seat > 100) {
							cout << "Invalid seat." << endl;
							flag = true;
						}
						else if (!(Rail.lastochki[itoe].rcars[caritoe].seats[seat - 1])) {
							cout << "This place is taken." << endl;
							flag = true;
						}
						else {
							flag = false;
							reserved_seats[realized_seats].railcar_num = railcar_num;
							reserved_seats[realized_seats].seat = seat - 1;
							realized_seats++;
							countoft--;
							Rail.lastochki[itoe].rcars[caritoe].seats[seat - 1] = true;
						}
					} while (flag);
				}
				amot -= Rail.lastochki[itoe].rcars[caritoe].free_seats;
				Rail.lastochki[itoe].rcars[caritoe].get_free_seat();
			}
			break;
		default:
			cout << "We don't have your preferences about your train and railcar. \nGive us them and then you can reserve some seats." << endl;
			break;
		}
	}
	void calculate_price() {
		if (realized_seats > 0) {
			switch (train_type) {
			case 0:
				switch (railcar_type)
				{
				case 0:
					for (int i = 0; i < realized_seats; i++) {
						over_price += int(500 * 1.6) - int(!(reserved_seats[i].upper)) * 50;
					}
					break;
				case 1:
					for (int i = 0; i < realized_seats; i++) {
						over_price += int(800 * 1.5) - int(!(reserved_seats[i].upper)) * 50;
					}
					break;
				case 2:
					for (int i = 0; i < realized_seats; i++) {
						over_price += 1500;
					}
					break;
				default:
					break;
				}
				break;
			case 1:
				switch (railcar_type)
				{
				case 0:
					for (int i = 0; i < realized_seats; i++) {
						over_price += 500 - int(!(reserved_seats[i].upper)) * 50;
					}
					break;
				case 1:
					for (int i = 0; i < realized_seats; i++) {
						over_price += 800 - int(!(reserved_seats[i].upper)) * 50;
					}
					break;
				default:
					break;
				}
				break;
			case 3:
				for (int i = 0; i < realized_seats; i++) {
					over_price += 900;
				}
				break;
			default:
				break;
			}
			cout << "The full price of your tickets is: " << over_price << "." << endl;
		}
		else {
			cout << "You didn't reserve any seats." << endl;
		}
	}
	void deny_order() {
		countoft = 0;
		amout = 0;
		amolt = 0;
		amot = 0;
		delete[] fios;
		fios = nullptr;
		got_data = false;
		realized_seats = 0;
		over_price = 0;
		delete[] reserved_seats;
		train_type = -1;
	}
	void form_tickets() {
		if (realized_seats > 0) {
			for (int i = 0; i < realized_seats; i++) {
				ticket ticket1 = ticket(data, fios[i], train_num, reserved_seats[i], mosca);
				Rail.new_ticket(ticket1);
				cout << ticket1;
			}
			deny_order();
		}
		else {
			cout << "Can't form tickets now. Not enough data." << endl;
		}
		
	}
	~kassa() {
		deny_order();
	}
};

int main(){
	railroad rail = railroad();
	kassa ticket_office = kassa(rail);
	ticket_office.check_seats();
	ticket_office.get_data();
	ticket_office.check_seats();
	ticket_office.reserv_seats();
	ticket_office.calculate_price();
	ticket_office.form_tickets();
	ticket_office.check_seats();
	/*ticket_office.reserv_seats();
	ticket_office.calculate_price();
	ticket_office.form_tickets();
	ticket_office.calculate_price();
	ticket_office.reserv_seats()*/;
}