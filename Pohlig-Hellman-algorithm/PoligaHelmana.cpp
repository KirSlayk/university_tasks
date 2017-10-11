#include <iostream>
#include <cmath>
#include <vector>
#include <map>
#include <memory>

// using std because simple project
using namespace std;

// use one file, because it is simple project

unsigned const primes_size = 11;
unsigned const int primes[primes_size] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31};

unsigned int pow_by_mod(unsigned int a, unsigned int b, unsigned int mod) {
	unsigned int res = a;
	// int degree = 2;
	if (0 == b) {
		return 1;
	}
	for (size_t i = 0; i < b - 1; ++ i) {
		res = (res * a) % mod;
	}
	return res;
}

template<typename T>
unsigned int pow(unsigned int a, T b) {
	return static_cast<unsigned int>(pow(static_cast<double>(a), static_cast<double>(b)));
}

template<typename T>
unsigned int divide(unsigned int a, T b) {
	return static_cast<unsigned int>(static_cast<double>(a) / b);
}

unsigned int calc_reverse(unsigned int num, unsigned int mod) {
	try {
		unsigned int result = 0;
		for (size_t i = 1; ; ++i) {
			unsigned int tmp = num * i;
			result = tmp % mod;
			if (1 == result) {
				return i;
			}
		}
	}
	catch(...) {
		cout<<"calc_reverse Error. Exit";
		exit(1);
	}
}

class PH {
public:
	PH() : 	p_(0)
			, g_(0)
			, y_(0)
			, multipliers_(map<unsigned int, unsigned int>())
			, chinese_coef_(map<unsigned int, unsigned int>())
			, system_(vector<pair<unsigned int, unsigned int>>())
			{}

	PH(unsigned int p, unsigned int g, unsigned int y) : 	p_(p)
															, g_(g)
															, y_(y)
															, multipliers_(map<unsigned int, unsigned int>())
															, chinese_coef_(map<unsigned int, unsigned int>())
															, system_(vector<pair<unsigned int, unsigned int>>())
															{}

	inline void PrintPGY() {
		cout<<"p = "<<this->p_<<" g = "<<this->g_<<" y = "<<this->y_<<endl;
	}

	// скорее всего не будет работать как inline
	inline void PrintMultipliers() {
		for (auto &e : this->multipliers_) {
			cout<<"value = "<<e.first<<" degre = "<<e.second<<endl;
		}
	}

	inline void ShowRelult() {
		cout<<endl<<"Система уравнений:"<<endl;
		for (auto &e : this->system_) {
			cout<<"x = "<<e.first<<" mod "<<e.second<<endl;
		}
	}

	void Factorization();
	void FindReminders();

private:
	unsigned int p_;
	unsigned int g_;
	unsigned int y_;
	map<unsigned int, unsigned int> multipliers_;
	map<unsigned int, unsigned int> chinese_coef_;
	vector<pair<unsigned int, unsigned int>> system_;

	unsigned int calc_module(unsigned int num, unsigned int mod);
	unsigned int calc_coef_of_module(unsigned int left_num, unsigned int right_num, unsigned int mod);
	pair<unsigned int, unsigned int> itec_calc_left_right_nums(	vector<pair<unsigned int, unsigned int>> &vec
																, unsigned int left_num
																, unsigned int right_num
																, unsigned int mod);
};


void PH::Factorization() {
	unsigned int tmp_p = this->p_ - 1;
	for (size_t i = 0; i < primes_size; ++i) {
		while (0 == tmp_p % primes[i]) {
			if (this->multipliers_.end() == this->multipliers_.find(primes[i])) {
				this->multipliers_[primes[i]] = 0;
			}
			++this->multipliers_[primes[i]];
			tmp_p /= primes[i];
		}
	}
	if (1 != tmp_p) {
		cout<<"Слишком большое число в разложении, надо использовать другой алгоритм"<<endl;
		exit(1);
	}
}


unsigned int PH::calc_module(unsigned int num, unsigned int mod) {
	try {
		unsigned int result = 0;
		for (size_t i = 1; ; ++i) {
			unsigned int tmp = pow_by_mod(num, i, mod);
			result = tmp % mod;
			if (1 == result) {
				return i;
			}
		}
	}
	catch(...) {
		cout<<"PH::calc_module Error. Exit";
		exit(1);
	}
}


unsigned int PH::calc_coef_of_module(unsigned int left_num, unsigned int right_num, unsigned int mod) {
	try {
		if (1 == right_num) {
			return 0;
		}
		for (size_t i = 1; ; ++i) {
			unsigned int tmp = pow_by_mod(left_num, i, mod);
			if (tmp == right_num) {
				return i;
			}
		}
	}
	catch (...) {
		cout<<"PH::calc_coef_of_module Error. Exit";
		exit(1);
	}
}


