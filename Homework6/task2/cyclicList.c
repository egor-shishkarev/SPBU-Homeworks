#include "cyclicList.h"
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

typedef struct Node {
	int value;
	int position;
	struct Node* next;
	struct Node* previous;
} Node;

typedef struct List {
	Node* head;
} List;

typedef struct Position {
	Node* position;
} Position;

List* createList(void) {
	List* temp = malloc(sizeof(List));
	temp->head = NULL;
	return temp;
}

Position* createPosition(List* list) {
	if (list == NULL) {
		return NULL;
	}
	Position* temp = malloc(sizeof(Position));
	temp->position = list->head;
	return temp;
}

int deletePosition(List* list, Position* position, int* errorCode) {
	position->position->previous->next = position->position->next;
	position->position->next->previous = position->position->previous;
	if (position->position == list->head) {
		list->head = position->position->next;
	}

	int temp = position->position->value;
	Node* nextElement = position->position->next;
	free(position->position);
	position->position = nextElement;

	return temp;
}

void deletePositionMemory(Position** position) {
	free(*position);
	*position = NULL;
}

int getNextPosition(Position* position) {
	if (position == NULL) {
		return -1;
	}
	position->position = position->position->next;
	return 0;
}

void increasePosition(Node* next, List *list) {
	Node* temp = next;
	while (temp != list->head->previous) {
		++(temp->position);
		temp = temp->next;
	}
	++(list->head->previous->position);
}

Node* findPosition(List* list, const int position) {
	if (list == NULL || list->head == NULL) {
		return NULL;
	}
	Node* temp = list->head;
	while (temp->position != position) {
		if (temp->next == NULL) {
			return NULL;
		}
		temp = temp->next;
	}
	return temp;
}

bool oneLeft(List* list) {
	return list->head == list->head->next; // Последний оставшийся элемент в циклическом списке указывает на самого себя
}

int insert(List* list, const int value, const int position) {
	if (list->head == NULL) { // Создаем новый узел, если список пуст
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return -1;
		}
		newNode->value = value;
		newNode->position = position;
		newNode->next = newNode;
		newNode->previous = newNode;
		list->head = newNode;
		return 0;
	}
	if (position < 0 || position > list->head->previous->position + 1) { // То есть переданная позиция больше хотя бы на два чем "последняя" позиция циклического списка
		return 1;
	}

	if (position == list->head->previous->position + 1) { // Если позиция больше на 1, то создаем новый узел и распределяем значения между граничными узлами для их связки
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return -1;
		}
		newNode->value = value;
		newNode->position = position;
		newNode->next = list->head;
		newNode->previous = list->head->previous;
		list->head->previous = newNode;
		list->head->previous->next = newNode;
		return 0;
	}

	Node* currentNode = findPosition(list, position);
	if (currentNode == NULL) {
		return -1;
	}
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		return -1;
	}
	newNode->value = value;
	newNode->position = position;
	currentNode->previous->next = newNode;
	currentNode->next->previous = newNode;
	newNode->previous = currentNode->previous;
	newNode->next = currentNode;
	if (position == 0) {
		list->head = newNode;
	}
	increasePosition(newNode->next, list);
}

void clearList(List** list) {
	Node* next = (*list)->head;
	while (next != (*list)->head) {
		(*list)->head = (*list)->head->next;
		free(next);
		next = (*list)->head;
	}
	free(*list);
	(*list) = NULL;
}