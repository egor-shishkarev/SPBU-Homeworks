#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int verificationIntScanf() {
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

int addNote(Phonebook* data) {
	int i = 0;
	while (strlen(data[i].name) > 0) {
		++i;
	}
	printf("Введите имя и телефон через пробел => ");
	while (scanf("%s", data[i].name) != 1) {};
	while (!getchar()) {};
	while (scanf("%s", data[i].phone) != 1) {};
}

int printNotes() {
	FILE* file = fopen("phonebook.txt", "r");
	if (file == NULL) {
		file = fopen("phonebook.txt", "w");
		fclose(file);
		printf("Файл был создан.");
	}
	printf("\nСписок контактов:\n");
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

int searchPhone(Phonebook* data) {
	FILE* file = fopen("phonebook.txt", "r");
	printf("Введите имя для поиска номера => ");
	char name[20] = { "" };
	while (scanf("%s", &name) != 1) {};
	bool findName = false;
	while (!feof(file) || !(findName)) {
		Phonebook currentNote;
		while (fscanf(file, "%s", &currentNote.name) != 1) {};
		getc(file);
		while (fscanf(file, "%s", &currentNote.phone) != 1) {};
		getc(file);
		if (strcmp(name, currentNote.name) == 0) {
			printf("Номер телефона %s - %s \n", currentNote.name, currentNote.phone);
			findName = true;
			break;
		}
	}
	fclose(file);
	if (!findName) {
		printf("Данного имени нет в списке.");
	}
}

int searchName(Phonebook* data) {
	FILE* file = fopen("phonebook.txt", "r");
	printf("Введите номер телефона для поиска имени => ");
	char phone[20] = { "" };
	while (scanf("%s", &phone) != 1) {};
	bool findPhone = false;
	while (!feof(file) || !(findPhone)) {
		Phonebook currentNote;
		while (fscanf(file, "%s", &currentNote.name) != 1) {};
		getc(file);
		while (fscanf(file, "%s", &currentNote.phone) != 1) {};
		getc(file);
		if (strcmp(phone, currentNote.phone) == 0) {
			printf("Владелец номера %s - %s \n", currentNote.phone, currentNote.name);
			findPhone = true;
			break;
		}
	}
	fclose(file);
	if (!findPhone) {
		printf("Данного имени нет в списке.");
	}
}

int saveNotes(Phonebook* data) {
	FILE* file = fopen("phonebook.txt", "a");
	int i = 0;
	printf("Были сохранены следующие записи: \n");
	while (strlen(data[i].name) > 0) {
		printf("%s %s\n", data[i].name, data[i].phone);
		fprintf(file, "%s", strcat(data[i].name, " "));
		fprintf(file, "%s", strcat(data[i].phone, "\n"));
		++i;
	}
	fclose(file);
}
