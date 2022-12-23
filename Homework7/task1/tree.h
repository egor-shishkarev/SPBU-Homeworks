#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

// ��������� - ������, ���������� ����: ����, ��������, ������ ���, ����� ���, ��������.
typedef struct Tree Tree;

// ��������� - ����, �������� ���� - ������.
typedef struct Node Node;

// ������� ��� ������ ������� ����� � ������. ���������� ��������� �� ������� ��� ������ ���� � ����������� �� �������� �����.
Node* nodeSearch(Node* node, const int key, int* errorCode);

// �������, ���������� 1, ���� �������� ����� ����������� ���� ������ ����� ��� -1, ���� �������� ������.
int choiceChild(Node* node, const int key);

// �������, ������� ������.
Tree* createTree(int *errorCode);

// ������� ���������� �������� � ������. ��������� �������� � ���� ������ ����.
void addElement(Tree* tree, const int key, const char* value, int* errorCode);

// ���������� ��������� �� ������ ������� ���� ������ ���� ����������� ����.
Node* theMostRightChild(Node* node);

// ���������� �������� �� ����������� �����. � ������ ���������� ����� ����������� ������ NULL.
char* searchValueFromKey(Tree* tree, const int key);

// ���������, ���� �� ���� � ������ ��� ���.
bool isKeyInTree(Tree* tree, const int key);

// ������� �������� �������� �� ������. ���� ������ ����� ���, ������ �� ������.
void deleteElement(Tree* tree, const int key, int* errorCode);

// �������� �������� �������� ������ � ������� ��������.
void deleteTree(Tree** tree);

// ���������� true ���� ���������� ���� �������� ����� ����� ��� false, ���� �������� ������ �����.
bool isLeftChild(Node* node, int* errorCode);