#include "tree.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX_SIZE_OF_STRING 50

int main() {
	setlocale(LC_ALL, ".1251");
	const char* fileName = "expression.txt";
	printf("Дерево разбора хранится в файле %s", fileName);
	FILE* file = fopen(fileName, "r");
	int numberOfSymbols = 0;
	char arrayOfSymbols[MAX_SIZE_OF_STRING] = {0};
	while (!feof(file)) {
		int symbol = getc(file);
		if (symbol == -1) {
			break;
		}
		arrayOfSymbols[numberOfSymbols] = (char)symbol;
		++numberOfSymbols;
	}
	fclose(file);
	printf("\n");
	for (int i = 0; i < numberOfSymbols; ++i) {
		printf("%c", arrayOfSymbols[i]);
	}
	Tree* tree = createParseTree(arrayOfSymbols, numberOfSymbols);
	return 0;
}

/*Что необходимо разработать:
Придумать алгоритм расстановки операндов и операций
Сделать алгоритм обхода дерева*/ 