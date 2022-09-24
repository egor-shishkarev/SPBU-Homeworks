#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int bubbleSort(int arrayOfNumbers[], const int lengthOfArray) {
	for (int i = 0; i < lengthOfArray; ++i) {
		bool flagOfChanged = false;
		for (int j = lengthOfArray - 1; j > i; --j) {
			if (arrayOfNumbers[j] < arrayOfNumbers[j - 1]) {
				const int buffer = arrayOfNumbers[j];
				arrayOfNumbers[j] = arrayOfNumbers[j - 1];
				arrayOfNumbers[j - 1] = buffer;
				flagOfChanged = true;
			}
		}
		if (!(flagOfChanged)) {
			break;
		}
	}
	return arrayOfNumbers;
}

/*int countSort() {

}*/

int main() {
	/*clock_t startBubbleSort = clock();
	clock_t endBubbleSort = clock();
	clock_t startCountSort = clock();
	clock_t endCountSort = clock();*/
	int arrayOfNumbers[5] = {0};
	srand(clock());
	for (int i = 0; i < 5; ++i) {
		arrayOfNumbers[i] = rand();
	}
	for (int i = 0; i < 5; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	bubbleSort(arrayOfNumbers, 5);
	printf("\n");
	for (int i = 0; i < 5; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	return 0;
}