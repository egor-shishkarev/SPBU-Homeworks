#include "functions.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

bool correctTests() {
	char *data[10] = {"Pasha", "88005553535", "Andrey", "89118745932", "Vladimir", "8(911)-627-53-27", "Anton", "+79114518723", "Ibragim", "216983-59-21" };
	Phonebook directory[5] = {"", ""};
	for (int i = 0; i < 5; ++i) {
		strcpy(directory[i].name, data[2 * i]);
		strcpy(directory[i].phone, data[2 * i + 1]);
	}
	const char* testFile = "tests.txt";
	FILE* file = fopen(testFile, "w");
	saveNotes(directory, testFile, false);
	bool allIsTrue = true;
	for (int i = 0; i < 5; ++i) {
		if (!(searchPhone(testFile, false, data[2 * i], data[2 * i + 1]) == 0 && searchName(testFile, false, data[2 * i], data[2 * i + 1]) == 0)) {
			allIsTrue = false;
			break;
		}
	}
	return allIsTrue;
}

bool incorrectCase() {
	char* data[10] = { "Pasha", "88005553535", "Andrey", "89118745932", "Vladimir", "8(911)-627-53-27", "Anton", "+79114518723", "Ibragim", "216983-59-21" };
	Phonebook directory[5] = { "", "" };
	for (int i = 0; i < 5; ++i) {
		strcpy(directory[i].name, data[2 * i]);
		strcpy(directory[i].phone, data[2 * i + 1]);
	}
	const char* testFile = "tests.txt";
	FILE* file = fopen(testFile, "w");
	saveNotes(directory, testFile, false);
	return searchName(testFile, false, "Misha", "89117845123") == -1 && searchPhone(testFile, false, "Misha", "89117845123") == -1;
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
		printf("������ �����. ������� ������������� ��������!\n");
	}
	return readValues;
}

int addNote(Phonebook* data) {
	int i = 0;
	while (strlen(data[i].name) > 0) {
		++i;
	}
	printf("������� ��� � ������� ����� ������ => ");
	while (scanf("%s", data[i].name) != 1) {};
	while (!getchar()) {};
	while (scanf("%s", data[i].phone) != 1) {};
	printf("������, ��������� ���������� � ����: \n");
	i = 0;
	while (strlen(data[i].name) > 0) {
		printf("%s %s\n", data[i].name, data[i].phone);
		++i;
	}	
}

int printNotes(const char *fileName) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		file = fopen(fileName, "w");
		fclose(file);
		printf("���� ��� ������.");
	}
	printf("\n������ ���������:\n");
	while (!feof(file)) {
		char* buffer = (char*)malloc(sizeof(char) * 100);
		if (buffer == NULL) {
			printf("������ �� ��� ������!");
			return -1;
		}
		if (fgets(buffer, 100, file) == 0) {
			free(buffer);
			break;
		}
		printf(buffer);
		free(buffer);
	}
	fclose(file);
	printf("\n");
}

int searchPhone(const char* fileName, bool consoleOutput, const char* testName, const char* testPhone) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		file = fopen(fileName, "w");
		fclose(file);
		printf("���� ��� ������.\n");
		printf("��� ��� ���� ������, � ��� ��� ������� ���.\n");
		return;
	}
	char name[20] = { "" };
	if (consoleOutput) {
		printf("������� ��� ��� ������ ������ => ");
		while (scanf("%s", &name) != 1) {};
	} else {
		strcpy(name, testName);
	}
	bool findName = false;
	while (!feof(file) || !(findName)) {
		Phonebook currentNote;
		if (fscanf(file, "%s", &currentNote.name) == -1) {
			break;
		}
		getc(file);
		if (fscanf(file, "%s", &currentNote.phone) == -1) {
			break;
		}
		getc(file);
		if (strcmp(name, currentNote.name) == 0) {
			if (consoleOutput) {
				printf("����� �������� %s - %s\n", currentNote.name, currentNote.phone);
			} else {
				return strcmp(testPhone, currentNote.phone);
			}
			findName = true;
			break;
		}
	}
	fclose(file);
	if (!findName) {
		if (consoleOutput) {
			printf("������� ����� ��� � ������.\n");
		} else {
			return -1;
		}
	}
}

int searchName(const char* fileName, bool consoleOutput, const char* testName, const char* testPhone) {
	FILE* file = fopen(fileName, "r");
	if (file == NULL) {
		file = fopen(fileName, "w");
		fclose(file);
		printf("���� ��� ������.\n");
		printf("��� ��� ���� ������, � ��� ��� ������� ���.\n");
		return;
	}
	char phone[20] = { "" };
	if (consoleOutput) {
		printf("������� ����� �������� ��� ������ ����� => ");
		while (scanf("%s", &phone) != 1) {};
	} else {
		strcpy(phone, testPhone);
	}
	bool findPhone = false;
	while (!feof(file) || !(findPhone)) {
		Phonebook currentNote;
		if (fscanf(file, "%s", &currentNote.name) == -1) {
			break;
		}
		getc(file);
		if (fscanf(file, "%s", &currentNote.phone) == -1) {
			break;
		}
		getc(file);
		if (strcmp(phone, currentNote.phone) == 0) {
			if (consoleOutput) {
				printf("�������� ������ %s - %s \n", currentNote.phone, currentNote.name);
			} else {
				return strcmp(testName, currentNote.name);
			}
			findPhone = true;
			break;
		}
	}
	fclose(file);
	if (!findPhone) {
		if (consoleOutput) {
			printf("������� ������ ��� � ������.\n");
		} else {
			return -1;
		}
	}
}

int saveNotes(Phonebook* data, const char* fileName, bool consoleOutput) {
	FILE* file = fopen(fileName, "a");
	int i = 0;
	if (consoleOutput) {
		printf("���� ��������� ��������� ������: \n");
	}
	if (!consoleOutput) {
		for (int i = 0; i < 5; ++i) {
			fprintf(file, "%s", strcat(data[i].name, " "));
			fprintf(file, "%s", strcat(data[i].phone, "\n"));
		}
		fclose(file);
		return;
	}
	while (strlen(data[i].name) > 0) {
		if (consoleOutput) {
			printf("%s %s\n", data[i].name, data[i].phone);
		}
		fprintf(file, "%s", strcat(data[i].name, " "));
		fprintf(file, "%s", strcat(data[i].phone, "\n"));
		strcpy(data[i].name, "");
		strcpy(data[i].phone, "");
		++i;
	}
	fclose(file);
}
