#include "tree.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>

int main() {
	setlocale(LC_ALL, ".1251");
	const char* fileName = "expression.txt";
	printf("Дерево разбора хранится в файле %s", fileName);
	FILE* file = fopen(fileName, "r");
	int numberOfSymbols = 0;
	while (!feof(file)) {
		int symbol = getc(file);
		++numberOfSymbols;
		if (symbol == -1) {
			break;
		}
	}
	fclose(file);
	file = fopen(fileName, "r");
	printf("%d", numberOfSymbols);
	++numberOfSymbols;
	char* arrayOfSymbols = calloc(numberOfSymbols, sizeof(char));
	numberOfSymbols = 0;
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
	free(arrayOfSymbols);
	printf("%d", (int)'2' - 48);
	return 0;
}

/*Что необходимо разработать:
Подумать над структурой узла в дереве (хранить int и char или только char?)
Придумать алгоритм выуживания операций и операндов из выражения
Придумать алгоритм расстановки операндов и операций
Сделать алгоритм обхода дерева
Придумать как вводить числа вида '22' через char*/