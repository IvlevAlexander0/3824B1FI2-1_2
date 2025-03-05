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

		size = size_a;
		mass = new int[size]();
		name = vector_name;
	}

	Vector(const Vector& vector) {
		name = vector.name;
		size = vector.size;
		delete[] mass;
		mass = new int[size]();
		for (int i = 0; i < size; i++) {
			mass[i] = vector.mass[i];
		}

	}

	void set_the_size(int size1) {
		if (size1 < 1 || size1>20) {
			std::cout << '\n' << name << ":" << "Error. Incorrect data (vector size)" << std::endl;
			size1 = 1;
		}

		int* new_mass = new int[size1]();

		for (int i = 0; i < size && i < size1; i++) {
			new_mass[i] = mass[i];

		}
		delete[] mass;

		mass = new_mass;
		size = size1;
	}

	void print_size() const {
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

	void print_component(int number) const {
		if (number < 1 || number > size) {
			std::cout << '\n' << name << ": " << "Error.Incorrect data(wrong number)" << std::endl;

		}
		else {
			std::cout << '\n' << name << ": " << "Component number: " << number << "\tThe value of the component: " << mass[number - 1];
			std::cout << '\n';
		}
	}

	void print_len() const {
		int sum = 0;
		for (int i = 0; i < size; i++) {
			sum += mass[i] * mass[i];
		}
		std::cout << '\n' << name << ": " << "Vector lenght: " << sqrt(sum) << std::endl;
	}

	
	int operator* (const Vector& v2) const {
		int sum = 0;
		if (this->size == v2.size) {
			for (int i = 0; i < v2.size; i++) {
				sum += this->mass[i] * v2.mass[i];
			}
			return sum;
		}
		else {
			return -1;
		}
	}

	
	Vector operator +(const Vector& v2) const {
		if (this->size == v2.size) {
			Vector v3(this->size, this->name + "+" + v2.name);
			for (int i = 0; i < v2.size; i++) {
				v3.mass[i] = this->mass[i] + v2.mass[i];
			}
			return v3;
		}
		else {

			return Vector(0, "Error size vectors");

		}

	}

	void print_sum() {
		std::cout << this->name << ": (";
		for (int i = 0; i < this->size - 1; i++) {
			std::cout << this->mass[i] << ",";
		}
		std::cout << this->mass[size - 1] << ")" << std::endl;
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

	// size1=3, new_size=5 -> v1(1,5,5,0,0)

	v1.set_the_size(5);
	v1.print_component(1);
	v1.print_component(2);
	v1.print_component(3);
	v1.print_component(4);
	v1.print_component(5);

	//v1(1,5,5,7,9)
	v1.set_component(4, 7);
	v1.set_component(5, 9);
	v1.print_component(4);
	v1.print_component(5);

	//size1=5, new_size=3 -> v1(1,5,5)
	v1.set_the_size(3);
	v1.print_component(1);
	v1.print_component(2);
	v1.print_component(3);
	v1.print_component(4);


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

	/*v1.sum(v1, v2);
	v1.proizvedenie(v1, v2);*/

	//operator overload
	int comp = v1 * v2;
	std::cout << "Composition v1 and v2: " << comp << std::endl;

	Vector v0 = v1 + v2;
	v0.print_sum();

	std::cout << "\n\nV3:\n";
	Vector v3(32);
	v3.print_size();
	v3.set_the_size(32);
	v3.print_size();
	v3.set_component(1, 89);
	v3.set_component(2, 5);
	v3.print_component(1);
	v3.print_component(2);

	v3.print_len();

	/*v2.proizvedenie(v2, v3);*/
	int compos2 = v2 * v3;
	std::cout << "Composition v2 and v3: " << compos2 << std::endl;

	Vector v01 = v1 + v3;
	v01.print_sum(); //Error size vectors

	//operator overload =
	std::cout << "\n\nV3 = V2:\n";
	v3 = v2;
	v3.print_size();
	v3.print_component(1);
	v3.print_component(2);
	v3.print_component(3);
	v3.print_len();


	//using the copy constructor
	std::cout << "\n\nV4:\n";
	Vector v4(v1);
	v4.print_size();
	v4.print_component(1);
	v4.print_component(2);
	v4.print_component(3);
	v4.print_len();

	return 0;
}

