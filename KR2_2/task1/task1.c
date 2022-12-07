#include "list.h"
#include <stdio.h>
#include <stdbool.h>

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
}

bool test1(void) {
	functionABPrint(7, 10, "test1.txt", "answer1.txt");
	FILE* file = fopen("answer1.txt", "r");
	const int* rightAnswer[] = { 4, 1, 3, 4, 5, 6, 5, 3, 4, 5, 6, 7, 9, 7, 12, 94, 12, 321 };
	while (!feof(file)) {

	}
}


int main(void) {
	test1();
	functionABPrint(7, 10, "f.txt", "g.txt");
	return 0;
}

// Даны числа a и b. За один просмотр файла f, элементами которого являются целые числа, и без 
// использования дополнительных файлов переписать его элементы в файл g так, чтобы первоначально были 
// записаны все числа, меньше заданного a, затем все числа из отрезка [a,b], затем все остальные. 
// Взаимный порядок в каждой из групп должен быть сохранен, предположений о количестве элементов делать нельзя.