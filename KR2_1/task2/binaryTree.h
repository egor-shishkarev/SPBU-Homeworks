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
// �������, ������� ������.
Tree* createTree(int* errorCode);
// ������� ���������� �������� � ������. ��������� �������� � ���� ������ ����.
void addElement(Tree* tree, const int key, int* errorCode);
// �������� �������� �������� ������ � ������� ��������.
void deleteTree(Tree** tree);
// ������ ����� ������.
void directOrder(Tree* tree, int* arrayOfElements);
// ������� ���������� �������� �������.
void binaryTreeSort(int* arrayOfNumbers, const int sizeOfArray);
