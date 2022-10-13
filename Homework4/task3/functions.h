#pragma once
#include <stdbool.h>
// ���������, ���������� ��� � ����� �������� 
typedef struct {
	char name[20];
	char phone[20];
} Phonebook;
// ������� �������� ����� ������ �����
int verificationIntScanf();
// �������� 5 ���� � ������� ��������� �� ������ � �������� ����, ����� �� ����� � ������ ��������
bool correctTests();
// �������� ������ 1 ������� ����� � ��������
bool incorrectCase();
// ������� ��������� � ������ ����� � ������ ���������, ������� ����� ��������� � ����
int addNote(Phonebook* data);
// ����� ���� ������� � �����
int printNotes(const char *fileName);
// ����� ������ �������� �� �����
int searchPhone(const char* fileName, bool consoleOutput, const char* testName, const char* testPhone);
// ����� ����� �� ������ ��������
int searchName(const char* fileName, bool consoleOutput, const char* testName, const char* testPhone);
// ���������� ���� ��������� ������� � ����
int saveNotes(Phonebook* data, const char* fileName, bool consoleOutput);