#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Double linked list
*
* Operations implemented:
* List creation : done;
* Node insertion : done;
* List crossing : done;
* Search : done;
* Node interchange (adress interchange) : done (adjacent);
* Node deletion : done (recursively);
* List deletion done;
* List sorting : done;
*/

struct Order
{
	char* clientName;
	char* telNo;
	char* adress;
	int waitingTime;
	int carId;
};

struct Node
{
	Order info;

	Node* left;
	Node* right;
};

struct DoubleList
{
	Node* start;
	Node* end;
};

DoubleList rearInsertion(DoubleList list, Order info)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	
	newNode->info = info;
	newNode->right = 0;
	newNode->left = list.end;
	
	if (list.end == 0) // the list is empty
	{
		list.start = list.end = newNode;
	}
	else
	{
		list.end->right = newNode;
		list.end = newNode;
	}

	return list;
}

DoubleList frontInsertion(DoubleList list, Order info)
{
	Node* newNode = (Node*)malloc(sizeof(Node));

	newNode->info = info;
	newNode->left = 0;
	newNode->right = list.start;

	if (list.start == 0) // the list is empty
	{
		list.start = list.end = newNode;
	}
	else
	{
		list.start->left = newNode;
		list.start = newNode;
	}
	
	return list;
}

void printList(DoubleList list)
{
	if (list.end == 0)
	{
		printf("\nThe list is empty!");
	}
	else
	{
		Node* temp = list.start;
		printf("\nPrinting the list: ");
		while (temp)
		{
			printf("\nOrder machine id: %d, client name: %s, client no: %s, adress: %s waiting time: %d",
				temp->info.carId, temp->info.clientName, temp->info.telNo, temp->info.adress, temp->info.waitingTime);

			temp = temp->right;
		}
	}
}

void printListReverse(DoubleList list)
{
	if (list.end == 0)
	{
		printf("\nThe list is empty!");
	}
	else
	{
		Node* temp = list.end;

		printf("\nPrinting the list in reverse order: ");
		while (temp)
		{
			printf("\nOrder machine id: %d, client name: %s, client no: %s, adress: %s",
					 temp->info.carId, temp->info.clientName, temp->info.telNo, temp->info.adress);

			temp = temp->left;
		}
	}
}

void orderCount(DoubleList list, int carId)
{
	if (list.start == 0)
	{
		printf("\nThe list is empty: search stopped!");
	}
	else
	{
		int counter = 0;

		Node* temp = list.start;

		while (temp)
		{
			if (temp->info.carId == carId)
			{
				counter++;
				printf("\n[FOUND] Machine id: %d, client name: %s, client no: %s, adress: %s",
					   temp->info.carId, temp->info.clientName, temp->info.telNo, temp->info.adress);
			}

			temp = temp->right;
		}

		printf("\nMachines found with id %d : %d", carId, counter);
	}
}

DoubleList interchangeAdj(DoubleList list, int a, int b)
{
	if (list.start != 0 && list.start->right)
	{
		Node* p;
		Node* q;
		Node* r;

		// case 1
		if (a == 1)
		{
			p = list.start;
			q = p->right;
			r = q->right;

			p->right = r;
			p->left = q;

			q->right = p;
			q->left = 0;

			list.start = q;

			return list;
		}

		Node* s;
		Node* position = list.start;
		// positioning trying
		while (position->right && a > 2)
		{
			position = position->right;
			a--;
		}

		if (position->right->right)
		{
			p = position;
			q = p->right;
			r = q->right;
			s = r->right;

			p->right = r;
			r->left = p;
			r->right = q;

			q->left = r;
			q->right = s;

			if (s != 0)
				s->left = q;
		}

		return list;
	}
	else
	{
		printf("\n[ADJ INTERCHANGE] List is empty or has only one element!");
	}
}

//Node* deleteNode(Node* list, int carId)
//{
//	if (list == 0)
//		return 0;
//	
//	if (list->info.carId == carId)
//	{
//		Node* temp = list->right;
//
//		if (temp)
//			temp->left = list->left;
//
//		if (list->info.clientName != 0)
//			free(list->info.clientName);
//
//		if (list->info.adress != 0)
//			free(list->info.adress);
//
//		if (list->info.telNo != 0)
//			free(list->info.telNo);
//
//		free(list);
//		return temp;
//	}
//
//	list->right = deleteNode(list->right, carId);
//
//	return list;
//}
//
//DoubleList deleteNode(DoubleList list, int carId)
//{
//	if (list.start == 0)
//	{
//		printf("\n[NODE DELETION]The list is empty!");
//		return list;
//	}
//	else
//	{
//		Node* temp = list.start;
//		temp = deleteNode(temp, carId);
//
//		list.start = temp;
//	
//		while (temp->right)
//		{
//			temp = temp->right;
//		}
//
//		list.end = temp;
//
//		return list;
//	}
//}

