#define _USE_MATH_DEFINES
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <math.h>
#include <cmath>
using namespace std;

double F(double x, double t) {
	return sin(x) + 2 * t / (t*t + 1);
}


double startCond(double x, double t) {
	return sin(x);
}

double leftCond(double x, double t) {
	return log(t*t + 1);
}

double rightCond(double x, double t) {
	return log(t*t + 1);
}

double realValue(double x, double t) {
	return sin(x) + log(t*t + 1);
}

int main() {
	double tempreture[100][100];
	double h, tau, timeMin, timeMax, hMin, hMax, sigma;
	int i, j, iCnt, jCnt;
	timeMin = 0;
	hMin = 0;
	timeMax = 10;
	hMax = M_PI;
	h = M_PI / 5;
 	//h = h / 2;
	tau = 0.25;
	tau = tau / 2;
	iCnt = ((hMax - hMin) / h) + 1;
	jCnt = ((timeMax - timeMin) / tau) + 1;
	sigma = tau / (h*h);

	for (i = 0; i < iCnt; i++)
		tempreture[0][i] = startCond(i*h, 0);
	for (j = 0; j < jCnt; j++) {
		tempreture[j][0] = leftCond(0, j*tau);
		tempreture[j][iCnt - 1] = rightCond(h*(iCnt - 1), j*tau);
	}

	for (j = 1; j < jCnt; j++) { // по времени
		for (i = 1; i < iCnt - 1; i++) { // по X
			tempreture[j][i] = sigma*tempreture[j - 1][i - 1] + (1 - 2 * sigma) * tempreture[j - 1][i]
				+ sigma*tempreture[j - 1][i + 1] + tau*F(i*h, (j - 1)*tau);
		}
	}

	freopen("out2.xls", "w", stdout);

	double errV = 0;
	for (i = 0; i < iCnt; i++) {
		cout << "   " << i*h;
	}
	cout << endl;
	for (j = 0; j < jCnt; j++) { // по времени
		cout << j*tau << "  ";
		for (i = 0; i < iCnt; i++) { // по X		
			cout << realValue(i*h, j*tau) << "  "; //tempreture[j][i] << "  ";
			errV += abs(tempreture[j][i] - realValue(i*h, j*tau));
		}
		cout << endl;
	}
	cout << "Ошибка: " << errV/(iCnt*jCnt);
}