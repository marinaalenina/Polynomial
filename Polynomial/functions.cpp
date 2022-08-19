#include <iostream>
#include <string>
#include"Polynomial.h"

bool Polynomial::NoNull(double m)const {
	return (std::abs(m) > eps);
}

double Polynomial::Sum(double m) const {
	if (NoNull(m))
		return m;
	else
		return 0.;
}

void Polynomial::resize() {
	int i = lenght;
	while (i > 0 && !NoNull(polynomial[i])) {
		i--;
	}
	Polynomial Pol(i + 1, polynomial);
	*this = Pol;
}


Polynomial::Polynomial() {//default
	lenght = 1;
	polynomial = new double[lenght];
	polynomial[0] = 0.;
}

Polynomial::Polynomial(int n, double* _polynomial) {
	lenght = n;
	polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		polynomial[i] = _polynomial[i];
}

Polynomial::Polynomial(const Polynomial& Pol) {//copy
	lenght = Pol.lenght;
	polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		polynomial[i] = Pol.polynomial[i];
}

Polynomial::Polynomial(int n, double c) {//same values
	lenght = n;
	polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		polynomial[i] = c;
}

Polynomial::Polynomial(int n) {// random 0-9
	lenght = n;
	polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		polynomial[i] = (int)rand() % 10;
}

Polynomial::Polynomial(std::initializer_list<double> list) {
	lenght = list.size() / 2;
	polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		polynomial[i] = 0;
	const double* l = list.begin();
	int index = 0;
	for (int i = 0; i < list.size(); i += 2) {
		polynomial[index] = *(l + i);
		index++;
	}
	resize();
}

Polynomial::~Polynomial() {
	if (polynomial != 0) {
		delete[] polynomial;
		lenght = 0;
	}
}

Polynomial Polynomial::operator=(const Polynomial& Pol) {
	lenght = Pol.lenght;
	polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++) {
		polynomial[i] = Pol.polynomial[i];
	}
	return *this;
}
bool Polynomial::operator==(const Polynomial& Pol)const {
	if (lenght != Pol.lenght)
		return false;
	else
		for (int i = 0; i < lenght; i++)
			if (std::abs(polynomial[i] - Pol.polynomial[i]) > eps)
				return false;
	return true;
}
bool Polynomial::operator!=(const Polynomial& Pol)const {
	if (lenght == Pol.lenght)
		return false;
	else
		for (int i = 0; i < lenght; i++)
			if (std::abs(polynomial[i] - Pol.polynomial[i]) > eps)
				return false;
	return true;
}

Polynomial& Polynomial::operator*=(double k) {
	for (int i = 0; i < lenght; i++) {
		if (NoNull(polynomial[i] * k))
			polynomial[i] *= k;
		else
			polynomial[i] = 0;

	}
	this->resize();
	return *this;
}
Polynomial& Polynomial::operator/=(double k) {
	for (int i = 0; i < lenght; i++) {
		if (NoNull(polynomial[i] / k))
			polynomial[i] /= k;
		else
			polynomial[i] = 0;

	}
	return *this;
}

Polynomial& Polynomial::operator+=(const Polynomial& Pol) {
	if (lenght >= Pol.lenght) {
		for (int i = 0; i < Pol.lenght; i++)
			polynomial[i] = Sum(polynomial[i] + Pol.polynomial[i]);
		return *this;
	}
	else {
		*this = (*this + Pol);
		return *this;
	}
}
Polynomial& Polynomial::operator-=(const Polynomial& Pol) {
	if (lenght >= Pol.lenght) {
		for (int i = 0; i < Pol.lenght; i++)
			polynomial[i] = Sum(polynomial[i] - Pol.polynomial[i]);
		return *this;
	}
	else {
		*this = (*this - Pol);
		return *this;
	}
}

Polynomial Polynomial::operator*(double k) const {
	if (k == 0)
		return Polynomial(1, 0.);
	double* _polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		_polynomial[i] = polynomial[i] * k;
	return Polynomial(lenght, _polynomial);
}

Polynomial Polynomial::operator/(double k) const {
	double* _polynomial = new double[lenght];
	for (int i = 0; i < lenght; i++)
		_polynomial[i] = polynomial[i] / k;
	return Polynomial(lenght, _polynomial);
}

Polynomial Polynomial::operator+(const Polynomial& Pol) const {
	int max_size = (Pol.lenght > lenght) ? Pol.lenght : lenght;
	int min_size = (Pol.lenght > lenght) ? lenght : Pol.lenght;
	double* _polynomial = new double[max_size];
	for (int i = 0; i < min_size; i++) {
		_polynomial[i] = Sum(Pol.polynomial[i] + polynomial[i]);
	}
	for (int i = min_size; i < max_size; i++) {
		if (Pol.lenght > lenght)
			_polynomial[i] = Pol.polynomial[i];
		else
			_polynomial[i] = polynomial[i];
	}
	Polynomial result(max_size, _polynomial);
	result.resize();
	return result;
}

