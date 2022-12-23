#pragma once

#include <stdbool.h>
#define MAX_SIZE_NAME 20
#define MAX_SIZE_PHONE 20

// ���������, ���������� ��� � ����� �������� 
typedef struct {
	char name[MAX_SIZE_NAME];
	char phone[MAX_SIZE_PHONE];
} Phonebook;

// ������� �������� ����� ������ �����
int verificationIntScanf(void);

// ������� ��������� ����� � ������ �� ����� � ������ �������� Phonebook
int readFile(Phonebook* data, const char* fileName);

// ������� ��������� � ������ ����� � ������ ���������, ������� ����� ��������� � ����
int addNote(Phonebook* data, const int* size);

// ����� ������ �������� �� �����
char* searchPhone(Phonebook* data, const char* name, const int* size);

// ����� ����� �� ������ ��������
char* searchName(Phonebook* data, const char* phone, const int* size);

// ���������� ���� ��������� ������� � ����
int saveNotes(Phonebook* data, const char* fileName, const int* size);