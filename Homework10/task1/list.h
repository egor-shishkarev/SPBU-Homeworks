#pragma once

// ��������� ���� - ������� ������.
typedef struct Node Node;

// ��������� ������, ���������� ��������� ����� ������.
typedef struct List List;

// �������, ��������� ����� ������.
List* createList(void);

// ��������� ������� � ����� ������.
void insertElement(List* list, const int number);

// �������, ��������� ������ � �������.
void printList(List* list);

// �������, ��������� ������.
void deleteList(List** list);

// ���������� ������� �� ������ �� �������.
int listElement(List* list, int position);

