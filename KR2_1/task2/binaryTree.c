#include "binaryTree.h"

typedef struct Node {
	int key;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

Node* nodeSearch(Node* node, const int key, int* errorCode) {
	if (node == NULL) {
		*errorCode = -1;
		return;
	}
	if (node->key > key) {
		return node->leftChild;
	}
	return node->rightChild;
}

int choiceChild(Node* node, const int key) {
	return node->key > key ? 1 : -1;
}

bool isLeftChild(Node* node, int* errorCode) {
	if (node == NULL || node->parent == NULL) {
		*errorCode = -1;
		return;
	}
	if (node->parent->leftChild == node) {
		return true;
	}
	return false;
}

Tree* createTree(int* errorCode) {
	Tree* tree = malloc(sizeof(Tree));
	if (tree == NULL) {
		*errorCode = -1;
		return -1;
	}
	tree->root = NULL;
	return tree;
}

void addElement(Tree* tree, const int key, int* errorCode) {
	if (tree->root == NULL) {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->key = key;
		newNode->rightChild = NULL;
		newNode->leftChild = NULL;
		newNode->parent = NULL;
		tree->root = newNode;
	}
	else {
		Node* currentNode = tree->root;
		while (true) {
			if (nodeSearch(currentNode, key, errorCode) != NULL && currentNode->key != key) {
				currentNode = nodeSearch(currentNode, key, errorCode);
			}
			else {
				break;
			}
		}
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->key = key;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->parent = currentNode;
		if (choiceChild(currentNode, key) == 1) {
			currentNode->leftChild = newNode;
		}
		else {
			currentNode->rightChild = newNode;
		}
	}
	return;
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

void deleteTreeRecursive(Node* node) {
	if (node == NULL) {
		return;
	}

	deleteTreeRecursive(node->leftChild);
	deleteTreeRecursive(node->rightChild);

	free(node);
	node = NULL;
}

void deleteTree(Tree* tree) {
	if (tree == NULL) {
		return;
	}
	deleteTreeRecursive(tree->root);
	free(tree);
	tree = NULL;
}

void directOrderRecursive(Node* currentNode, int* arrayOfElements, int* currentCount) {
	if (currentNode == NULL) {
		return;
	}
	directOrderRecursive(currentNode->leftChild, arrayOfElements, currentCount);
	arrayOfElements[*currentCount] = currentNode->key;
	++(* currentCount);
	directOrderRecursive(currentNode->rightChild, arrayOfElements, currentCount);
}

void directOrder(Tree* tree, int* arrayOfElements) {
	int currentCount = 0;
	directOrderRecursive(tree->root, arrayOfElements, &currentCount);
}

void binaryTreeSort(int* arrayOfNumbers, const int sizeOfArray) {
	int errorCode = 0;
	Tree* tree = createTree(&errorCode);
	for (int i = 0; i < sizeOfArray; ++i) {
		addElement(tree, arrayOfNumbers[i], &errorCode);
	}
	directOrder(tree, arrayOfNumbers);
	deleteTree(tree);
}