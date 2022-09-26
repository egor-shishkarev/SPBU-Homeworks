﻿#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>


int verificationIntScanf() {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		else {
			printf("Ошибка ввода. Введите целочисленное значение!\n");
		}
	}
	return readValues;
}

long double verificationLongDoubleScanf() {
	long double readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%lf", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		else {
			printf("Ошибка ввода. Введите число!\n");
		}
	}
	return readValues;
}

long double exponentiationLinear(const long double number, const int power) {
	if (number == 0 && power <= 0) {
		return 0;
	}
	long double result = power == 0 ? 1 : number;
	for (int i = 0; i < abs(power) - 1; ++i) {
		result *= number;
	}
	return power < 0 ? 1 / result : result;
}

long double exponentiationLogarithm(const long double number, const int power) {
	if (number == 0 && power <= 0) {
		return 0;
	}
	long double result = 1;
	long double buffer = number;
	int additionalPower = abs(power);
	while (additionalPower != 0) {
		if (additionalPower % 2 == 1) {
			result *= buffer;
			additionalPower -= 1;
		}
		else {
			buffer *= buffer;
			additionalPower /= 2;
		}
	}
	return power < 0 ? 1 / result : result;
}


bool testExpanentiation(const long double number, const int power) {
	if (number == 0 && power <= 0) {
		return (exponentiationLinear(number, power) == 0 && exponentiationLogarithm(number, power) == 0);
	}
	return exponentiationLinear(number, power) == pow(number, power) && exponentiationLogarithm(number, power) == pow(number, power);
}

bool correctCase() {
	return testExpanentiation(13, 4) && testExpanentiation(-3, 3) && testExpanentiation(2, 6);
}

bool incorrectCase() {
	return testExpanentiation(0, -3) && testExpanentiation(0, 0);
}

bool edgeCase() {
	return testExpanentiation(45, 0) && testExpanentiation(98, 1) && testExpanentiation(0, 5);
}
int main() {
	setlocale(LC_ALL, ".1251");
	if (!(correctCase() && incorrectCase() && edgeCase())) {
		printf("Тесты были провалены, найдите ошибку!");
	}
	printf("Тесты успешно пройдены!\n");
	printf("Введите число, которое хотите возвести в степень => ");
	const long double number = verificationLongDoubleScanf();
	printf("Введите степень => ");
	const int power = verificationIntScanf();
	printf("Число полученное с помощью алгоритма сложностью O(n) => %lf\n", exponentiationLinear(number, power));
	printf("Число полученное с помощью алгоритма сложностью O(log n) => %lf", exponentiationLogarithm(number, power));
	return 0;
}
