#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <time.h>

#define lengthOfArray 15

int quickSort(int* arrayOfNumbers, int firstIndex, int lastIndex) {
	if (firstIndex < lastIndex) {
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
		quickSort(arrayOfNumbers, firstIndex, right);
		quickSort(arrayOfNumbers, left, lastIndex);

	}
}

int main() {
	int arrayOfNumbers[lengthOfArray] = {0};
	srand(clock(NULL));
	for (int i = lengthOfArray / 2; i < lengthOfArray; ++i) {
		arrayOfNumbers[i] = rand();
	}
	for (int i = 0; i <= lengthOfArray / 2; ++i) {
		arrayOfNumbers[i] = rand();
	}
	for (int i = 0; i < lengthOfArray; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	quickSort(arrayOfNumbers, 1, lengthOfArray - 1);
	printf("\n");
	for (int i = 0; i < lengthOfArray; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	return 0;
}