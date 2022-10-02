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

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите два целых числа => ");
	int firstNumber = verificationIntScanf();
	int secondNumber = verificationIntScanf();
	int firstMask = pow(2, floor(log2(firstNumber)));
	int secondMask = pow(2, floor(log2(secondNumber)));
	for (int i = 0; i < floor(log2(firstNumber + (firstNumber == 0)) + 1); ++i) {
		printf("%s", firstNumber & firstMask ? "1" : "0");
		firstMask >>= 1;
	}
	printf("\n");
	for (int i = 0; i < floor(log2(secondNumber + (secondNumber == 0)) + 1); ++i) {
		printf("%s", secondNumber & secondMask ? "1" : "0");
		secondMask >>= 1;
	}
	return 0;
}