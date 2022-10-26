#include "C:\Users\Егор\source\repos\SPBU-Homeworks\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MaxExpressionLength 50

bool isDigit(char symbol) {
	char allDigits[11] = { "0123456789" };
	for (int i = 0; i < 10; ++i) {
		if (symbol == allDigits[i]) {
			return true;
		}
	}
	return false;
}

bool isOperation(char symbol) {
	char allOperations[5] = { "-+*/" };
	for (int i = 0; i < 5; ++i) {
		if (symbol == allOperations[i]) {
			return true;
		}
	}
	return false;
}

int expressionEvaluation(const char postfixExpression[], const int lengthOfExpression, int *errorCode) {
	Stack* stack = createStack();
	if (stack == NULL) {
		printf("Стек не был создан.");
		return -1;
	}
	for (int i = 0; i < lengthOfExpression; ++i) {
		const char currentElement = postfixExpression[i];
		if (isDigit(currentElement)) {
			*errorCode = push(stack, (int)currentElement - 48); // единице соответсвует код 49, двойке 50 и т.д.
			if (*errorCode) {
				deleteStack(stack);
				return -1;
			}
		}
		if (isOperation(currentElement)) {
			const int secondNumber = pop(stack, errorCode);
			const int firstNumber = pop(stack, errorCode);
			switch (currentElement) {
			case '-': {
				push(stack, firstNumber - secondNumber);
				if (*errorCode) {
					deleteStack(stack);
					return -1;
				}
				break;
			}
			case '+': {
				push(stack, firstNumber + secondNumber);
				if (*errorCode) {
					deleteStack(stack);
					return -1;
				}
				break;
			}
			case '*': {
				push(stack, firstNumber * secondNumber);
				if (*errorCode) {
					deleteStack(stack);
					return -1;
				}
				break;
			}
			case '/':
				push(stack, firstNumber / secondNumber);
				if (*errorCode) {
					deleteStack(stack);
					return -1;
				}
				break;
			}
		}
	}
	int result = pop(stack, errorCode);
	if (*errorCode) {
		deleteStack(stack);
		return -1;
	}
	deleteStack(stack);
	return result;
}

bool correctCase(void) {
	char postfixExpression[MaxExpressionLength] = { "96-12+*" };
	int errorCode = 0;
	const int result = expressionEvaluation(postfixExpression, 7, &errorCode);
	return result == 9;
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!correctCase()) {
		printf("Тесты были провалены.");
		return -1;
	}
	printf("Тесты пройдены успешно.\n");
	printf("Данная программа позволяет вычислить арифметическое выражение в постфиксной форме.\n\
Введите не более %d символов в одну строчку в виде '9 8 *' => ", MaxExpressionLength);
	char postfixExpression[MaxExpressionLength] = { "" };
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
	const int result = expressionEvaluation(postfixExpression, currentElement, &errorCode);
	if (errorCode) {
		printf("При вычислении возникла ошибка.");
		return -1;
	}
	printf("Результат вычисления выражения - %d", result);
	return 0;
}