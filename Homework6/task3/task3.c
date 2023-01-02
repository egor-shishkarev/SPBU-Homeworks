#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <string.h>

int main(void) {
	setlocale(LC_ALL, ".1251");
	List* list = createList();
	int errorCode = 0;
	int position = 1;
	FILE* file = fopen("phonebook.txt", "r");
	while (!feof(file)) {
		char* name = malloc(20 * sizeof(char));
		if (fscanf(file, "%s", name) == 0) {
			break;
		}
		getc(file);
		char* phone = malloc(20 * sizeof(char));
		if (fscanf(file, "%s", phone) == 0) {
			break;
		}
		insert(list, name, phone, position, &errorCode);
		++position;
	}
	for (int i = 1; i < position; ++i) {
		printf("%s - %s\n", getName(list, i), getPhone(list, i));
	}
	List* secondList = list;
	for (int i = 0; i < 2; ++i) {
		secondList = getNextPosition(secondList);
	}
	List* mergedList = mergeSort(list, secondList, 2, 2);
	for (int i = 1; i <= 4; ++i) {
		printf("%s - %s\n", getName(mergedList, i), getPhone(mergedList, i));
	}
	return 0;
} 