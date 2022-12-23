#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// Структура - узел, включает в себя 4 поля: значение, левый сын, правый сын и родитель.
typedef struct Node Node;

// Структура - дерево, включает в себя 1 поле - корень.
typedef struct Tree Tree;

// Функция удаления дерева и очищения памяти.
void deleteTree(Tree** tree);

// Функция создания дерева.
Tree* createParseTree(void);

// Функция добавления операций и операндов в дерево.
void addElementsToTree(Tree* tree, char* arrayOfSymbols);

// Вывод выражения в виде дерева в консоль с помощью обхода дерева.
void treePrint(Tree* tree);

// Функция подсчета выражения, записанного в дерево.
int treeResult(Tree* tree);
