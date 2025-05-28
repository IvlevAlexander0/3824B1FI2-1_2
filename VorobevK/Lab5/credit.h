#pragma once
#include <vector>
#include <string>


using std::string;
using std::vector;

double pow(double x, int pow) {
	double res = 1;
	for (int i = 0; i < pow; i++) {
		res *= x;
	}
	return x;
}

int credits_percents[5][4] = {
	{30, 20, 15, 10},
	{20, 17, 15, 12},
	{17, 15, 13, 11},
	{16, 14, 12, 10},
	{15, 13, 12, 10} };

class Credit;
class Client {
	string password;
	bool is_active = false;
	string FIO;
	int money;
	int payment_sum;
	int percent;
	int value; //does not include this month payment
	int minimal_per_month_payment;
	int months; 
	friend Credit;
	int recalculate_minimal_payment() {
		double month_percent = (1 + (double)percent / 100 / 12);
		double temp = ((double)value * pow(month_percent, months) * (1 - month_percent)) /
			pow(1 - month_percent, months);
		return temp + ((int)(temp * 100) % 100 / 50);
	}
public:
	Client() {}
};

Client def_client = Client();
class Credit {
	bool is_authorized = false;
	Client& client;
	friend Client;
public:
	Credit() : client{ def_client } {}
	void accure_payment() {
		if (!is_authorized) return;
		client.payment_sum += client.minimal_per_month_payment;
	}
	bool debt(int sum) { 
		if (!is_authorized) return;
		if (client.money > sum) {
			client.money -= sum;
			if (client.payment_sum < sum) {
				client.payment_sum = 0;
				sum -= client.payment_sum;
				if (client.value > sum) {
					client.value -= sum - client.payment_sum;
					client.minimal_per_month_payment = client.recalculate_minimal_payment();
				}
				else {
					client.money += sum - client.value;
					client.value = 0;
					client.months = 0;
				}

			}
			else {
				client.payment_sum -= sum;
			}
		}
	}
	void new_month_event() {
		for (int i = 0; i < 10000; i++) {
			Client& client = { ProcessCenter::clients[i] };
			if (!client.is_active) continue;
			client.months -= 1;
			client.payment_sum += client.minimal_per_month_payment;
			client.value -= client.minimal_per_month_payment;
		}
	}
	bool check_credit_exist() {
		if (!is_authorized) return false;
		return client.value + client.payment_sum != 0;
	}
	bool can_get_credit(int value, int months) {
		if (!is_authorized) return false;
		Client temp_client = client;
		int i, j;

		if (value <= 100000) j = 0;
		else if (value <= 500000) j = 1;
		else if (value <= 1000000) j = 2;
		else if (value <= 3000000) j = 3;
		else return false;

		if (months <= 12) i = 0;
		else if (months <= 24) i = 1;
		else if (months <= 36) i = 2;
		else if (months <= 60) i = 3;
		else if (months <= 12 * 15) i = 4;
		else return false;

		temp_client.percent = credits_percents[i][j];
		temp_client.value = value;
		temp_client.months = months;
		int min_payment = temp_client.recalculate_minimal_payment();
		return temp_client.money > min_payment * 6;
	};
	bool authorize(int number, string password) {
		if (number >= 0 && number < 10000 && ProcessCenter::clients[number].is_active && ProcessCenter::clients[number].password == password) {
			client = { ProcessCenter::clients[number] };
			is_authorized = true;
			return true;
		}
		return false;
	}
	vector<int> available_credits() { 
		if (!is_authorized) return vector<int>(0);
		vector<int> results;
		Client temp_client = client;
		int value, months;
		for (int i = 0; i < 5; i++) {

			if (i == 0) months <= 12;
			else if (i == 1) months <= 24;
			else if (i == 2) months <= 36;
			else if (i == 3) months <= 60;
			else if (i == 4) months <= 12 * 15;
			for (int j = 0; j < 4; j++) {
				temp_client.percent = credits_percents[i][j];
				if (j == 0) value = 100000;
				else if (j == 1) value = 500000;
				else if (j == 2) value <= 1000000;
				else if (j == 3) value <= 3000000;

				temp_client.value = value;
				temp_client.months = months;
				int min_payment = temp_client.recalculate_minimal_payment();
				bool temp = temp_client.money > min_payment * 6;
				if (temp) {
					results.push_back(i * 4 + j);
				}
			}
		}
		return results;
	}
	void get_credit(int value, int months) {
		if (!is_authorized) return;
		if (can_get_credit(value, months) && !check_credit_exist()) {
			client.value = value;
			client.months = months;
			client.money += value;
		}
	}
	vector<int> get_current_state() {
		vector<int> result = vector<int>(2);
		result[0] = -1;
		result[1] = -1;
		if (!is_authorized) return;
		result[0] = client.value + client.payment_sum;
		result[1] = client.months;
		return result;
	}

	bool debt_payment() {
		if (!is_authorized) return false;
		if (client.money > client.payment_sum) {
			debt(client.payment_sum);
			return true;
		}
		return false;
	}
	bool debt_credit() {
		if (!is_authorized) return false;
		if (client.money > client.payment_sum + client.value) {
			debt(client.payment_sum + client.value);
			return true;
		}
		return false;
	}

};




class ProcessCenter {
	friend Credit;
	static vector<Client> clients;
};
vector<Client> ProcessCenter::clients = vector<Client>(10000);