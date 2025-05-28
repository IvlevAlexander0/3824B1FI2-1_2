#include <vector>
#include <fstream>

using std;

class Tabulator {
	double(*func)(double);
	double start;
	double end;
	int count;
	vector<double> values;
public:
	Tabulator() :count{ 0 }, values{ vector<double>(0) } {}
	Tabulator(double(*func_)(double), double start_, double end_, int count_) : func{ func_ }, start{ start_ },
		end{ end_ }, count{ count_ } {}

	void set_func(double(*func_)(double)) {
		func = func_;
	}
	int get_count() {
		return count;
	}
	void set_count(int a){
		count = a;
	}
	void set_range(double a, double b) {
		start = a;
		end = b;
	}
	double* get_range(double* res) {
		return res = { start, end };
	}
	vector<double> tabulate() {
		double step = (end - start) / count;
		values.resize(count);
		double input = start;
		for (int i = 0; i < count; i ++) {
			values[i] = func(input);
			input += step;
		}
		return values;
	}

	vector<double> tabulate_and_save(ofstream& out){
		tabulate();
		if(out.is_open())
		for (double i : values) {
			out << i << endl;
		}
		return values;
	}
};