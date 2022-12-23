#include "phonebook.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <stdbool.h>

bool correctTests(void) {
    char* data[10] = { "Pasha", "88005553535", "Andrey", "89118745932", "Vladimir", "8(911)-627-53-27", "Anton", "+79114518723", "Ibragim", "216983-59-21" };
    int size = 5;
    Phonebook directory[5] = { "", "" };
    for (int i = 0; i < size; ++i) {
        strcpy(directory[i].name, data[2 * i]);
        strcpy(directory[i].phone, data[2 * i + 1]);
    }
    const char* testFile = "tests.txt";
    FILE* file = fopen(testFile, "w");
    saveNotes(directory, testFile, &size);
    bool allAreTrue = true;	
    for (int i = 0; i < 5; ++i) {
        char name[100] = { 0 };
        char phone[100] = { 0 };
        searchName(directory, data[2 * i + 1], &size, name); 
        searchPhone(directory, data[2 * i], &size, phone);
        if (!(strcmp(phone, data[2 * i + 1]) == 0 && strcmp(name, data[2 * i]) == 0)) {
            allAreTrue = false;
            break;
        }
    }
    return allAreTrue;
}

int printNotes(const char* fileName) {
    FILE* file = fopen(fileName, "r");
    if (file == NULL) {
        file = fopen(fileName, "w");
        fclose(file);
        printf("Файл был создан.");
    }
    printf("\nСписок контактов:\n");
    while (!feof(file)) {
        char buffer[100] = { "" };
        if (fgets(buffer, 100, file) == 0) {
            break;
        }
        printf(buffer);
    }
    fclose(file);
    printf("\n");
}

bool incorrectCase(void) {
    char* data[10] = { "Pasha", "88005553535", "Andrey", "89118745932", "Vladimir", "8(911)-627-53-27", "Anton", "+79114518723", "Ibragim", "216983-59-21" };
    int size = 5;
    Phonebook directory[5] = { "", "" };
    for (int i = 0; i < size; ++i) {
        strcpy(directory[i].name, data[2 * i]);
        strcpy(directory[i].phone, data[2 * i + 1]);
    }
    const char* testFile = "tests.txt";
    FILE* file = fopen(testFile, "w");
    saveNotes(directory, testFile, &size);
    char name[100] = { 0 };
    char phone[100] = { 0 };
    searchName(directory, "89117845123", &size, name);
    searchPhone(directory, "Misha", &size, phone);

    return name != "Misha" && phone != "89117845123";
}

int workingMode(int mode, Phonebook *data, const char *phoneDirectory, int* size) {
    switch (mode) {
    case 0:
        printf("Работа закончена.");
        return 0;
    case 1:
        addNote(data, size);
        break;
    case 2:
        printNotes(phoneDirectory);
        break;
    case 3:
        printf("Введите имя для которого хотите найти телефон => ");
        char nameToFind[MAX_SIZE_NAME] = { "" };
        scanf("%s", nameToFind);
        char phone[100] = { 0 };
        searchPhone(data, nameToFind, size, phone);
        printf("%s\n", phone);
        break;
    case 4:
        printf("Введите телефон для которого хотите найти имя => ");
        char phoneToFind[MAX_SIZE_PHONE] = { "" };
        scanf("%s", phoneToFind);
        char name[100] = {0};
        searchName(data, phoneToFind, size, name);
        printf("%s\n", name);
        break;
    case 5:
        saveNotes(data, phoneDirectory, size);
        break;
    default:
        while (mode < 0 || mode > 5) {
            printf("Введено неверное значение, повторите ввод => ");
            mode = verificationIntScanf();
        }
        workingMode(mode, data, phoneDirectory, size);
    }
}

int main(void) {
    setlocale(LC_ALL, ".1251");
    if (!(correctTests() && incorrectCase())) {
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
    Phonebook data[100] = { "", "" };
    int sizeOfBook = readFile(data, phoneDirectory);
    while (true) {
        workingMode(mode, data, phoneDirectory, &sizeOfBook);
        if (mode == 0) {
            break;
        }
        printf("Введите цифру => ");
        mode = verificationIntScanf();
    }
    return 0;
}
