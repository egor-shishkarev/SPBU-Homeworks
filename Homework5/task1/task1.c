#include "C:\Users\Егор\source\repos\SPBU-Homeworks\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#define MaxExpressionLength 50

bool isDigit(int symbol) {
	int allDigits = 9876543210;
	for (int i = 0; i < 11; ++i) {
		if (symbol == allDigits % 10) {
			return true;
		}
		allDigits /= 10;
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
	push(stack, 100);
	printf("%d\n", top(stack));
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
				push(stack, firstNumber - secondNumber);
				printf("%d", firstNumber - secondNumber);
				break;
			}
			case '+': {
				push(stack, firstNumber + secondNumber);
				printf("%d", firstNumber - secondNumber);
				break;
			}
			case '*': {
				push(stack, firstNumber * secondNumber);
				printf("%d", top(stack));
				break;
			}
			case '/':
				push(stack, firstNumber / secondNumber);
				printf("%d", top(stack));
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
	printf("[%d]", atoi("4"));
	printf("%d", expressionEvaluation(postfixExpression, currentElement));
	return 0;
}