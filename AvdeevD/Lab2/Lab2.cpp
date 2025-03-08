#include <iostream>

class DinArr
{
public:
	DinArr() {
		n = 4;
		arr = new double[n];
	}
	DinArr(int n_) :
		n(n_), arr(new double[n]) {};
	void set_n_manual() {
		int x;
		std::cout << "Enter size of the array: " << std::endl;
		std::cin >> x;
		int old_n = n;
		n = x;
		double* arr_1 = new double[n];
		for (int i = 0; i < n; i++) {
			arr[i] = 0;
		}
		if (old_n < n) {
			for (int i = 0; i < old_n; i++) {
				arr_1[i] = arr[i];
			}
			arr = arr_1;
		}
		else {
			for (int i = 0; i < n; i++) {
				arr_1[i] = arr[i];
			}
			arr = arr_1;
		}
		delete[] arr_1;
	}
	void set_n(int x) {
		int old_n = n;
		n = x;
		double* arr_1 = new double[n];
		for (int i = 0; i < n; i++) {
			arr[i] = 0;
		}
		if (old_n < n) {
			for (int i = 0; i < old_n; i++) {
				arr_1[i] = arr[i];
			}
			arr = arr_1;
		}
		else {
			for (int i = 0; i < n; i++) {
				arr_1[i] = arr[i];
			}
			arr = arr_1;
		}
		delete[] arr_1;
	}
	int get_n()const {
		return n;
	}
	double get_itoe(int i)const {
		if (i < n) {
			return arr[i];
		}
		else {
			std::cout << "There is no such index for a number." << std::endl;
		}
	}
	void set_itoe_manual(int i) {
		if (i < n) {
			double itoe;
			std::cout << "Enter the number: ";
			std::cin >> itoe; 
			arr[i] = itoe;
		}
		else {
			std::cout << "It's not a valid number." << std::endl;
		}
	}
	void set_itoe(int i, double itoe) {
		if (i < n) {
			arr[i] = itoe;
		}
		else {
			std::cout << "It's not a valid index." << std::endl;
		}
	}
	double find_min() {
		double minimum = arr[0];
		for (int i = 1; i < n; i++) {
			if (arr[i] <= minimum) {
				minimum = arr[i];
			}
		}
		return minimum;
	}
	void check_sort() {
		int count = 0;
		for (int i = 1; i < n; i++) {
			if (arr[i - 1] < arr[i]) {
				++count;
			}
		}
		if (count == n - 1) {
				std::cout << "The array is sorted." << std::endl;
		}
		else {
			std::cout << "The array is not sorted." << std::endl;
		}
	}
	DinArr not_odd() {
		int not_odd_n = 0;
		for (int i = 0; i < n; i++) {
			if (i % 2 != 0) {
				not_odd_n++;
			}
		}
		DinArr res;
		res.set_n(not_odd_n);
		int count = 0;
		for (int i = 0; i < n; i++) {
			if (i % 2 != 0) {
				res.set_itoe(count, arr[i]);
				count++;
			}
		}
		return res;
	}
	friend std::ostream& operator<<(std::ostream& stream, const DinArr& arr);
	~DinArr() {};


private:
	int n;
	double* arr;
};
std::ostream& operator<<(std::ostream& stream, const DinArr& arr) 
{
	stream << "Size of array - " << arr.get_n() << std::endl;
	for (int i = 0; i < arr.get_n(); i++) {
		stream << i << " number is " << arr.get_itoe(i) << "." << std::endl;
	}
	return stream;
}


int main() {
	int n = 6;
	DinArr arr;
	arr.set_n(n);
	for (int i = 0; i < n; i++) {
		double num;
		std::cout << "Enter the " << i << " number: ";
		std::cin >> num;
		arr.set_itoe(i, num);
	}
	std::cout << arr;
	std::cout << arr.not_odd();
	arr.check_sort();
	std::cout << arr.find_min() << std::endl;
	return 0;
}