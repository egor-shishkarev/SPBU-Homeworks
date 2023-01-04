#pragma once

#define MAX_NAME_SIZE 20
#define MAX_PHONE_SIZE 20

// ����������� ���������� ��� ���������� ���� ��� �������� � �������� ������
typedef enum deleteMode deleteMode;

// ���������� ��� ������ ���������� 
typedef enum sortMode sortMode;

// ��������� ������, �������� ��� ����: ������, ����� � �����
typedef struct List List;

// ������� ������ ������
void printList(List* list);

// ������� ������ � ������ ������� ���� "��� - ����� ��������"
void readFromFile(List* list, const char* path/*, int* errorCode*/);

// ������� �������� ������
List* createList(void);

// ���������� ������ ��������
List* mergeSort(List* list/*, int* errorCode*/, sortMode mode);

// ������� �������� ������
void deleteList(List** list, deleteMode mode);