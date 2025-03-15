#include <iostream>

class DinArr
{
public:
	DinArr() {
		n = 4;
		arr = new double[n];
	}
	DinArr(int n_) :
		n(n_), arr(nullptr) {
		if (n_ <= 0) {
			throw "Bad size.";
		}
		arr = new double[n];
	};
	void set_n_manual() {
		int x;
		std::cout << "Enter size of the array: " << std::endl;
		std::cin >> x;
		int old_n = n;
		n = x;
		double* arr_1 = new double[n];
		for (int i = 0; i < n; i++) {
			arr_1[i] = 0;
		}
		if (old_n < n) {
			for (int i = 0; i < old_n; i++) {
				arr_1[i] = arr[i];
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				arr_1[i] = arr[i];
			}
		}
		delete[] arr;
		arr = arr_1;
	}
	void set_n(int x) {
		int old_n = n;
		n = x;
		double* arr_1 = new double[n];
		for (int i = 0; i < n; i++) {
			arr_1[i] = 0;
		}
		if (old_n < n) {
			for (int i = 0; i < old_n; i++) {
				arr_1[i] = arr[i];
			}
		}
		else {
			for (int i = 0; i < n; i++) {
				arr_1[i] = arr[i];
			}
		}
		delete[] arr;
		arr = arr_1;
	}
	int get_n()const {
		return n;
	}
	double get_itoe(int i)const {
		if (i >= 0 && i < n) {
			return arr[i];
		}
		else {
			std::cout << "There is no such index for a number. The returning value will be 0." << std::endl;
			return 0;
		}
	}
	void set_itoe_manual(int i) {
		if (i >= 0 && i < n) {
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
		if (i >= 0 && i < n) {
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
		bool flag = true;
		for (int i = 1; i < n; i++) {
			if (arr[i] < arr[i - 1]) {
				flag = false;
				break;
			}
		}
		if (flag) {
			std::cout << "The array is sorted in ascending order." << std::endl;
		}
		else {
			flag = true;
			for (int i = 1; i < n; i++) {
				if (arr[i] > arr[i-1]) {
					flag = false;
				}
			}
			if (flag) {
				std::cout << "The array is sorted in descending order." << std::endl;
			}
			else {
				std::cout << "The array is not sorted." << std::endl;
			}
		}
	}
	DinArr not_odd() {
		int not_odd_n = floor(n/2);
		DinArr res;
		res.set_n(not_odd_n);
		for (int i = 1; i < n; i+2) {
			res.set_itoe(i, arr[i]);
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