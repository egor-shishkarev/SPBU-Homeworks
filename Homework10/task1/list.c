#include "list.h"

typedef struct Node {
	int number;
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

void insertElement(List* list, const int number) {
	if (list->head == NULL) {
		Node* newNode = malloc(sizeof(Node));
		list->head = newNode;
		newNode->next = NULL;
		newNode->number = number;
		list->tail = newNode;
		return;
	}
	Node* newNode = malloc(sizeof(Node));
	newNode->number = number;
	list->tail->next = newNode;
	newNode->next = NULL;
	list->tail = newNode;
	return;
}

void printList(List* list) {
	Node* currentNode = list->head;
	while (currentNode != NULL) {
		if (currentNode == list->head) {
			printf("[%d]: ", currentNode->number + 1);
			currentNode = currentNode->next;
			continue;
		}
		printf("%d ", currentNode->number + 1);
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
	free(node);

}

void deleteList(List* list) {
	deleteListRecursively(list->head);
	free(list);
	list = NULL;
}

