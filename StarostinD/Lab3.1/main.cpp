#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

class Func {
	double (*f)(double);
	string name;
	enum { exp_, sin_, cos_, log_, asin_, acos_, unknown} n;
	double (* const ex)(double) = exp;
	double (* const asn)(double) = asin;
	double (* const acs)(double) = acos;
	double (* const ln)(double) = log;
	friend class Taylor;
	long double factorial(int n) {
		static vector<long double> res{ 1 };
		if (res.size() < n + 1) {
			for (int i = res.size(); i <= n; ++i) {
				res.push_back(res[i - 1] * i);
			}
		}
		return res[n];
	}
	 vector<long double> arc_d(long double a, long double x1, long double x2) {
		if (!x1) {
			return vector<long double>{a * (-2) * x2, x1 + 1, x2 - 1};
		}
		else {
			return vector<long double>{a * x1, x1 - 1, x2, (a * (-2)) * x2, x1 + 1, x2 - 1};
		}
	}
public:
	Func() : f(NULL), name(""), n(unknown) {};
	Func(double (*g)(double)) : f(g) {
		if (g == ex) {
			name = "exp(x)";
			n = exp_;
		}
		else if (g == asn) {
			name = "arcsin(x)";
			n = asin_;
		}
		else if (g == acs) {
			name = "arccos(x)";
			n = acos_;
		}
		else if (g == ln) {
			name = "log(1 + x)";
			n = log_;
		}
		else {
			name = "";
			n = unknown;
		}
	}
	Func(const string& fname): f(NULL), name(fname) {
		if (fname == "exp(x)") {
			f = exp;
			n = exp_;
		}
		else if (fname == "arcsin(x)") {
			f = asin;
			n = asin_;
		}
		else if (fname == "arccos(x)") {
			f = acos;
			n = acos_;
		}
		else if (fname == "log(1 + x)") {
			f = log;
			n = log_;
		}
		else {
			f = NULL;
			n = unknown;
		}
	}
	Func(const Func& g) : f(g.f), name(g.name), n(g.n) {};
	long double calculate(const unsigned int cnt, const long double point, const long double x, string& formula) {
		long double sum = 0;
		long double var = 1;
		switch (n) {
		case(exp_): {
			formula.append("e^" + to_string(point) + "(1");
			var = x - point;
			for (int i = 1; i < cnt; ++i) {
				sum += (var / factorial(i));
				var *= (x - point);
				formula.append(" + (x - " + to_string(point) + ")^" + to_string(i) + " / " + to_string(i) + "!");
			}
			formula.append(")");
			sum *= exp(point);
			break;
		}
		case(asin_): {
			if (x > 1 || x < -1) {
				cout << "Error! x must belong to the interval [-1; 1]\n";
				return -NAN;
			}
			formula.append("arcsin(x) = arcsin(" + to_string(point) + ")");
			sum = 0;
			vector<long double> coefs{ 1, 0, -0.5 };
			var = 0;
			long double x_p = x - point;
			for (int i = 1; i < cnt; ++i) {
				for (int j = 0; j < coefs.size(); j += 3) {
					var += coefs[j] * pow(point, coefs[j + 1]) * pow(1. - point * point, coefs[j + 2]);
				}
				formula.append(" + " + to_string(var / factorial(i)) + " * (x - " + to_string(point) + ")^" + to_string(i));
				var = (var / factorial(i)) * x_p;
				sum += var;
				var = 0;
				x_p *= (x - point);
				vector<long double> t1, t2;
				if (i + 1 != cnt) {
					for (int j = 0; j < coefs.size(); j += 3) {
						if (coefs[j] != 0) {
							t1 = arc_d(coefs[j], coefs[j + 1], coefs[j + 2]);
							for (int h = 0; h < t1.size(); h += 3) {
								if (t1[h] != 0) {
									t2.push_back(t1[h]);
									t2.push_back(t1[h + 1]);
									t2.push_back(t1[h + 2]);
								}
							}
						}
					}
					coefs = t2;
					t2.resize(0);
					t1.resize(0);
				}
			}
			sum += asin(point);
			break;
		}
		case acos_: {
			if (x > 1 || x < -1) {
				cout << "Error! x must belong to the interval [-1; 1]\n";
				return -NAN;
			}
			formula.append("arccos(x) = arccos(" + to_string(point) + ")");
			sum = 0;
			vector<long double> coefs{ -1, 0, -0.5 };
			var = 0;
			long double x_p = x - point;
			for (int i = 1; i < cnt; ++i) {
				for (int j = 0; j < coefs.size(); j += 3) {
					var += coefs[j] * pow(point, coefs[j + 1]) * pow(1. - point * point, coefs[j + 2]);
				}
				formula.append(" + " + to_string(var / factorial(i)) + " * (x - " + to_string(point) + ")^" + to_string(i));
				var = (var / factorial(i)) * x_p;
				sum += var;
				var = 0;
				x_p *= (x - point);
				vector<long double> t1, t2;
				if (i + 1 != cnt) {
					for (int j = 0; j < coefs.size(); j += 3) {
						if (coefs[j] != 0) {
							t1 = arc_d(coefs[j], coefs[j + 1], coefs[j + 2]);
							for (int h = 0; h < t1.size(); h += 3) {
								if (t1[h] != 0) {
									t2.push_back(t1[h]);
									t2.push_back(t1[h + 1]);
									t2.push_back(t1[h + 2]);
								}
							}
						}
					}
					coefs = t2;
					t2.resize(0);
					t1.resize(0);
				}
			}
			sum += acos(point);
			break;
		}
		case log_: {
			if (x <= -1) {
				cout << "Error! x must be greater than -1\n";
				return -NAN;
			}
			sum = 0;
			long double var_0 = (x - point) / (1 + point);
			var = var_0;
			int sign = 1;
			formula.append("ln(1 + x) = ln(" + to_string(1 + point) +  ")");
			for (int i = 1; i < cnt; ++i) {
				sum += sign * var / i;
				if (i & 1) {
					formula.append(" + ");
				}
				else {
					formula.append(" - ");
				}
				formula.append("(x - " + to_string(point) + ")^" + to_string(i) + " / (" + to_string(i) + "*(" + to_string(1 + point) + ")^" + to_string(i) + ")");
				var *= var_0;
				sign = -sign;
			}
			sum += log(1. + point);
			break;
		}
		default: {
			cout << "Error! Wrong function name!\n";
			break;
		}
		}

		return sum;
	}
	string formula(const unsigned int cnt, const long double point, string& formula) {
		long double var = 1;
		switch (n) {
		case(exp_): {
			formula.append("e^" + to_string(point) + "(1");
			for (int i = 1; i < cnt; ++i) {
				formula.append(" + (x - " + to_string(point) + ")^" + to_string(i) + " / " + to_string(i) + "!");
			}
			formula.append(")");
			break;
		}
		case(asin_): {
			formula.append("arcsin(x) = arcsin(" + to_string(point) + ")");
			vector<long double> coefs{ 1, 0, -0.5 };
			var = 0;
			for (int i = 1; i < cnt; ++i) {
				for (int j = 0; j < coefs.size(); j += 3) {
					var += coefs[j] * pow(point, coefs[j + 1]) * pow(1. - point * point, coefs[j + 2]);
				}
				var = (var / factorial(i));
				formula.append(" + " + to_string(var) + " * (x - " + to_string(point) + ")^" + to_string(i));
				var = 0;
				vector<long double> t1, t2;
				if (i + 1 != cnt) {
					for (int j = 0; j < coefs.size(); j += 3) {
						if (coefs[j] != 0) {
							t1 = arc_d(coefs[j], coefs[j + 1], coefs[j + 2]);
							for (int h = 0; h < t1.size(); h += 3) {
								if (t1[h] != 0) {
									t2.push_back(t1[h]);
									t2.push_back(t1[h + 1]);
									t2.push_back(t1[h + 2]);
								}
							}
						}
					}
					coefs = t2;
					t2.resize(0);
					t1.resize(0);
				}
			}
			break;
		}
		case acos_: {
			vector<long double> coefs{ -1, 0, -0.5 };
			var = 0;
			formula.append("arccos(x) = arccos(" + to_string(point) + ")");
			for (int i = 1; i < cnt; ++i) {
				for (int j = 0; j < coefs.size(); j += 3) {
					var += coefs[j] * pow(point, coefs[j + 1]) * pow(1. - point * point, coefs[j + 2]);
				}
				var = (var / factorial(i));
				formula.append(" + " + to_string(var) + " * (x - " + to_string(point) + ")^" + to_string(i));
				var = 0;
				vector<long double> t1, t2;
				if (i + 1 != cnt) {
					for (int j = 0; j < coefs.size(); j += 3) {
						if (coefs[j] != 0) {
							t1 = arc_d(coefs[j], coefs[j + 1], coefs[j + 2]);
							for (int h = 0; h < t1.size(); h += 3) {
								if (t1[h] != 0) {
									t2.push_back(t1[h]);
									t2.push_back(t1[h + 1]);
									t2.push_back(t1[h + 2]);
								}
							}
						}
					}
					coefs = t2;
					t2.resize(0);
					t1.resize(0);
				}
			}
			break;
		}
		case log_: {
			formula.append("ln(1 + x) = ln(" + to_string(1 + point) + ")");
			for (int i = 1; i < cnt; ++i) {
				if (i & 1) {
					formula.append(" + ");
				}
				else {
					formula.append(" - ");
				}
				formula.append("(x - " + to_string(point) + ")^" + to_string(i) + " / (" + to_string(i) + "*(" + to_string(1 + point) + ")^" + to_string(i) + ")");
			}
			break;
			}
		default: {
			cout << "Error! Wrong function name!\n";
			break;
		}
		}

		 return formula;
	}
};

