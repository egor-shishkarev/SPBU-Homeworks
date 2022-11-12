#include "list.h"

typedef struct Node {
	char* value;
	int count;
	Node* next;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
} List;

List* createList(void) {
	List* list = malloc(sizeof(List));
	if (list == NULL) {
		return -1;
	}
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void insertElement(List* list, const char* value) {
 	if (list->head == NULL) {
		Node* newNode = malloc(sizeof(Node));
		list->head = newNode;
		char* newValue = calloc(strlen(value), sizeof(char));
		strcpy(newValue, value);
		newNode->value = newValue;
		newNode->next = NULL;
		newNode->count = 1;
		list->tail = newNode;
		return;
	}
	Node* currentNode = list->head;
	while (currentNode != NULL) {
		if (strcmp(currentNode->value, value) == 0) {
			++(currentNode->count);
			return;
		}
		currentNode = currentNode->next;
	}
	Node* newNode = malloc(sizeof(Node));
	char* newValue = calloc(strlen(value), sizeof(char));
	strcpy(newValue, value);
	newNode->value = newValue;
	newNode->count = 1;
	list->tail->next = newNode;
	newNode->next = NULL;
	list->tail = newNode;
	return;
}

void printList(List* list) {
	Node* currentNode = list->head;
	while (currentNode != NULL) {
		printf("%s", currentNode->value);
		currentNode = currentNode->next;
	}
}