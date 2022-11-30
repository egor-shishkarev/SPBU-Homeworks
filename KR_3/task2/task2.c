#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <locale.h>

int verificationIntScanf(void) {
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
void bubbleSort(int arrayOfNumbers[], const int lengthOfArray) {
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
}

void bubbleSortOfEven(int* arrayOfNumbers, const int lengthOfArray) {
	for (int i = 0; i < lengthOfArray; ++i) {
		for (int j = lengthOfArray - 1; j > i; --j) {
			if (arrayOfNumbers[j] % 2 != 0) {
				continue;
			}
			for (int k = j - 1; k >= i; --k) {
				if (arrayOfNumbers[k] % 2 != 0) {
					continue;
				}
				if (arrayOfNumbers[j] < arrayOfNumbers[k] && arrayOfNumbers[j] % 2 == 0 && arrayOfNumbers[k] % 2 == 0) {
					const int buffer = arrayOfNumbers[j];
					arrayOfNumbers[j] = arrayOfNumbers[k];
					arrayOfNumbers[k] = buffer;
					break;
				}
			}
		}
	}
}

bool test1(void) {
	int example[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	bubbleSortOfEven(example, 8);
	const int rightArray[8] = { 2, 7, 4, 5, 6, 3, 8, 1 };
	for (int i = 0; i < 8; ++i) {
		if (example[i] != rightArray[i]) {
			return false;
		}
	}
	return true;
}

bool test2(void) {
	int example[5] = { 5, 4, 3, 2, 1 };
	bubbleSortOfEven(example, 5);
	const int rightArray[5] = { 5, 2, 3, 4, 1 };
	for (int i = 0; i < 5; ++i) {
		if (example[i] != rightArray[i]) {
			return false;
		}
	}
	return true;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!(test1() && test2())) {
		printf("Тесты не пройдены!");
		return -1;
	}
	printf("Тесты успешно пройдены!\n");
	printf("Введите количество элементов в массиве => ");
	const int numberOfElements = verificationIntScanf();
	printf("Вводите числа через enter: \n");
	int* arrayOfElements = calloc(numberOfElements, sizeof(int));
	if (arrayOfElements == NULL) {
		printf("Память не была выделена.");
		return -1;
	}
	for (int i = 0; i < numberOfElements; ++i) {
		arrayOfElements[i] = verificationIntScanf();
	}
	bubbleSortOfEven(arrayOfElements, numberOfElements);
	printf("Массив, отсортированный пузырьком только для четных элементов: \n");
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", arrayOfElements[i]);
	}
	free(arrayOfElements);
	return 0;
}