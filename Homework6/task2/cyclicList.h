#pragma once

// Структура, состоящая из трех полей: позиция, указатель на предыдущий и следующий элемент
typedef struct List List;

// Функция создания циклического списка
List* createCyclicList(int* errorCode);

// Функция добавления элемента в циклический список
int insertElement(List* list, const int position, int* errorCode);

// Функция удаления элемента из циклического списка
int deleteElement(List* list, const int gap, int* errorCode);

// Функция, необходимая для возвращения последнего элемента из списка
int lastPosition(List* list, int* errorCode);

// Функция для удаления списка
void deleteList(List* list);