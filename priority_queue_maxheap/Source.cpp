#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum Status
{
	CONFIRMED = 1,
	PENDING = 2
};

enum Channel
{
	PHONE = 1,
	APPLICATION = 2
};

struct Reservation
{
	int id;
	char* clientName;
	char* phoneNumber;
	unsigned duration;
	Channel channel;
	Status status;
};

struct Heap
{
	Reservation *res;
	int dim;
};

struct Stack
{
	Reservation info;
	Stack* next;
};

Stack* push(Stack* stack, Reservation info)
{
	Stack* newNode = (Stack*)malloc(sizeof(Stack));
	newNode->info = info;

	if (stack == 0)
	{
		newNode->next = 0;
	}
	else
	{
		newNode->next = stack;
	}

	return newNode;
}

void filtrationRecap(Heap queue, int index)
{
	int N = index;
	int left = 2 * N + 1;
	int right = 2 * N + 2;

	if (left < queue.dim && queue.res[N] < queue.res[left])
		N = left;
	if (right < queue.dim && queue.res[N] < queue.res[right])
		N = right;

	if (N != index)
	{
		Reservation temp = queue.res[index];

		queue.res[index] = queue.res[N];
		queue.res[N] = temp;

		filtrationRecap(queue, N);
	}
}

void filtration(Heap queue, int index)
{
	int N = index;
	int left = 2 * N + 1;
	int right = 2 * N + 2;

	if (left < queue.dim && queue.res[N].duration < queue.res[left].duration)
	{
		N = left;
	}
	if (right < queue.dim && queue.res[N].duration < queue.res[right].duration)
	{
		N = right;
	}

	if (index != N)
	{
		Reservation temp = queue.res[index];

		queue.res[index] = queue.res[N];
		queue.res[N] = temp;

		filtration(queue, N);
	}
}

void insertElement(Heap* queue, Reservation res)
{
	Reservation *newArray = (Reservation*)malloc(((*queue).dim + 1) * sizeof(Reservation));

	for (int i = 0; i < (*queue).dim; i++)
	{
		newArray[i] = (*queue).res[i];
	}

	newArray[(*queue).dim] = res;
	(*queue).dim++;

	free((*queue).res);
	(*queue).res = newArray;

	// TO DO FILTRATION HERE
	for (int i = ((*queue).dim - 1) / 2; i >= 0; i--)
	{
		filtration((*queue), i);
	}
}

void printRaport(Heap queue)
{
	FILE* f;

	f = fopen("Raport.txt", "w");

	if (f)
	{
		for (int i = 0; i < queue.dim; i++)
		{
			if (queue.res[i].status == PENDING)
			{
				fprintf(f, "%d,%s,%s,%d,%d,%d\n",
					queue.res[i].id, queue.res[i].clientName, queue.res[i].phoneNumber,
					queue.res[i].duration, queue.res[i].channel, queue.res[i].status);
			}
		}
	}

	fclose(f);
}

Stack* extractElement(Heap* queue, Stack* stack)
{
	Reservation temp;

	temp = queue->res[0];

	if (temp.status == CONFIRMED)
	{
		queue->res[0] = queue->res[queue->dim - 1];
		queue->res[queue->dim - 1] = temp;

		Reservation *newArray = (Reservation*)malloc((queue->dim - 1) * sizeof(Reservation));
		for (int i = 0; i < queue->dim - 1; i++)
		{
			newArray[i] = queue->res[i];
		}
		queue->dim--;
		free(queue->res);
		queue->res = newArray;

		stack = push(stack, temp);

		for (int i = (queue->dim - 1) / 2; i >= 0; i--)
		{
			filtration(*queue, i);
		}
	}

	return stack;
}

void main()
{
	FILE* f;

	Reservation res;
	Heap priQueue;

	priQueue.res = 0;
	priQueue.dim = 0;

	f = fopen("Reservations.txt", "r");

	if (f)
	{
		char bufferName[64];
		char bufferPhone[64];

		fscanf(f, "%d,%[^,],%[^,],%d,%d,%d", 
				&res.id, bufferName, bufferPhone, 
				&res.duration, &res.channel, &res.status);

		while (!feof(f))
		{
			res.clientName = (char*)malloc((strlen(bufferName) + 1) * sizeof(char));
			strcpy(res.clientName, bufferName);

			res.phoneNumber = (char*)malloc((strlen(bufferPhone) + 1) * sizeof(char));
			strcpy(res.phoneNumber, bufferPhone);

			// TO DO INSERTION HERE
			insertElement(&priQueue, res);

			fscanf(f, "%d,%[^,],%[^,],%d,%d,%d",
				&res.id, bufferName, bufferPhone,
				&res.duration, &res.channel, &res.status);
		}
	}
	else
	{
		perror("[ERROR] Reservation.txt");
	}

	fclose(f);

	printRaport(priQueue);

	Stack* stack = 0;
	for (int i = 0; i < priQueue.dim/2; i++)
	{
		priQueue.res[i].status = CONFIRMED;
		stack = extractElement(&priQueue, stack);
	}

	printf("\n");
}