#pragma once
// ��������� ������
typedef struct List List; 
// ������� �������
int insert(List* list, int value);
// ������� �������� ������
List* createList(const int a, const int b);
// ������� ������ ������ � ����
void printListInFile(List* list, const char* g);
// ������� �������� �������� �� ������
int deleteElement(List* list, const int value);
// ������� �������� ������
void deleteList(List** list);