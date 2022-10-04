#include "smartQuickSort.h"
#include <stdio.h>
#include <stdbool.h>
#include <malloc.h> 
#include <locale.h>
#include <time.h>
#include <stdlib.h>

int maxCountInSortArray(int* arrayOfNumbers, const int lengthOfArray) {
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
		}
		else {
			++countOfElements;
		}
		++i;
	}
	if (arrayOfNumbers[i - 1] == arrayOfNumbers[i] && countOfElements > maxCount) {
		element = arrayOfNumbers[i];
	}
	return element;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Данная программа находит наиболее часто встречающийся элемент в массиве.\n");
	FILE* file = fopen("array.txt", "r");
	if (file == NULL) {
		printf("Файл не найден.");
		return 1;
	}
	int data[150] = {0};
	int linesRead = 0;
	int numberOfElements = 0;
	while (!feof(file)) {
		int buffer = 0;
		const int readBytes = fscanf(file, "%d", &buffer);
		if (readBytes < 0) {
			break;
		}
		if (linesRead == 0) {
			numberOfElements = buffer;
			++linesRead;
			continue;
		}
		data[linesRead-1] = buffer;
		++linesRead;
	}
	fclose(file);
	printf("Созданный массив: \n");
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", data[i]);
	}
	smartQuickSort(data, 0, numberOfElements - 1);
	printf("\nОтсортированный массив: \n");
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", data[i]);
	}
	printf("\nНаиболее часто встречающийся элемент в массиве => %d", maxCountInSortArray(data, numberOfElements));
	return 0;
}