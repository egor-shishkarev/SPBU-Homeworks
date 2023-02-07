#include "tree.h"
#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

#define MAX_SIZE_OF_STRING 50

bool test(void) {
	Tree* tree = createParseTree();
	readFileToTree("test.txt", tree);
	const int result = treeResult(tree);
	deleteTree(&tree);
	return result == 3;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не были пройдены!");
		return -1;
	}
	printf("Тесты пройдены успешно.\n");
	const char* fileName = "expression.txt";
	printf("Дерево разбора хранится в файле '%s'", fileName);
	FILE* file = fopen(fileName, "r");
	int numberOfSymbols = 0;
	char arrayOfSymbols[MAX_SIZE_OF_STRING] = { 0 };
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
	for (int i = numberOfSymbols - 1; i >= 0; --i) {
		if (arrayOfSymbols[i] == ' ') {
			arrayOfSymbols[i] = '\0';
		}
		else {
			arrayOfSymbols[i + 1] = '\0';
			break;
		}
	}
	for (int i = 0; i < numberOfSymbols; ++i) {
		printf("%c", arrayOfSymbols[i]);
	}
	printf("\nОбход по дереву: \n");
	Tree* tree = createParseTree();
	readFileToTree(fileName, tree);
	treePrint(tree);
	printf("\nРезультат обхода дерева - %d", treeResult(tree));
	deleteTree(&tree);
	return 0;
}
