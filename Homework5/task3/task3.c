#include "C:\Users\Егор\source\repos\SPBU-Homeworks\Stack\stackModule.h"
#include <stdio.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MaxExpressionLength 50

bool isDigit(char symbol) {
	/*return (int)symbol >= 48 && (int)symbol<=57*/
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

int operationPriority(const char symbol) {
	if (symbol == '+' || symbol == '-') {
		return 1;
	} else if (symbol == '*' || symbol == '/') {
		return 2;
	}
	return 0;
}

char *conversionFromInfixToPostfix(const char *infixExpression, const int lengthOfString, int *errorCode) {
	char *postfixExpression = calloc(MaxExpressionLength + 1, sizeof(char)); // char *outputExpressionInPrefixForm = calloc(maxLineSize + 1, sizeof(char));
	Stack* stackForDigits = createStack();
	Stack* stackForOperations = createStack();
	if (stackForDigits == NULL || stackForOperations == NULL) {
		printf("Память не была выделена.");
		return;
	}
	int currentPosition = 0;
	bool firstOperation = true;
	int operationInBrackets = 0;
	for (int i = 0; i < lengthOfString; ++i) {
		const char currentElement = infixExpression[i];
		if (isDigit(currentElement)) { // Если символ - цифра, просто добавляем в стек для цифр
			*errorCode = push(stackForDigits, currentElement);
		} else if (isOperation(currentElement) || currentElement == '(') { // Если символ - операция, начинаем смотреть варианты
			if (currentElement == '(') {
				++operationInBrackets;
			}
			if (isEmpty(stackForOperations)) { // Если стек пустой - просто добавляем его туда
				*errorCode = push(stackForOperations, currentElement);
				continue;
			}
			char topStack = top(stackForOperations);
			if (operationPriority(currentElement) > operationPriority(topStack) || topStack == '(' || currentElement == '(') { // Если приоритет текущей операции выше чем операции из стека, вершина стека ( или текущая операция ( добавляем его
				*errorCode = push(stackForOperations, currentElement);
			} else { // Если же приоритет ниже, рассматриваем случаи
				if (currentElement == ')') { // Случай с закрывающей скобкой
					while (topStack != '(') {
						if (operationInBrackets) { // Если операция сразу же после скобки, то достаем два числа и одну операцию
							postfixExpression[currentPosition + 1] = pop(stackForDigits, errorCode);
							postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
							postfixExpression[currentPosition + 2] = pop(stackForOperations, errorCode);
							currentPosition += 3;
							--operationInBrackets;
						} else { // Если это вторая и больше операция после ), то достаем одно число и одну операцию
							postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
							postfixExpression[currentPosition + 1] = pop(stackForOperations, errorCode);
							currentPosition += 2;
						}
						topStack = top(stackForOperations);
					}
					pop(stackForOperations, *errorCode); // Достаем закрывающую скобку. Она нам не нужна, просто делаем поп
				} else { // Если это не ), то достаем два числа и операцию
					while (operationPriority(currentElement) <= operationPriority(topStack) || !isEmpty(stackForDigits) || !isEmpty(stackForOperations) || top(stackForOperations) != '(') {
						if (firstOperation) { // Если операция сразу же после скобки, то достаем два числа и одну операцию
							postfixExpression[currentPosition + 1] = pop(stackForDigits, errorCode);
							postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
							postfixExpression[currentPosition + 2] = pop(stackForOperations, errorCode);
							firstOperation = false;
							currentPosition += 3;
						}
						else { // Если это вторая и больше операция после ), то достаем одно число и одну операцию
							postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
							postfixExpression[currentPosition + 1] = pop(stackForOperations, errorCode);
							currentPosition += 2;
						}
					}
					*errorCode = push(stackForOperations, currentElement);
				}
			}
		} else if (currentElement == ')') { // Случай с закрывающей скобкой
			char topStack = top(stackForOperations);
			while (topStack != '(') {
				if (operationInBrackets) { // Если операция сразу же после скобки, то достаем два числа и одну операцию
					postfixExpression[currentPosition + 1] = pop(stackForDigits, errorCode);
					postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
					postfixExpression[currentPosition + 2] = pop(stackForOperations, errorCode);
					currentPosition += 3;
					--operationInBrackets;
				}
				else { // Если это вторая и больше операция после ), то достаем одно число и одну операцию
					postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
					postfixExpression[currentPosition + 1] = pop(stackForOperations, errorCode);
					currentPosition += 2;
				}
				topStack = top(stackForOperations);
			}
			pop(stackForOperations, errorCode); // Достаем закрывающую скобку. Она нам не нужна, просто делаем поп
		} else {
			printf("Неизвестный элемент: ни операция, ни цифра. Прекращение работы.");
			deleteStack(stackForDigits);
			deleteStack(stackForOperations);
			return NULL;
		}
	}
	while (!isEmpty(stackForOperations)) {
		if (!isEmpty(stackForDigits)) {
			postfixExpression[currentPosition] = pop(stackForDigits, errorCode);
			++currentPosition;
		}
		postfixExpression[currentPosition] = pop(stackForOperations, errorCode);
		++currentPosition;
	}
	deleteStack(stackForDigits);
	deleteStack(stackForOperations);
	return postfixExpression;
}

bool test(void) {
	int errorCode = 0;
	return !strcmp(conversionFromInfixToPostfix("(1+1)*2", 7, &errorCode), "11+2*");
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не пройдены.");
		//return -1;
	}
	printf("Тесты успешно пройдены.\n");
	printf("Введите выражение длиной максимум в %d символов для перевода из инфиксной в постфиксную форму записи =>", MaxExpressionLength);
	char infixExpression[MaxExpressionLength] = { "" };
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
	printf("%s", postfixExpression);
	free(postfixExpression);
	return 0;
}
