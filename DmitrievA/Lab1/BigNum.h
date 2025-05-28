#pragma once

#include <limits.h>
#include <ostream>
#include <iostream>
#include <string>
#include <math.h>

using std::string;
string nums[64] = {
"1",
"2",
"4",
"8",
"16",
"32",
"64",
"128",
"256",
"512",
"1024",
"2048",
"4096",
"8192",
"16384",
"32768",
"65536",
"131072",
"262144",
"524288",
"1048576",
"2097152",
"4194304",
"8388608",
"16777216",
"33554432",
"67108864",
"134217728",
"268435456",
"536870912",
"1073741824",
"2147483648",
"4294967296",
"8589934592",
"17179869184",
"34359738368",
"68719476736",
"137438953472",
"274877906944",
"549755813888",
"1099511627776",
"2199023255552",
"4398046511104",
"8796093022208",
"17592186044416",
"35184372088832",
"70368744177664",
"140737488355328",
"281474976710656",
"562949953421312",
"1125899906842624",
"2251799813685248",
"4503599627370496",
"9007199254740992",
"18014398509481984",
"36028797018963968",
"72057594037927936",
"144115188075855872",
"288230376151711744",
"576460752303423488",
"1152921504606846976",
"2305843009213693952",
"4611686018427387904",
"9223372036854775808",
};

class BigNumStr {
	string str;
public:
	size_t size; // how many characters in string excepting \0
	BigNumStr(void) {
		this->str = string("");
		this->size = 0;
	}
	BigNumStr(string str_) {
		this->str = string(str_);
		this->size = str_.size();
	}
	BigNumStr(const BigNumStr& str_) : str{ str_.str }, size{ str_.size } {};
	BigNumStr operator +(BigNumStr str1) {
		BigNumStr ns = BigNumStr(string(std::max(str1.size, size), '0'));
		bool flag = 0, pflag = 0;
		for (int i = 0; i < std::min(str1.size, size); i++) {
			pflag = flag;
			flag = 0;
			if (str1[i] + this->operator[](i) + pflag - 2 * '0' > 9) {
				flag = 1;
			}
			ns[i] = '0' + this->operator[](i) + str1[i] - 2 * '0' - flag * 10 + pflag;
		}
		BigNumStr bigger = str1.size > size ? str1 : *this;
		for (int i = std::min(str1.size, size); i < bigger.size; i++) {
			pflag = flag;
			flag = 0;
			if (bigger[i] + pflag > '9') {
				flag = 1;
			}
			ns[i] = bigger[i] + pflag - flag * 10;
		}
		if (flag) {
			ns.uppend_digit();
			ns[ns.size - 1] = '1';
		}

		return ns;
	}
	void uppend_digit() {
		this->str.insert(0, 1, '0');
		this->size += 1;
	}
	void uppend_digit(size_t count) {
		this->str.insert(0, count, '0');
		this->size += count;
	}
	char& operator [] (size_t index) {
		return str[size - index - 1];
	}
	string get_string() {
		return string(str);

	}
};

std::ostream& operator << (std::ostream& stream, BigNumStr& p_str) {
	stream << p_str.get_string();
	return stream;
}


class BigNum {
	static BigNumStr strings[64];
private: unsigned int num1;
		int num2;
public:
	BigNum(int num) {
		this->num1 = num;
		this->num2 = 0;
	}
	BigNum(unsigned num1_, int num2_) :num1{ num1_ }, num2{ num2_ } {}
	BigNum(void) {
		this->num1 = 0;
		this->num2 = 0;
	}
	BigNum(const BigNum& bignum) {
		this->num1 = bignum.num1;
		this->num2 = bignum.num2;
	}

