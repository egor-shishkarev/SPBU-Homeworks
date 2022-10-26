#include "C:\Users\Егор\source\repos\SPBU-Homeworks\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MaxExpressionLength 50

bool isDigit(char symbol) {
	char allDigits[10] = { "0123456789" };
	for (int i = 0; i < 11; ++i) {
		if (symbol == allDigits[i]) {
			return true;
		}
	}
	return false;
}

bool isOperation(char symbol) {
	char allOperations[4] = { "-+*/" };
	for (int i = 0; i < 5; ++i) {
		if (symbol == allOperations[i]) {
			return true;
		}
	}
	return false;
}

int expressionEvaluation(const char postfixExpression[], const int lengthOfExpression) {
	int* errorCode = 0;
	Stack* stack = createStack();
	for (int i = 0; i < lengthOfExpression; ++i) {
		const char currentElement = postfixExpression[i];
		if (isDigit(currentElement)) {
			push(stack, currentElement);
		}
		if (isOperation(currentElement)) {
			const char firstNumber = pop(stack, errorCode);
			const char secondNumber = pop(stack, errorCode);
			switch (currentElement) {
			case '-': {
				push(stack, (char)(atoi(firstNumber) - atoi(secondNumber)));
				break;
			}
			case '+': {
				push(stack, (char)(atoi(firstNumber) + atoi(secondNumber)));
				break;
			}
			case '*': {
				push(stack, (char)(atoi(firstNumber) * atoi(secondNumber)));
				break;
			}
			case '/':
				push(stack, (char)(atoi(firstNumber) / atoi(secondNumber)));
				break;
			}
		}
	}
	int result = pop(stack, errorCode);
	return result;
}

int main() {
	setlocale(LC_ALL, ".1251");
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
	printf("%d", expressionEvaluation(postfixExpression, currentElement));
	return 0;
}