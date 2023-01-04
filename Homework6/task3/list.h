#pragma once

#define MAX_NAME_SIZE 20
#define MAX_PHONE_SIZE 20

// Специальная переменная для уменьшения кода при удалении и стирании списка
typedef enum deleteMode deleteMode;

// Переменная для выбора сортировки 
typedef enum sortMode sortMode;

// Структура список, содержит три поля: голова, хвост и длина
typedef struct List List;

// Функция вывода списка
void printList(List* list);

// Функция чтения в список записей типа "имя - номер телефона"
void readFromFile(List* list, const char* path/*, int* errorCode*/);

// Функция создания списка
List* createList(void);

// Сортировка списка слиянием
List* mergeSort(List* list/*, int* errorCode*/, sortMode mode);

// Функция удаления списка
void deleteList(List** list, deleteMode mode);