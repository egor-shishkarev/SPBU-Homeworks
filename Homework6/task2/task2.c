#include "cyclicList.h"
#include <stdio.h>
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
		printf("Было введено не целочисленное значение! \n");
	}
	return readValues;
}

int countingRhyme(const int numberOfWarriors, const int killEvery, int *errorCode) {
	if (numberOfWarriors <= 0 || killEvery <= 0) {
		*errorCode = -1;
		return -1;
	}
	if (killEvery == 1) {
		return numberOfWarriors;
	}
	List* list = createList();
	if (list == NULL) {
		return -1;
	}
	for (int i = 0; i < numberOfWarriors; ++i) {
		*errorCode = insert(list, i + 1, i);
		if (*errorCode) {
			return *errorCode;
		}
	}
	Position* position = createPosition(list);
	if (position == NULL) {
		*errorCode = -1;
		return -1;
	}
	int step = 1;
	while (!oneLeft(list)) {
		++step;
		getNextPosition(position);
		if (step == killEvery) {
			deletePosition(list, position, errorCode);
			if (*errorCode) {
				return *errorCode;
			}
			step = 1;
		}
	}
	int temp = deletePosition(list, position, errorCode);

	clearList(&list);
	deletePositionMemory(&position);

	return temp;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Данная программа позволяет вычислить последнего оставшегося воина в кругу.\n");
	printf("Введите количество воинов в кругу => ");
	const int numberOfWarriors = verificationIntScanf();
	printf("Введите число m такое, что убивают каждого m-го => ");
	const int killEvery = verificationIntScanf();
	int errorCode = 0;
	const int result = countingRhyme(numberOfWarriors, killEvery, &errorCode);
	printf("Последний выживший - %d", result);
	return 0;
}