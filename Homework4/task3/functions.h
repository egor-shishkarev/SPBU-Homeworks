#pragma once
#include <stdbool.h>
// Структура, содержащая имя и номер телефона 
typedef struct {
	char name[20];
	char phone[20];
} Phonebook;
// Функция проверки ввода целого числа
int verificationIntScanf();
// Проверка 5 имен и номеров телефонов на запись в тестовый файл, поиск по имени и номеру телефона
bool correctTests();
// Проверка поиска 1 ложного имени и телефона
bool incorrectCase();
// Функция добавляет в массив имена и номера телефонов, которую можно сохранить в файл
int addNote(Phonebook* data);
// Вывод всех записей в файле
int printNotes(const char *fileName);
// Поиск номера телефона по имени
int searchPhone(const char* fileName, bool consoleOutput, const char* testName, const char* testPhone);
// Поиск имени по номеру телефона
int searchName(const char* fileName, bool consoleOutput, const char* testName, const char* testPhone);
// Сохранение всех введенных записей в файл
int saveNotes(Phonebook* data, const char* fileName, bool consoleOutput);