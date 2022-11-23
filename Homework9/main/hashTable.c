#include "hashTable.h"

typedef struct Node {
	char* value;
	int count;
	Node* next;
} Node;

typedef struct List {
	Node* head;
	Node* tail;
} List;

List** createTable(const int size) {
	List** hashTable = calloc(size, sizeof(List));
	for (int i = 0; i < size; ++i) {
		hashTable[i] = createList();
	}
	return hashTable;
}

void deleteTable(List** hashTable, const int hashSize) {
	for (int i = 0; i < hashSize; ++i) {
		deleteList(&hashTable[i]);
	}
	free((*hashTable));
}

List** increaseTable(List** hashTable, const int hashSize, const int newSize, int *errorCode) {
	hashTable = (List**)realloc(hashTable, sizeof(List) * newSize);
	for (int i = hashSize; i < newSize; ++i) {
		hashTable[i] = createList();
	}
	List** additionalTable = createTable(hashSize);
	for (int i = 0; i < hashSize; ++i) {
		Node* currentNode = hashTable[i]->head;
		while (currentNode != NULL) {
			addElement(additionalTable, currentNode->value, currentNode->count, hashSize);
			currentNode = currentNode->next;
		}
	}
	for (int i = 0; i < hashSize; ++i) {
		eraseList(hashTable[i]);
	}
	for (int i = 0; i < hashSize; ++i) {
		Node* currentNode = additionalTable[i]->head;
		while (currentNode != NULL) {
			addElement(hashTable, currentNode->value, currentNode->count, newSize);
			currentNode = currentNode->next;
		}
	}
	deleteTable(additionalTable, hashSize);
	return hashTable;
}

unsigned long long hashFunction(const char* value, const int hashSize) {
	const int stringSize = strlen(value);
	unsigned long long result = 0;
	const int primeNumber = 23;
	for (int i = 0; i < stringSize; ++i) {
		result += (unsigned long long)value[i] * pow(primeNumber, stringSize - i);
	}
	result = abs(result);
	return result;
}

void addElement(List** hashTable, const char* value, const int count, const int hashSize) {
	unsigned long long position = hashFunction(value, hashSize);
	position %= hashSize;
	while (true) {
		if (hashTable[position]->head == NULL) {
			break;
		}
		if (strcmp(hashTable[position]->head->value, value) == 0) {
			break;
		}
		position = (position + 1) % hashSize;
	}
	insertElement(hashTable[position], value, count);
}

void printAllElements(List* list) {
	Node* node = list->head;
	while (node != NULL) {
		printf("%s - %d\n", node->value, node->count);
		node = node->next;
	}
}

int depthOfList(List* list) {
	int depth = 0;
	Node* node = list->head;
	while (node != NULL) {
		++depth;
		node = node->next;
	}
	return depth;
}

