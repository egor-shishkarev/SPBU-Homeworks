#include <stdio.h>
#include <stdbool.h>
#include <math.h>
#include <locale.h>
#include <string.h>

int verificationIntScanf() {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Ошибка ввода. Введите целочисленное значение!\n");
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
		printf("Ошибка ввода. Введите число!\n");
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
			--additionalPower;
		} else {
			buffer *= buffer;
			additionalPower /= 2;
		}
	}
	return power < 0 ? 1 / result : result;
}

bool testExponentiation(const long double number, const int power) {
	if (number == 0 && power <= 0) {
		return exponentiationLinear(number, power) == 0 && exponentiationLogarithm(number, power) == 0;
	}
	return exponentiationLinear(number, power) == pow(number, power) && exponentiationLogarithm(number, power) == pow(number, power);
}

bool correctCase() {
	return testExponentiation(13, 4) && testExponentiation(-3, 3) && testExponentiation(2, 6);
}

bool incorrectCase() {
	return testExponentiation(0, -3) && testExponentiation(0, 0);
}

bool edgeCase() {
	return testExponentiation(45, 0) && testExponentiation(98, 1) && testExponentiation(0, 5);
}

int main(int argc, char* argv[]) {
	if (argc > 1 && strcmp(argv[1], "-test") == 0) {
		if (!(correctCase() && incorrectCase() && edgeCase())) {
			return 1;
		}
		return 0;
	}
	setlocale(LC_ALL, ".1251");
	printf("Введите число, которое хотите возвести в степень => ");
	const long double number = verificationLongDoubleScanf();
	printf("Введите степень => ");
	const int power = verificationIntScanf();
	printf("Число, полученное с помощью алгоритма сложностью O(n) => %lf\n", exponentiationLinear(number, power));
	printf("Число, полученное с помощью алгоритма сложностью O(log n) => %lf", exponentiationLogarithm(number, power));
	return 0;
}