	BigNum operator + (BigNum num) {
		BigNum res = 0;
		if (num.num1 > UINT32_MAX - num1) {
			res.num2 = 1;
		}
		res.num1 = num.num1 + num1;
		res.num2 = res.num2 + num.num2 + num2;
		return res;
	}
	string to_string() {
		if (num2 == 0) {
			return std::to_string(num1);
		}
		else {
			BigNumStr res;
			if (num2 > 0) {
				res = BigNumStr(std::to_string(num1));
				unsigned p = 1;
				for (int i = 32; i < 64; i++) {
					if ((num2 & p )!= 0) {
						res = res + BigNumStr(nums[i]);
					}
					p *= 2;
				}
				return res.get_string();
			}
			
			else {
				BigNum pos_num = -(*this);
				res = pos_num.to_string();
				string res_str = res.get_string();
				res_str.insert(res_str.begin(), '-');
				return res_str;
			}
		}
	}
	BigNum operator -() {
		BigNum num = *this;
		if (num.num2 > 0) {
			num.num2 = ~num.num2;
			num.num1 = ~num.num1;
			num.num1++;
			if (num.num1 == 0) {
				num.num2++;
			}
		}
		else {
			num.num1--;
			if (num.num1 == UINT32_MAX) {
				num.num2--;
			}
			num.num1 = ~num.num1;
			num.num2 = ~num.num2;
		}
		return num;
	}
	BigNum operator - (BigNum num) {
		return *this + (-num);
	}
	BigNum operator << (int num) {
		if (num > 64 || num < 0) { return BigNum(0); }
		if (num == 0) return BigNum(*this);
		int t_num2;
		unsigned t_num1;
		if (num >= 32) {
			t_num1 = 0;
			t_num2 = num1 << (num - 32);
		}
		else {
			t_num1 = num1 << num;
			t_num2 = (num2 << num) | (num1 >> 32 - num);
		}
		
		return BigNum(t_num1, t_num2);
	}
	BigNum operator >> (int num) {
		if (num > 64 || num < 0) { return BigNum(0); }
		if (num == 0) return BigNum(*this);
		unsigned t_num2;
		unsigned t_num1;
		if (num >= 32) {
			t_num2 = 0;
			t_num1 = num2 >> (num - 32);
		}
		else {
			t_num2 = num2 >> num;
			t_num1 = (num1>>num) | (num2 << (32 - num));
		}
		return BigNum(t_num1, t_num2);
	}
	BigNum operator & (BigNum num) {
		return BigNum(num.num1 & num1, num.num2 & num2);
	}
	bool operator != (BigNum num) {
		return (num1 != num.num1) || (num.num2 != num2);
	}
	BigNum operator *(BigNum num1) {
		BigNum res = 0;
		BigNum p = BigNum(1);
		for (int i = 0; i < 64; i++) {
			if ((p & (*this)) != 0) {
				res = res + (num1 << i);
			}
			p = p + p;
		}
		return res;
	}
	bool operator < (BigNum num) {
		if (num.num2 == num2) {
			return num1 < num.num1;
		}
		return num2 < num.num2;
	}
	bool operator == (BigNum num) {
		return num.num1 == num1 && num.num2 == num2;
	}
	BigNum abs() {
		if (*this < 0) {
			return -*this;
		}
		return *this;
	}
	BigNum operator / (BigNum num) {
		if (num == 0) throw "Divide by Zero error";
		if (num == *this) return 1;
		BigNum cp1 = this->abs(), cp2 = num.abs();
		if (cp1 < cp2) return 0;
		BigNum res = 0;
		BigNum temp = cp2;
		int i = 0;
		while (temp < *this) {
			i++;
			temp = temp << 1;
		}
		i--;
		cp2 = cp2 << i;
		BigNum p = 1;
		p = p << i;
		while (i >= 0) {
			if (cp2 < cp1) {
				cp1 = cp1 - cp2;
				res = res + p;
			}
			cp2 = cp2 >> 1;
			p = p >> 1;
			i--;
		}
		if (((*this)<0) ^ (num<0)) {
			return -res;
		}
		return res;
	}
	BigNum operator % (BigNum num) {
		return *this - ((*this) / num);
	}
};

std::ostream& operator << (std::ostream& stream, BigNum p_str) {
	stream << p_str.to_string();
	return stream;
}
