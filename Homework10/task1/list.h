#pragma once

// �������� ������, ���������� ��������� ����� ������.
typedef struct List List;

// �������, ��������� ����� ������.
List* createList(void);

// ��������� ������� � ����� ������.
void insertElement(List* list, const int number);

// �������, ��������� ������ � �������.
void printList(List* list);

// �������, ��������� ������.
void deleteList(List** list);

