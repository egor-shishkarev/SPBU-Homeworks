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
		else {
			printf("Ошибка ввода. Введите целочисленное значение!\n");
		}
	}
	return readValues;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите число, до которого хотите найти простые числа => ");
	int numberToSearchPrime = verificationIntScanf();
	if (numberToSearchPrime < 2) {
		printf("До введённого значения нет простых чисел.");
		return 1;
	}
	int *arrayOfNumbers = (int*)malloc(2 * numberToSearchPrime * sizeof(int));
	for (int i = 2; i < numberToSearchPrime + 1; ++i) {
		arrayOfNumbers[i] = i;
	}
	int currentPrime = arrayOfNumbers[2];
	bool flagSearchPrime = true;
	while (flagSearchPrime) {
		flagSearchPrime = false;
		for (int i = 2 * currentPrime; i < numberToSearchPrime + 1; i += currentPrime) {
			arrayOfNumbers[i] = 0;
		}
		for (int j = currentPrime + 1; j < numberToSearchPrime + 1; ++j) {
			if (arrayOfNumbers[j] != 0) {
				currentPrime = arrayOfNumbers[j];
				flagSearchPrime = true;
				break;
			}
		}
    }
	for (int i = 2; i < numberToSearchPrime + 1; ++i) {
		if (arrayOfNumbers[i] != 0) {
			printf("%d ", arrayOfNumbers[i]);
		}
	}
	free(arrayOfNumbers);
	return 0;
}