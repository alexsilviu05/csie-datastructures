#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Client
{
	unsigned int id;
	char* name;
	float budget;
	int duration;
	float cost;
};

struct Node
{
	Client info;
	int BF;

	Node* left;
	Node* right;
};

struct StackNode
{
	Client info;
	StackNode* next;
};

StackNode* push(StackNode* stack, Client info)
{
	StackNode* newElement = (StackNode*)malloc(sizeof(StackNode));

	newElement->info = info;
	
	if (stack)
	{
		newElement->next = stack;
	}
	else
	{
		newElement->next = 0;
	}

	return newElement;
}

int max(int a, int b)
{
	return a > b ? a : b;
}

int H(Node* avl)
{
	if (avl == 0)
		return 0;
	else
	{
		return 1 + max(H(avl->left), H(avl->right));
	}
}

void computeBF(Node* avl)
{
	if (avl)
	{
		avl->BF = H(avl->right) - H(avl->left);
	}
}

Node* simpleRight(Node* pivot, Node* leftChild)
{
	pivot->left = leftChild->right;
	computeBF(pivot);

	leftChild->right = pivot;
	computeBF(leftChild);

	return leftChild;
}

Node* simpleLeft(Node* pivot, Node* rightChild)
{
	pivot->right = rightChild->left;
	computeBF(pivot);

	rightChild->left = pivot;
	computeBF(rightChild);

	return rightChild;
}

Node* doubleRightLeft(Node* pivot, Node* rightChild)
{
	pivot->right = simpleRight(rightChild, rightChild->left);
	computeBF(pivot);

	rightChild = pivot->right;
	rightChild = simpleRight(pivot, rightChild);
	computeBF(rightChild);

	return rightChild;
}

Node* doubleLeftRight(Node* pivot, Node* leftChild)
{
	pivot->left = simpleLeft(leftChild, leftChild->right);
	computeBF(pivot);

	leftChild = pivot->left;
	leftChild = simpleRight(pivot, leftChild);
	computeBF(leftChild);

	return leftChild;
}

Node* insertElement(Node* avl, Client info)
{
	if (avl)
	{
		if (avl->info.id < info.id)
			avl->right = insertElement(avl->right, info);
		if (avl->info.id >= info.id)
			avl->left = insertElement(avl->left, info);
	}
	else
	{
		Node* newElement = (Node*)malloc(sizeof(Node));

		newElement->info = info;

		newElement->left = 0;
		newElement->right = 0;

		avl = newElement;
	}

	// compute BF
	computeBF(avl);

	// do balancing
	if (avl->BF == 2)
	{
		if (avl->right->BF == -1)
		{
			avl = doubleRightLeft(avl, avl->right);
		}
		else
		{
			avl = simpleLeft(avl, avl->right);
		}
	}
	else if (avl->BF == -2)
	{
		if (avl->left->BF == 1)
		{
			avl = doubleLeftRight(avl, avl->left);
		}
		else
		{
			avl = simpleRight(avl, avl->left);
		}
	}

	return avl;
}

void printInordine(Node* avl)
{
	if (avl == 0)
		return;

	printInordine(avl->left);
	printf("\nClient [%d] : %s", avl->info.id, avl->info.name);
	printInordine(avl->right);
}

void printPreordine(Node* avl)
{
	if (avl == 0)
		return;

	printf("\nClient [%d] : %s", avl->info.id, avl->info.name);
	printPreordine(avl->left);
	printPreordine(avl->right);
}

void printDiference(Node* element)
{
	float sum;

	sum = element->info.budget - element->info.cost;

	if (sum < 0)
	{
		printf("\n[%s]Budget passed with %5.2f", element->info.name, sum);
	}
	else
	{
		printf("\n[%s]Budget remaining: %5.2f", element->info.name, sum);
	}
}

void computeDifference(Node* avl)
{
	if (avl == 0)
		return;

	computeDifference(avl->left);
	printDiference(avl);
	computeDifference(avl->right);
}

StackNode* pushToStack(Node* avl, StackNode* stack)
{
	if (avl)
	{
		if (avl->left == 0 && avl->right == 0)
		{
			stack = push(stack, avl->info);
			return stack;
		}

		stack = pushToStack(avl->left,stack);
		stack = pushToStack(avl->right,stack);
	}

	return stack;
}

int checkDeb(Node* avl)
{
	if ((avl->info.budget - avl->info.cost) < 0)
		return 1;
	else
		return 0;
}
int getDebtors(Node* avl)
{
	if (avl == 0)
		return 0;

	if (checkDeb(avl) == 1)
		return 1;

	return getDebtors(avl->left) + getDebtors(avl->right);
}

void main()
{
	FILE* f;

	Client c;
	Node* AVL = 0;
	StackNode* stack = 0;

	f = fopen("Clients.txt", "r");

	if (f)
	{
		char nameBuffer[64];

		fscanf(f, "%d,%[^,],%f,%d,%f",
			&c.id, nameBuffer, &c.budget, &c.duration, &c.cost);

		while (!feof(f))
		{
			c.name = (char*)malloc((strlen(nameBuffer) + 1) * sizeof(char));
			strcpy(c.name, nameBuffer);

			// TO DO INSERTION HERE
			AVL = insertElement(AVL, c);

			fscanf(f, "%d,%[^,],%f,%d,%f",
				&c.id, nameBuffer, &c.budget, &c.duration, &c.cost);
		}
	}
	else
	{
		perror("[ERROR] Clients.txt");
	}

	fclose(f);

	printf("\nInordine: ");
	printInordine(AVL);

	printf("\nPreordine: ");
	printPreordine(AVL);

	printf("\nCompute funds: ");
	computeDifference(AVL);

	stack = pushToStack(AVL, stack);

	printf("\nDebtors number: %d", getDebtors(AVL));

	printf("\n");
}