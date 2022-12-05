#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
// Струкутра - узел, содержащщая три поля: число, указатель на следующий узел и указатель на предыдущий узел.
typedef struct Node Node;
// Структура - список, содержит в себе два поля: узел head - начало списка и узел tail - конец списка.
typedef struct List List;
// Функция создания списка. Возвращает указатель на него.
List* createList(int *errorCode);
// Функция добавления элемента в список.
void insertElement(List* list, const int number, int* errorCode);
// Функция удаления списка.
void deleteList(List* list);
// Функция проверки списка на симметричность.
bool isSymethric(List* list, int *errorCode);