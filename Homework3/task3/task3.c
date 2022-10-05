#include <stdio.h>
#include <stdbool.h>
#include <malloc.h> 
#include <locale.h>
#include <time.h>
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

int maxCountInSortArray(int* arrayOfNumbers, const int lengthOfArray) {
	if (arrayOfNumbers == NULL || lengthOfArray <= 0) {
		return NULL;
	}
	int element = arrayOfNumbers[0];
	int countOfElements = 1;
	int maxCount = 0;
	int i = 0;
	while (i < lengthOfArray - 1) {
		if (arrayOfNumbers[i] != arrayOfNumbers[i + 1]) {
			if (countOfElements > maxCount) {
				maxCount = countOfElements;
				element = arrayOfNumbers[i];
			}
			countOfElements = 1;
		} else {
			++countOfElements;
		}
		++i;
	}
	if (arrayOfNumbers[i - 1] == arrayOfNumbers[i] && countOfElements > maxCount) {
		element = arrayOfNumbers[i];
	}
	return element;
}

bool testMostFrequentlyElement(int* arrayOfNumbers, const int lengthOfArray, const int rightNumber) {
	const int result = smartQuickSort(arrayOfNumbers, 0, lengthOfArray - 1);
	return (result + 1) * (maxCountInSortArray(arrayOfNumbers, lengthOfArray) == rightNumber);
}

bool test1() {
	int arrayOfNumbers[6] = { 3, 1, 2, 3, 3, 2 };
	return testMostFrequentlyElement(arrayOfNumbers, 6, 3);
}

bool test2() {
	int arrayOfNumbers[10] = { 7, 5, 6, 1, 2, 7, 12, 4, 4, 1 };
	return testMostFrequentlyElement(arrayOfNumbers, 10, 1) || testMostFrequentlyElement(arrayOfNumbers, 10, 4) || testMostFrequentlyElement(arrayOfNumbers, 10, 7);
}

bool test3() {
	int arrayOfNumbers[1] = { 0 };
	return testMostFrequentlyElement(arrayOfNumbers, 1, 0);
}

bool incorrectCase() {
	int arrayOfNumbers[4] = { 1, 2, 3, 1 };
	return !(testMostFrequentlyElement(arrayOfNumbers, 0, 1));
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!(test1() && test2() && test3() && incorrectCase())) {
		printf("Тесты не пройдены!");
		return -1;
	}
	printf("Тесты пройдены!\n");
	printf("Данная программа находит наиболее часто встречающийся элемент в массиве.\nЕсли хотите ввести свой массив - введите 1. \nЕсли хотите увидеть пример - введите 0. => ");
	int flagOfMode = verificationIntScanf();
	if (flagOfMode != 1 && flagOfMode != 0) {
		printf("Значение не было распознано, работа программы завершена.");
		return 1;
	}
	printf("Введите длину массива => ");
	int numberOfElements = verificationIntScanf();
	int* arrayOfNumbers = (int*)calloc(numberOfElements, sizeof(int));
	if (arrayOfNumbers == NULL) {
		printf("Произошла ошибка, массив не был создан.");
		return -1;
	}
	switch (flagOfMode) {
	case 0:
		srand(clock());
		for (int i = 0; i < numberOfElements; ++i) {
			arrayOfNumbers[i] = rand() % (10) + 1;
		}
		break;
	case 1:
		printf("Вводите элементы через enter => ");
		for (int i = 0; i < numberOfElements; ++i) {
			arrayOfNumbers[i] = verificationIntScanf();
		}
		break;
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
	printf("\nНаиболее часто встречающийся элемент в массиве => %d", maxCountInSortArray(arrayOfNumbers, numberOfElements));
	free(arrayOfNumbers);
	return 0;
}