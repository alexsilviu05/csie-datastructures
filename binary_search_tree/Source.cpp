#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Source
{
	PHONE = 1,
	ONLINE = 2,
	SHOWROOM = 3
};

enum State
{
	PENDING = 1,
	CONFIRMED = 2,
	DELIVERED = 3,
	EXECUTED = 4
};

struct Order
{
	unsigned int id;
	char* clientName;
	int noProducts;
	float value;
	Source source;
	State state;
};

struct Node
{
	Order info;

	Node* left;
	Node* right;
};

// passing the structure via levels
struct pNode
{
	Node* node;
	pNode* next;
};

//Node* insertElement(Node* t, Order info)
//{
//	if (t == 0)
//	{
//		Node* newElement = (Node*)malloc(sizeof(Node));
//
//		newElement->info = info;
//
//		newElement->left = 0;
//		newElement->right = 0;
//
//		t = newElement;
//	}
//
//	if (t->info.id > info.id)
//		t->left = insertElement(t->left, info);
//	if (t->info.id < info.id)
//		t->right = insertElement(t->right, info);
//	if (t->info.id == info.id)
//		printf("\nDuplicated key[%d] not inserted!", info.id);
//
//	return t;
//}

Node* insertElement(Node* t, Order info)
{
	if (t == 0)
	{
		Node* newElement = (Node*)malloc(sizeof(Node));

		newElement->info = info;

		newElement->left = 0;
		newElement->right = 0;

		t = newElement;

		return t;
	}

	if (t->info.id < info.id)
		t->right = insertElement(t->right, info);
	if (t->info.id > info.id)
		t->left = insertElement(t->left, info);
	if (t->info.id == info.id)
		printf("\nDuplicated key[%d] not inserted!", info.id);

	return t;
}

void printInordine(Node* tree)
{
	if (tree == 0)
		return;

	printInordine(tree->left);

	printf("\nOrder [%d]: %s, noProd: %d, orderValue: %f, source: %d, state: %d",
		tree->info.id, tree->info.clientName, tree->info.noProducts, tree->info.value,
		tree->info.source, tree->info.state);

	printInordine(tree->right);
}


void printPostOrdine(Node* tree)
{
	if (tree == 0)
		return;

	printPostOrdine(tree->left);
	printPostOrdine(tree->right);
	printf("\nOrder [%d]: %s, noProd: %d, orderValue: %f, source: %d, state: %d",
		tree->info.id, tree->info.clientName, tree->info.noProducts, tree->info.value,
		tree->info.source, tree->info.state);
}

void printPreOrdine(Node* tree)
{
	if (tree == 0)
		return;

	printf("\nOrder [%d]: %s, noProd: %d, orderValue: %f, source: %d, state: %d",
		tree->info.id, tree->info.clientName, tree->info.noProducts, tree->info.value,
		tree->info.source, tree->info.state);
	printPreOrdine(tree->left);
	printPreOrdine(tree->right);
}

// find the number of leafs in the structure
int leafNumber(Node* tree)
{
	if (tree)
	{
		if (tree->left == 0 && tree->right == 0)
			return 1;
		return leafNumber(tree->left) + leafNumber(tree->right);
	}

	return 0;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int height(Node* tree)
{
	if (tree == 0)
		return 0;

	return 1 + max(height(tree->left), height(tree->right));
}

pNode* put(pNode* vector, Node* element)
{
	pNode* newNode = (pNode*)malloc(sizeof(pNode));

	newNode->node = element;
	newNode->next = 0;

	if (vector == 0)
	{
		return newNode;
	}

	pNode* temp = vector;
	while (temp->next)
		temp = temp->next;

	temp->next = newNode;

	return vector;
}

void levelParsing(Node* tree, int level, pNode* *vector)
{
	if (tree)
	{
		levelParsing(tree->left, level + 1, vector);
		vector[level - 1] = put(vector[level - 1], tree);
		levelParsing(tree->right, level + 1, vector);
	}
}

void main()
{
	FILE* f;
	Order info;

	Node* tree = 0;

	f = fopen("Orders.txt", "r");

	if (f)
	{
		char bufferName[32];

		fscanf(f, "%d,%[^,],%d,%f,%d,%d",
			   &info.id, bufferName, &info.noProducts, &info.value, &info.source, &info.state);

		while (!feof(f))
		{
			info.clientName = (char*)malloc((strlen(bufferName) + 1) * sizeof(char));
			strcpy(info.clientName, bufferName);

			// Insertion
			tree = insertElement(tree, info);

			fscanf(f, "%d,%[^,],%d,%f,%d,%d",
				&info.id, bufferName, &info.noProducts, &info.value, &info.source, &info.state);
		}
	}
	else
	{
		perror("[ERROR] Orders.txt");
	}

	printf("\nInordine: ");
	printInordine(tree);

	printf("\nPostordine: ");
	printPostOrdine(tree);

	printf("\nPreordine: ");
	printPreOrdine(tree);

	printf("\nNo of leafs: %d", leafNumber(tree));

	printf("\nTree height: %d", height(tree));

	int treeHeight = height(tree);
	pNode* *vector = (pNode**)malloc(treeHeight * sizeof(pNode));
	for (int i = 0; i < treeHeight; i++)
		vector[i] = 0;

	levelParsing(tree, 1, vector);

	printf("\nPrinting elements by leveling up the structure: ");
	for (int i = 0; i < treeHeight; i++)
	{
		printf("\nLevel %d: ", i+1);

		pNode* temp = vector[i];
		while (temp)
		{
			printf("\n%s", temp->node->info.clientName);
			temp = temp->next;
		}
	}

	
	printf("\n");
}