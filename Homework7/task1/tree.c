#include "tree.h"
#include <stdio.h>
#include <stdlib.h> 
#include <string.h>
#include <malloc.h>

typedef struct Node {
	int key;
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
 } Node;

typedef struct Tree {
	Node* root;
} Tree;

Node* nodeSearch(Node* node, const int key, int *errorCode) {
	if (node == NULL) {
		*errorCode = -1;
		return NULL;
	}
	if (node->key > key) {
		return node->leftChild;
	} 
	return node->rightChild;
}

int choiceChild(Node* node, const int key) {
	return node->key > key ? 1 : -1;
}

bool isLeftChild(Node* node, Node* parentNode ,int *errorCode) {
	if (node == NULL || parentNode == NULL) {
		*errorCode = -1;
		return false;
	}
	return parentNode->leftChild == node;
}

bool isRightChild(Node* node, Node* parentNode, int* errorCode) {
	if (node == NULL || parentNode == NULL) {
		*errorCode = -1;
		return false;
	}
	return parentNode->rightChild == node;
}

Tree* createTree(int *errorCode) {
	Tree* tree = malloc(sizeof(Tree));
	if (tree == NULL) {
		*errorCode = -1;
		return NULL;
	}
	tree->root = NULL;
	return tree;
}

void addElement(Tree* tree, const int key, const char* value, int *errorCode) {
	if (tree->root == NULL) {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->key = key;
		newNode->value = calloc(strlen(value) + 1, sizeof(char));
		if (newNode->value == NULL) {
			*errorCode = -1;
			return;
		}
		strcpy(newNode->value, value);
		newNode->rightChild = NULL;
		newNode->leftChild = NULL;
		tree->root = newNode;
		return;
	}
	Node* currentNode = tree->root;
	while (true) {
		if (nodeSearch(currentNode, key, errorCode) != NULL && currentNode->key != key) {
			currentNode = nodeSearch(currentNode, key, errorCode);
		} else {
			break;
		}
	}
	if (currentNode->key == key) {
		free(currentNode->value);
		currentNode->value = calloc(strlen(value) + 1, sizeof(char));
		if (currentNode->value == NULL) {
			*errorCode = -1;
			return;
		}
		strcpy(currentNode->value, value);
		return;
	}
	Node* newNode = malloc(sizeof(Node));
	if (newNode == NULL) {
		*errorCode = -1;
		return;
	}
	newNode->key = key;
	newNode->value = calloc(strlen(value) + 1, sizeof(char));
	if (newNode->value == NULL) {
		*errorCode = -1;
		return;
	}
	strcpy(newNode->value, value);
	newNode->leftChild = NULL;
	newNode->rightChild = NULL;
	if (choiceChild(currentNode, key) == 1) {
		currentNode->leftChild = newNode;
	} else {
		currentNode->rightChild = newNode;
	}
}

char* searchValueFromKey(Tree* tree, const int key) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return NULL;
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
	if (searchValueFromKey(tree, key) != NULL) {
		return true;
	}
	return false;
}

Node* theMostRightChild(Node* node) {
	Node* currentNode = node;
	if (currentNode->leftChild != NULL) {
		currentNode = currentNode->leftChild;
	}
	while (currentNode->rightChild != NULL) {
		currentNode = currentNode->rightChild;
	}
	return currentNode;
}

void deleteElement(Tree* tree, const int key, int* errorCode) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return;
		}
		if (key > currentNode->key && currentNode->rightChild->key != key) {
			currentNode = currentNode->rightChild;
		} else if (key < currentNode->key && currentNode->leftChild->key != key) {
			currentNode = currentNode->leftChild;
		} else {
			break;
		}
	}
	Node* nodeToDelete = tree->root;
	if (tree->root->key != key) {
		if (currentNode->leftChild->key == key) {
			nodeToDelete = currentNode->leftChild;
		} else if (currentNode->rightChild->key == key) {
			nodeToDelete = currentNode->rightChild;
		}
	}
	if (nodeToDelete->leftChild == NULL && nodeToDelete->rightChild == NULL) {
		if (isLeftChild(nodeToDelete, currentNode, errorCode) && *errorCode != -1) {
			currentNode->leftChild = NULL;
		} else if (isRightChild(nodeToDelete, currentNode, errorCode) && *errorCode != -1) {
			currentNode->rightChild = NULL;
		} else {
			tree->root = NULL;
		}
		free(nodeToDelete->value);
		free(nodeToDelete);
		nodeToDelete = NULL;
		return;
	}
	if (nodeToDelete->leftChild != NULL && nodeToDelete->rightChild == NULL) {
		if (nodeToDelete == tree->root) {
			tree->root = nodeToDelete->leftChild;

		} else {
			if (isLeftChild(nodeToDelete, currentNode, errorCode) && *errorCode != -1) {
				currentNode->leftChild = nodeToDelete->leftChild;
			}
			else if (isRightChild(nodeToDelete, currentNode, errorCode), *errorCode != -1) {
				currentNode->rightChild = nodeToDelete->leftChild;
			}
			else {
				return;
			}
		}
		free(nodeToDelete->value);
		free(nodeToDelete);
		nodeToDelete = NULL;
		return;
	}
	if (nodeToDelete->leftChild == NULL && nodeToDelete->rightChild != NULL) {
		if (nodeToDelete == tree->root) {
			tree->root = nodeToDelete->rightChild;
		} else {
			if (isLeftChild(nodeToDelete, currentNode, errorCode) && *errorCode != -1) {
				currentNode->leftChild = nodeToDelete->rightChild;
			}
			else if (*errorCode != -1) {
				currentNode->rightChild = nodeToDelete->rightChild;
			}
			else {
				return;
			}
		}
		free(nodeToDelete->value);
		free(nodeToDelete);
		nodeToDelete = NULL;
		return;
	}
	if (nodeToDelete->leftChild != NULL && nodeToDelete->rightChild != NULL) {
		Node* replacementNode = theMostRightChild(nodeToDelete);
		const int replacementKey = replacementNode->key;
		free(nodeToDelete->value);
		nodeToDelete->value = calloc(strlen(replacementNode->value) + 1, sizeof(char));
		if (nodeToDelete->value == NULL) {
			*errorCode = -1;
			return;
		}
		strcpy(nodeToDelete->value, replacementNode->value);
		deleteElement(tree, replacementNode->key, errorCode);
		nodeToDelete->key = replacementKey;
		if (*errorCode == -1) {
			return;
		}
	}
}

void deleteTreeRecursive(Node* node) {
	if (node == NULL) {
		return;
	}
	deleteTreeRecursive(node->leftChild);
	deleteTreeRecursive(node->rightChild);
	free(node->value);
	free(node);
	node = NULL;
}

void deleteTree(Tree** tree) {
	if ((*tree) == NULL) {
		return;
	}
	if ((*tree)->root == NULL) {
		free((*tree));
		tree = NULL;
		return;
	}
	deleteTreeRecursive((*tree)->root);
	free((*tree));
	*tree = NULL;
}
