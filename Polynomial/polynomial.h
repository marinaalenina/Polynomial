#pragma once
#include <initializer_list>
#include <string>


class Polynomial {
private:
	double* polynomial;
	int lenght;
	double eps = 1e-10;

	bool NoNull(double m)const;
	double Sum(double m) const;
	void resize();
public:
	Polynomial();

	Polynomial(int n, double* _polynomial);

	Polynomial(const Polynomial& Pol);

	Polynomial(int n, double c);

	Polynomial(int n);

	Polynomial(std::initializer_list<double> list);

	~Polynomial();

	Polynomial operator=(const Polynomial& Pol);

	bool operator==(const Polynomial& Pol)const;

	bool operator!=(const Polynomial& Pol)const;

	Polynomial& operator*=(double k);

	Polynomial& operator/=(double k);

	Polynomial& operator+=(const Polynomial& Pol);

	Polynomial& operator-=(const Polynomial& Pol);

	Polynomial operator*(double k) const;

	Polynomial operator/(double k) const;

	Polynomial operator+(const Polynomial& Pol) const;

	Polynomial operator-(const Polynomial& Pol) const;

	Polynomial operator*(const Polynomial& Pol) const;

	Polynomial operator/(const Polynomial& Pol) const;

	Polynomial operator%(const Polynomial& Pol) const;

	const double& operator[](int i) const;

	double& operator[](int i);

	explicit operator std::string() const;

	friend std::ostream& operator << (std::ostream& out, const Polynomial& pol);

	void Print();
};
