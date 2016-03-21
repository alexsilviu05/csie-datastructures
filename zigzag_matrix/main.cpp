#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <string.h>
#include <malloc.h>

/**
* Declaring the structure of the zigzag matrix
**/
struct matrix
{
	char** m;
	int* lines;
	int* collumns;
};

/**
* Getting away the default 0xcccccc values (VS2015)
**/
void create(matrix* _m)
{
	(*_m).lines = NULL;
	(*_m).collumns = NULL;
	(*_m).m = NULL;
}

/**
* Here comes the magic
* Initilization of the zigzag matrix
**/
void init(matrix* _m)
{
	// check world for validating exit status
	char check[7] = "finish";
	char buffer[256];

	// allocation for lines&collumns and initilization
	(*_m).lines = (int*)malloc(1 * sizeof(int));
	(*(*_m).lines) = 0;
	(*_m).collumns = (int*)malloc(1 * sizeof(int));
	(*(*_m).collumns) = 0;

	// some GUI stuf goes gere
	printf("Welcome to the jagged matrix generator! \n");
	printf("In order to exit the program, please enter the word \'finish\' \n");

	// obtaining input
	printf("\nEnter the word: ");
	gets_s(buffer,255);

	// looping while the input word != 'finish' (this is the execution status)
	while (strcmp(check,buffer) != 0)
	{
		// alocating a new vector of n+1 elements
		int* auxc = (int*)malloc(((*(*_m).lines)+1) * sizeof(int));
		// copying the values in new vector
		for (int i = 0; i < (*(*_m).lines); i++)
		{
			auxc[i] = (*_m).collumns[i];
		}
		// adding on the last position the number of chars of the input word
		auxc[(*(*_m).lines)] = (strlen(buffer) + 1);
		// eliberating memory
		free((*_m).collumns);
		// swaping addresses
		(*_m).collumns = auxc;

		// alocating a new vector of pointers of n+1 elements
		char** auxm = (char**)malloc(((*(*_m).lines) + 1) * sizeof(char*));
		// copying the adresses in new vector
		for (int i = 0; i < (*(*_m).lines); i++)
		{
			auxm[i] = (*_m).m[i];
		}
		// generating memory space for the input word
		auxm[(*(*_m).lines)] = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
		// insert the input word on the last position on the vector
		strcpy(auxm[(*(*_m).lines)], buffer);
		// freeing the vector of adresses, but the adresses inside are kept in the aux
		free((*_m).m);
		// making the magic swap
		(*_m).m = auxm;

		// incrementing the no of lines, because we had a new word to insert
		// ps sometimes I forgot to increment it, many hours spent on this situation in the past
		(*(*_m).lines) += 1;

		// getting input
		printf("\nEnter the word: ");
		gets_s(buffer, 255);
	}

	printf("Finish keyword detected! \n");

}

/**
* Display the result
**/
void display(matrix* _m)
{
	// minimal GUI items
	printf("Final matrix information: \n");
	printf("No of lines: %d \n", *(*_m).lines);

	printf("Matrix structure: \n");

	for (int i = 0; i < *(*_m).lines; i++)
	{
		printf("\n Line number [%d]: ", i);
		// must pay attention on (*_m).collumns[i]
		for (int j = 0; j < (*_m).collumns[i]; j++)
			printf("%c", (*_m).m[i][j]);
	}
}

/**
* Cleaning the garbage when the program completes:
* create, init, display
**/
void free(matrix* _m)
{
	// we had a matrix, so we must first delete the elements and then the vector
	for (int i = 0; i < *(*_m).lines; i++)
		free((*_m).m[i]);
	free((*_m).m);

	// easy job here
	free((*_m).lines);
	free((*_m).collumns);

	printf("\n Heap memory successfully freed.");
}

void main()
{
	matrix* pM = (matrix*)malloc(sizeof(matrix));

	create(pM);
	init(pM);
	display(pM);

	free(pM);

	printf("\n Goodbye! \n");
}