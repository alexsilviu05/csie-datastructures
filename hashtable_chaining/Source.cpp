#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_DIM 250

enum TaskState
{
	OPEN = 0,
	PENDING = 1,
	DUPLICATED = 2,
	SOLVED = 3,
	CLOSED = 4,
	OTHER = 5
};

struct Task
{
	char* id;
	char* date;
	char* engineerName;
	int complexity;
	TaskState state;
};

struct Node
{
	Task info;
	Node* next;
};

Node* insertNode(Node* list, Task info)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = info;

	if (list == 0)
	{
		newNode->next = 0;
		return newNode;
	}
	else
	{
		Node* temp = list;
		while (temp->next)
			temp = temp->next;
		
		newNode->next = 0;
		temp->next = newNode;
	}

	return list;
}

int hash(char* string)
{
	int temp = 0;
	int position;

	for (unsigned int i = 0; i < strlen(string); i++)
	{
		temp += string[i];
	}

	position = temp % HT_DIM;

	return position;
}

Node** insertElement(Node* *HTable, Task t)
{
	int position;

	position = hash(t.engineerName);

	HTable[position] = insertNode(HTable[position], t);

	return HTable;
}

void printList(Node* list, int i)
{
	if (list)
	{
		if (list->next) // there are colisions
		{
			printf("\nColision group at index: %d", i);

			Node* temp = list;
			while (temp)
			{
				printf("\n[COLISIONED]Task[%s]: Engineer: %s, complexity:%d, state:%d",
					temp->info.id, temp->info.engineerName, temp->info.complexity, temp->info.state);

				temp = temp->next;
			}
		}
		else
		{
			printf("\nTask[%s]: Engineer: %s, complexity:%d, state:%d",
					list->info.id, list->info.engineerName, list->info.complexity, list->info.state);
		}
	}
}

Node* deleteClosed(Node* node)
{
	if (node == 0)
		return 0;

	if (node->info.state == CLOSED)
	{
		Node* temp = node->next;

		if (node->info.id != 0)
			free(node->info.id);
		if (node->info.date != 0)
			free(node->info.date);
		if (node->info.engineerName != 0)
			free(node->info.engineerName);

		free(node);
		node = 0;

		return temp;
	}

	node->next = deleteClosed(node->next);

	return node;
}

void writeTable(Node* *HTable)
{
	FILE *f;

	f = fopen("Tasks.csv", "w");

	if (f)
	{
		for (int i = 0; i < HT_DIM; i++)
		{
			if (HTable[i])
			{
				Node* temp = HTable[i];

				while (temp)
				{
					fprintf(f, "%d,%s,%s,%s,%d\n",
						temp->info.complexity, temp->info.id, temp->info.date, temp->info.engineerName,
						temp->info.state);
					temp = temp->next;
				}
			}
		}
	}
	else
	{
		printf("\nFile couldn't be opened!");
	}

	fclose(f);
}

void deleteClosed(Node* *HTable)
{
	for(int i = 0; i < HT_DIM; i++)
	{
		if (HTable[i])
			HTable[i] = deleteClosed(HTable[i]);
	}

	writeTable(HTable);
}

void printHTable(Node* *HTable)
{
	for (int i = 0; i < HT_DIM; i++)
	{
		if (HTable[i])
			printList(HTable[i],i);
	}
}

// se modifica inregistrari in htable
// se da numele vechi si numele nou
// se modifica inregistrarile, se recalculeaza hash si se reinsereaza nodul cu noul hash
void main()
{
	FILE* f;

	// creating space for hashtable
	Node* *HTable;
	HTable = (Node**)malloc(HT_DIM * sizeof(Node*));

	// initializing elements of hashtable with 0 == NULL
	for (int i = 0; i < HT_DIM; i++)
	{
		HTable[i] = 0;
	}


	Task t;

	f = fopen("Tasks.csv", "r");

	if (f)
	{
		char bufferId[64];
		char bufferDate[64];
		char bufferName[64];

		fscanf(f, "%d,%[^,],%[^,],%[^,],%d", &t.complexity, bufferId, bufferDate, bufferName, &t.state);
		while (!feof(f))
		{
			t.id = (char*)malloc((strlen(bufferId) + 1) * sizeof(char));
			strcpy(t.id, bufferId);

			t.date = (char*)malloc((strlen(bufferDate) + 1) * sizeof(char));
			strcpy(t.date, bufferDate);

			t.engineerName = (char*)malloc((strlen(bufferName) + 1) * sizeof(char));
			strcpy(t.engineerName, bufferName);

			// TO DO INSERTION HERE
			HTable = insertElement(HTable, t);

			fscanf(f, "%d,%[^,],%[^,],%[^,],%d", &t.complexity, bufferId, bufferDate, bufferName, &t.state);
		}
	}
	else
	{
		printf("\nOpening file error!");
	}

	fclose(f);

	printHTable(HTable);

	printf("\nDelete closed tasks from HTable: ");
	deleteClosed(HTable);
	printHTable(HTable);

	printf("\n");
}