#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define lengthOfArray 10
/*Написать программу, которая заполняет массив случайными значениями 
(с использованием функции rand из stdlib.h), потом преобразует его без 
использования дополнительных массивов так, что в начале массива будут элементы, 
меньшие первого, а в конце — большие либо равные первому. Программа должна работать за линейное время.*/

int quickSort(int *arrayOfNumbers, int firstElement, int lastElement) {
	if (firstElement < lastElement) {
		int left = firstElement;
		int right = lastElement;
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
		quickSort(arrayOfNumbers, firstElement, right);
		quickSort(arrayOfNumbers, left, lastElement);

	} 
}

int main() {
	int arrayOfNumbers[lengthOfArray] = {0};
	srand(clock(NULL));
	for (int i = 0; i < lengthOfArray; ++i) {
		arrayOfNumbers[i] = rand();
	}
	for (int i = 0; i < lengthOfArray; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	quickSort(arrayOfNumbers, 0, lengthOfArray - 1);
	printf("\n");
	for (int i = 0; i < lengthOfArray; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	return 0;
}

