#include "AVLTree.h"

typedef struct Node {
	int key;
	char* value;
	int balance;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
} Node;

typedef struct AVLTree {
	Node* root;
} AVLTree;

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

AVLTree* createTree(int* errorCode) {
	AVLTree* tree = malloc(sizeof(AVLTree));
	if (tree == NULL) {
		*errorCode = -1;
		return -1;
	}
	tree->root = NULL;
	return tree;
}

void addElement(AVLTree* tree, const int key, char* value, int* errorCode) {
	if (tree->root == NULL) {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->key = key;
		newNode->balance = 0;
		char* newValue = calloc(strlen(value) + 1, sizeof(char));
		if (newValue == NULL) {
			*errorCode = -1;
			return;
		}
		strcpy(newValue, value);
		newNode->value = newValue;
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
		if (currentNode->key == key) {
			char* newValue = calloc(strlen(value) + 1, sizeof(char));
			strcpy(newValue, value);
			free(currentNode->value);
			currentNode->value = newValue;
			return;
		}
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			*errorCode = -1;
			return;
		}
		newNode->key = key;
		char* newValue = calloc(strlen(value) + 1, sizeof(char));
		if (newValue == NULL) {
			*errorCode = -1;
			return;
		}
		strcpy(newValue, value);
		newNode->value = newValue;
		newNode->balance = 0;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->parent = currentNode;
		if (choiceChild(currentNode, key) == 1) {
			currentNode->leftChild = newNode;
		}
		else {
			currentNode->rightChild = newNode;
		}
		newNode->parent->balance += isLeftChild(newNode, errorCode) * (-2) + 1;
		if (newNode->parent->balance == 0) {
			return;
		} else {
			countingBalance(newNode->parent, errorCode);
		}
		if (balance(newNode, tree)->parent == NULL) {
			tree->root = balance(newNode, tree);
		}
	}
	return;
}

char* searchValueFromKey(AVLTree* tree, const int key) {
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode == NULL) {
			return "NULL";
		}
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		}
		else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		}
		else if (currentNode->key == key) {
			return currentNode->value;
		}
	}
}

bool isKeyInTree(AVLTree* tree, const int key) {
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
			return true;
		}
	}
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

void deleteElement(AVLTree* tree, const int key, int* errorCode) {
	if (!isKeyInTree(tree, key)) {
		return;
	}
	Node* currentNode = tree->root;
	while (true) {
		if (currentNode->key > key) {
			currentNode = currentNode->leftChild;
		}
		else if (currentNode->key < key) {
			currentNode = currentNode->rightChild;
		}
		else if (currentNode->key == key) {
			break;
		}
	}
	if (currentNode->rightChild == NULL && currentNode->leftChild == NULL) {
		if (currentNode == tree->root) {
			free(currentNode->value);
			currentNode->value = NULL;
			free(currentNode);
			tree->root = NULL;
			return;
		}
		if (isLeftChild(currentNode, errorCode) && !errorCode) {
			currentNode->parent->leftChild = NULL;
		}
		else {
			currentNode->parent->rightChild = NULL;
		}
		currentNode->key = NULL;
		currentNode->value = NULL;
		free(currentNode);
		return;
	}
	Node* replacementNode = theMostRightChild(currentNode);
	currentNode->key = replacementNode->key;
	free(currentNode->value);
	char* newValue = calloc(strlen(replacementNode->value) + 1, sizeof(char));
	if (newValue == NULL) {
		*errorCode = -1;
		return;
	}
	strcpy(newValue, replacementNode->value);
	currentNode->value = newValue;
	if (replacementNode->leftChild != NULL) {
		if (!isLeftChild(replacementNode, errorCode)) {
			replacementNode->parent->rightChild = replacementNode->leftChild;
		}
		else {
			currentNode->leftChild = replacementNode->leftChild;
			replacementNode->leftChild->parent = currentNode;
		}
	}
	else {
		if (isLeftChild(replacementNode, errorCode) && !errorCode) {
			replacementNode->parent->leftChild = NULL;
		}
		else {
			replacementNode->parent->rightChild = NULL;
		}
	}
	replacementNode->parent = NULL;
	free(replacementNode->value);
	replacementNode->value = NULL;
	free(replacementNode);
}

void deleteTreeRecursive(Node* node) { 
	if (node == NULL) {
		return;
	}

	deleteTreeRecursive(node->leftChild);
	deleteTreeRecursive(node->rightChild);

	free(node->value);
	node->value = NULL;
	free(node);
	node = NULL;
}

void deleteTree(AVLTree** tree) {
	if ((*tree) == NULL) {
		return;
	}
	deleteTreeRecursive((*tree)->root);
	free(*tree);
	*tree = NULL;
}

Node* smallLeftRotate(Node* a, AVLTree* tree) {
	Node* b = a->rightChild;
	Node* c = b->leftChild;
	b->leftChild = a;
	a->rightChild = c;
	if (c != NULL) {
		c->parent = a;
	}
	b->parent = a->parent;
	a->parent = b;
	if (a == tree->root) {
		tree->root = b;
	}
	b->balance = 0;
	return b;
}

Node* smallRightRotate(Node* a, AVLTree* tree) {
	Node* b = a->leftChild;
	Node* c = b->rightChild;
	b->rightChild = a;
	a->leftChild = c;
	if (c != NULL) {
		c->parent = a;
	}
	b->parent = a->parent;
	a->parent = b;
	if (a == tree->root) {
		tree->root = b;
	}
	return b;
}

Node* bigLeftRotate(Node* a, AVLTree* tree) {
	Node* b = a->rightChild;
	Node* c = b->leftChild;
	a->rightChild = c->leftChild;
	c->leftChild->parent = a;
	b->leftChild = c->rightChild;
	c->rightChild->parent = b;
	c->parent = a->parent;
	c->leftChild = a;
	a->parent = c;
	c->rightChild = b;
	b->parent = c;
	if (a == tree->root) {
		tree->root = c;
	}
	return c;
}

Node* bigRightRotate(Node* a, AVLTree *tree) {
	Node* b = a->leftChild;
	Node* c = b->rightChild;
	a->leftChild = c->rightChild;
	c->rightChild->parent = a;
	b->rightChild = c->leftChild;
	c->leftChild->parent = b;
	c->parent = a->parent;
	c->rightChild = a;
	a->parent = c;
	c->leftChild = b;
	b->parent = c;
	if (a == tree->root) {
		tree->root = c;
	}
	return c;
}

Node* balance(Node* node, AVLTree* tree) {
	if (node == NULL) {
		return;
	}
	if (node->balance == 2) {
		if (node->rightChild->balance >= 0)
			return smallLeftRotate(node, tree);
		return bigLeftRotate(node, tree);
	} else if (node->balance == -2) {
		if (node->leftChild->balance <= 0)
			return smallRightRotate(node, tree);
		return bigRightRotate(node, tree);
	} else {
		balance(node->parent, tree);
	}
	return node;
}

Node* countingBalance(Node* node, int *errorCode) {
	if (node->parent == NULL) {
		return;
	}
	if (isLeftChild(node, errorCode)) {
		--node->parent->balance;
	} else {
		++node->parent->balance;
	}
	countingBalance(node->parent, errorCode);
}


