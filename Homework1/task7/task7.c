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
		else {
			printf("Ошибка ввода. Введите целочисленное значение!\n");
		}
	}
	return readValues;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Введите длину первой строки => ");
	const int firstLength = verificationIntScanf() + 1;
	printf("Введите первую строку => ");
	char* arrayOfElementsFirst = (char*)malloc(firstLength);
	char* firstAdditionalPointer = gets(arrayOfElementsFirst);
	if (!firstAdditionalPointer) {
		printf("Введенное значение не было распознано!");
		return 1;
	}
	printf("Введите длину второй строки => ");
	const int secondLength = verificationIntScanf() + 1;
	printf("Введите вторую строку => ");
	char* arrayOfElementsSecond = (char*)malloc(secondLength);
	char* secondAdditionalPointer = gets(arrayOfElementsSecond);
	if (!secondAdditionalPointer) {
		printf("Введенное значение не было распознано!");
		return 1;
	}
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