#pragma once

#include <stdbool.h>

// Структура - дерево, содержащая поля: ключ, значение, правый сын, левый сын, родитель.
typedef struct Tree Tree;

// Структура - узел, содержит поле - корень.
typedef struct Node Node;

// Функция, создает дерево.
Tree* createTree(int *errorCode);

// Функция добавления элемента в дерево. Принимает значение и ключ нового узла.
void addElement(Tree* tree, const int key, const char* value, int* errorCode);

// Возвращает значение по переданному ключу. В случае отсутствия ключа вовзвращает строку NULL.
char* searchValueFromKey(Tree* tree, const int key);

// Проверяет, есть ли ключ в дереве или нет.
bool isKeyInTree(Tree* tree, const int key);

// Функция удаления элемента из дерева. Если такого ключа нет, ничего не делает.
void deleteElement(Tree* tree, const int key, int* errorCode);

// Основной алгоритм удаления дерева с помощью рекурсии.
void deleteTree(Tree** tree);
