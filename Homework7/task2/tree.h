#pragma once

// Структура - узел, включает в себя 4 поля: значение, левый сын, правый сын и родитель.
typedef struct Node Node;

// Структура - дерево, включает в себя 1 поле - корень.
typedef struct Tree Tree;

// Функция удаления дерева и очищения памяти.
void deleteTree(Tree** tree);

// Функция создания дерева.
Tree* createParseTree(void);

// Вывод выражения в виде дерева в консоль с помощью обхода дерева.
void treePrint(Tree* tree);

// Функция подсчета выражения, записанного в дерево.
int treeResult(Tree* tree);

// Запись выражения в виде дерева
int readFileToTree(const char* fileName, Tree* tree);