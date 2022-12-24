#include "..\..\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAX_EXPRESSION_LENGTH 50

bool isDigit(char symbol) {
	return symbol >= '0' && symbol <= '9';
}

bool isOperation(char symbol) {
	return strchr("-+*/", symbol) != NULL;
}

int operationPriority(const char symbol) {	
	if (symbol == '+' || symbol == '-') {
		return 1;
	} else if (symbol == '*' || symbol == '/') {
		return 2;
	}
	return 0;
}

char* conversionFromInfixToPostfix(const char *infixExpression, const int lengthOfString, int *errorCode) {
	char *postfixExpression = calloc(MAX_EXPRESSION_LENGTH + 1, sizeof(char));
	if (postfixExpression == NULL) {
		*errorCode = -1;
		return NULL;
	}
	Stack* stackForOperations = createStack();
	if (stackForOperations == NULL) {
		*errorCode = -1;
		free(postfixExpression);
		return NULL;
	}
	int currentIndex = 0;
	for (int i = 0; i < lengthOfString; ++i) {
		const char symbol = infixExpression[i];
		if (isDigit(symbol)) {
			postfixExpression[currentIndex] = symbol;
			continue;
		} else if (isOperation(symbol)) {
			//
		} else {
			*errorCode = -1;
			free(postfixExpression);
			deleteStack(stackForOperations);
			return NULL;
		}
	}
	deleteStack(stackForOperations);
	return postfixExpression;
}

bool test(void) {
	int errorCode = 0;
	return !strcmp(conversionFromInfixToPostfix("(1+1)*2", 7, &errorCode), "11+2*");
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не пройдены.");
		return -1;
	}
	printf("Тесты успешно пройдены.\n");
	printf("Введите выражение длиной максимум в %d символов для перевода из инфиксной в постфиксную форму записи =>", MAX_EXPRESSION_LENGTH);
	char infixExpression[MAX_EXPRESSION_LENGTH] = { "" };
	int currentElement = 0;
	char currentChar = getchar();
	while (currentChar != '\n') {
		if (currentChar == ' ') {
			currentChar = getchar();
			continue;
		}
		infixExpression[currentElement] = currentChar;
		++currentElement;
		currentChar = getchar();
	}
	int errorCode = 0;
	char *postfixExpression = conversionFromInfixToPostfix(infixExpression, currentElement, &errorCode);
	if (errorCode == -1) {
		printf("Произошла ошибка!");
		free(postfixExpression);
		return -1;
	}
	printf("%s", postfixExpression);
	free(postfixExpression);
	return 0;
}
