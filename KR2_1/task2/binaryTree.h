#pragma once
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
// Структура - дерево, содержащая поля: ключ, значение, правый сын, левый сын, родитель.
typedef struct Tree Tree;
// Структура - узел, содержит поле - корень.
typedef struct Node Node;
// Функция, создает дерево.
Tree* createTree(int* errorCode);
// Функция добавления элемента в дерево. Принимает значение и ключ нового узла.
void addElement(Tree* tree, const int key, int* errorCode);
// Основной алгоритм удаления дерева с помощью рекурсии.
void deleteTree(Tree** tree);
// Прямой обход дерева.
void directOrder(Tree* tree, int* arrayOfElements);
// Функция сортировки бинарным деревом.
void binaryTreeSort(int* arrayOfNumbers, const int sizeOfArray);
