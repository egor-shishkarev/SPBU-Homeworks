#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

int workingMode(int mode, Phonebook *data, const char *phoneDirectory) {
	switch (mode) {
	case 0:
		printf("Работа закончена.");
		return 0;
		break;
	case 1:
		addNote(data);
		break;
	case 2:
		printNotes(phoneDirectory);
		break;
	case 3:
		searchPhone(phoneDirectory, true, "", "");
		break;
	case 4:
		searchName(phoneDirectory, true, "", "");
		break;
	case 5:
		saveNotes(data, phoneDirectory, true);
		break;
	default:
		printf("Введено неверное значение, повторите ввод => ");
		int currentMode = verificationIntScanf();
		workingMode(currentMode, data, phoneDirectory);
	}
}

int main() {
	setlocale(LC_ALL, ".1251");
	if (!correctTests() && incorrectCase()) {
		printf("Тесты не пройдены!");
		return -1;
	}
	printf("Тесты успешно пройдены.\n");
	const char *phoneDirectory = "phonebook.txt";
	printf("Добро пожаловать в программу-телефонный справочник!\nВводите имена на английском языке!\nДлина номера и имени ограничена 20 символами.\nВыберите действие:\n");
	printf("0 - выйти\n1 - добавить запись(имя и телефон)\n2 - распечатать все имеющиеся записи\n\
3 - найти телефон по имени\n4 - найти имя по телефону\n5 - сохранить текущие данные в файл");
	printf("\nВведите цифру => ");
	int mode = verificationIntScanf();
	Phonebook data[100] = {"", ""};
	if (data == NULL) {
		printf("Память не была выделена.");
		return -1;
	}
	while (true) {
		workingMode(mode, data, phoneDirectory);
		if (mode == 0) {
			break;
		}
		printf("Введите цифру => ");
		mode = verificationIntScanf();
	}
	return 0;
}
