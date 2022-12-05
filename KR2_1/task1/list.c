#include "list.h"

typedef struct Node {
	int number;
	Node* next;
	Node* previous;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
} List;

List* createList(int *errorCode) {
	List* list = malloc(sizeof(List));
	if (list == NULL) {
		*errorCode = -1;
		return;
	}
	list->head = NULL;
	list->tail = NULL;
	return list;
}

void insertElement(List* list, const int number, int *errorCode) {
	if (list->head == NULL) {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		list->head = newNode;
		newNode->next = NULL;
		newNode->previous = NULL;
		newNode->number = number;
		list->tail = newNode;
		return;
	}
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		*errorCode = -1;
		return;
	}
	newNode->number = number;
	newNode->previous = list->tail;
	list->tail->next = newNode;
	newNode->next = NULL;
	list->tail = newNode;
	return;
}

void deleteListRecursively(Node* node) {
	if (node == NULL) {
		return;
	}
	if (node->next != NULL) {
		deleteListRecursively(node->next);
	}
	node->number = NULL;
	free(node);

}

void deleteList(List* list) {
	deleteListRecursively(list->head);
	free(list);
	list = NULL;
}

bool isSymethric(List* list, int *errorCode) {
	Node* headNode = list->head;
	if (headNode == NULL) {
		*errorCode = -1;
		return false;
	}
	Node* tailNode = list->tail;
	if (tailNode == NULL) {
		*errorCode = -1;
		return false;
	}
	if (headNode == tailNode) {
		return true;
	}
	while (headNode != tailNode && headNode->previous != tailNode || (headNode->previous == NULL) || (tailNode->next == NULL)) {
		if (headNode->number != tailNode->number) {
			return false;
		}
		headNode = headNode->next;
		tailNode = tailNode->previous;
	}
	return true;
}