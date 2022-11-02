#include "list.h"
#include <stdio.h>
#include <malloc.h>
#include <string.h>

typedef struct Node {
	int position;
	char *name;
	char *phone;
	struct Node* next;
} Node;

typedef struct List {
	Node* head;
} List;

List* createList(void) {
	List* list = malloc(sizeof(List));
	list->head = NULL;
	return list;
}

int insert(List* list, const char name[], const char phone[], const int position, int* errorCode) {
	if (list == NULL || position <= 0) {
		*errorCode = -1;
		return;
	}
	if (list->head == NULL) {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->position = position;
		newNode->next = NULL;
		newNode->name = name;
		newNode->phone = phone;
		list->head = newNode;
	} else {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->position = position;
		Node* temp = list->head;
		while (temp->next != NULL) {
			temp = temp->next;
		}
		temp->next = newNode;
		newNode->next = NULL;
		newNode->name = name;
		newNode->phone = phone;
	}
}

char* getName(List* list, int position) {
	Node* temp = list->head;
	while (temp->position != position) {
		temp = temp->next;
	}
	return temp->name; 
}

char* getPhone(List* list, int position) {
	Node* temp = list->head;
	while (temp->position != position) {
		temp = temp->next;
	}
	return temp->phone;
}

List* getNextPosition(Node* head) {
	return head->next;
}

List* mergeSort(List* listFirst, List* listSecond, const int countFirst, const int countSecond) {
	List* list = createList();
	int firstPosition = listFirst->head->position;
	int secondPosition = listSecond->head->position;
	int firstCounter = 0;
	int secondCounter = 0;
	int errorCode = 0;
	for (int i = 0; i < countFirst + countSecond; ++i) {
		if (firstCounter == countFirst) {
			while (secondCounter != countSecond) {
				insert(list, getName(listSecond, secondPosition), getPhone(listSecond, secondPosition), secondPosition, &errorCode);
				++secondPosition;
				++secondCounter;
			}
			break;
		}
		if (secondCounter == countSecond) {
			while (firstCounter != countFirst) {
				insert(list, getName(listFirst, firstPosition), getPhone(listFirst, firstPosition), firstPosition, &errorCode);
				++firstPosition;
				++firstCounter;
			}
			break;
		}
		if (strcmp(getName(listFirst, firstPosition), getName(listSecond, secondPosition)) < 0) {
			insert(list, getName(listFirst, firstPosition), getPhone(listFirst, firstPosition), firstPosition, &errorCode);
			++firstPosition;
			++firstCounter;
		} else {
			insert(list, getName(listSecond, secondPosition), getPhone(listSecond, secondPosition), secondPosition, &errorCode);
			++secondPosition;
			++secondCounter;
		}
	}
	return list;
}