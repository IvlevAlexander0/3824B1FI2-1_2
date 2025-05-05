#pragma once
#include <string>
#include <vector>
#include <iostream>

using std::string;
using std::vector;
using std::ostream;

class RailwayTicketOffice;
class Train;

enum place_type {
	SITTING = 1,
	UPPER,
	BOTTOM
};

class Wagon {
	int sitting_places;
	int upper_places;
	int bottom_places;
	vector<bool> places; //свободно ли место
	int free_sitting_places = 0;
	int free_upper_places = 0;
	int free_bottom_places = 0;
	int total_count;
	int cost = 0;
	friend Train;
public:
	Wagon(int sitting_places_ = 0, int upper_places_ = 0, int bottom_places_ = 0, int cost_=0) :
		sitting_places{ sitting_places_ }, upper_places{ upper_places_ }, bottom_places{ bottom_places_ }, total_count{ sitting_places_ + upper_places_ + bottom_places}, cost{cost_},
		free_sitting_places{ sitting_places_ }, free_upper_places{ upper_places_ }, free_bottom_places{ bottom_places_ }
	{
		places = vector<bool>(sitting_places + upper_places + bottom_places, true);
	}
	bool is_places_free(int type, int count) {
		if (count == 0) {
			return true;
		}
		switch (type)
		{
		case SITTING:
			return count < free_sitting_places;
		case UPPER:
			return count < free_upper_places;
		case BOTTOM:
			return count < free_bottom_places;
		default:
			return false;
		}
	}
	bool is_places_free(int sitting_places, int upper_places, int bottom_places) {
		return is_places_free(SITTING, sitting_places) && is_places_free(UPPER, upper_places) && is_places_free(BOTTOM, bottom_places);
	}
	vector<int> buy_places(int type, int count) {
		if (!is_places_free(type, count) || count == 0) {
			return vector<int>(0);
		}
		int start_pos;
		switch (type)
		{

		case SITTING:
			free_sitting_places -= count;
			start_pos = 0;
			break;
		case UPPER:
			start_pos = free_sitting_places;
			free_upper_places -= count;
			break;
		case BOTTOM:
			start_pos = free_sitting_places + free_upper_places;
			free_bottom_places -= count;
			break;
		}
		int counter = 0;
		vector<int> buied_places(count);
		for (int i = start_pos; i < total_count && counter < count; i++) {
			if (places[i]) {
				places[i] = false;
				buied_places[counter] = i;
				counter++;
			}
		}
		return buied_places;
	}
	vector<int> buy_places(int sitting_places, int upper_places, int bottom_places) {
		if ((!is_places_free(sitting_places, upper_places, bottom_places))
			|| sitting_places + upper_places + bottom_places == 0) {
			return vector<int>(0);
		}
		vector<int> res(0);
		res.reserve(sitting_places + upper_places + bottom_places);
		vector<int> bsp = buy_places(SITTING, sitting_places);
		if(bsp.size()>0)
			res.insert(res.cbegin(), bsp.cbegin(), bsp.cend());
		vector<int> bup = buy_places(UPPER, upper_places);
		if (bup.size() > 0)
			res.insert(res.cbegin()+ sitting_places, bup.cbegin(), bup.cend());
		vector<int> bbp = buy_places(BOTTOM, bottom_places);
		if (bbp.size() > 0)
			res.insert(res.cbegin() + sitting_places+upper_places, bbp.cbegin(), bbp.cend());
		return res;
	}
	void free_places(vector<int> places_) {
		for (int i : places_) {
			this->places[i] = true;
		}
	}
};

class Train {
	int cost;
	vector<Wagon> wagons;
public:
	size_t wagons_count;
	Train() {}
	Train(vector<Wagon> wagons_, int cost_ = 0) : wagons{ wagons_ }, wagons_count{ wagons_.size() }, cost{ cost_ } {}
	bool chek_is_places_free(int wagon, int type, int count) {
		return wagons[wagon].is_places_free(type, count);
	}
	bool chek_is_places_free(int wagon, int sitting_places, int upper_places, int bottom_places) {
		return wagons[wagon].is_places_free(sitting_places, upper_places, bottom_places);
	}
	vector<int> buy_places(int wagon, int sitting_places, int upper_places, int bottom_places) {
		return wagons[wagon].buy_places(sitting_places, upper_places, bottom_places);
	}
	int get_cost(int wagon, int sitting_places, int upper_places, int bottom_places) {
		return cost*(sitting_places + upper_places + bottom_places) + wagons[wagon].cost + sitting_places * 50 + upper_places * 20 + bottom_places * 30;
	}
	void free_places(int wagon, vector<int> places) {
		wagons[wagon].free_places(places);
	}
};
class Bilet;
ostream& operator << (ostream& out, Bilet bilet);
class Bilet {
public:
	int date;
	int train;
	int wagon;
	int place;
	string fio;
	friend ostream& operator << (ostream& out, Bilet bilet);
	Bilet() {}
	Bilet(int date_, int train_, int wagon_, int place_, string fio_):
		train{ train_ }, wagon{ wagon_ }, place{ place_ }, fio{ fio_ }, date{ date_ } {}
};

