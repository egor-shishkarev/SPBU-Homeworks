#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

int verificationIntScanf() {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		else {
			printf("Ошибка ввода. Введите целочисленное значение!\n");
		}
	}
	return readValues;
}

int main() {
	setlocale(LC_ALL, ".1251");
	// Вывод пояснений и ввод значений
	printf("Введите кол-во элементов в массиве => ");
	int amountOfElements = verificationIntScanf();
	int* arrayOfElements = (int*)malloc(amountOfElements * sizeof(int));
	// Ввод элементов массива
	printf("Вводите элементы массива через enter: ");
	int counterOfZeroElements = 0;
	for (int i = 0; i < amountOfElements; ++i) {
		arrayOfElements[i] = verificationIntScanf();
		if (arrayOfElements[i] == 0) {
			++counterOfZeroElements;
		}
	}
	// Очищение памяти массива
	free(arrayOfElements);
	// Вывод ответа
	printf("Количество нулевых элементов в ведённом массиве => %d", counterOfZeroElements);
	return 0;
}