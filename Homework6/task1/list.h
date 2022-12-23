#pragma once

// Структура, включающая структуру Node, которая содержит три поля: значение, следующий элемент и предыдущий.
typedef struct List List;

// Функция, помещающая элемент в список. 
int insert(List* list, int value);

// Функция, вовзращающая элемент из "верха" списка.
int topElement(List* list, int* errorCode);

// Функция, удаляющая элемент из списка.
int deleteElement(List* list, int value);

// Функция, удаляющая список. 
void deleteList(List** list);

// Функция, создающая список. Возвращает указатель на него.
List* createList(void);

// Функция, выводящая весь список.
void printList(List* list);
