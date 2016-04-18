#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10 // variable for option number 1
#define MAXBUFFER 256 // max buffer for char vector

struct node
{
	int data;
	node *next;
} *front, *rear;

// function protypes
void adauga();
void sterge();
void marime_coada();
void check();
void f_element();
void catoi();

void main()
{
	int choice;

	while (1)
	{
		printf("enter the choice \n");
		printf("1 : create an empty queue \n2 : Insert element\n");
		printf("3 : Dequeue an element \n4 : Check if empty\n");
		printf("5. Get the first element of the queue\n");
		printf("6. Get the number of entries in the queue\n");
		printf("7. Call ASCI to int custom atoi function\n");
		printf("8. Exit\n");

		// menu driven program
		scanf("%d", &choice);
		switch (choice) 
		{
		case 1:
			printf("Empty queue is created with a capacity of %d\n", MAX);
			break;
		case 2:
			adauga();
			break;
		case 3:
			sterge();
			break;
		case 4:
			check();
			break;
		case 5:
			f_element();
			break;
		case 6:
			marime_coada();
			break;
		case 7:
			catoi();
			break;
		case 8:
			exit(0);
		default:
			printf("wrong choice\n");
			break;
		}
	}
}

// to insert elements in queue
void adauga()
{
	struct node *temp;

	temp = (struct node*)malloc(sizeof(node));
	printf("Enter value to be inserted \n");
	scanf("%d", &temp->data);
	temp->next = NULL;
	if (rear == NULL)
	{
		front = rear = temp;
	}
	else
	{
		rear->next = temp;
		rear = temp;
	}
}

// delete elements from queue
void sterge()
{
	struct node *temp;

	temp = front;
	if (front == NULL)
	{
		printf("queue is empty \n");
		front = rear = NULL;
	}
	else
	{
		printf("deleted element is %d\n", front->data);
		front = front->next;
		free(temp);
	}
}

// check if queue is empty or not
void check()
{
	if (front == NULL)
		printf("\nQueue is empty\n");
	else
		printf("\n*************** Elements are present in the queue **************\n");
}

// returns first element of queue
void f_element()
{
	if (front == NULL)
	{
		printf("\n**************** The queue is empty ****************\n");
	}
	else
		printf("\n**************** The front element is %d ***********\n", front->data);
}

// returns number of entries and displays the elements in queue
void marime_coada()
{
	struct node *temp;

	temp = front;
	int cnt = 0;
	if (front == NULL)
	{
		printf(" queue empty \n");
	}
	while (temp)
	{
		printf("%d  ", temp->data);
		temp = temp->next;
		cnt++;
	}
	printf("\n********* size of queue is %d ******** \n", cnt);
}

// extra function: check if it's number

bool esteNumeric(char x)
{
	return (x >= '0' && x <= '9') ? true : false;
}

// ASCII to int custom function
void catoi()
{
	char buffer[MAXBUFFER];
	
	int rezultat = 0;
	int semn =  1;
	int poz = 0;


	struct node *temp;

	printf("\nInsert the number: ");
	scanf("%s", buffer);

	if (buffer[0] == '-')
	{
		semn = -1;
		poz++;
	}
	if (buffer[0] == '+')
	{
		semn = 1;
		poz++;
	}

	for (; buffer[poz] != '\n'; poz++)
	{
		if (esteNumeric(buffer[poz]) == false)
		{
			return;
		}

		rezultat = buffer[poz] - '0';
		
		temp = (struct node*)malloc(sizeof(node));
		temp->data = semn * rezultat;

		temp->next = NULL;
		if (rear == NULL)
		{
			front = rear = temp;
		}
		else
		{
			rear->next = temp;
			rear = temp;
		}

	}
	
}