#pragma once

#include <stdbool.h>

#define MAX_KEY_SIZE 10
#define MAX_VALUE_SIZE 100

// ��������� ���-������. �������� ���� - ������.
typedef struct AVLTree AVLTree;

// ������� �������� ���-������.
AVLTree* createTree(int* errorCode);

// ������� �������� ������.
void deleteTree(AVLTree** tree);

// ������� ���������� �������� � ������.
void addElement(AVLTree* tree, const char* key, const char* value, int* errorCode);

// ������� ������ �������� �� �����. ���������� NULL, ���� ������� ����� ���.
char* searchValueFromKey(AVLTree* tree, const char* key);

// ������� �������� ���������� ����� � ������.
bool isKeyInTree(AVLTree* tree, const char* key);

// ������� �������� �������� �� ������.
void deleteElement(AVLTree* tree, const char* key, int* errorCode);