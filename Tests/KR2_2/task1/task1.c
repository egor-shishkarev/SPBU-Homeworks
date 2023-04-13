#include "list.h"
#include <stdio.h>
#include <stdbool.h>
#include <locale.h>

void functionABPrint(const int a, const int b, const char* f, const char* g) {
	FILE* file = fopen(f, "r");
	List* list = createList(a, b);
	while (!feof(f)) {
		int currentNumber = 0;
		const int isEnd = fscanf(file, "%d", &currentNumber);
		if (isEnd == -1) {
			break;
		}
		insert(list, currentNumber);
	}
	fclose(file);
	deleteElement(list, a);
	deleteElement(list, b);
	printListInFile(list, g);
	deleteList(&list);
}

bool test1(void) {
	functionABPrint(7, 10, "test1.txt", "answer1.txt");
	FILE* file = fopen("answer1.txt", "r");
	const int* rightAnswer[] = { 4, 1, 3, 4, 5, 6, 5, 3, 4, 5, 6, 7, 9, 7, 12, 94, 12, 321 };
	int counter = 0;
	while (!feof(file)) {
		int currentNumber = 0;
		const int isEnd = fscanf(file, "%d", &currentNumber);
		if (isEnd == -1) {
			break;
		}
		if (rightAnswer[counter] != currentNumber) {
			return false;
		}
		++counter;
	}
	return true;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	if (!test1()) {
		printf("Тесты не были пройдены!");
	}
	printf("Тесты пройдены успешно!");
	functionABPrint(7, 10, "f.txt", "g.txt");
	return 0;
}
