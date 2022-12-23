#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <malloc.h>
#include <string.h>

// ��������� - ����, �������� � ���� 4 ����: ��������, ����� ���, ������ ��� � ��������.
typedef struct Node Node;

// ��������� - ������, �������� � ���� 1 ���� - ������.
typedef struct Tree Tree;

// ������� �������� ������ � �������� ������.
void deleteTree(Tree** tree);

// ������� �������� ������.
Tree* createParseTree(void);

// ������� ���������� �������� � ��������� � ������.
void addElementsToTree(Tree* tree, char* arrayOfSymbols);

// ����� ��������� � ���� ������ � ������� � ������� ������ ������.
void treePrint(Tree* tree);

// ������� �������� ���������, ����������� � ������.
int treeResult(Tree* tree);
