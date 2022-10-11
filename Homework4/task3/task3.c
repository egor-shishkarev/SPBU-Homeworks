#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>

typedef struct {
	char name[20];
	char phone[20];
} phonebook;

/*Написать программу — телефонный справочник. Она должна уметь хранить имена и номера телефонов, в интерактивном режиме осуществлять следующие операции:

0 - выйти
1 - добавить запись (имя и телефон)
2 - распечатать все имеющиеся записи
3 - найти телефон по имени
4 - найти имя по телефону
5 - сохранить текущие данные в файл
При запуске программа должна читать данные из файла (того самого, в который сохраняет данные), 
	если файла нет — начинать с пустой базы номеров. Размер базы ограничен сотней записей.*/

int addNote() {
	FILE* file = fopen("phonebook.txt", "a");
	printf("Введите имя => ");
	phonebook note;
	gets(&note.name);
	printf("Введите номер => ");
	gets(&note.phone);
	fprintf(file, "%s", "\n");
	fprintf(file, "%s", note.name);
	fprintf(file, "%s", " ");
	fprintf(file, "%s", note.phone);
	fprintf(file, "%s", "\0");
	fclose(file);
}

int printNotes() {
	FILE* file = fopen("phonebook.txt", "r"); 
	while (!feof(file)) { 
		char *buffer = (char*)malloc(sizeof(char) * 100); 
		if (buffer == NULL) {
			printf("Массив не был создан!");
			return -1;
		}
		fgets(buffer, 100, file);
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