#pragma once

#include <stdbool.h>
#define MAX_SIZE_NAME 20
#define MAX_SIZE_PHONE 20

// Структура, содержащая имя и номер телефона 
typedef struct {
	char name[MAX_SIZE_NAME];
	char phone[MAX_SIZE_PHONE];
} Phonebook;

// Функция проверки ввода целого числа
int verificationIntScanf(void);

// Функция считывает имена и номера из файла в массив структур Phonebook
int readFile(Phonebook* data, const char* fileName);

// Функция добавляет в массив имена и номера телефонов, которую можно сохранить в файл
int addNote(Phonebook* data, const int* size);

// Поиск номера телефона по имени
char* searchPhone(Phonebook* data, const char* name, const int* size);

// Поиск имени по номеру телефона
char* searchName(Phonebook* data, const char* phone, const int* size);

// Сохранение всех введенных записей в файл
int saveNotes(Phonebook* data, const char* fileName, const int* size);