#include <stdio.h>
#include <math.h>
#include <locale.h>
#include <stdbool.h>

int verificationIntScanf() {
	int readValues;
	while (true) {
		int correctlyReadValues;
		correctlyReadValues = scanf("%d", &readValues);
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
	// Ввод значений
	printf("Введите два числа, неполное частное которых вы хотите узнать.\n");
	const int a = verificationIntScanf();
	const int b = verificationIntScanf();
	// Проверка деления на ноль
	if (b == 0) {
		printf("На ноль делить нельзя!");
		return(1);
	}
	// Объявляем новые переменные: неполное частное и знаки чисел a и b
	int count = 0;
	const int signA = a < 0 ? -1 : 1;
	const int signB = b < 0 ? -1 : 1;
	// Перебор всевозможных случаев
	switch (signA) {
	case 1:
		switch (signB) {
		case 1:
			while (a >= (count + 1) * b) {
				count += 1;
			}
			break;
		case -1:
			while (a >= (count - 1) * b) {
				count -= 1;
			}
			break;
		}
		break;
	case -1:
		switch (signB) {
		case 1:
			while (abs(a) > (count + 1) * b) {
				count += 1;
			}
			count = -count - 1;
			break;
		case -1:
			while (abs(a) > (count + 1) * abs(b)) {
				count += 1;
			}
			count += 1;
			break;
		}
		break;
	}
	// Вывод неполного частного
	printf("%d", count);
}

