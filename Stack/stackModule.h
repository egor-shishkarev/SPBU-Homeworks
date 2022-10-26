#pragma once
#include "typeStack.h"
#include <stdbool.h>
// ���������, ���������� ������ ��������� - Node, ������� � ���� ������� �������� ��� ����: �������� � ����� ���������� �������� � "�����".
typedef struct Stack Stack;
// ������� ��� ���������� �����. ������� ����������� � ���� �����.
int push(Stack* stack, uncertainType element);
// �������, ����������� "��������" ������� � ����� �����.
int pop(Stack* stack, int* errorCode);
// ������� �������� ����� �� ���������� ���������.
bool isEmpty(Stack* stack);
// ������� �������� ����� � �������� ������, ���������� ��� ���������.
void deleteStack(Stack* stack);
// ������� �������� �����.
Stack* createStack(void);
// ������� ��������� �������� � ����� �����. �� ������ �������.
int top(Stack* stack);