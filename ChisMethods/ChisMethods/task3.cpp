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
	double h, tau, timeMin, timeMax, hMin, hMax, sigma,p;
	double A[100], B[100], C[100], D[100], alifa[100], beta[100];
	int i, j, iCnt, jCnt;
	timeMin = 0;
	hMin = 0;
	timeMax = 10;
	hMax = M_PI;
	h = M_PI / 5;
	tau = 0.25;
	tau = tau / 2;
	h = h / 2;
	iCnt = ((hMax - hMin) / h) + 1;
	jCnt = ((timeMax - timeMin) / tau) + 1;
	sigma = tau / (h*h);
	p = 0.5;

	for (i = 0; i < iCnt; i++)
		tempreture[0][i] = startCond(i*h, 0);
	for (j = 0; j < jCnt; j++) {
		tempreture[j][0] = leftCond(0, j*tau);
		tempreture[j][iCnt - 1] = rightCond(h*(iCnt - 1), j*tau);
	}

	for (j = 1; j < jCnt; j++) { // по времени
		alifa[1] = 0;
		beta[1] = tempreture[j][0];
		for (i = 1; i < iCnt; i++){ // по Х
			/*A[i] = -(1-p)*tau;
			C[i] = h * h + 2*(1-p)*tau ;
			B[i] = -(1 - p)*tau;
			D[i] = tempreture[j - 1][i] * (h * h - 2 * p*tau) + tempreture[j - 1][i - 1] * p*tau +
				+tempreture[j - 1][i + 1] * p*tau + tau*F(i*h,(j-0.5) * tau);
			*/
			A[i] = -0.5*sigma;
			C[i] = 1 + sigma;
			B[i] = -0.5*sigma;
			D[i] = tempreture[j - 1][i] * (1 - sigma) + 0.5*sigma* tempreture[j - 1][i - 1] + 0.5*sigma *tempreture[j - 1][i + 1]
				+ F(i*h, (j - 0.5) * tau)*sigma;
			alifa[i + 1] = -B[i] / (A[i] * alifa[i] + C[i]);
			beta[i + 1] = (D[i] - A[i] * beta[i]) / (A[i] * alifa[i] + C[i]);
		}

		for (i = iCnt - 2; i >= 1; i--) { // по Х
			tempreture[j][i] = alifa[i + 1] * tempreture[j][i + 1] + beta[i + 1];

		}
		double test = tempreture[1][5] * alifa[5] + beta[5];
		int sdkfskld = 0;
		double test1 = tempreture[1][1] * alifa[1] + beta[1];
		double test2 = tempreture[1][2] * alifa[2] + beta[2];
		int rrr = 0;
	}


	freopen("task3_1.xls", "w", stdout);


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
	//cout << "Ошибка: " << errV/(iCnt*jCnt);
}