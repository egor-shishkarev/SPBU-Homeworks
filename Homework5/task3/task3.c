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

void addToString(char* string, const char symbol, int* currentIndex) {
	string[*currentIndex] = symbol;
	++(*currentIndex);
	string[*currentIndex] = ' ';
	++(*currentIndex);
}


char* conversionFromInfixToPostfix(const char *infixExpression, const int lengthOfString, int *errorCode) {
	if (infixExpression == NULL) {
		*errorCode = -1;
		return NULL;
	}
	char *postfixExpression = calloc(2 * MAX_EXPRESSION_LENGTH + 1, sizeof(char));
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
		if (symbol == ' ') {
			continue;
		}
		if (isDigit(symbol)) {
			addToString(postfixExpression, symbol, &currentIndex);
			continue;
		} else if (symbol == '(') {
			push(stackForOperations, '(');
			continue;
		} else if (symbol == ')') {
			while (!isEmpty(stackForOperations) && top(stackForOperations) != '(') {
				char currentOperation = pop(stackForOperations, errorCode);
				if (*errorCode == -1) {
					free(postfixExpression);
					deleteStack(stackForOperations);
					return NULL;
				}
				addToString(postfixExpression, currentOperation, &currentIndex);
			}
			pop(stackForOperations, errorCode);
			if (*errorCode == -1) {
				*errorCode = 1;
				free(postfixExpression);
				deleteStack(stackForOperations);
				return NULL;
			}
		} else if (isOperation(symbol)) {
			const int priority = operationPriority(symbol);
			while (!isEmpty(stackForOperations) && operationPriority(top(stackForOperations)) >= priority) {
				addToString(postfixExpression, pop(stackForOperations, errorCode), &currentIndex);
				if (*errorCode == -1) {
					free(postfixExpression);
					deleteStack(stackForOperations);
					return NULL;
				}
			}
			push(stackForOperations, symbol);
		} else {
			*errorCode = 1;
			free(postfixExpression);
			deleteStack(stackForOperations);
			return NULL;
		}
	}
	while (!isEmpty(stackForOperations)) {
		const char currentSymbol = pop(stackForOperations, errorCode);
		if (*errorCode == -1) {
			free(postfixExpression);
			deleteStack(stackForOperations);
			return NULL;
		}
		if (currentSymbol == ')' || currentSymbol == '(') {
			free(postfixExpression);
			deleteStack(stackForOperations);
			*errorCode = 1;
			return NULL;
		}
		addToString(postfixExpression, currentSymbol, &currentIndex);
	}
	deleteStack(stackForOperations);
	return postfixExpression;
}

bool test(void) {
	char firstExpression[] = "(1+1)*2";
	char secondExpression[] = "1+2/3-8*(9*7+6*4)-4";
	char firstIncorrectExpression[] = "(1+2*3";
	char secondIncorrectexpression[] = "(1+A)/2";

	char firstRightAnswer[] = "1 1 + 2 * ";
	char secondRightAnswer[] = "1 2 3 / + 8 9 7 * 6 4 * + * - 4 - ";

	int errorCode = 0;
	char* firstAnswer = conversionFromInfixToPostfix(firstExpression, (int)strlen(firstExpression), &errorCode);
	if (errorCode) {
		return false;
	}
	char* secondAnswer = conversionFromInfixToPostfix(secondExpression, (int)strlen(secondExpression), &errorCode);
	if (errorCode) {
		return false;
	}

	int firstErrorCode = 0;
	char* thirdAnswer = conversionFromInfixToPostfix(firstIncorrectExpression, (int)strlen(firstIncorrectExpression), &firstErrorCode);

	int secondErrorCode = 0;
	char* fourthAnswer = conversionFromInfixToPostfix(secondIncorrectexpression, (int)strlen(secondIncorrectexpression), &secondErrorCode);
	
	int errorCodeForNull = 0;

	bool result = !strcmp(firstAnswer, firstRightAnswer) && !strcmp(secondAnswer, secondRightAnswer) && thirdAnswer == NULL && firstErrorCode == 1 \
		&& fourthAnswer == NULL && secondErrorCode == 1 && conversionFromInfixToPostfix(NULL, 0, &errorCodeForNull) == NULL && errorCodeForNull == -1;
	
	free(firstAnswer);
	free(secondAnswer);
	free(thirdAnswer);
	free(fourthAnswer);

	return result;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не были пройдены!");
		return -1;
	}
	printf("Тесты успешно пройдены.\n");
	printf("Допустимые символы: скобки - ( и ), цифры - 0 - 9, операции - +, -, *, /. Числа не поддерживаются, только цифры\n");
	printf("Введите выражение длиной максимум в %d символов для перевода из инфиксной в постфиксную форму записи => ", MAX_EXPRESSION_LENGTH);
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
	if (errorCode == 1) {
		printf("\nВыражение введено неверно! Проверьте допустимые символы и соответствие скобок.\n");
		return -1;
	}
	if (errorCode == -1) {
		printf("\nПроизошла ошибка с выделением памяти!\n");
		free(postfixExpression);
		return -1;
	}
	printf("\n%s\n", postfixExpression);
	free(postfixExpression);
	return 0;
}
