#include <iostream>
#include <random>
#include <string>
#define COUNT_CASSETE 6
#define FOR_CLIENT 1
#define FOR_CARD 2
#define FOR_PIN 3

class Card {
	friend class Client;
	friend class Processing_Centre;

	std::string card_number; //����� �����
	long int amount; //����� �� ����� �����
	std::string PIN; //���-���

	bool block;

	Card() : amount(0), block(false) {}
};

class Client {

	friend class Processing_Centre; //��������� ����� �������������, ����� ����� ������ � ��� ��������� �����

private:

	std::string last_name; //�������
	std::string first_name; //���
	std::string patronymic; //��������
	Card* cards; // ������ ���� (� ������� ����� ���� ���������)
	int count_card;
	int INC_card;


	Client(const std::string& last = "", const std::string& first = "", const std::string& patr = "") :
		last_name(last), first_name(first), patronymic(patr), count_card(0), INC_card(5) {
		cards = new Card[INC_card];

	}


	//������� ������������
	Client& operator =(const Client& cl) {
		if (this != &cl) {
			last_name = cl.last_name;
			first_name = cl.first_name;
			patronymic = cl.patronymic;
			count_card = cl.count_card;
			INC_card = cl.INC_card;

			delete[]cards;
			cards = new Card[INC_card];
			for (int i = 0; i < count_card; i++) {
				cards[i] = cl.cards[i];
			}
		}
		return *this;
	}
	void new_cards(Card& c) {
		if (count_card >= INC_card) {
			INC_card *= 2;
			Card* new_card = new Card[INC_card];
			for (int i = 0; i < count_card; i++) {
				new_card[i] = cards[i];
			}
			delete[]cards;
			cards = new_card;
		}
		cards[count_card] = c;
		++count_card;
	}

	~Client() {
		delete[]cards;

	}

};


class Processing_Centre {

private:

	Client* clients; //���-�� ����������� ����� ��������� ��������
	int INC;
	int count_client;

	void new_mass_client() {
		INC *= 2;

		Client* mass2 = new Client[INC];
		for (int i = 0; i < count_client; i++) {
			mass2[i] = clients[i];
		}
		delete[]clients;
		clients = mass2;
	}

	int check_man(const std::string& l, const std::string& f, const std::string& p) const {
		for (int i = 0; i < count_client; i++) {
			if (clients[i].last_name == l && clients[i].first_name == f && clients[i].patronymic == p) {
				return i;
			}
		}
		return -1;
	}

	


public:
	Processing_Centre() : count_client(0), INC(5) {
		clients = new Client[INC];
	}
	~Processing_Centre() {
		delete[]clients;
	}

	//�������� ������������
	Processing_Centre& operator=(const Processing_Centre& oth) {
		if (this != &oth) {
			INC = oth.INC;
			count_client = oth.count_client;
			delete[]clients;
			clients = new Client[INC];
			for (int i = 0; i < count_client; i++) {
				clients[i] = oth.clients[i];
			}
		}
		return *this;
	}

	int find_card_client(const std::string& c, int l) const { //l - �����, ��� ������� �� �������

		for (int i = 0; i < count_client; i++) {
			for (int j = 0; j < clients[i].count_card; j++) {
				if (clients[i].cards[j].card_number == c) {
					if (l == FOR_CLIENT) {
						return i;
					}
					else if (l == FOR_CARD) {
						return j;
					}
				}
			}

		}
		return -1;
	}

	void add_client(const std::string& l, const std::string& f, const std::string& p) {

		int value = check_man(l, f, p);

		if (value != -1) {
			std::cout << "The person has already been added to the system" << std::endl; //������� ��� ��� �������� � �������
			return;
		}

		if (count_client >= INC) {
			new_mass_client(); //����������� ������ ��� ��������
		}

		clients[count_client++] = Client(l, f, p); //��������� ������� (� ���� 0 ����, ����������� ������� ��� ����� - 5 (����������))
	}



	void add_card(const std::string& l, const std::string& f, const std::string& p) {
		int index_man = check_man(l, f, p);
		if (index_man == -1) {
			std::cout << "The person is not in the system" << std::endl; //�������� ��� � �������
			return;
		}

		//������� ����� �����
		std::mt19937 gen(std::random_device{}());
		std::uniform_int_distribution<int>dist(1, 9999);
		std::string num;
		int chislo;

		do {
			chislo = dist(gen);
			num = std::to_string(chislo);
			int len = num.size();

			while (len < 4) {
				num = "0" + num;
				len++;
			}


		} while (find_card_client(num, FOR_CARD) != -1);

		//������� ��� ���
		std::uniform_int_distribution<int>dist2(0, 9999);
		std::string pin;
		int chislo2;
		chislo2 = dist2(gen);
		pin = std::to_string(chislo2);
		int len2 = pin.size();
		while (len2 < 4) {
			pin = "0" + pin;
			len2++;
		}

		//��������� ����� �������
		Card card1;
		card1.card_number = num;
		card1.PIN = pin;

		clients[index_man].new_cards(card1);

	}

