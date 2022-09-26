#include <stdio.h>
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
	// Вывод пояснений и ввод значений переменных
	printf("Данная программа меняет значения двух целочисленных переменных местами\n");
	printf("Введите первое целочисленное значение переменной => ");
	int firstNumber = verificationIntScanf();
	printf("Введите второе целочисленное значение переменной => ");
	int secondNumber = verificationIntScanf();
	// Основные арифметические операции
	firstNumber = firstNumber + secondNumber;
	secondNumber = firstNumber - secondNumber;
	firstNumber = firstNumber - secondNumber;
	// Вывод результата
	printf("Первая переменная => %d \nВторая переменная => %d\n", firstInt, secondInt);
	return 0;
}