Node* deleteNode(Node* node, int carId)
{
	if (node == 0)
		return 0;
	
	if (node->info.carId == carId)
	{
		Node* temp = node->right;
		if (temp)
			temp->left = node->left;

		if (node->info.clientName != 0)
			free(node->info.clientName);
		if (node->info.adress != 0)
			free(node->info.adress);
		if (node->info.telNo != 0)
			free(node->info.telNo);

		free(node);
		return temp;
	}

	node->right = deleteNode(node->right,carId);
	return node;
}

DoubleList deleteNode(DoubleList list, int carId)
{
	if (list.start == 0)
	{
		printf("\n[DELETION] List is empty!");
		return list;
	}
	else
	{
		Node* temp = list.start;

		temp = deleteNode(temp, carId);

		list.start = temp;
		while (temp->right)
			temp = temp->right;
		list.end = temp;

		return list;
	}
}

void swap(Node** a, Node** b)
{
	Node* temp = (Node*)malloc(sizeof(Node));

	temp->info = (*a)->info;

	(*a)->info = (*b)->info;
	(*b)->info = temp->info;

	free(temp);
}
Node* sort(Node* list)
{
	int sorted = 0;

	do
	{
		Node* temp = list;
		sorted = 0;

		while (temp->right)
		{
			if (temp->info.waitingTime > temp->right->info.waitingTime)
			{
				swap(&temp, &temp->right);
				sorted = 1;
			}

			temp = temp->right;
		}

		temp = 0;

	} while (sorted);

	return list;
}

DoubleList sort(DoubleList list)
{
	if (list.start == 0)
	{
		printf("\n[SORTING] The list is empty!");
		return list;
	}
	else
	{
		Node* temp = list.start;
		temp = sort(temp);

		list.start = temp;

		while (temp->right)
			temp = temp->right;

		list.end = temp;

		return list;
	}
}

Node* cleanMemory(Node* list)
{
	if (list == 0)
		return 0;
	
	Node* temp = list->right;

	if (list->info.clientName != 0)
		free(list->info.clientName);
	if (list->info.adress != 0)
		free(list->info.adress);
	if (list->info.telNo != 0)
		free(list->info.telNo);

	free(list);

	temp = cleanMemory(temp);

	return list;
}

DoubleList cleanMemory(DoubleList list)
{
	if (list.start == 0)
	{
		printf("\n[CLEAN MEMORY] List is empty!");
		return list;
	}
	else
	{
		Node* temp = list.start;
		temp = cleanMemory(temp);

		list.start = 0;
		list.end = 0;
	}
}

void main()
{
	FILE* f;
	Order com;
	DoubleList list;

	list.start = 0;
	list.end = 0;

	f = fopen("Orders.txt", "r");

	if (f)
	{
		char nameBuffer[64];
		char phoneBuffer[32];
		char adressBuffer[64];

		fscanf(f, "%d, %[^,], %[^,], %[^,], %d", &com.carId, nameBuffer, phoneBuffer, adressBuffer, &com.waitingTime);
		
		while (!feof(f))
		{
			com.clientName = (char*)malloc((strlen(nameBuffer) + 1) * sizeof(char));
			strcpy(com.clientName, nameBuffer);

			com.telNo = (char*)malloc((strlen(phoneBuffer) + 1) * sizeof(char));
			strcpy(com.telNo, phoneBuffer);

			com.adress = (char*)malloc((strlen(adressBuffer) + 1) * sizeof(char));
			strcpy(com.adress, adressBuffer);

			// insert the item into the double linked list
			list = rearInsertion(list, com);

			fscanf(f, "%d, %[^,], %[^,], %[^,], %d", &com.carId, nameBuffer, phoneBuffer, adressBuffer, &com.waitingTime);

		}
	}
	else
	{
		perror("[ERROR] Orders.txt");
	}

	printList(list);
	printListReverse(list);
	orderCount(list, 1);

	printf("\nAdjacent interchange: ");

	list = interchangeAdj(list, 4, 5);
	printList(list);

	printf("\nDelete node: ");
	list = deleteNode(list, 2);
	printList(list);

	printf("\nSorting the list by waiting time: ");
	list = sort(list);
	printList(list);

	printf("\nCleaning the list from memory");
	list = cleanMemory(list);

	printf("\n");
}