	void info_man(int k) {
		std::cout << "\n";
		std::cout << "Last name: " << clients[k].last_name << "\n"
			<< "First name: " << clients[k].first_name << "\n"
			<< "Patronymic: " << clients[k].patronymic << std::endl;
	}
	void info_card(const std::string& c) { //������� �����, � �� ������� (�� ������ ��� �����)
		int index_man = find_card_client(c, FOR_CLIENT);
		int index_card = find_card_client(c, FOR_CARD);
		std::cout << "Number card: " << clients[index_man].cards[index_card].card_number << "\t"
			<< "Balanse: " << clients[index_man].cards[index_card].amount << std::endl;
		if (clients[index_man].cards[index_card].block == true) {
			std::cout << "The card is blocked" << std::endl;
		}
		else {
			std::cout << "The card is not blocked" << std::endl;
		}
	}

	int check_PIN_code(int index_man, int index_card, const std::string& pin) {

		if (clients[index_man].cards[index_card].PIN == pin) {
			return 1;
		}
		else {
			return -1;
		}
	}


	//������� ��� ������������� � main (�������� ����� ����� ��� ��� ���)
	std::string get_card(const std::string& l, const std::string& f, const std::string& p, int index, int p_c) {
		int index_man = check_man(l, f, p);
		if (index_man == -1) {
			std::cout << "The person is not in the system" << std::endl;
			return "";
		}
		else if (index >= 0 && index < clients[index_man].count_card) {
			if (p_c == FOR_CARD) {
				return clients[index_man].cards[index].card_number;
			}
			else if (p_c == FOR_PIN) {
				return clients[index_man].cards[index].PIN;
			}
		}
		std::cout << "Error: Index out of range or invalid parameters." << std::endl;
		return "";
	}

	//������� ���������� � ������ ������������:
	void inf(const std::string& l, const std::string& f, const std::string& p) {
		int index_man = check_man(l, f, p);
		if (index_man == -1) {
			std::cout << "The person is not in the system" << std::endl;
			return;
		}
		for (int i = 0; i < clients[index_man].count_card; i++) {
			std::cout << "Card[" << i << "]:\n";
			std::cout << "Number: " << clients[index_man].cards[i].card_number << ", ";
			std::cout << "PIN: " << clients[index_man].cards[i].PIN << "\n\n";
		}
	}

	//������������� �����
	void block_card(int index_man, int index_card) {

		clients[index_man].cards[index_card].block = true;

	}

	//�������� �� ������� ����������� �����
	int nalichie(int index_man, int index_card, int summ) {

		if (clients[index_man].cards[index_card].block == true) {
			std::cout << "The card is blocked" << std::endl;
			return -1;
		}
		if (clients[index_man].cards[index_card].amount < summ) {
			std::cout << "There are not enough funds on your card" << std::endl;
			return -1;
		}
	}

	//����� �������������
	int card_is_blocked(int index_man, int index_card) {

		if (clients[index_man].cards[index_card].block == true) {
			return 1;
		}
		return 0;
	}

	//������� �� ����� ������
	void deduct(int index_man, int index_card, int summ) {
		clients[index_man].cards[index_card].amount = clients[index_man].cards[index_card].amount - summ;
	}
	//��������� ����
	void top_accaunt(int index_man, int index_card, int summ) {
		clients[index_man].cards[index_card].amount = clients[index_man].cards[index_card].amount + summ;
	}

};

class ATM {

private:
	const int Nominal_banknots[6] = { 100,200,500,1000,2000,5000 };
	const int Cassete_Capacity = 2000000; //<������� ������ ������� � 2000 ����� �����>
	const int max_count_banknotes = 40; // ������������ ���-�� �����

	int cassete[COUNT_CASSETE];
	int number_attempts_PIN; //���������� ������� ������� ��� ���

	std::string card;
	bool card_is_accept; //����� �������?
	bool PIN_entered;

	int card_b;

	int index_man0;
	int index_card0;

	Processing_Centre& centre; //��������� ������ ��� ����� ����� ����� ��������
	//�� ������, ��� ����� ������� ������������ ������������, ���� ATM �� �������� Processing_Centre


public:

	ATM(Processing_Centre& c) :card_is_accept(0), centre(c) {
		for (int i = 0; i < COUNT_CASSETE; i++) {
			cassete[i] = Cassete_Capacity * 0.8;

		}
	}

	~ATM() {}

