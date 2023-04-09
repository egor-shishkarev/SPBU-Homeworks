#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

// Структура - дерево, содержащая поля: ключ, значение, правый сын, левый сын, родитель.
typedef struct AVLTree AVLTree;

// Структура - узел, содержит поле - корень.
typedef struct Node Node;

// Функция для поиска нужного места в дереве. Возвращает указатель на правого или левого сына в зависимости от значения ключа.
Node* nodeSearch(Node* node, const int key, int* errorCode);

// Функция, возвращает 1, если значение ключа переданного узла больше ключа или -1, если значение меньше.
int choiceChild(Node* node, const int key);

// Функция, создает дерево.
AVLTree* createTree(int* errorCode);

// Функция добавления элемента в дерево. Принимает значение и ключ нового узла.
void addElement(AVLTree* tree, const int key, const char* value, int* errorCode);

// Вовзращает указатель на самого правого сына левого сына переданного узла.
Node* theMostRightChild(Node* node);

// Возвращает значение по переданному ключу. В случае отсутствия ключа вовзвращает строку NULL.
char* searchValueFromKey(AVLTree* tree, const int key);

// Проверяет, есть ли ключ в дереве или нет.
bool isKeyInTree(AVLTree* tree, const int key);

// Функция удаления элемента из дерева. Если такого ключа нет, ничего не делает.
void deleteElement(AVLTree* tree, const int key, int* errorCode);

// Основной алгоритм удаления дерева с помощью рекурсии.
void deleteTree(AVLTree** tree);

// Возвращает true если переданный узел является левым сыном или false, если является правым сыном.
bool isLeftChild(Node* node, int* errorCode);

// Балансирует узлы в дереве.
Node* balance(Node* node, AVLTree* tree);

// Подсчитывает баланс в дереве.
Node* countingBalance(Node* node, int* errorCode);
