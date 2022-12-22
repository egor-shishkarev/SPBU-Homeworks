#include "cyclicList.h"
#include <stdio.h>
#include <malloc.h>

typedef struct Node {
	int position;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct List {
	Node* head;
} List;

List* createCyclicList(int* errorCode) {
	List* list = malloc(sizeof(List));
	if (list == NULL) {
		*errorCode = -1;
		return;
	}
	list->head = NULL;
	return list;
}

int insertElement(List* list, const int position, int* errorCode) {
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
		newNode->next = newNode;
		newNode->previous = newNode;
		list->head = newNode;
	}
	else {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->position = position;
		newNode->next = list->head->next;
		newNode->previous = list->head;
		list->head->next->previous = newNode;
		list->head->next = newNode;
	}
}

int deleteElement(List* list, const int gap, int* errorCode) {
	if (list == NULL || list->head == NULL) {
		*errorCode = -1;
		return;
	}
	Node* temp = list->head->next;
	for (int i = 0; i < gap; ++i) {
		temp = temp->previous;
	}
	temp->next->previous = temp->previous;
	temp->previous->next = temp->next;
	list->head = temp->previous;
	free(temp);
}

int lastPosition(List* list, int *errorCode) {
	if (list == NULL || list->head == NULL) {
		*errorCode = -1;
		return;
	}
	return list->head->position;
}

void deleteList(List* list) {
	free(list->head);
	free(list);
}