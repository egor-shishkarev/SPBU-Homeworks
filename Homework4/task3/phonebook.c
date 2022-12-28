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
        printf("Ошибка ввода. Введите целочисленное значение!\n");
    }
    return readValues;
}

int readFile(Phonebook* data, const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        file = fopen(fileName, "w");
        fclose(file);
        printf("Файл был создан.\n");
        printf("Так как файл пустой, в нем нет никаких имён.\n");
        return 0;
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
    printf("Введите имя и телефон через пробел => ");
    while (scanf("%s", data[*size].name) != 1) {
    }
    while (!getchar()) {};
    while (scanf("%s", data[*size].phone) != 1) {};
    ++(*size);
}

void searchPhone(Phonebook* data, const char* name, const int* size, char* buffer) {
    int currentIndex = 0;
    while (currentIndex < *size) {
        Phonebook currentNote = data[currentIndex];
        if (strcmp(name, currentNote.name) == 0) {
            strcpy(buffer, currentNote.phone);
            return;
        }
        ++currentIndex;
    }
    buffer = NULL;
}

void searchName(Phonebook* data, const char* phone, const int* size, char* buffer) {
    int currentIndex = 0;
    while (currentIndex < *size) {
        Phonebook currentNote = data[currentIndex];
        if (strcmp(phone, currentNote.phone) == 0) {
            strcpy(buffer, currentNote.name);
            return;
        }
        ++currentIndex;
    }
    buffer = NULL;
}

int saveNotes(Phonebook* data, const char* fileName, const int* size) {
    FILE* file = fopen(fileName, "w");
    for (int i = 0; i < *size; ++i) {
        fprintf(file, "%s ", data[i].name);
        fprintf(file, "%s\n", data[i].phone);
    }
    fclose(file);
}
