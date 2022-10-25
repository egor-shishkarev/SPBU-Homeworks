#include "C:\Users\Егор\source\repos\SPBU-Homeworks\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>
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

int expressionEvaluation(const char prefixExpression[], const int lengthOfExpression) {

}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Данная программа позволяет вычислить арифметическое выражение в постфиксной форме.\n\
Введите не более %d символов в одну строчку в виде '9 8 *' => ", MaxExpressionLength);
	char postfixExpression[MaxExpressionLength] = {""};
	if (postfixExpression == NULL) {
		printf("Память не была выделена.");
		return -1;
	}
	char currentChar = getchar();
	int currentElement = 0;
	Stack* stack = createStack();
	while (currentChar != '\n') {
		if (currentChar == ' ') {
			currentChar = getchar();
			continue;
		}
		push(stack, currentChar);
		++currentElement;
		currentChar = getchar();
	}
	for (int i = 0; i < MaxExpressionLength; ++i) {
		printf("'%c'", postfixExpression[i]);
	}
	printf("%s", isDigit(postfixExpression[0]) ? "Yes" : "No");
	return 0;
}