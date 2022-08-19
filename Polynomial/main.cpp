#include<iostream>
#include"polynomial.h"

using namespace std;


int main() {
	int lenght1 = 5;
	double* arr1 = new double[lenght1];
	for (int i = 0; i < lenght1; i++)
		arr1[i] = (double)i + 1.;
	Polynomial pl1(lenght1, arr1);
	int lenght2 = 3;
	double* arr3 = new double[lenght1];
	arr3[0] = -1.;
	arr3[1] = -4.;
	arr3[2] = -3.;
	arr3[3] = 1.;
	arr3[4] = 1.;
	Polynomial pl4(lenght1, arr3);
	double* arr4 = new double[4];
	arr4[0] = -1.;
	arr4[1] = -1.;
	arr4[2] = 1.;
	arr4[3] = 1.;
	Polynomial pl5(4, arr4);


	Polynomial pl2(lenght2);
	cout << "A = ";
	cout << pl1 << endl;

	cout << "A + A = ";
	cout << pl1 + pl1 << endl;

	cout << "A += A = ";
	cout << (pl1 += pl1) << endl;

	cout << "2 * A - 2 * A = ";
	cout << (pl1 - pl1) << endl;

	cout << "B = ";
	cout << pl2 << endl;

	cout << "2 * A * B = ";
	cout << ((pl1 * 2) * pl2) << endl;

	cout << "2 * A / 2 * A = ";
	cout << (pl1 / pl1) << endl;

	Polynomial pl3(lenght1 - 2, arr1);
	cout << "C = ";
	cout << pl3 << endl;

	cout << "2 * A / C = ";
	cout << ((pl1 * 2) / pl3) << endl;

	cout << "(2 * A + 2 * A) / C = ";
	cout << (((pl1 * 2) + (pl1 * 2)) / pl3) << endl;

	cout << "2 * A * 0 = ";
	cout << (pl1 * 0.) << endl;

	cout << "2 * A % C = ";
	cout << ((pl1 * 2) % pl3) << endl;

	cout << "C += 2 * A = ";
	cout << (pl3 += (pl1 * 2)) << endl;

	cout << "D = ";
	cout << pl4 << endl;

	cout << "E = ";
	cout << pl5 << endl;

	cout << "D % E = ";
	cout << (pl4 % pl5) << endl;

	getchar();
	return 0;
}