pair<unsigned int, unsigned int> PH::itec_calc_left_right_nums(	vector<pair<unsigned int
																, unsigned int>> &vec
																, unsigned int left_num
																, unsigned int right_num
																, unsigned int mod) {
	unsigned int coef_x = vec.back().second;
	unsigned int coef_free = vec.back().first;
	for (int i = vec.size() - 2; i >= 0; --i) {
		auto tmp = coef_x;
		coef_x *= vec[i].second;
		coef_free += tmp * vec[i].first;
	}
	cout<<"степень основания в левой части: "<<coef_free<<" степень основания * x в левой части: "<<coef_x<<endl;
	cout<<"пример: g^11 * g^2x = y mod p "<<endl;
	unsigned int new_right_num = right_num * (calc_reverse(pow_by_mod(left_num, coef_free, mod), mod)) % mod;;
	unsigned int new_left_num = pow_by_mod(left_num, coef_x, mod);
	return pair<unsigned int, unsigned int>(new_left_num, new_right_num);
}



void PH::FindReminders() {
	unsigned int tmp_p = this->p_ - 1;
	for (auto &e: this->multipliers_) {
		cout<<"множитель "<<e.first<<" степень "<<e.second<<endl;
		unsigned int num_of_el = 1;
		vector<unsigned int> g_hatch;
		vector<unsigned int> y_hatch;
		vector<pair<unsigned int, unsigned int>> computable_values;
		map<unsigned int, pair<unsigned int, unsigned int>> keys;
		for (size_t i = 0; i < e.second; ++i) {
			unsigned int divider = pow(e.first, i + 1);
			cout<<"текущий делитель "<<divider<<endl;
			g_hatch.push_back(pow_by_mod(g_, divide(tmp_p, divider), this->p_)) ;
			cout<<"g^((p-1)/текущий делитель) = "<<g_hatch.back()<<endl;
			y_hatch.push_back(pow_by_mod(y_, divide(tmp_p, divider), this->p_));
			cout<<"y^((p-1)/текущий делитель) = "<<g_hatch.back()<<endl;
			if (keys.end() != keys.find(num_of_el - 1)) {
				vector<pair<unsigned int, unsigned int>>tmp_vec;
				for (size_t i = num_of_el - 1; i > 0; --i) {
					auto tmp_arg = make_pair(keys.find(i)->second.first, keys.find(i)->second.second);
					tmp_vec.push_back(tmp_arg);
				}
				auto tmp_pair = this->itec_calc_left_right_nums(tmp_vec, g_hatch.back(), y_hatch.back(), this->p_);
				g_hatch.push_back(tmp_pair.first);
				y_hatch.push_back(tmp_pair.second);
				cout<<"после изменений g^((p-1)/текущий делитель) = "<<g_hatch.back()<<endl;
				cout<<"после изменений y^((p-1)/текущий делитель) = "<<y_hatch.back()<<endl;
			}
			
			auto key = this->calc_coef_of_module(g_hatch.back(), y_hatch.back(), this->p_);
			auto val = this->calc_module(g_hatch.back(), this->p_);
			cout<<"x = "<<key<<" mod "<<val<<endl;
			auto res = pair<unsigned int, unsigned int>(key, val);
			computable_values.push_back(res);
			keys.insert(pair<unsigned int, pair<unsigned int, unsigned int>>(num_of_el++, res));
		}
		unsigned int mod = computable_values.begin()->second;
		unsigned int left_num = computable_values.begin()->first;
		for (int i = 1; i < computable_values.size(); ++i) {
			auto tmp = mod;
			cout<<"tmp "<<tmp<<" mod "<<mod<<" left "<<left_num<<endl;
			mod *= computable_values[i].second;
			left_num += tmp * computable_values[i].first;
		}
		cout<<"Одно из уравнений для китайской теоремы:"<<endl;
		cout<<"x = "<<left_num<<" mod "<<mod<<endl;
		this->system_.push_back(make_pair(left_num, mod));
	}
}

int main(int argc, char *argv[]) {
	if (argc < 4) {
		cout<<"Мало аргументов"<<endl;
		return 0;
	}
	auto ph = make_shared<PH>(PH(static_cast<unsigned int>(atoi(argv[1]))
								, static_cast<unsigned int>(atoi(argv[2]))
								, static_cast<unsigned int>(atoi(argv[3]))
								));

	ph->Factorization();
	
	ph->PrintPGY();
	ph->PrintMultipliers();

	ph->FindReminders();

	ph->ShowRelult();
	return 0;
}