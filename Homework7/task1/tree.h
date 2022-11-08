#pragma once
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

typedef struct Tree Tree;
typedef struct Node Node;
Node* nodeSearch(Node* node, const int key);
int choiceChild(Node* node, const int key);
Tree* createTree(void);
void addElement(Tree* tree, const int key, const char* value);
Node* theMostRightChild(Node* node);
char* searchValueFromKey(Tree* tree, const int key);
bool isKeyInTree(Tree* tree, const int key);
void deleteElement(Tree* tree, const int key);
void deleteTreeRecursive(Node* node);
void deleteTree(Tree** tree);
bool isLeftChild(Node* node);