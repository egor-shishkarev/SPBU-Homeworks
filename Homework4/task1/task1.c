#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#define MAX(x, y) (((x) > (y)) ? (x) : (y))

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

void summaryOfTwoBinary(const long long int first, const long long int second, const maxBite) {
	long long int mask = 1;
	int *result = (int*)malloc((8 * maxBite) * sizeof(int));
	if (result == NULL) {
		printf("Массив не был создан.");
		return -1;
	}
	int buffer = 0;
	for (int i = 8 * maxBite - 1; i >= 0; --i) {
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
	for (int i = 0; i < 8 * maxBite; ++i) {
		if (i != 0 && i % 8 == 0) {
			printf(" ");
		}
		printf("%d", result[i]);
	}
	printf("\nСумма в десятичной системе счисления: ");
	long long int sumDecimal = -*(result + 7) * pow(2, (maxBite - 1) * 8);
	for (int i = 8; i < 8 * maxBite + 1; ++i) {
		sumDecimal += (int)pow(2, 8 * maxBite - 1  - i) * result[i];
	}
	printf("%d", sumDecimal);
	free(result);
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите два целых числа в диапазоне от -1073741823 до 1073741823 => ");
	long long int firstNumber = verificationIntScanf();
	long long int secondNumber = verificationIntScanf();
	long long int biteToFirst = (int)floor(log2(2 * abs(firstNumber) + (firstNumber == 0)) / 8) + 2;
	long long int biteToSecond = (int)floor(log2(2 * abs(secondNumber) + (secondNumber == 0)) / 8) + 2;
	long long int maxBite = MAX(biteToFirst, biteToSecond);
	if (firstNumber < 0) {
		firstNumber += pow(256, maxBite);
	}
	if (secondNumber < 0) {
		secondNumber += pow(256, maxBite);
	}
	long long int firstMask = pow(256, maxBite) / 2;
	long long int secondMask = firstMask;
	printf(" \n");
	for (int i = 0; i < 8 * maxBite; ++i) {
		if (i != 0 && i % 8 == 0) {
			printf(" ");
		}
		printf("%s", firstNumber & firstMask ? "1" : "0");
		firstMask >>= 1;
	}
	printf("\n");
	for (int i = 0; i < 8 * maxBite; ++i) {
		if (i != 0 && i % 8 == 0) {
			printf(" ");
		}
		printf("%s", secondNumber & secondMask ? "1" : "0");
		secondMask >>= 1;
	}
	printf("\n");
	for (int i = 0; i < 9 * maxBite; ++i) {
		printf("-");
	}
	printf("\n");
	summaryOfTwoBinary(firstNumber, secondNumber, maxBite);
	return 0;
}

