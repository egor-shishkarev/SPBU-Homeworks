#pragma once
#include <stdbool.h>
// Структура, содержащая другую структуру - Node, которая в свою очередь содержит два поля: значение и адрес следующего элемента в "стеке".
typedef struct Stack Stack;
// Функция для заполнения стека. Элемент добавляется в верх стека.
int push(Stack* stack, int element);
// Функция, позволяющая "вытащить" элемент с верха стека.
int pop(Stack* stack, int* errorCode);
// Функция проверки стека на отсутствие элементов.
bool isEmpty(Stack* stack);
// Функция удаления стека и очищения памяти, выделенной под указатель.
void deleteStack(Stack* stack);
// Функция создания стека.
Stack* createStack(void);
// Функция получения элемента с верха стека. Не достаёт элемент.
int top(Stack* stack);