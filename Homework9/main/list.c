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

void insertElement(List* list, const char* value, const int count) {
 	if (list->head == NULL) {
		Node* newNode = malloc(sizeof(Node));
		list->head = newNode;
		char* newValue = calloc(strlen(value) + 1, sizeof(char));
		strcpy(newValue, value);
		newNode->value = newValue;
		newNode->next = NULL;
		newNode->count = count;
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
	char* newValue = calloc(strlen(value) + 1, sizeof(char));
	strcpy(newValue, value);
	newNode->value = newValue;
	newNode->count = 1;
	list->tail->next = newNode;
	newNode->next = NULL;
	list->tail = newNode;
	return;
}

void insertValue(Node* node, const int value) {

}

void printList(List* list) {
	Node* currentNode = list->head;
	while (currentNode != NULL) {
		printf("%s", currentNode->value);
		currentNode = currentNode->next;
	}
}

void deleteListRecursively(Node* node) {
	if (node == NULL) {
		return;
	}
	if (node->next != NULL) {
		deleteListRecursively(node->next);
	}
	free(node->value);
	node->value = NULL;
	free(node);

}

void deleteList(List** list) {
	deleteListRecursively((*list)->head);
	free((*list));
	*list = NULL;
}

void recursiveErase(Node* node) {
	if (node != NULL) {
		recursiveErase(node->next);
	} else {
		return;
	}
	node->count = 0;
	node->value = NULL;
	node->next = NULL;
	free(node);
}

void eraseList(List* list) {
	Node* currentNode = list->head;
	recursiveErase(currentNode);
	list->head = NULL;
}

bool isElementInList(List* list, const char* value) {
	Node* currentNode = list->head;
	while (currentNode != NULL) {
		if (strcmp(currentNode->value, value) == 0) {
			return true;
		}
		currentNode = currentNode->next;
	}
	return false;
}