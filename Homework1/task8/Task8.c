#include <stdio.h>
#include <locale.h>
#include <malloc.h>
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

int rotatePartOfArray(int* arrayToRotate, const int start, const int end) {
	for (int i = 0; i < (end - start + 1) / 2; ++i) {
		const int buffer = arrayToRotate[start + i];
		arrayToRotate[start + i] = arrayToRotate[end - i];
		arrayToRotate[end - i] = buffer;
	}
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите два числа через enter: m и n для обозначения части массива, которые нужно перевернуть => ");
	int m = verificationIntScanf();
	int n = verificationIntScanf();
	if (m == 0 || n == 0) {
		printf("Для данной задачи массив не может иметь длину 0");
		return 1;
	}
	int lenArray = n + m;
	int* arrayOfNumbers = (int*)malloc((lenArray) * sizeof(int));
	arrayOfNumbers[0] = 0;
	// Создаем массив от 1 до n + m
	for (int i = 1; i < (n + m) + 1; ++i) {
		arrayOfNumbers[i] = i;
	}
	// Переворачиваем куски массива
	rotatePartOfArray(arrayOfNumbers, 1, m);
	rotatePartOfArray(arrayOfNumbers, m + 1, n + m);
	rotatePartOfArray(arrayOfNumbers, 1, n + m);
	// вывод массива
	for (int i = 1; i < n + m + 1; ++i) {
		printf("%d ", arrayOfNumbers[i]);
	}
	// Очищаем массив
	free(arrayOfNumbers);
	return 0;
}