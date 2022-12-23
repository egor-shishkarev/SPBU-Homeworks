#include "..\..\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>

int verificationIntScanf(void) {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Было введено не целое число!\n");
	}
	return readValues;
}

bool isOpenBracket(const char symbol) {
	return strchr("({[", symbol) != NULL;
}

bool isClosedBracket(const char symbol) {
	return strchr(")}]", symbol) != NULL;
}

bool conformityOfBrackets(const char openBracket, const char closedBracket) {
	return strchr("({[", openBracket) == strchr(")}]", closedBracket);
}

bool parenthesisBalance(const char *arrayOfSymbols, const int lengthOfString, int *errorCode) {
	Stack* stack = createStack();
	if (stack == NULL) {
		*errorCode = -1;
		return false;
	}
	for (int i = 0; i < lengthOfString; ++i) {
		const char currentSymbol = arrayOfSymbols[i];
		if (isOpenBracket(currentSymbol)) {
			*errorCode = push(stack, currentSymbol);
		} else if (isClosedBracket(currentSymbol) && !isEmpty(stack)) {
			const char openBracket = top(stack);
			if (conformityOfBrackets(openBracket, currentSymbol)) {
				pop(stack, errorCode);
				if (*errorCode) {
					deleteStack(stack);
					return false;
				}
				continue;
			}
		} else {
			continue;
		}
	}
	bool result = isEmpty(stack);
	deleteStack(stack);
	return result;
}

bool correctCase(void) {
	const char arrayOfSymbols[7] = { "({})[]" };
	int errorCode = 0;
	return parenthesisBalance(arrayOfSymbols, 6, &errorCode);
}

bool incorrectCase(void) {
	const char arrayOfSymbols[4] = { "{{}" };
	int errorCode = 0;
	return !parenthesisBalance(arrayOfSymbols, 3, &errorCode);
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!(correctCase() && incorrectCase())) {
		printf("Тесты не были пройдены.");
		return -1;
	}
	printf("Тесты пройдены успешно.\n");
	printf("Данная программа позволяет проверить баланс скобок в строке (разрешены три вида скобок (), {}, [])\nВведите длину строки => ");
	const int lengthOfString = verificationIntScanf();
	printf("Введите строчку со скобками (без пробелов) => ");
	const char* arrayOfSymbols = calloc(lengthOfString, sizeof(char));
	if (arrayOfSymbols == NULL) {
		printf("Память не была выделена, массив не создан.");
		return -1;
	}
	while (scanf("%s", arrayOfSymbols) != 1) {};
	int errorCode = 0;
	const bool result = parenthesisBalance(arrayOfSymbols, lengthOfString, &errorCode);
	if (errorCode) {
		printf("Возникла ошибка при вычислении баланса скобок.");
		return -1;
	}
	printf("Выражение %s", result ? "верное" : "неверное");
	free(arrayOfSymbols);
	return 0;
}
