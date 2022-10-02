#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>

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

void summaryOfTwoBinary(const int first, const int second) {
	int mask = 1;
	int result[9] = { 0 };
	int buffer = 0;
	for (int i = 8; i >= 0; --i) {
		const int digitFirst = first & mask ? 1 : 0;
		const int digitSecond = second & mask ? 1 : 0;
		if (digitFirst + digitSecond + buffer >= 2) {
			result[i] = (digitFirst + digitSecond + buffer) % 2;
			buffer = 1;
			mask <<= 1;
			continue;
		}
		result[i] = (digitFirst + digitSecond + buffer) % 2;
		buffer = 0;
		mask <<= 1;
	}
	printf(" ");
	for (int i = 1; i < 9; ++i) {
		printf("%d", result[i]);
	}
	printf("\nСумма в десятичной системе счисления: ");
	int sumDecimal = 0;
	for (int i = 1; i < 9; ++i) {
		sumDecimal += pow(2, 8 - i) * result[i];
	}
	printf("%d", sumDecimal);
}
int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите два целых числа в диапазоне от -128 до 127 => ");
	int firstNumber = verificationIntScanf();
	while (firstNumber < -128 || firstNumber > 127) {
		printf("Введено значение, находящееся за пределами допустимого.\nВведите верное значение (от -128 до 127) => ");
		firstNumber = verificationIntScanf();
	}
	if (firstNumber < 0) {
		firstNumber += 256;
	}
	int secondNumber = verificationIntScanf();
	while (secondNumber < -128 || secondNumber > 127) {
		printf("Введено значение, находящееся за пределами допустимого.\nВведите верное значение (от -128 до 127) => ");
		secondNumber = verificationIntScanf();
	}
	if (secondNumber < 0) {
		secondNumber += 256;
	}
	int firstMask = 128;
	int secondMask = firstMask;
	printf(" ");
	for (int i = 0; i < 8; ++i) {
		printf("%s", firstNumber & firstMask ? "1" : "0");
		firstMask >>= 1;
	}
	printf("\n ");
	for (int i = 0; i < 8; ++i) {
		printf("%s", secondNumber & secondMask ? "1" : "0");
		secondMask >>= 1;
	}
	printf("\n --------\n");
	summaryOfTwoBinary(firstNumber, secondNumber);
	return 0;
}

