#pragma once

// ������� ���������� ��������� �� ������ ��������, 
// �� ������� ����� ���������� ��� ��������� �����.
int* createArrayOfPrefixFunction(const char* string, int* errorCode);

// ���������� ������ ������� ���������� ������ � ������.
int findString(const char* text, const char* string, int* offset);