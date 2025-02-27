#include <iostream>

class converter {
private:
	double weight;
	double converted;
	int flag = 0;
public:
	converter() {
		weight = 0;
		converted = 0;
	};

	converter(double x) :
		weight(x), converted(0) {};

	void set_weight(double x) {
		weight = x;
	}

	double get_weight() {
		return weight;
	}

	void convert_to_pharmpound() { //использую традиционную версию на основе тройской или же британскую аптекарскую меру
		converted = (weight * 1000) / 373;
		flag = 1;
	}

	void convert_to_troyounce() {
		converted = (weight * 1000) / 31;
		flag = 2;
	}

	double get_converted() {
		return converted;
	}

	void print_itself() {
		std::cout << "Weight in kilos: " << weight << std::endl;
		switch (flag)
		{
		case 1:
			std::cout << "Weight in pharmacy pounds: " << converted << "." << std::endl;
			break;
		case 2:
			std::cout << "Weight in troy ounces: " << converted << "." << std::endl;
			break;
		default:
			std::cout << "You didn't convert weight at that moment." << std::endl;
			break;
		}
	}
};

int main()
{
	converter weight(20);
	weight.convert_to_pharmpound();
	std::cout << weight.get_converted() << std::endl;
	weight.set_weight(10);
	weight.convert_to_troyounce();
	std::cout << weight.get_weight() << "\n" << weight.get_converted() << std::endl;
	weight.print_itself();
}
