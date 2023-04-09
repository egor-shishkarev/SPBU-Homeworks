#pragma once

// Сруткура список, позволящая добавлять новые города.
typedef struct List List;

// Функция, создающая новый список.
List* createList(void);

// Добавляет элемент в конец список.
void insertElement(List* list, const int number);

// Функция, выводящая список в консоль.
void printList(List* list);

// Функция, удаляющая список.
void deleteList(List** list);

