#pragma once

#include <stdio.h>
#include <string.h>
#include <malloc.h>
// ������� ���������� ��������� �� ������ ��������, 
// �� ������� ����� ���������� ��� ��������� �����.
int* createArrayOfPrefixFunction(char* string, int* errorCode);
// ���������� ������ ������� ���������� ������ � ������.
int findString(char* text, char* string, int* offset);