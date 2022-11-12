#include "tree.h"

typedef struct Node {
	char* value;
	struct Node* leftChild;
	struct Node* rightChild;
	struct Node* parent;
} Node;

typedef struct Tree {
	Node* root;
} Tree;

char* getOperation(char* arrayOfSymbols) {
	char* newValue = calloc(2, sizeof(char));
	if (newValue == NULL) {
		return;
	}
	newValue[0] = arrayOfSymbols[1];
	return newValue;
}

char* getOperand1(char* arrayOfSymbols) {
	int numberOfOpenBrackets = 0;
	int numberOfClosedBrackets = 0;
	const int lengthOfString = strlen(arrayOfSymbols);
	for (int i = 0; i < lengthOfString; ++i) {
		if (arrayOfSymbols[i] == '(') { 
			++numberOfOpenBrackets;
		}
		else if (arrayOfSymbols[i] == ')') {
			++numberOfClosedBrackets;
		}
		if (numberOfOpenBrackets == numberOfClosedBrackets + 1 && numberOfOpenBrackets > 1) {
			char* operand1 = calloc(i - 3 + 2, sizeof(char));
			if (operand1 == NULL) {
				return -1;
			}
			for (int j = 2; j < i; ++j) {
				operand1[j - 2] = arrayOfSymbols[j + 1];
			}
			return operand1;
		}
	}
	if (numberOfClosedBrackets == numberOfOpenBrackets) {
		int currentPosition = 3;
		while (arrayOfSymbols[currentPosition] != ' ') {
			++currentPosition;
		}
		char* operand1 = calloc(currentPosition - 3 + 1, sizeof(char));
		if (operand1 == NULL) {
			return -1;
		}
		for (int i = 3; i < currentPosition; ++i) {
			operand1[i - 3] = arrayOfSymbols[i];
		}
		return operand1; 
	}
}

char* getOperand2(char* arrayOfSymbols) {
	int numberOfOpenBrackets = 0;
	int numberOfClosedBrackets = 0;
	int lengthOfString = strlen(arrayOfSymbols);
	for (int i = 0; i < lengthOfString; ++i) {
		if (arrayOfSymbols[i] == '(') {
			++numberOfOpenBrackets;
		}
		else if (arrayOfSymbols[i] == ')') {
			++numberOfClosedBrackets;
		}
		if (numberOfOpenBrackets == numberOfClosedBrackets + 1 && numberOfOpenBrackets > 1) {
			char* operand2 = calloc(lengthOfString - i - 2, sizeof(char));
			if (operand2 == NULL) {
				return -1;
			}
			for (int k = i + 2; k < lengthOfString - 1; ++k) {
				operand2[k - i - 2] = arrayOfSymbols[k];
			}
			return operand2;
		}
	}
	if (numberOfClosedBrackets == numberOfOpenBrackets) {
		int currentPosition = 3;
		while (arrayOfSymbols[currentPosition] != ' ') {
			++currentPosition;
		}
		char* operand2 = calloc(lengthOfString - 1 - currentPosition, sizeof(char));
		if (operand2 == NULL) {
			return -1;
		}
		for (int i = currentPosition + 1; i < lengthOfString - 1; ++i) {
			operand2[i - currentPosition - 1] = arrayOfSymbols[i];
		}
		return operand2; 
	}
}

void addPartToTree(Tree* tree, char* operation, char* operand1, char* operand2, Node* currentNode) {
	if (currentNode == NULL) {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return;
		}
		if (currentNode == tree->root) {
			tree->root = newNode;
			newNode->parent = NULL;
		}
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		currentNode = newNode;
	}
	char* newValue = calloc(2, sizeof(char));
	if (newValue == NULL) {
		return;
	}
	strcpy(newValue, operation);
	currentNode->value = newValue;
	if (operand1[0] == '(') {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return;
		}
		newNode->parent = currentNode;
		currentNode->leftChild = newNode;
		addPartToTree(tree, getOperation(operand1), getOperand1(operand1), getOperand2(operand1), newNode);
	}
	else {
		char* newValue = calloc(strlen(operand1) + 1, sizeof(char));
		strcpy(newValue, operand1);
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return;
		}
		newNode->parent = currentNode;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->value = newValue;
		currentNode->leftChild = newNode;
	}
	if (operand2[0] == '(') {
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return;
		}
		newNode->parent = currentNode;
		currentNode->rightChild = newNode;
		addPartToTree(tree, getOperation(operand2), getOperand1(operand2), getOperand2(operand2), newNode);
	}
	else {
		char* newValue = calloc(strlen(operand2) + 1, sizeof(char));
		strcpy(newValue, operand2);
		Node* newNode = malloc(sizeof(Node));
		if (newNode == NULL) {
			return;
		}
		newNode->parent = currentNode;
		newNode->leftChild = NULL;
		newNode->rightChild = NULL;
		newNode->value = newValue;
		currentNode->rightChild = newNode;
	}
}

void addElementsToTree(Tree* tree, char* arrayOfSymbols) {
	addPartToTree(tree, getOperation(arrayOfSymbols), getOperand1(arrayOfSymbols), getOperand2(arrayOfSymbols), tree->root);
}

Tree* createParseTree(void) {
	Tree* tree = malloc(sizeof(Tree));
	if (tree == NULL) {
		return -1;
	}
	tree->root = NULL;
	return tree;
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

long long int charToInt(char* number) {
	int currentPosition = 0;
	int result = 0;
	if (number[0] == '-') {
		currentPosition = 1;
	}
	while (number[currentPosition] != '\0') {
		result *= 10;
		result += (int)number[currentPosition] - 48;
		++currentPosition;
	}
	return result - 2 * result * (number[0] == '-');
}

bool isOperation(char* arrayOfSymbols) {
	return arrayOfSymbols[0] == '+' || arrayOfSymbols[0] == '-' || arrayOfSymbols[0] == '*' || arrayOfSymbols[0] == '/';
}

void treeTraversal(Node* node) {
	if (isOperation(node->value)) {
		printf("(%s ", node->value);
	}
	else {
		printf("%s ", node->value);
	}

	if (node->leftChild != NULL) {
		treeTraversal(node->leftChild);
	}
	if (node->rightChild != NULL) {
		treeTraversal(node->rightChild);
	}
	if (node->rightChild == NULL && node->parent->rightChild == node) {
		printf(") ");
	}
}

void treePrint(Tree* tree) {
	 treeTraversal(tree->root);
	 printf(isOperation(tree->root->rightChild->value) ? ")": "");
}

int calculateResult(Node* node, int* result) {
	if (isOperation(node->value)) {
		const char operation = (node->value)[0];
		switch (operation) {
		case '+': {
			*result = calculateResult(node->leftChild, result) + calculateResult(node->rightChild, result);
			break;
		}
		case '-': {
			*result = calculateResult(node->leftChild, result) - calculateResult(node->rightChild, result);
			break;
		}
		case '*': {
			*result = calculateResult(node->leftChild, result) * calculateResult(node->rightChild, result);
			break;
		}
		case '/': {
			*result = calculateResult(node->leftChild, result) / calculateResult(node->rightChild, result);
			break;
		}
		}
	}
	else if (node != NULL) {
		return charToInt(node->value);
	}
	return *result;
}

int treeResult(Tree* tree) {
	int result = 0;
	calculateResult(tree->root, &result);
	return result;
}
