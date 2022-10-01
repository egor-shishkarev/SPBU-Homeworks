#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
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
	}
	else {
		insertionSort(arrayOfNumbers, firstIndex, lastIndex);
	}
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Данная программа позволяет продемонстрировать сортировку qsort с элементами алгоритма сортировки вставками\nЕсли хотите отсортировать свой массив - введите 1. \nЕсли хотите увидеть пример сортировки - введите 0. => ");
	int flagOfMode = verificationIntScanf();
	if (flagOfMode != 1 && flagOfMode != 0) {
		printf("Значение не было распознано, работа программы завершена.");
		return 1;
	}
	printf("Введите длину массива, который хотите отсортировать вставками => ");
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
			arrayOfNumbers[i] = rand() % (500) + 1;
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
	printf("\nОтсортированный массив: \n");
	smartQuickSort(arrayOfNumbers, 0, numberOfElements - 1);
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	free(arrayOfNumbers);
	return 0;
}