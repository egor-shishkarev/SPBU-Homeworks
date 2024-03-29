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
int addNote(Phonebook* data, int* size);

// ����� ������ �������� �� �����
void searchPhone(Phonebook* data, const char* name, const int* size, char* buffer);

// ����� ����� �� ������ ��������
void searchName(Phonebook* data, const char* phone, const int* size, char* buffer);

// ���������� ���� ��������� ������� � ����
int saveNotes(Phonebook* data, const char* fileName, const int* size);