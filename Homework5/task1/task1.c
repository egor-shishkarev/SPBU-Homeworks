#include "..\..\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MAX_EXPRESSION_LENGTH 50

bool isDigit(const char symbol) {
	return symbol >= '0' && symbol <= '9';
}

bool isOperation(char symbol) {
	return strchr("-+*/", symbol) != NULL;
}

int evaluateExpression(const char postfixExpression[], const int lengthOfExpression, int *errorCode) {
	Stack* stack = createStack();
	if (stack == NULL) {
		*errorCode = -1;
		return -1;
	}
	for (int i = 0; i < lengthOfExpression; ++i) {
		const char currentElement = postfixExpression[i];
		if (isDigit(currentElement)) {
			*errorCode = push(stack, currentElement - '0');
			if (*errorCode) {
				deleteStack(stack);
				return -1;
			}
		}
		if (isOperation(currentElement)) {
			const int secondNumber = pop(stack, errorCode);
			if (*errorCode) {
				deleteStack(stack);
				return -1;
			}
			const int firstNumber = pop(stack, errorCode);
			if (*errorCode) {
				deleteStack(stack);
				return -1;
			}
			switch (currentElement) {
			case '-': {
				push(stack, firstNumber - secondNumber);
				break;
			}
			case '+': {
				push(stack, firstNumber + secondNumber);
				break;
			}
			case '*': {
				push(stack, firstNumber * secondNumber);
				break;
			}
			case '/':
				push(stack, firstNumber / secondNumber);
				break;
			}

		}
	}
	int result = pop(stack, errorCode);
	bool empty = isEmpty(stack);
	if (*errorCode) {
		deleteStack(stack);
		return -1;
	}
	deleteStack(stack);
	if (empty) {
		return result;
	}
	*errorCode = -2;
	return -1;
}

bool correctCase(void) {
	char postfixExpression[MAX_EXPRESSION_LENGTH] = { "96-12+*" };
	int errorCode = 0;
	const int result = evaluateExpression(postfixExpression, 7, &errorCode);
	return result == 9 && errorCode == 0;
}

bool incorrectCaseStack(void) {
	char postfixExpression[MAX_EXPRESSION_LENGTH] = { "-96" };
	int errorCode = 0;
	const int result = evaluateExpression(postfixExpression, 4, &errorCode);
	return result == -1 && errorCode == -1;
}

bool incorrectCaseExpression(void) {
	char postfixExpression[MAX_EXPRESSION_LENGTH] = { "5566++" };
	int errorCode = 0;
	const int result = evaluateExpression(postfixExpression, 7, &errorCode);
	return result == -1 && errorCode == -2;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!correctCase() && incorrectCaseStack() && incorrectCaseExpression()) {
		printf("Тесты были провалены.");
		return -1;
	}
	printf("Тесты пройдены успешно.\n");
	printf("Данная программа позволяет вычислить арифметическое выражение в постфиксной форме.\n\
Введите не более %d символов в одну строчку в виде '9 8 *' => ", MAX_EXPRESSION_LENGTH);
	char postfixExpression[MAX_EXPRESSION_LENGTH] = { "" };
	int currentElement = 0;
	char currentChar = getchar();
	while (currentChar != '\n') {
		if (currentChar == ' ') {
			currentChar = getchar();
			continue;
		}
		postfixExpression[currentElement] = currentChar;
		++currentElement;
		currentChar = getchar();
	}
	int errorCode = 0;
	const int result = evaluateExpression(postfixExpression, currentElement, &errorCode);
	if (errorCode == -1) {
		printf("Произошла ошибка со стэком (Создание или попытка взять элемент из пустого стэка)");
		return -1;
	}
	if (errorCode == -2) {
		printf("Выражение введено неверно! Проверьте перед вводом.");
		return -1;
	}
	printf("Результат вычисления выражения - %d", result);
	return 0;
}