	void accept_card(const std::string& c) { //������� �����

		if (card_is_accept) {
			std::cout << "The card has already been inserted into the ATM" << std::endl;
			return;
		}

		if (centre.find_card_client(c, FOR_CARD) == -1) {
			std::cout << "The card was not found" << std::endl;
			card_is_accept = false;
			return;
		}

		card = c;

		index_man0 = centre.find_card_client(card, FOR_CLIENT);
		index_card0 = centre.find_card_client(card, FOR_CARD);

		std::cout << "\nThe card is accepted" << std::endl;

		card_is_accept = true; //����� ���������

		PIN_entered = false; //��� ��� �� ������

		number_attempts_PIN = 0; //���������� ������� ������ ��� ��� (������ � 1)

	}

	void find_client() {
		if (card_is_accept) {

			if (centre.card_is_blocked(index_man0, index_card0)) {
				std::cout << "Your card is blocked" << std::endl;
				return;
			}

			if (PIN_entered) {

				centre.info_man(index_man0);

			}
			else {
				std::cout << "Enter the correct PIN code" << std::endl;

			}

		}
		else {
			std::cout << "You need to insert a card" << std::endl;

		}
	}

	void check_PIN(const std::string& p) {
		if (card_is_accept) {

			if (centre.card_is_blocked(index_man0, index_card0)) {
				std::cout << "Your card is blocked" << std::endl;
				return;
			}

			int res = centre.check_PIN_code(index_man0, index_card0, p);
			if (res == 1) {
				std::cout << "Correct PIN code" << std::endl;
				PIN_entered = true; //��� ��� ����������
				number_attempts_PIN = 0;

			}
			else {
				std::cout << "Incorrect PIN code" << std::endl;
				PIN_entered = false; //��� ��� �� ����������
				number_attempts_PIN++;
				std::cout << "Attempt number: " << number_attempts_PIN << std::endl;

				if (number_attempts_PIN >= 3) {

					centre.block_card(index_man0, index_card0);

					std::cout << "Your card is blocked" << std::endl;
					return;
				}

			}
		}
		else {
			std::cout << "You need to insert a card" << std::endl;
		}
	}

	//��������� �����
	void balance_info() {
		if (card_is_accept) {

			if (centre.card_is_blocked(index_man0, index_card0)) {
				std::cout << "Your card is blocked" << std::endl;
				return;
			}

			if (PIN_entered) {
				//int index_man = centre.find_card_client(c, FOR_CLIENT);
				centre.info_man(index_man0);
				centre.info_card(card);

			}
			else {
				std::cout << "Enter the correct PIN code" << std::endl;

			}

		}
		else {
			std::cout << "You need to insert a card" << std::endl;

		}

	}

	//������ ������� ��������
	void give_out_cash(int n) {
		if (card_is_accept) {

			if (centre.card_is_blocked(index_man0, index_card0)) {
				std::cout << "Your card is blocked" << std::endl;
				return;
			}

			if (PIN_entered) {
				if (n % 100 != 0 || n <= 0) { //����� ��������, ��� n - ��� ����� �����
					std::cout << "Incorrect value." << std::endl;
					return;
				}
				int value = centre.nalichie(index_man0, index_card0, n);
				if (value == -1) {
					return;
				}

				int copy_cassete[6];
				for (int i = 0; i < COUNT_CASSETE; i++) {
					copy_cassete[i] = cassete[i];

				}

				int count = 0;
				int summ = n;
				for (int i = 5; i >= 0; i--) {
					if (Nominal_banknots[i] <= summ) {
						int count_banknot = summ / Nominal_banknots[i];

						if (cassete[i] <= 0) {
							continue;
						}

						if (count + count_banknot > max_count_banknotes) { /*���� ����� ������� ���������� ������� ��� 40. (�������-�� �� 40 + ����� ���-�� > 40)*/

							count_banknot = max_count_banknotes - count;
						}

						if (cassete[i] < count_banknot) {
							count_banknot = cassete[i]; //���� � ������� ������ ������� ��� �����, �� ������ ��� ���� � �������� � ������ �������
						}

						summ -= count_banknot * Nominal_banknots[i];
						copy_cassete[i] -= count_banknot;
						count += count_banknot;
						if (summ == 0 || count >= max_count_banknotes) {
							break;
						}
					}
				}

				if (summ > 0) {
					std::cout << "ATM cannot dispense the requested amount. Please try again with a different amount." << std::endl;
					//������ ��������� ����������� ��������


					return;
				}

				for (int i = 0; i < COUNT_CASSETE; i++) {
					cassete[i] = copy_cassete[i];

				}

				centre.deduct(index_man0, index_card0, n);
				std::cout << "Your balance has been changed (reduced)" << std::endl;

			}
			else {
				std::cout << "Enter the correct PIN code" << std::endl;
			}

		}
		else {
			std::cout << "You need to insert a card" << std::endl;
		}
	}


