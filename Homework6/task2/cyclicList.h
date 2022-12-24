#pragma once

// ���������, ��������� �� ���� �����: �������, ��������� �� ���������� � ��������� �������
typedef struct List List;

// ������� �������� ������������ ������
List* createCyclicList(int* errorCode);

// ������� ���������� �������� � ����������� ������
int insertElement(List* list, const int position, int* errorCode);

// ������� �������� �������� �� ������������ ������
int deleteElement(List* list, const int gap, int* errorCode);

// �������, ����������� ��� ����������� ���������� �������� �� ������
int lastPosition(List* list, int* errorCode);

// ������� ��� �������� ������
void deleteList(List* list);