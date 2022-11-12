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

void addElement(List** hashTable, const char* value, const int hashSize) {
	const int position = hashFunction(value, hashSize);
	insertElement(hashTable[position], value);
}

int hashFunction(const char* value, const int hashSize) {
	const int stringSize = strlen(value);
	int result = 0;
	const int primeNumber = 23;
	for (int i = 0; i < stringSize; ++i) {
		result += (int)value[i] * pow(primeNumber, stringSize - i);
		result %= (hashSize - 1);
	}
	return result;
}

void printAllElements(List* list) {
	Node* node = list->head;
	while (node != NULL) {
		printf("%s - %d\n", node->value, node->count);
		node = node->next;
	}
}