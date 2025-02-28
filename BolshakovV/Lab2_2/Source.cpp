#include <iostream> 
#include <cmath>


class Vector {

private:
	int size;
	int* mass;
	std::string name;

public:
	Vector(int size_a = 1, const std::string& vector_name = "V0") {

		if (size_a < 1 || size_a>20) {
			std::cout << "\nError. Incorrect data (vector size)" << std::endl;
			size_a = 1;
		}
		else {
			size = size_a;
		}
		mass = new int[size];
		name = vector_name;
	}
	void set_the_size(int size1) {
		if (size1 < 1 || size1>20) {
			std::cout << '\n' << name << ":" << "Error. Incorrect data (vector size)" << std::endl;
			size1 = 1;
		}
		delete[] mass;
		size = size1;
		mass = new int[size];
	}
	void print_size() {
		std::cout << '\n' << name << ": " << "Vector size: " << size << std::endl;
	}
	void set_component(int number, int value) { // NUMBER = INDEX + 1
		if (number < 1 || number > size) {
			std::cout << '\n' << name << ": " << "Error. Incorrect data (wrong number)" << std::endl;

		}
		else {
			mass[number - 1] = value;
		}
	}
	void print_component(int number) {
		if (number < 1 || number > size) {
			std::cout << '\n' << name << ": " << "Error.Incorrect data(wrong number)" << std::endl;

		}
		else {
			std::cout << '\n' << name << ": " << "Component number: " << number << "\tThe value of the component: " << mass[number - 1];
			std::cout << '\n';
		}
	}
	void print_len() {
		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += mass[i] * mass[i];
		}
		std::cout << '\n' << name << ": " << "Vector lenght: " << sqrt(sum) << std::endl;
	}
	void proizvedenie(const Vector& v1, const Vector& v2) {
		int sum = 0;
		if (v1.size == v2.size) {
			for (int i = 0; i < size; i++) {
				sum += v1.mass[i] * v2.mass[i];
			}
			std::cout << "\nComposition " << v1.name << " and " << v2.name << ": " << sum << std::endl;
		}
		else {
			std::cout << "\nError size1 not equal to size2" << " (" << v1.name << " and " << v2.name << ")" << std::endl;
		}

	}

	void sum(const Vector& v1, const Vector& v2) {
		Vector v3(v1.size);

		if (v1.size == v2.size) {
			for (int i = 0; i < size; i++) {
				v3.mass[i] = v1.mass[i] + v2.mass[i];
			}

			std::cout << "Sum " << v1.name << " and " << v2.name << ": " << "V3 (";
			for (int i = 0; i < v3.size - 1; i++) {
				std::cout << v3.mass[i] << ",";
			}
			std::cout << v3.mass[size - 1] << ")" << std::endl;
		}
		else {
			std::cout << "\nError size1 not equal to size2" << " (" << v1.name << " and " << v2.name << ")" << std::endl;
		}

	}

	Vector& operator = (const Vector& b) {

		if (&b != this) {
			delete[]mass;
			size = b.size;
			mass = new int[size];
			for (int i = 0; i < size; i++) {
				mass[i] = b.mass[i];
			}
		}
		return *this;

	}

	~Vector() {
		delete[]mass;

	}

};


int main() {

	Vector v1(5, "V1");

	v1.set_the_size(3);
	v1.print_size();
	v1.set_component(1, 1);
	v1.set_component(2, 5);
	v1.set_component(3, 5);
	v1.print_component(1);
	v1.print_component(2);
	v1.print_component(3);
	v1.print_len();


	Vector v2(2, "V2");

	v2.set_the_size(3);
	v2.print_size();
	v2.set_component(1, 6);
	v2.set_component(2, 8);
	v2.set_component(3, 7);
	v2.print_component(1);
	v2.print_component(2);
	v2.print_component(3);
	v2.print_len();

	v1.sum(v1, v2);
	v1.proizvedenie(v1, v2);

	Vector v3;
	v3.set_the_size(32);
	v3.print_size();
	v3.set_component(1, 89);
	v3.set_component(2, 5);

	v3.print_component(1);
	v3.print_component(2);

	v3.print_len();

	v2.proizvedenie(v2, v3);

	v3 = v2;
	v3.print_size();
	v3.print_component(1);
	v3.print_component(2);
	v3.print_component(3);
	v3.print_len();

	return 0;
}

