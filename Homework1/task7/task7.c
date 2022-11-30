#include <stdio.h>
#include <stdbool.h>
#include <malloc.h>
#include <locale.h>

int verificationIntScanf() {
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

int stringInput(const int length) {
	char* arrayOfElements = (char*)malloc(length);
	char* additionalPointer = gets(arrayOfElements);
	if (!additionalPointer) {
		printf("Введенное значение не было распознано!");
		return 1;
	}
	return arrayOfElements;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите длину первой строки => ");
	const int firstLength = verificationIntScanf() + 1;
	printf("Введите первую строку => ");
	char* arrayOfElementsFirst = stringInput(firstLength);
	printf("Введите длину второй строки => ");
	const int secondLength = verificationIntScanf() + 1;
	printf("Введите вторую строку => ");
	char* arrayOfElementsSecond = stringInput(secondLength);
	int countOfOccurrences = 0;
	for (int i = 0; i < firstLength - secondLength + 1; ++i) {
		bool flagOfStringMatches = true;
		for (int j = 0; j < secondLength - 1; ++j) {
			if (arrayOfElementsFirst[i + j] != arrayOfElementsSecond[j]) {
				flagOfStringMatches = false;
				break;
			}
		}
		if (flagOfStringMatches) {
			++countOfOccurrences;
		}
	}
	printf("Количество вхождений строки второй строки в первую = %d", countOfOccurrences);
	free(arrayOfElementsFirst);
	free(arrayOfElementsSecond);
	return 0;
}
