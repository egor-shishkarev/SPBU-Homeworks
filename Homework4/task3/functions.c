#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	char name[80];
	char phone[20];
} Phonebook;

int addNote() {
	FILE* file = fopen("phonebook.txt", "a");
	printf("Введите имя => ");
	Phonebook note;
	gets(&note.name);
	printf("%llu", strlen(note.name));
	printf("Введите номер => ");
	gets(&note.phone);
	printf("%llu", strlen(note.phone));
	fprintf(file, "%s", strcat(note.name, " "));
	fprintf(file, "%s", strcat(note.phone, "\n"));
	fclose(file);
}

int printNotes() {
	FILE* file = fopen("phonebook.txt", "r");
	if (file == NULL) {
		printf("Файл пуст.\n");
		return -1;
	}
	while (!feof(file)) {
		char* buffer = (char*)malloc(sizeof(char) * 100);
		if (buffer == NULL) {
			printf("Массив не был создан!");
			return -1;
		}
		if (fgets(buffer, 100, file) == 0) {
			free(buffer);
			break;
		}
		printf(buffer);
		free(buffer);
	}
	printf("\n");
	fclose(file);
}

int searchPhone() {
	FILE* file = fopen("phonebook.txt", "r");
	printf("Введите имя для поиска номера => ");
	while (!feof(file)) {
		char* buffer = (char*)malloc(sizeof(char) * 100);
		if (buffer == NULL) {
			printf("Массив не был создан!");
			return -1;
		}
		fgets(buffer, 100, file);
		for (int i = 0; i < 100; ++i) {
			printf("%c", buffer[i]);
		}
		free(buffer);
	}
	fclose(file);
}