Polynomial Polynomial::operator-(const Polynomial& Pol) const {
	int max_size = (Pol.lenght > lenght) ? Pol.lenght : lenght;
	int min_size = (Pol.lenght > lenght) ? lenght : Pol.lenght;
	double* _polynomial = new double[max_size];
	for (int i = 0; i < min_size; i++) {
		_polynomial[i] = Sum(polynomial[i] - Pol.polynomial[i]);
	}
	for (int i = min_size; i < max_size; i++) {
		if (Pol.lenght > lenght)
			_polynomial[i] = Pol.polynomial[i];
		else
			_polynomial[i] = polynomial[i];
	}
	Polynomial result(max_size, _polynomial);
	result.resize();
	return result;
}

Polynomial Polynomial::operator*(const Polynomial& Pol) const {
	int size = lenght + Pol.lenght - 1;
	double* _polynomial = new double[size];
	int max_size = (Pol.lenght > lenght) ? Pol.lenght : lenght;
	int min_size = (Pol.lenght > lenght) ? lenght : Pol.lenght;
	for (int i = 0; i < size; i++) {
		_polynomial[i] = 0;
		for (int j = 0; j <= i; j++) {
			_polynomial[i] += ((lenght > j) ? polynomial[j] : 0) * ((Pol.lenght > i - j) ? Pol.polynomial[i - j] : 0);
		}
	}
	return Polynomial(size, _polynomial);
}

Polynomial Polynomial::operator/(const Polynomial& Pol) const {
	if (lenght < Pol.lenght)
		return Polynomial();
	Polynomial quotient(lenght - Pol.lenght + 1, 0.);
	Polynomial dividend(lenght, polynomial);

	for (int i = 0; i < quotient.lenght; i++) {
		quotient.polynomial[quotient.lenght - 1 - i] =
			dividend.polynomial[dividend.lenght - 1 - i] /
			Pol.polynomial[Pol.lenght - 1];
		for (int j = 0; j < Pol.lenght; j++) {
			if (NoNull(dividend.polynomial[dividend.lenght - 1 - i - j]
				- Pol.polynomial[Pol.lenght - 1 - j]
				* quotient.polynomial[quotient.lenght - 1 - i])
				)

				dividend.polynomial[dividend.lenght - 1 - i - j] -=
				Pol.polynomial[Pol.lenght - 1 - j] *
				quotient.polynomial[quotient.lenght - 1 - i];
			else
				dividend.polynomial[dividend.lenght - 1 - i - j] = 0.;
		}
	}
	return quotient;
}

Polynomial Polynomial::operator%(const Polynomial& Pol) const {
	Polynomial quotient(lenght - Pol.lenght + 1, 0.);
	Polynomial dividend(lenght, polynomial);

	for (int i = 0; i < quotient.lenght; i++) {
		quotient.polynomial[quotient.lenght - 1 - i] =
			dividend.polynomial[dividend.lenght - 1 - i]
			/ Pol.polynomial[Pol.lenght - 1];
		for (int j = 0; j < Pol.lenght; j++) {
			if (NoNull(dividend.polynomial[dividend.lenght - 1 - i - j]
				- Pol.polynomial[Pol.lenght - 1 - j] *
				quotient.polynomial[quotient.lenght - 1 - i]))

				dividend.polynomial[dividend.lenght - 1 - i - j] -=
				Pol.polynomial[Pol.lenght - 1 - j] *
				quotient.polynomial[quotient.lenght - 1 - i];
			else
				dividend.polynomial[dividend.lenght - 1 - i - j] = 0.;
		}
	}
	dividend.resize();
	return dividend;
}

const double& Polynomial::operator[](int i) const {
	if (i >= lenght) {
		return 0.;
	}
	else {
		return polynomial[i];
	}
}

double& Polynomial::operator[](int i) {
	if (i >= lenght) {
		double l = 0;
		return l;
	}
	else {
		return polynomial[i];
	}
}

Polynomial::operator std::string() const {
	std::string string_Polynomial;
	std::string string_number;
	bool number_null = true;
	for (int i = lenght - 1; i >= 0; i--) {
		string_number = std::to_string(abs(polynomial[i]));
		if (string_number[string_number.size() - 1] == '0') {
			for (size_t i = string_number.size() - 1; string_number[i] == '0'; i--) {
				string_number.erase(i, 1);
			}
			if (string_number[string_number.size() - 1] == '.')
				string_number.erase(string_number.size() - 1, 1);
		}
		if (string_number != "0") {
			if ((polynomial[i] > 0) && (!number_null)) {
				string_Polynomial.append(" + ");
			}
			if (polynomial[i] < 0) {
				string_Polynomial.append(" - ");
			}
			string_Polynomial.append(string_number);
			if (i != 0) {
				if (i == 1) {
					string_Polynomial.append("*x");
				}
				else {
					string_Polynomial.append("*x^");
					string_Polynomial.append(std::to_string(i));
				}
			}
			number_null = false;
		}
	}
	if (number_null)
		string_Polynomial.append("0");
	return string_Polynomial;
}

std::ostream& operator << (std::ostream& out, const Polynomial& pol) {
	return out << std::string(pol);
}

void Polynomial::Print() {
	for (int i = 0; i < lenght; i++) {
		if (polynomial[i] > 0 && i != 0)
			std::cout << " + " << polynomial[i] << "*x^" << i;
		else if (polynomial[i] < 0 && i != 0)
			std::cout << " - " << std::abs(polynomial[i]) << "*x^" << i;
		else
			std::cout << polynomial[i];
	}
	std::cout << std::endl;
}


