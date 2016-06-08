#define  _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Recipe
{
	char* id;
	unsigned int itemsNo;
	char** itemsList;
	char* author;
};

struct Node
{
	Recipe info;
	Node* next;
};

Node* push(Node* stack, Recipe info)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = info;

	if (stack == 0)
	{
		newNode->next = 0;
		return newNode;
	}

	newNode->next = stack;

	return newNode;
}

void printStack(Node* stack)
{
	Node* temp = stack;

	while (temp)
	{
		printf("\nRecipe[%s] Author: %s, no of items: %d : ", temp->info.id, temp->info.author, temp->info.itemsNo);
		for (unsigned int i = 0; i < temp->info.itemsNo; i++)
		{
			printf("%s ", temp->info.itemsList[i]);
		}

		temp = temp->next;
	}
}

void main()
{
	FILE* f;
	Recipe r;
	Node* stack = 0;

	f = fopen("Recipes.txt", "r");

	if (f)
	{
		char bufferId[32];
		char bufferItems[124];
		char bufferAuthor[64];

		fscanf(f, "%d,%[^,],%[^,],%[^,\n]", &r.itemsNo, bufferId, bufferAuthor, bufferItems);
		while (!feof(f))
		{
			r.id = (char*)malloc((strlen(bufferId) + 1) * sizeof(char));
			strcpy(r.id, bufferId);

			r.author = (char*)malloc((strlen(bufferAuthor) + 1) * sizeof(char));
			strcpy(r.author, bufferAuthor);

			char* token;
			char separator[2] = ";";

			r.itemsList = (char**)malloc(r.itemsNo * sizeof(char*));

			char bufferTok[124];
			strcpy(bufferTok, bufferItems);

			token = strtok(bufferTok, separator);

			for (unsigned int i=0; i < r.itemsNo; i++)
			{
				r.itemsList[i] = (char*)malloc((strlen(token) + 1) * sizeof(char));
				strcpy(r.itemsList[i], token);

				token = strtok(0,separator);
			}

			stack = push(stack, r);

			fscanf(f, "%d,%[^,],%[^,],%[^,\n]", &r.itemsNo, bufferId, bufferAuthor, bufferItems);
		}
	}
	else
	{
		perror("[ERROR] Recipes.txt");
	}

	printStack(stack);

	printf("\n");
}