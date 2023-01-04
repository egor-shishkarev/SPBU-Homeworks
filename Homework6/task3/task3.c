#include "list.h"
#include <stdio.h>
#include <locale.h>
#include <stdbool.h>

int verificationIntScanf(void) {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Ошибка ввода. Введите целочисленное значение!\n");
	}
	return readValues;
}

int main(void) {
	setlocale(LC_ALL, ".1251");
	const char* path = "phonebook.txt";
	printf("Записи находятся в файле %s\n", path);
	printf("Для сортировки по имени введите 0, для сортировки по телефону введите 1 => ");
	int mode = verificationIntScanf();
	while (mode != 0 && mode != 1) {
		printf("Введено неверное значение, повторите ввод! => ");
		mode = verificationIntScanf();
	}
	List* list = createList();
	readFromFile(list, path);
	List* mergedList = mergeSort(list, mode);
	printf("Список до сортировки: \n");
	printList(list);
	printf("\nСписок после сортировки: \n");
	printList(mergedList);
	deleteList(&list, 1);
	deleteList(&mergedList, 1);
	return 0;
}