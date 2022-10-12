#pragma once
//
typedef struct {
	char name[20];
	char phone[20];
} Phonebook;
//
int verificationIntScanf();
int addNote(Phonebook* data);
int printNotes();
int searchPhone(Phonebook* data);
int searchName(Phonebook* data);
int saveNotes(Phonebook* data);