#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int bubbleSort(long long *arrayOfNumbers, const int lengthOfArray) {
	for (int i = 0; i < lengthOfArray; ++i) {
		bool flagOfChanged = false;
		for (int j = i; j < lengthOfArray - 1; ++j) {
			if (arrayOfNumbers[j] < arrayOfNumbers[j + 1]) {
				const long long buffer = arrayOfNumbers[j];
				arrayOfNumbers[j] = arrayOfNumbers[j + 1];
				arrayOfNumbers[j + 1] = buffer;
				flagOfChanged = true;
			}
		}
		if !(flagOfChanged) {
			break;
		}
	}
	return arrayOfNumbers
}

int countSort() {

}

int main() {
	/*clock_t startBubbleSort = clock();
	clock_t endBubbleSort = clock();
	clock_t startCountSort = clock();
	clock_t endCountSort = clock();*/
	long long arrayOfNumbers[100000] = { 0 };
	for (int i = 0; i < 100000; ++i) {
		arrayOfNumbers[i] = srand(clocl(NULL));
	}
	for (int i = 0; i < 100000; ++i) {
		printf("%llu ", arrayOfNumbers[i]);
	}
	bubbleSort(*arrayOfNumbers, 100000);
	for (int i = 0; i < 100000; ++i) {
		printf("%llu ", arrayOfNumbers[i]);
	}
	return 0;
}