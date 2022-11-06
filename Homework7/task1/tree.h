#pragma once
#include <stdbool.h>
typedef struct Tree Tree;
typedef struct Node Node;
Node* nodeSearch(Node* node, const int key);
int choiceChild(Node* node, const int key);
Tree* createTree(void);
void addElement(Tree* tree, const int key, char* value);
char* theMostRightChild(Tree* tree);
char* searchValueFromKey(Tree* tree, const int key);
bool isKeyInTree(Tree* tree, const int key);