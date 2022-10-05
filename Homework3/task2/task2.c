﻿#include <stdio.h>
#include <stdbool.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <time.h>

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

void insertionSort(int* arrayOfNumbers, int firstIndex, int lastIndex) {
	int currentElement = 1;
	int lengthOfArray = lastIndex - firstIndex + 1;
	while (currentElement < lengthOfArray) {
		while (arrayOfNumbers[currentElement] < arrayOfNumbers[currentElement - 1] && currentElement >= 1) {
			const int buffer = arrayOfNumbers[currentElement - 1];
			arrayOfNumbers[currentElement - 1] = arrayOfNumbers[currentElement];
			arrayOfNumbers[currentElement] = buffer;
			--currentElement;
		}
		++currentElement;
	}
}

int smartQuickSort(int* arrayOfNumbers, int firstIndex, int lastIndex) {
	if (arrayOfNumbers == NULL || firstIndex > lastIndex || firstIndex < 0 || lastIndex < 0) {
		return -1;
	}
	if ((firstIndex < lastIndex) && (lastIndex - firstIndex + 1) < 10) {
		int left = firstIndex;
		int right = lastIndex;
		int middle = arrayOfNumbers[(left + right) / 2];
		do {
			while (arrayOfNumbers[left] < middle) {
				++left;
			}
			while (arrayOfNumbers[right] > middle) {
				--right;
			}
			if (left <= right) {
				const int buffer = arrayOfNumbers[left];
				arrayOfNumbers[left] = arrayOfNumbers[right];
				arrayOfNumbers[right] = buffer;
				++left;
				--right;
			}
		} while (left <= right);
		smartQuickSort(arrayOfNumbers, firstIndex, right);
		smartQuickSort(arrayOfNumbers, left, lastIndex);
	} else {
		insertionSort(arrayOfNumbers, firstIndex, lastIndex);
	}
	return 0;
}

bool binarySearch(int* arrayOfNumbers, int lengthOfArray, int elementToSearch) {
	if (lengthOfArray <= 0 || arrayOfNumbers == NULL) {
		return -1;
	}
	int left = 0;
	int right = lengthOfArray - 1;
	int middle = (left + right) / 2;
	while (left + 1 != right) {
		if (elementToSearch < arrayOfNumbers[middle]) {
			right = middle;
		} else {
			left = middle;
		}
		middle = (left + right) / 2;
	}
	return arrayOfNumbers[left] == elementToSearch || arrayOfNumbers[lengthOfArray - 1] == elementToSearch;
}

bool testSearch(int* arrayOfNumbers, const int lengthOfArray, const int numberToSearch) {
	const int result = smartQuickSort(arrayOfNumbers, 0, lengthOfArray - 1);
	return binarySearch(arrayOfNumbers, lengthOfArray, numberToSearch) * (result + 1);
}

bool test1() {
	int arrayOfNumbers[5] = {78, 45, 32, 67, 12};
	return testSearch(arrayOfNumbers, 5, 32);
}

bool test2() {
	int arrayOfNumbers[10] = { 124, 437, 475, 124, 987, 142, 654, 898, 675, 323 };
	return testSearch(arrayOfNumbers, 10, 654);
}

bool test3() {
	int arrayOfNumbers[20] = { 1242, 23, 235, 25325, 253, 676, 897, 214, 1243, 546, 5767, 4446, 6118, 984, 100, 365, 784, 1, 20, 36 };
	return !testSearch(arrayOfNumbers, 20, 2);
}

bool incorrectCase() {
	int arrayOfNumbers[1] = { 0 };
	return !testSearch(arrayOfNumbers, 0, 0);
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!(test1() && test2() && test3() && incorrectCase())) {
		printf("Тесты не пройдены!");
		return -1;
	}
	printf("Тесты пройдены!\n");
	printf("Введите два числа через Enter. \nПервое - количество элементов массива, \nвторое - количество случайных чисел, для которых вы хотите проверить - содержатся они в сгенерированном массиве или нет => ");
	int numberOfElements = verificationIntScanf() + 1;
	int *arrayOfNumbers = (int*)calloc(numberOfElements, sizeof(int));
	--numberOfElements;
	if (arrayOfNumbers == NULL) {
		printf("Произошла ошибка, массив не был создан.");
		return 1;
	}
	int numberToSearch = verificationIntScanf() + 1;
	int *arrayToSearch = (int*)calloc(numberToSearch, sizeof(int));
	--numberToSearch;
	if (arrayToSearch == NULL) {
		printf("Произошла ошибка, массив не был создан.");
		return 1;
	}
	srand(clock());
	for (int i = 0; i < numberOfElements; ++i) {
		arrayOfNumbers[i] = rand() % (500) + 1;
	}
	printf("Созданный массив: \n");
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	smartQuickSort(arrayOfNumbers, 0, numberOfElements - 1);
	printf("\nОтсортированный массив: \n");
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	for (int i = 0; i < numberToSearch; ++i) {
		arrayToSearch[i] = rand() % (500) + 1;
	}
	smartQuickSort(arrayToSearch, 0, numberToSearch - 1);
	printf("\nМассив для поиска: \n");
	for (int i = 0; i < numberToSearch; ++i) {
		printf("%d ", arrayToSearch[i]);
	}
	int i = 0;
	while (i < numberToSearch) {
		if (i < numberToSearch - 1 && *(arrayToSearch + i) == *(arrayToSearch + i + 1)) {
			++i;
			continue;
		}
		const bool result = binarySearch(arrayOfNumbers, numberOfElements, arrayToSearch[i]);
		printf("\n%d - %s", arrayToSearch[i], result ? "true" : "false");
		++i;
	}
	free(arrayOfNumbers);
	free(arrayToSearch);
	return 0;
}