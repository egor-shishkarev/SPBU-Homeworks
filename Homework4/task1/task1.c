#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <malloc.h>
#include <math.h>
#include <stdlib.h>

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

int sumDisplay(const int* result, const int maxBite) {
	for (int i = 0; i < 8 * maxBite; ++i) {
		if (i != 0 && i % 8 == 0) {
			printf(" ");
		}
		printf("%d", *(result + i));
	}
}

long long int additionOfTwoBinary(const long long int first, const long long int second, const int maxBite, bool showSum) {
	if (first > 1073741823 || first < -1073741823 || second > 1073741823 || second < -1073741823 || maxBite < 2) {
		return NULL;
	}
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
	if (showSum) {
		sumDisplay(result, maxBite);
	}
	long long int sumDecimal = -*(result + 7) * pow(2, (maxBite - 1) * 8);
	for (int i = 8; i < 8 * maxBite + 1; ++i) {
		sumDecimal += (long long int)pow(2, 8 * maxBite - 1  - i) * *(result + i);
	}
	free(result);
	return sumDecimal;
}

bool testSum(const long long int first, const long long int second, const int bites) {
	if (first > 1073741823 || first < -1073741823 || second > 1073741823 || second < -1073741823 || bites < 2) {
		return additionOfTwoBinary(first, second, bites, false) == NULL;
	}
	return additionOfTwoBinary(first, second, bites, false) == first + second;
}

bool test1(void) {
	long long int firstNumber = 128;
	long long int secondNumber = 256;
	return testSum(firstNumber, secondNumber, 3);
}

bool test2(void) {
	long long int firstNumber = -89;
	long long int secondNumber = -104;
	return testSum(firstNumber, secondNumber, 2);
}

bool test3(void) {
	long long int firstNumber = 1073741823;
	long long int secondNumber = 142723;
	return testSum(firstNumber, secondNumber, 5);
}

bool incorrectCase(void) {
	long long int firstNumber = 1073741824;
	long long int secondNumber = -1073741824;
	return testSum(firstNumber, secondNumber, 5);
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!(test1() && test2() && test3() && incorrectCase())) {
		printf("Тесты не пройдены!");
		return -1;
	}
	printf("Тесты успешно пройдены!\n");
	printf("Введите два целых числа в диапазоне от -1073741823 до 1073741823 => ");
	long long int firstNumber = verificationIntScanf();
	while (firstNumber > 1073741823 || firstNumber < -1073741823) {
		printf("Введено неверное значение. Повторите попытку => ");
		firstNumber = verificationIntScanf();
	}
	long long int secondNumber = verificationIntScanf();
	while (secondNumber > 1073741823 || secondNumber < -1073741823) {
		printf("Введено неверное значение. Повторите попытку => ");
		secondNumber = verificationIntScanf();
	}
	long long int biteToFirst = (int)floor(log2(2 * abs(firstNumber) + (firstNumber == 0)) / 8) + 2;
	long long int biteToSecond = (int)floor(log2(2 * abs(secondNumber) + (secondNumber == 0)) / 8) + 2;
	long long int maxBite = max(biteToFirst, biteToSecond);
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
	printf("\nСумма в десятичной системе счисления: %lli", additionOfTwoBinary(firstNumber, secondNumber, maxBite, true));
	return 0;
}

