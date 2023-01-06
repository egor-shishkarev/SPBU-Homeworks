#include "tree.h"

typedef struct Node {
	int key;
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
 } Node;

typedef struct Tree {
	Node* root;
} Tree;

Node* nodeSearch(Node* node, const int key, int *errorCode) {
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

bool isLeftChild(Node* node, int *errorCode) {
	if (node == NULL || node->parent == NULL) {
		*errorCode = -1;
		return;
	}
	return node->parent->leftChild == node;
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
	} else {
		Node* currentNode = tree->root;
		while (true) {
			if (nodeSearch(currentNode, key, errorCode) != NULL && currentNode->key != key) {
				currentNode = nodeSearch(currentNode, key, errorCode);
			} else { 
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
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->parent = currentNode;
		if (choiceChild(currentNode, key) == 1) {
			currentNode->leftChild = newNode;
		} else {
			currentNode->rightChild = newNode;
		}
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

void deleteElement(Tree* tree, const int key, int *errorCode) {
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
			free(currentNode);
			tree->root = NULL;
			return;
		}
		if (isLeftChild(currentNode, errorCode) && !errorCode) {
			currentNode->parent->leftChild = NULL;
		} else {
			currentNode->parent->rightChild = NULL;
		}
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
		} else {
			currentNode->leftChild = replacementNode->leftChild;
			replacementNode->leftChild->parent = currentNode;
		}
	} else {
		if (isLeftChild(replacementNode, errorCode) && !errorCode) {
			replacementNode->parent->leftChild = NULL;
		} else {
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

void deleteTree(Tree** tree) {
	if ((*tree) == NULL) {
		return;
	}
	deleteTreeRecursive((*tree)->root);
	free(*tree);
	*tree = NULL;
}
