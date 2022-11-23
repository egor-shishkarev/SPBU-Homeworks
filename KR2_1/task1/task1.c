#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

int verificationIntScanf(void) {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Было введено нецелочисленное значение! \n");
	}
	return readValues;
}

bool correctCase(void) {
	int errorCode = 0;
	List* list = createList(&errorCode);
	for (int i = 0; i < 500000; ++i) {
		insertElement(list, i, &errorCode);
	}
	for (int i = 499999; i >= 0; --i) {
		insertElement(list, i, &errorCode);
	}
	return isSymethric(list, &errorCode) && !errorCode;
}

bool incorrectCase(void) {
	int errorCode = 0;
	List* list = createList(&errorCode);
	for (int i = 0; i < 100; ++i) {
		insertElement(list, i, &errorCode);
	}
	insertElement(list, 9, &errorCode);
	insertElement(list, 10, &errorCode);
	for (int i = 99; i >= 0; --i) {
		insertElement(list, i, &errorCode);
	}
	return !isSymethric(list, &errorCode) && !errorCode;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!(correctCase() && incorrectCase())) {
		printf("Тесты не были пройдены!");
		return -1;
	}
	printf("Тесты пройдены успешно!\n");
	FILE* file = fopen("example.txt", "r");
	int errorCode = 0;
	List* list = createList(&errorCode);
	if (errorCode) {
		printf("Произошла ошибка при выделении памяти.");
		return -1;
	}
	while (!feof(file)) {
		const int currentNumber = 0;
		if (fscanf(file, "%d", &currentNumber) == -1) {
			break;
		}
		insertElement(list, currentNumber, &errorCode);
		if (errorCode) {
			printf("Произошла ошибка при выделении памяти.");
			return -1;
		}
	}
	fclose(file);
	bool listIsSymethric = isSymethric(list, &errorCode);
	if (errorCode) {
		printf("Произошла ошибка во время проверки на симметричность. В файле не было чисел.");
		return -1;
	}
	printf(listIsSymethric ? "Список симметричен." : "Список не симметричен.");
	deleteList(list);
	return 0;
}
