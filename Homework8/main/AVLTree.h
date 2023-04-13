#pragma once

#include <stdbool.h>

#define MAX_KEY_SIZE 10
#define MAX_VALUE_SIZE 100

// Структура АВЛ-дерева. Содержит поле - корень.
typedef struct AVLTree AVLTree;

// Функция создания АВЛ-дерева.
AVLTree* createTree(int* errorCode);

// Функция удаления дерева.
void deleteTree(AVLTree** tree);

// Функция добавления элемента в дерево.
void addElement(AVLTree* tree, const char* key, const char* value, int* errorCode);

// Функция поиска значения по ключу. Возвращает NULL, если данного ключа нет.
char* searchValueFromKey(AVLTree* tree, const char* key);

// Функция проверки нахождения ключа в дереве.
bool isKeyInTree(AVLTree* tree, const char* key);

// Функция удаления элемента из дерева.
void deleteElement(AVLTree* tree, const char* key, int* errorCode);