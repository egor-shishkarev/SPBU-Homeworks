#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node Node;
typedef struct Tree Tree;
void deleteTree(Tree** tree);
Tree* createParseTree(const char* arrayOfSymbols, const int lengthOfString);
void addPartToTree(Tree* tree, char operation, char* operand1, char* operand2, Node* currentNode);
void addElementsToTree(Tree* tree, const char* arrayOfSymbols);
