#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>

long double bubbleSort(int arrayOfNumbers[], const int lengthOfArray) {
	clock_t startBubbleSort = clock();
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
	clock_t endBubbleSort = clock();
	return (endBubbleSort - startBubbleSort);
}

/*int countSort() {

}*/

int main() {
	setlocale(LC_ALL, ".1251");
	/*clock_t startCountSort = clock();
	clock_t endCountSort = clock();*/
	srand(clock());
	int arrayOfNumbers[100000] = {0};
	for (int i = 0; i < 100000; ++i) {
		arrayOfNumbers[i] = rand();
	}
	long double timeForBubble = bubbleSort(arrayOfNumbers, 100000);
	printf("\n");
	printf("\nВремя работы сортировки пузырьком => %5.2Lf мс", timeForBubble);
	return 0;
}