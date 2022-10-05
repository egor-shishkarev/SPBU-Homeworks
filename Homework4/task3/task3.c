#include <stdio.h>
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
	FILE* file = fopen("phonebook.txt", "w");
	printf("Введите имя => ");
	phonebook note;
	scanf("%s", &note.name);
	printf("Введите номер без пробелов, тире и '+' => ");
	verificationIntScanf(note.phone);
	fprintf(note.name, "%s", file);
	fprintf("  ", "%s", file);
	fprintf(note.phone, "%s", file);
	fprintf("\n", "%s", file);
	fclose(file);
}

int printNotes() {
	FILE* file = fopen("phonebook.txt", "r");
	while (!feof(file)) {

	}
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
		break;
	case 3:
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
	setlocale(LC_ALL, ".1251");
	printf("Добро пожаловать в программу-телефонный справочник!\nВыберите действие:\n");
	printf("0 - выйти\n1 - добавить запись(имя и телефон)\n2 - распечатать все имеющиеся записи\n\
3 - найти телефон по имени\n4 - найти имя по телефону\n5 - сохранить текущие данные в файл");
	printf("Введите цифру => ");
	int mode = verificationIntScanf();
	while (workingMode(mode) != 0) {
		workingMode(mode);
		printf("\nВведите цифру => ");
		int mode = verificationIntScanf();
	}
	return 0;
}