class Taylor {
	Func* f;
	unsigned int cnt;
	double point;
	long double* value;
	string formula;
	friend class Func;
public:
	Taylor() : f(nullptr), cnt(0), point(0), value(nullptr) {};
	Taylor(double (* const g)(double), unsigned int cnt_, double point_) : f(new Func(g)), cnt(cnt_), point(point_), value(nullptr), formula("") {};
	Taylor(const string g, unsigned int cnt_, double point_) : f(new Func(g)), cnt(cnt_), point(point_), value(nullptr), formula("") {};
	Taylor(const Func& g, unsigned int cnt_, double point_) : f(new Func(g)), cnt(cnt_), point(point_), value(nullptr), formula("") {};
	void set_function(double (* const g)(double)) {
		if (f != nullptr) {
			delete f;
		}
		f = new Func(g);
	}
	void set_function(const string g) {
		if (f != nullptr) {
			delete f;
		}
		f = new Func(g);
	}
	string get_name() {
		return f->name;
	}
	int get_length() {
		return cnt;
	}
	void set_length(unsigned int l) {
		if (l != cnt) {
			value = nullptr;
			formula = "";
			cnt = l;
		}
	}
	double get_point() {
		return point;
	}
	void set_point(double point_) {
		if (point_ != point) {
			value = nullptr;
			formula = "";
			point = point_;
		}
	}
	string get_formula() {
		if (value == nullptr && formula == "") {
			return f->formula(cnt, point,formula);
		}
		else {
			return formula;
		}
	}
	string get_formula(const double x, long double& res) {
		if (value == nullptr) {
			value = new long double;
			*value = f->calculate(cnt, point, x, formula);
		}
		res = *value;
		return formula;
	}
	long double get_value(const double x) {
		if (value == nullptr) {
			value = new long double;
			*value = f->calculate(cnt, point, x, formula);
		}
		return *value;
	}
	long double deviation(const double x) {
		if (value == nullptr) {
			value = new long double;
			*value = f->calculate(cnt, point, x, formula);
		}
		if (f->f == f->ln) {
			return f->f(1 + x) - *value;
		}
		return f->f(x) - *value;
	}
	~Taylor() {
		if (value != nullptr) {
			delete value;
		}
		if (f != nullptr) {
			delete f;
		}
	}
};

