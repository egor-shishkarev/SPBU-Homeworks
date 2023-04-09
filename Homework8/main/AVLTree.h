#pragma once

#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>

// ��������� - ������, ���������� ����: ����, ��������, ������ ���, ����� ���, ��������.
typedef struct AVLTree AVLTree;

// ��������� - ����, �������� ���� - ������.
typedef struct Node Node;

// ������� ��� ������ ������� ����� � ������. ���������� ��������� �� ������� ��� ������ ���� � ����������� �� �������� �����.
Node* nodeSearch(Node* node, const int key, int* errorCode);

// �������, ���������� 1, ���� �������� ����� ����������� ���� ������ ����� ��� -1, ���� �������� ������.
int choiceChild(Node* node, const int key);

// �������, ������� ������.
AVLTree* createTree(int* errorCode);

// ������� ���������� �������� � ������. ��������� �������� � ���� ������ ����.
void addElement(AVLTree* tree, const int key, const char* value, int* errorCode);

// ���������� ��������� �� ������ ������� ���� ������ ���� ����������� ����.
Node* theMostRightChild(Node* node);

// ���������� �������� �� ����������� �����. � ������ ���������� ����� ����������� ������ NULL.
char* searchValueFromKey(AVLTree* tree, const int key);

// ���������, ���� �� ���� � ������ ��� ���.
bool isKeyInTree(AVLTree* tree, const int key);

// ������� �������� �������� �� ������. ���� ������ ����� ���, ������ �� ������.
void deleteElement(AVLTree* tree, const int key, int* errorCode);

// �������� �������� �������� ������ � ������� ��������.
void deleteTree(AVLTree** tree);

// ���������� true ���� ���������� ���� �������� ����� ����� ��� false, ���� �������� ������ �����.
bool isLeftChild(Node* node, int* errorCode);

// ����������� ���� � ������.
Node* balance(Node* node, AVLTree* tree);

// ������������ ������ � ������.
Node* countingBalance(Node* node, int* errorCode);
