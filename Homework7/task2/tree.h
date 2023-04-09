#pragma once

// ��������� - ������, �������� � ���� 1 ���� - ������.
typedef struct Tree Tree;

// ������� �������� ������ � �������� ������.
void deleteTree(Tree** tree);

// ����� ��������� � ���� ������ � ������� � ������� ������ ������.
void treePrint(Tree* tree);

// ������� �������� ���������, ����������� � ������.
int treeResult(Tree* tree);

// ������ ��������� � ���� ������
Tree* readFileToTree(const char* fileName);