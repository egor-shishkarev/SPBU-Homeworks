#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

#define MAX_SIZE_OF_STRING 50

bool isPalindrome(char* arrayOfSymbols, const int length) {
	for (int i = 0; i < length / 2; ++i) {
		if (arrayOfSymbols[i] != arrayOfSymbols[length - i - 1]) {
			return false;
		}
	}
	return true;
}

bool test(void) {
	char arrayOfSymbols[16] = { "яидусмечемсудия" };
	return isPalindrome(arrayOfSymbols, 15);
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test()) {
		printf("Тесты не были пройдены!");
		return -1;
	}
	printf("Тесты были пройдены.\n");
	printf("Введите строку для её проверки на палиндром, не более чем %d символов: \n", MAX_SIZE_OF_STRING);
	int currentNumberOfChar = getchar();
	char arrayOfSymbols[MAX_SIZE_OF_STRING] = { 0 };
	int currentNumber = 0;
	while (currentNumberOfChar != 10) { 
		if (currentNumberOfChar == 32) { 
			currentNumberOfChar = getchar();
			continue;
		}
		arrayOfSymbols[currentNumber] = (char)currentNumberOfChar;
		++currentNumber;
		currentNumberOfChar = getchar();
	} 
	printf(isPalindrome(arrayOfSymbols, currentNumber) ? "Строка является палиндромом!" : "Строка не является палиндромом!");
	return 0;
}
