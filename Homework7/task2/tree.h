#pragma once

// Структура - дерево, включает в себя 1 поле - корень.
typedef struct Tree Tree;

// Функция удаления дерева и очищения памяти.
void deleteTree(Tree** tree);

// Вывод выражения в виде дерева в консоль с помощью обхода дерева.
void treePrint(Tree* tree);

// Функция подсчета выражения, записанного в дерево.
int treeResult(Tree* tree);

// Запись выражения в виде дерева
Tree* readFileToTree(const char* fileName);