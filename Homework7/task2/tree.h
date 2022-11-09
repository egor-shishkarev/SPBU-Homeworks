#pragma once
#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>

typedef struct Node Node;
typedef struct Tree Tree;
Tree* createTree(int* errorCode);
void deleteTree(Tree** tree);
Tree* createParseTree(const char* arrayOfSymbols, const int lengthOfString);
