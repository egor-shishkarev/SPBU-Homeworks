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

void bubbleEvenSort(int* arrayOfElements, const int lengthOfArray) {
	for (int i = 0 + 1 * (lengthOfArray % 2 != 0); i < lengthOfArray; i += 2) {
		bool flagOfChanges = true;
		for (int j = lengthOfArray - 1 * (lengthOfArray % 2 != 0) - 1; j > i; j -= 2) {
			if (arrayOfElements[j] < arrayOfElements[j - 2]) {
				const int buffer = arrayOfElements[j];
				arrayOfElements[j] = arrayOfElements[j - 2];
				arrayOfElements[j - 2] = buffer;
				flagOfChanges = true;
			}
		}
		if (!flagOfChanges) {
			break;
		}
	}
}

bool test1(void) {
	int example[8] = { 8, 7, 6, 5, 4, 3, 2, 1 };
	bubbleEvenSort(example, 8);
	const int rightArray[8] = { 8, 1, 6, 3, 4, 5, 2, 7 };
	for (int i = 0; i < 8; ++i) {
		if (example[i] != rightArray[i]) {
			return false;
		}
	}
	return true;
}

bool test2(void) {
	int example[5] = { 5, 4, 3, 2, 1 };
	bubbleEvenSort(example, 5);
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
	bubbleEvenSort(arrayOfElements, numberOfElements);
	printf("Массив, отсортированный пузырьком только по четным позициям: \n");
	for (int i = 0; i < numberOfElements; ++i) {
		printf("%d ", arrayOfElements[i]);
	}
	free(arrayOfElements);
	return 0;
}