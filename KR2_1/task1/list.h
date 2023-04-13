#pragma once
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdbool.h>
// ��������� - ����, ����������� ��� ����: �����, ��������� �� ��������� ���� � ��������� �� ���������� ����.
typedef struct Node Node;
// ��������� - ������, �������� � ���� ��� ����: ���� head - ������ ������ � ���� tail - ����� ������.
typedef struct List List;
// ������� �������� ������. ���������� ��������� �� ����.
List* createList(int *errorCode);
// ������� ���������� �������� � ������.
void insertElement(List* list, const int number, int* errorCode);
// ������� �������� ������.
void deleteList(List* list);
// ������� �������� ������ �� ��������������.
bool isSymethric(List* list, int *errorCode);