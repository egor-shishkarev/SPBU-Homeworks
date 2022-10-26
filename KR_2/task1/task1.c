#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool searchTest(const int *numberOfSymbols, const int* arrayOfCountSymbols, const char* arrayOfRightSymbols, const int count) {
	for (int i = 0; i < count; ++i) {
		char symbol = arrayOfRightSymbols[i];
		int countOfSymbol = arrayOfCountSymbols[i];
		if (numberOfSymbols[(int)symbol] != countOfSymbol) {
			return false;
		}
	}
	return true;
}

bool test1(void) {
	int numberOfSymbols[257] = {0};
	const int maxCode = findSymbols("test1.txt", numberOfSymbols);
	const char arrayOfRightSymbols[4] = { 'A', 'B', 'C'};
	const int arrayOfCountSymbols[4] = { 3, 3, 3 };
	return searchTest(numberOfSymbols, arrayOfCountSymbols, arrayOfRightSymbols, 3);
}

int findSymbols(const char *fileName, int *arrayOfSymbols) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		printf("Такого файла нет.");
		return -1;
	}
	int maxCode = -1;
	while (!feof(file)) {
		const char currentSymbol = getc(file);
		const int code = currentSymbol;
		if (code > maxCode) {
			maxCode = code;
		}
		if (code < 0) {
			continue;
		}
		arrayOfSymbols[code] += 1;
	}
	fclose(file);
	return maxCode;
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!test1()) {
		printf("Тесты не пройдены.");
		return -1;
	}
	printf("Тесты успешно пройдены.\n");
	int numberOfSymbols[257] = {0};
	int maxCode = findSymbols("text.txt", numberOfSymbols);
	for (int i = 0; i < maxCode + 1; ++i) {
		if (numberOfSymbols[i] != 0) {
			if (i == 10 && numberOfSymbols[i] != 0) {
				printf("Символ '\\n' встречается в файле - %d раз\n", numberOfSymbols[i]);
				continue;
			}
			printf("Символ '%c' встречается в файле - %d раз\n", (char)i, numberOfSymbols[i]);
		}
	}
	if (maxCode == -1) {
		printf("В файле нет символов, он пуст.");
	}
	return 0;
}