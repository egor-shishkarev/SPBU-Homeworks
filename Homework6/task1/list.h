#pragma once
// ���������, ���������� ��������� Node, ������� �������� ��� ����: ��������, ��������� ������� � ����������.
typedef struct List List;
// �������, ���������� ������� � ������. 
int insert(List* list, int value);
// �������, ������������ ������� �� "�����" ������.
int getValue(List* list, int* errorCode);
// �������, ��������� ������� �� ������.
int deleteElement(List* list, int value);
// �������, ��������� ������. 
void deleteList(List** list);
// �������, ��������� ������. ���������� ��������� �� ����.
List* createList(void);
// �������, ��������� ���� ������.
void printList(List* list);
