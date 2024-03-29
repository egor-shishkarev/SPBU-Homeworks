#pragma once

// ���������, ��������� �� ���� �����: �������, ��������� �� ���������� � ��������� �������
typedef struct List List;

// ������� �������� ������������ ������
List* createCyclicList(int* errorCode);

// ������� ���������� �������� � ����������� ������
void insertElement(List* list, const int position, int* errorCode);

// ������� �������� �������� �� ������������ ������
void deleteElement(List* list, const int gap, int* errorCode);

// �������, ����������� ��� ����������� ���������� �������� �� ������
int lastPosition(List* list, int* errorCode);

// ������� ��� �������� ������
void deleteList(List** list);