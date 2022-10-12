﻿#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>
/*Написать программу — телефонный справочник. Она должна уметь хранить имена и номера телефонов, в интерактивном режиме осуществлять следующие операции:

0 - выйти
1 - добавить запись (имя и телефон)
2 - распечатать все имеющиеся записи
3 - найти телефон по имени
4 - найти имя по телефону
5 - сохранить текущие данные в файл
При запуске программа должна читать данные из файла (того самого, в который сохраняет данные), 
	если файла нет — начинать с пустой базы номеров. Размер базы ограничен сотней записей.*/

int workingMode(int mode) {
	switch (mode) {
	case 0:
		printf("Работа закончена.");
		return 0;
		break;
	case 1:
		addNote();
		break;
	case 2:
		printNotes();
		break;
	case 3:
		searchPhone();
		break;
	case 4:
		break;
	case 5:
		break;
	default:
		printf("Введено неверное значение, повторите ввод.");
		int currentMode = verificationIntScanf();
		workingMode(currentMode);
	}
}

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

int main() {
	setlocale(LC_ALL, "Russian");
	printf("Добро пожаловать в программу-телефонный справочник!\nВыберите действие:\n");
	printf("0 - выйти\n1 - добавить запись(имя и телефон)\n2 - распечатать все имеющиеся записи\n\
3 - найти телефон по имени\n4 - найти имя по телефону\n5 - сохранить текущие данные в файл");
	printf("\nВведите цифру => ");
	int mode = verificationIntScanf();
	while (true) {
		workingMode(mode);
		if (mode == 0) {
			break;
		}
		printf("Введите цифру => ");
		mode = verificationIntScanf();
	}
	return 0;
}
/*PhoneBookEntry entry;
const char* name = "Ivan Ivanov";
entry.name = malloc(sizeof(char) * (strlen(name) + 1));
if (entry.name == NULL) {
return -1;
}
strcpy(entry.name, name);
strcpy(entry.phone, "+7 (911) 123-45-67");
printf("%s - %s", entry.name, entry.phone);
free(entry.name);
return 0;
*/

/*int main() {
PhoneBookEntry entry;
entry.name = malloc(sizeof(char) * 30);
if (entry.name == NULL) {
return -1;
}
scanf("%s", entry.name);
scanf("%[^\n]", entry.phone);
printf("%s - %s", entry.name, entry.phone);
free(entry.name);
return 0;*/