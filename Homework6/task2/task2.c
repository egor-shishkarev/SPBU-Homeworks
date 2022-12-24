#include "cyclicList.h"
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

int verificationIntScanf() {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1 && readValues != 0) {
			break;
		}
		printf("Было введено нецелочисленное или нулевое значение! \n");
	}
	return readValues;
}

int remainingWarrior(const int numberOfWarriors, const int killEvery, int *errorCode) {
	List* list = createCyclicList(errorCode);
	if (*errorCode) {
		return -1;
	}
	for (int i = 0; i < numberOfWarriors; ++i) {
		insertElement(list, i + 1, errorCode);
		if (*errorCode) {
			return -1;
		}
	}
	for (int i = 0; i < numberOfWarriors - 1; ++i) {
		deleteElement(list, killEvery, errorCode);
		if (*errorCode) {
			return -1;
		}
	}
	const int result = lastPosition(list, errorCode);
	if (*errorCode) {
		return -1;
	}
	deleteList(&list);
	return result;
}

bool correctCase(void) {
	int errorCode = 0;
	return remainingWarrior(12, 2, &errorCode) == 9 && errorCode == 0;
}

bool incorrectCase(void) {
	int errorCode = 0;
	remainingWarrior(-3, 0, &errorCode);
	return errorCode != 0;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!(correctCase() && incorrectCase())) {
		printf("Тесты не были пройдены!");
		return -1;
	}
	printf("Тесты пройдены успешно!\n");
	printf("Введите количество воинов в кругу => ");
	const int numberOfWarriors = verificationIntScanf();
	printf("Введите такое число m, что каждого m-го воина убивают => ");
	const int killEvery = verificationIntScanf();
	int errorCode = 0;
	const int result = remainingWarrior(numberOfWarriors, killEvery, &errorCode);
	if (errorCode == -1) {
		printf("Произошла ошибка с выделением памяти!");
		return errorCode;
	}
	printf("Выживший воин находится под номером %d", result);
	return 0;
}
