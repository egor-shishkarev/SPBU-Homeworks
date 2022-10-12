#pragma once
// Структура, содержащая имя и номер телефона 
typedef struct {
	char name[20];
	char phone[20];
} Phonebook;
// Функция проверки ввода целого числа
int verificationIntScanf();
// Функция добавляет в массив имена и номера телефонов, которую можно сохранить в файл
int addNote(Phonebook* data);
// Вывод всех записей в файле
int printNotes();
// Поиск номера телефона по имени
int searchPhone(Phonebook* data);
// Поиск имени по номеру телефона
int searchName(Phonebook* data);
// Сохранение всех введенных записей в файл
int saveNotes(Phonebook* data);