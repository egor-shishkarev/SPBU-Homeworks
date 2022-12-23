#include "phonebook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

int verificationIntScanf(void) {
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

int readFile(Phonebook* data, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        file = fopen(fileName, "w");
        fclose(file);
        printf("���� ��� ������.\n");
        printf("��� ��� ���� ������, � ��� ��� ������� ���.\n");
        return;
    }
    int currentElement = 0;
    while (!feof(file) || currentElement <= 100) {
        Phonebook currentNote;
        if (fscanf(file, "%s", &currentNote.name) == -1) {
            break;
        }
        getc(file);
        if (fscanf(file, "%s", &currentNote.phone) == -1) {
            break;
        }
        getc(file);
        data[currentElement] = currentNote;
        ++currentElement;
    }
    fclose(file);
    return currentElement;
}

int addNote(Phonebook* data, int* size) {
    printf("������� ��� � ������� ����� ������ => ");
    while (scanf("%s", data[*size].name) != 1) {};
    while (!getchar()) {};
    while (scanf("%s", data[*size].phone) != 1) {};
    ++(*size);
}

char* searchPhone(Phonebook* data, const char* name, const int* size) {
    int currentIndex = 0;
    while (currentIndex < *size) {
        Phonebook currentNote = data[currentIndex];
        if (strcmp(name, &currentNote.name) == 0) {
            return currentNote.phone;
        }
        ++currentIndex;
    }
    return "��� ������ �����!\n";
}

char* searchName(Phonebook* data, const char* phone, int* size) {
    int currentIndex = 0;
    while (currentIndex < *size) {
        Phonebook currentNote = data[currentIndex];
        if (strcmp(phone, &currentNote.phone) == 0) {
            return currentNote.name;
        }
        ++currentIndex;
    }
    return "��� ������ ��������!\n";
}

int saveNotes(Phonebook* data, const char* fileName, const int* size) {
    FILE* file = fopen(fileName, "w");
    for (int i = 0; i < *size; ++i) {
        fprintf(file, "%s ", data[i].name);
        fprintf(file, "%s\n", data[i].phone);
    }
    fclose(file);
}
