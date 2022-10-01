#include <stdio.h>
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
}

bool searchElement(int* arrayOfNumbers, int lengthOfArray, int elementToSearch) {
	bool result = false;
	int i = 0;
	while (arrayOfNumbers[i] <= elementToSearch && i < lengthOfArray - 1) {
		if (arrayOfNumbers[i] == elementToSearch) {
			result = true;
			break;
		}
		++i;
	}
	return result;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите два числа через Enter. \nПервое - количество элементов массива, второе - количество случайных чисел, для которых вы хотите проверить - содержатся они в сгенерированном массиве или нет => ");
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
		const bool result = searchElement(arrayOfNumbers, numberOfElements, arrayToSearch[i]);
		printf("\n%d - %s", arrayToSearch[i], result ? "true" : "false");
		++i;
	}
	free(arrayOfNumbers);
	free(arrayToSearch);
	return 0;
}