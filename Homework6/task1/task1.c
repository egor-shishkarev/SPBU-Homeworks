#include "list.h"
#include <stdio.h>
#include <locale.h>
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
		printf("Было введено не целочисленное значение! \n");
	}
	return readValues;
}

void workingMode(const int mode, List *list) {
	switch (mode) {
	case 0: {
		printf("Работа окончена!");
		deleteList(&list);
		break;
	}
	case 1: {
		printf("Введите целочисленное значение для добавления в список => ");
		const int value = verificationIntScanf();
		insert(list, value);
		break;
	}
	case 2: {
		printf("Введите значение элемента, который хотите удалить => ");
		const int valueToDelete = verificationIntScanf();
		const bool isElementInList = deleteElement(list, valueToDelete);
		if (!isElementInList) {
			printf("Элемент успешно удалён!\n");
			break;
		} else {
			printf("Данного элемента нет в списке! Проверьте наличие элементов командой номер 3.\n");
			break;
		}
		break;
	}
	case 3: {
		printList(list);
		break;
	}
	default: {
		printf("Введенной команды нет в списке, повторите ввод!\n");
		break;
	}
	}
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Добро пожаловать в программу 'сортированный список'!\n");
	printf("Введите следующие значения для продолжения или выхода из программы:\n0 – выйти\n1 – добавить значение в \
сортированный список\n2 – удалить значение из списка\n3 – распечатать список\n");
	int mode = -1;
	List* list = createList();
	while (mode != 0) {
		printf("Введите номер команды => ");
		mode = verificationIntScanf();
		workingMode(mode, list);
	}
	return 0;
}
