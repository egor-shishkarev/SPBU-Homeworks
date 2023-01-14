#pragma once

#include <stdbool.h>

// ��������� - ������, ���������� ����: ����, ��������, ������ ���, ����� ���, ��������.
typedef struct Tree Tree;

// ��������� - ����, �������� ���� - ������.
typedef struct Node Node;

// �������, ������� ������.
Tree* createTree(int *errorCode);

// ������� ���������� �������� � ������. ��������� �������� � ���� ������ ����.
void addElement(Tree* tree, const int key, const char* value, int* errorCode);

// ���������� �������� �� ����������� �����. � ������ ���������� ����� ����������� ������ NULL.
char* searchValueFromKey(Tree* tree, const int key);

// ���������, ���� �� ���� � ������ ��� ���.
bool isKeyInTree(Tree* tree, const int key);

// ������� �������� �������� �� ������. ���� ������ ����� ���, ������ �� ������.
void deleteElement(Tree* tree, const int key, int* errorCode);

// �������� �������� �������� ������ � ������� ��������.
void deleteTree(Tree** tree);
