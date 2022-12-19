#pragma once
// Структура списка
typedef struct List List; 
// Функция вставки
int insert(List* list, int value);
// Функция создания списка
List* createList(const int a, const int b);
// Функция печати списка в файл
void printListInFile(List* list, const char* g);
// Функция удаления элемента из списка
int deleteElement(List* list, const int value);
// Функция уадления списка
void deleteList(List** list);