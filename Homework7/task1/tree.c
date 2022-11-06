#include "tree.h"
#include <malloc.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node {
	int key;
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
	//struct parent* Node;
 } Node;

typedef struct Tree {
	Node* root;
} Tree;

Node* nodeSearch(Node* node, const int key) {
	if (node->key > key) {
		return node->leftChild;
	} 
	return node->rightChild;
}

int choiceChild(Node* node, const int key) {
	return node->key > key ? 1 : -1;
}

Tree* createTree(void) {
	Tree* tree= malloc(sizeof(Tree));
	if (tree == NULL) {
		return;
	}
	tree->root = NULL;
	return tree;
}

void addElement(Tree* tree, const int key, char* value) {
	if (tree->root == NULL) {
		Node* newNode = malloc(sizeof(Node));
		newNode->key = key;
		newNode->value = value;
		newNode->rightChild = NULL;
		newNode->leftChild = NULL;
		tree->root = newNode;
	} else {
		Node* currentNode = tree->root;
		while (nodeSearch(currentNode, key) != NULL) {
			currentNode = nodeSearch(currentNode, key);
		}
		Node* newNode = malloc(sizeof(Node));
		newNode->key = key;
		newNode->value = value;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		if (choiceChild(currentNode, key) == 1) {
			currentNode->leftChild = newNode;
		} else {
			currentNode->rightChild = newNode;
		}
	}
	return;
}

char* searchValueFromKey(Tree* tree, const int key) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return "NULL";
		}
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		} else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		} else if (currentNode->key == key) {
			return currentNode->value;
		}
	}
}

bool isKeyInTree(Tree* tree, const int key) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return false;
		}
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		}
		else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		}
		else if (currentNode->key == key) {
			return tree;
		}
	}
}

char* theMostRightChild(Tree* tree) {
	Node* currentNode = tree->root;
	while (currentNode->rightChild != NULL) {
		currentNode = currentNode->rightChild;
	}
	return currentNode->value;
}