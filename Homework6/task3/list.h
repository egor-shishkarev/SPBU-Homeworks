#pragma once

#include <stdbool.h>

#define MAX_NAME_SIZE 20
#define MAX_PHONE_SIZE 20

// Специальная переменная для уменьшения кода при удалении и стирании списка
typedef enum DeleteMode {
    erase,
    delete
} DeleteMode;

// Переменная для выбора сортировки 
typedef enum SortMode {
    name,
    phone
} SortMode;

// Структура узла списка. Содержит 4 поля: имя, номер телефона, позицию и указатель на следующий узел.
typedef struct Node Node;

// Структура список, содержит три поля: голова, хвост и длина
typedef struct List List;

// Функция вывода списка
void printList(List* list);

// Функция чтения в список записей типа "имя - номер телефона"
List* readFromFile(const char* path, int* errorCode);

// Функция создания списка
List* createList(int* errorCode);

// Сортировка списка слиянием
List* mergeSort(List* list, SortMode mode, int* errorCode);

// Функция удаления списка
void deleteList(List** list, DeleteMode mode);

// Возвращает голову списка
Node* headOfList(List* list);

// Функция добавления элемента в список
void addElement(List* list, char* name, char* phone, const int position, int* errorCode);

// Следующий элемент из списка
Node* nextElement(Node* node);

// Проверка на соответствие имени и телефона узла
bool testNode(Node* node, char* name, char* phone);
