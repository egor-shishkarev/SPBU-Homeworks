#pragma once

#include <stdbool.h>
#define MAX_NAME_SIZE 20
#define MAX_PHONE_SIZE 20

// ����������� ���������� ��� ���������� ���� ��� �������� � �������� ������
typedef enum deleteMode deleteMode;

// ���������� ��� ������ ���������� 
typedef enum sortMode sortMode;

// ��������� ���� ������. �������� 4 ����: ���, ����� ��������, ������� � ��������� �� ��������� ����.
typedef struct Node Node;

// ��������� ������, �������� ��� ����: ������, ����� � �����
typedef struct List List;

// ������� ������ ������
void printList(List* list);

// ������� ������ � ������ ������� ���� "��� - ����� ��������"
void readFromFile(List* list, const char* path, int* errorCode);

// ������� �������� ������
List* createList(int* errorCode);

// ���������� ������ ��������
List* mergeSort(List* list, sortMode mode, int* errorCode);

// ������� �������� ������
void deleteList(List** list, deleteMode mode);

// ���������� ������ ������
Node* headOfList(List* list);

// ������� ���������� �������� � ������
void addElement(List* list, char* name, char* phone, const int position, int* errorCode);

// ��������� ������� �� ������
Node* nextElement(Node* node);

// �������� �� ������������ ����� � �������� ����
bool testNode(Node* node, char* name, char* phone);