//ostream& operator << (ostream& out, Bilet bilet) {
//	out << bilet.date << ' ' << bilet.train << ' ' << bilet.wagon << ' ' << bilet.place << ' ' << bilet.fio;
//	return out;
//}


class GorkovoRailway {
	static vector<Bilet> sold_bilets;
	vector<Train> trains;
	vector<vector<Train>> schedule;
	friend RailwayTicketOffice;
	GorkovoRailway() {
		Wagon plackart = Wagon(0, 27, 27, 1);

		Wagon kupe = Wagon(0, 18, 18, 2);

		Wagon sv = Wagon(0, 0, 18, 3);

		Wagon martin_wagon = Wagon(100, 0, 0, 4);

		Train martin = Train(vector<Wagon>(8, martin_wagon), 300);
		vector<Wagon> wagons_for_firm(12);
		for (int i = 0; i < 2; i++) {
			wagons_for_firm[i] = sv;
		}
		for (int i = 2; i < 8; i++) {
			wagons_for_firm[i] = kupe;
		}
		for (int i = 8; i < 12; i++) {
			wagons_for_firm[i] = plackart;
		}
		Train firm = Train(wagons_for_firm, 200);
		vector<Wagon> wagons_for_speedy(12);
		for (int i = 0; i < 4; i++) {
			wagons_for_speedy[i] = kupe;
		}
		for (int i = 4; i < 12; i++) {
			wagons_for_speedy[i] = plackart;
		}
		Train speedy = Train(wagons_for_speedy, 250);
		this->trains = vector<Train>(10);
		for (int i = 0; i < 3; i++) {
			trains[i] = martin;
		}
		trains[3] = firm;
		trains[4] = speedy;
		for (int i = 5; i < 8; i++) {
			trains[i] = martin;
		}
		trains[8] = firm;
		trains[9] = speedy;
		schedule = vector<vector<Train>>(30, trains);

	}
public:
	static GorkovoRailway& Instance() {
		static GorkovoRailway instance;
		return { instance };
	}
};



class RailwayTicketOffice {
	vector<Bilet> bilets;
	int date;
	int train;
	int wagon;
	int sitting_places;
	int upper_places;
	int bottom_places = 0;
	string fio;
	vector<int> reserved_places;
public:
	RailwayTicketOffice(int date_, int train_, int wagon_, string fio_, int sitting_places_ = 0, int upper_places_ = 0, int bottom_places_ = 0) :
		sitting_places{ sitting_places_ }, upper_places{ upper_places_ }, bottom_places{ bottom_places_ }, fio{ fio_ }
	{
		if (date_ < 0 || date_ > 30) {
			throw "Wrong date";
		}
		if (train_ < 1 || train_ > 10) {
			throw "Wrong train";
		}
		train = train_ - 1;
		GorkovoRailway& gr = GorkovoRailway::Instance();
		Train target_train = gr.schedule[date][train];
		if (wagon_ > target_train.wagons_count || wagon_ < 1) {
			throw "Incorrect wagon";
		}
		wagon = wagon_;
	}
	bool check_is_free() {
		GorkovoRailway& gr = GorkovoRailway::Instance();
		Train target_train = gr.schedule[date][train];
		return target_train.chek_is_places_free(wagon, sitting_places, upper_places, bottom_places);
	}
	void reserv_places() {
		if (check_is_free()) {
			GorkovoRailway& gr = GorkovoRailway::Instance();
			Train target_train = gr.schedule[date][train];
			reserved_places = target_train.buy_places(wagon, sitting_places, upper_places, bottom_places);
		}
	}
	int get_price() {
		GorkovoRailway& gr = GorkovoRailway::Instance();
		Train target_train = gr.schedule[date][train];
		return target_train.get_cost(wagon, sitting_places, upper_places, bottom_places);
	}
	int ureserve_places() {
		GorkovoRailway& gr = GorkovoRailway::Instance();
		Train target_train = gr.schedule[date][train];
		target_train.free_places(wagon, reserved_places);
	}
	vector<Bilet> get_bilets() {
		GorkovoRailway& gr = GorkovoRailway::Instance();
		bilets = vector<Bilet>(reserved_places.size());
		for (int i = 0; i < reserved_places.size(); i++) {
			bilets[i] = Bilet(date, train, wagon, reserved_places[i], fio);
			gr.sold_bilets.push_back(bilets[i]);
		}

		return bilets;
	}
};