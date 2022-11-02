#include "list.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>

int main() {
	setlocale(LC_ALL, ".1251");
	List* list = createList();
	int errorCode = 0;
	int position = 1;
	/*insert(list, "Egor", "89116175014", position, &errorCode);
	printf("%s", getName(list, position));*/
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
	for (int i = 1; i <= position; ++i) {
		printf("%s - %s\n", getName(list, i), getPhone(list, i));
	}
	return 0;
} 