#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

bool searchTest() {

}

bool test1(void) {
	int arrayOfSymbols[257] = {0};
	int maxCode = findSymbols("test1.txt", arrayOfSymbols);

}

bool test2(void) {

}

bool test3(void) {

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
	int arrayOfSymbols[257] = {0};
	int maxCode = findSymbols("text.txt", arrayOfSymbols);
	for (int i = 0; i < maxCode + 1; ++i) {
		if (arrayOfSymbols[i] != 0) {
			if (i == 10 && arrayOfSymbols[i] != 0) {
				printf("Символ '\\n' встречается в файле - %d раз\n", arrayOfSymbols[i]);
				continue;
			}
			printf("Символ '%c' встречается в файле - %d раз\n", (char)i, arrayOfSymbols[i]);
		}
	}
	if (maxCode == -1) {
		printf("В файле нет символов, он пуст.");
	}
	return 0;
}