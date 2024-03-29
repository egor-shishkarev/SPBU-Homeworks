#pragma once

#include "stackType.h"
#include <stdbool.h>

// ���������, ���������� ������ ��������� - Node, ������� � ���� ������� �������� ��� ����: �������� � ����� ���������� �������� � "�����".
typedef struct Stack Stack;

// ������� ��� ���������� �����. ������� ����������� � ���� �����.
int push(Stack* stack, uncertainType element);

// �������, ����������� "��������" ������� � ����� �����.
uncertainType pop(Stack* stack, int* errorCode);

// ������� �������� ����� �� ���������� ���������.
bool isEmpty(Stack* stack);

// ������� �������� ����� � �������� ������, ���������� ��� ���������.
void deleteStack(Stack* stack);

// ������� �������� �����.
Stack* createStack(void);

// ������� ��������� �������� � ����� �����. �� ������ �������.
uncertainType top(Stack* stack);