int main() {
	cout << "List of functions: 1. exp(x) \t 2. arcsin(x) \t 3. arccos(x) \t 4. ln(1 + x)\n";
	Func ex("exp(x)");
	Taylor ex_(ex, 30, 3.51);
	cout << ex_.get_name() << endl;
	double x = 20;
	cout << "Formula: " << ex_.get_formula() << "\n VALUE(" << x << "): " << ex_.get_value(x) << ' ' 
		 << " DEVIATION : " << ex_.deviation(x) << " e^x = " << exp(x) << endl;
	Taylor asn(asin, 1, 0.25);
	x = 0.59;
	cout << "\n\n" << asn.get_name() << ": \n";
	for (int i = 1; i <= 21; ++i) {
		cout << "cnt = " << asn.get_length() << " a = " << asn.get_point() << " x = " << x << " VALUE = " << fixed << setprecision(20) << asn.get_value(x) << " AND DEVIATION = " << asn.deviation(x);
		cout << setprecision(2) << endl;
		cout << "Formula: " << asn.get_formula() << endl;
		asn.set_length(i + 1);
	}
	Taylor acs(acos, 1, 0.16);
	cout << "\n\n" << acs.get_name() << ": \n";
	for (int i = 1; i <= 21; ++i) {
		cout << "cnt = " << acs.get_length() << " a = " << acs.get_point() << " x = " << x << " VALUE = " << fixed << setprecision(20) << acs.get_value(x) << " AND DEVIATION = " << acs.deviation(x);
		cout << setprecision(2) << endl;
		cout << "Formula: " << acs.get_formula() << endl;
		acs.set_length(i + 1);
	}
	x = 4;
	Taylor lg("log(1 + x)", 1, 2);
	cout << "\n\n" << lg.get_name() << ": \n";
	for (int i = 1; i <= 20; ++i) {
		cout << "cnt = " << lg.get_length() << " a = " << lg.get_point() << " x = " << x << " VALUE = " << fixed << setprecision(20) << lg.get_value(x) << " AND DEVIATION = " << lg.deviation(x);
		cout << setprecision(2) << endl;
		cout << "Formula: " << lg.get_formula() << endl;
		lg.set_length(i + 1);
	}
	return 0;
}