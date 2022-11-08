#include "tree.h"
#include <stdio.h>
#include <locale.h>

#define MAX_STRING_SIZE 50

int verificationIntScanf(void) {
	int readValues = 0;
	while (true) {
		int correctlyReadValues = scanf("%d", &readValues);
		while (getchar() != '\n') {
		}
		if (correctlyReadValues == 1) {
			break;
		}
		printf("Было введено нецелочисленное значение! \n");
	}
	return readValues;
}

int main() {
	setlocale(LC_ALL, ".1251");
	printf("Данная программа - словарь, который интерактивно работает с ключами и значениями.\n");
	printf("Введите следующие числа, чтобы выполнить предложенные команды:\n0 - выйти\n1 - добавить значение по ключу в словарь\n2 - \
получить значение по ключу\n3 - проверить наличие ключа в словаре\n4 - удалить ключ и его значение\n");
	int errorCode = 0;
	Tree* tree = createTree(&errorCode);
	while (true) {
		printf("Введите команду => ");
		int mode = verificationIntScanf();
		switch (mode) {
		case 0: {
			deleteTree(&tree);
			printf("Работа окончена!");
			return 0;
		}
		case 1: {
			printf("Введите ключ => ");
			const int key = verificationIntScanf();
			printf("Введите значение длинной не более %d символов => ", MAX_STRING_SIZE);
			char value[MAX_STRING_SIZE] = { 0 };
			gets(value);
			addElement(tree, key, value, &errorCode);
			if (errorCode) {
				printf("Произошла ошибка в работе!");
				return -1;
			}
			break;
		}
		case 2: {
			printf("Введите ключ => ");
			const int key = verificationIntScanf();
			printf("Значение по данному ключу - %s\n", searchValueFromKey(tree, key));
			break;
		}
		case 3: {
			printf("Введите ключ => ");
			const int key = verificationIntScanf();
			printf(isKeyInTree(tree, key) ? "Данный ключ есть в словаре.\n" : "Данного ключа нет в словаре!\n");
			break;
		}
		case 4: {
			printf("Введите ключ, значение для которого хотите удалить => ");
			const int key = verificationIntScanf();
			deleteElement(tree, key, &errorCode);
			if (errorCode) {
				printf("Произошла ошибка в работе!");
				return -1;
			}
			break; 
		}
		default: {
			printf("Данной команды нет в списке, повторите ввод!");
			continue;
		}
		}
	}
	return 0;
}