	//������� ��������
	void accept_cash(int n) {
		if (card_is_accept) {

			if (PIN_entered) {

				if (n % 100 != 0 || n <= 0) { //����� ��������, ��� n - ��� ����� �����
					std::cout << "Incorrect value." << std::endl;
					return;
				}

				int copy_cassete[6];
				for (int i = 0; i < COUNT_CASSETE; i++) {
					copy_cassete[i] = cassete[i];

				}

				int count_accept = 0;
				int summ = n;
				for (int i = 5; i >= 0; i--) {
					if (Nominal_banknots[i] <= summ) {
						int count_banknot = summ / Nominal_banknots[i];

						if (count_banknot > 0) {

							int diff = Cassete_Capacity - cassete[i];
							if (diff <= 0) {
								continue; //������� � ������ ��������� ���������
							}

							if (count_banknot > diff) {
								count_banknot = diff; //����� �������, ������� ���������� � �������
							}

							if (count_banknot <= 0) {
								continue;
							}

							if (count_accept + count_banknot > max_count_banknotes) {
								count_banknot = max_count_banknotes - count_accept;
							}

							summ -= count_banknot * Nominal_banknots[i];
							copy_cassete[i] += count_banknot;
							count_accept += count_banknot;
						}



						if (summ == 0 || count_accept >= max_count_banknotes) {
							break;
						}
					}
				}
				if (summ > 0 || count_accept >= max_count_banknotes) {
					std::cout << "The ATM cannot accept this amount. Please try again with a different amount." << std::endl;

					return;
				}

				for (int i = 0; i < COUNT_CASSETE; i++) {
					cassete[i] = copy_cassete[i];

				}

				centre.top_accaunt(index_man0, index_card0, n);
				std::cout << "Your balance has been changed (replenished)" << std::endl;
			}
			else {
				std::cout << "Enter the correct PIN code" << std::endl;
			}

		}
		else {
			std::cout << "You need to insert a card" << std::endl;
		}
	}

	//������� ����� ������� 
	void return_card() {
		if (card_is_accept) {

			card_is_accept = false;

			std::cout << "Thank you for visiting!" << std::endl;
		}
		else {
			std::cout << "You need to insert a card" << std::endl;
		}
	}

	//������� ��� ������ ��������� �����
	void print_cassete() {
		for (int i = 0; i < COUNT_CASSETE; i++) {
			std::cout << "cassete [" << i + 1 << "]: " << cassete[i] << std::endl;

		}
	}

};



int main() {
	//���������� �������, ������ �����
	Processing_Centre centre;

	std::string l = "Bolshakov";
	std::string f = "Vladislav";
	std::string p = "Vladimirovich";
	centre.add_client(l, f, p);

	centre.add_card(l, f, p);
	centre.add_card(l, f, p);

	std::string card = centre.get_card(l, f, p, 0, FOR_CARD);
	std::string pin = centre.get_card(l, f, p, 0, FOR_PIN);

	std::string card1 = centre.get_card(l, f, p, 1, FOR_CARD);
	std::string pin1 = centre.get_card(l, f, p, 1, FOR_PIN);

	std::cout << card << " PIN: " << pin << std::endl;
	std::cout << card1 << " PIN1: " << pin1 << std::endl;

	//������ � ����������
	ATM atm(centre);

	atm.accept_card(card);

	//����� �������� �� ������ �����
	atm.find_client(); //��� �� ������ (����� �������)

	//��������� ��� ���
	atm.check_PIN(pin);

	//��������� ����� �������
	atm.balance_info();

	//������� �������� ��� ����� (������� ������)
	atm.accept_card(card1);

	atm.give_out_cash(1500); //�� ������� �������

	atm.accept_cash(2500);

	atm.balance_info(); //balance replenished - ����������

	atm.give_out_cash(1200);

	atm.balance_info(); //balance reduced - ����������

	atm.return_card();

	atm.accept_card(card1);
	atm.balance_info(); //������� ��� ��� ���� (������)

	atm.check_PIN("0788");
	atm.check_PIN("0010");
	atm.check_PIN("1562"); //Your card is blocked

	atm.balance_info(); //Your card is blocked

	//����� �������
	std::string l5 = "Bolshakov1";
	std::string f5 = "Vladislav1";
	std::string p5 = "Vladimirovich1";
	centre.add_client(l5, f5, p5);

	centre.add_card(l5, f5, p5);

	std::string card2 = centre.get_card(l, f, p, 0, FOR_CARD);
	std::string pin2 = centre.get_card(l, f, p, 0, FOR_PIN);

	atm.accept_card(card2); //�� ����������, ��� ��� ����� ����������� �������� ��� ��� � ���������

	atm.print_cassete(); //���������� ��������� ��������

	return 0;
}