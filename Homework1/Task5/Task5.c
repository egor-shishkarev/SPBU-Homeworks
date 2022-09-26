#include <stdio.h>
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

int main() {
	system("chcp 1251");
	system("cls");
	printf("Введите длину получаемой строки => ");
	const int numberOfElemnets = verificationIntScanf();
	char* arrayOfElements = (char*)malloc(numberOfElemnets);
	printf("Введите строку, баланс скобок в которой хотите проверить => ");
	char* additionalPointer = gets(arrayOfElements);
	bool correctlyParentheses = true;
	int result = 0;
	for (int i = 0; i < numberOfElemnets; ++i) {
		if (arrayOfElements[i] == ')') {
			--result;
		}
		else if (arrayOfElements[i] == '(') {
			++result;
		}
		if (result < 0) {
			correctlyParentheses = false;
			break;
		}
	}
	if (result != 0) {
		correctlyParentheses = false;
	}
	printf(correctlyParentheses == true ? "Баланс скобок соблюден" : "Баланс скобок не соблюден");
	free(arrayOfElements);
	return 0;
}