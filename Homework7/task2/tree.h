#pragma once

// ��������� - ����, �������� � ���� 4 ����: ��������, ����� ���, ������ ��� � ��������.
typedef struct Node Node;

// ��������� - ������, �������� � ���� 1 ���� - ������.
typedef struct Tree Tree;

// ������� �������� ������ � �������� ������.
void deleteTree(Tree** tree);

// ������� �������� ������.
Tree* createParseTree(void);

// ����� ��������� � ���� ������ � ������� � ������� ������ ������.
void treePrint(Tree* tree);

// ������� �������� ���������, ����������� � ������.
int treeResult(Tree* tree);

// ������ ��������� � ���� ������
int readFileToTree(const char* fileName, Tree* tree);