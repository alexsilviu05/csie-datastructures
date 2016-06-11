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
	Reservation *reservations;
	int dim;
};

void filtration(Heap h, int index)
{
	int N = index;
	int left = 2 * N + 1;
	int right = 2 * N + 2;

	if (left < h.dim && h.reservations[N].duration > h.reservations[left].duration)
	{
		N = left;
	}
	if (right < h.dim && h.reservations[N].duration > h.reservations[right].duration)
	{
		N = right;
	}

	if (N != index)
	{
		Reservation temp = h.reservations[index];

		h.reservations[index] = h.reservations[N];
		h.reservations[N] = temp;

		filtration(h, N);
	}
}

void insertElement(Heap* heap, Reservation res)
{
	Reservation *newArray = (Reservation*)malloc(((*heap).dim + 1) * sizeof(Reservation));

	for (int i = 0; i < (*heap).dim; i++)
	{
		newArray[i] = heap->reservations[i];
	}

	newArray[heap->dim] = res;
	heap->dim++;

	if (heap->reservations)
		free(heap->reservations);

	heap->reservations = newArray;

	for (int i = (heap->dim - 1) / 2; i >= 0; i--)
	{
		filtration((*heap), i);
	}
}

Reservation extractElement(Heap* h)
{
	Reservation temp = h->reservations[0];

	h->reservations[0] = h->reservations[h->dim - 1];
	h->reservations[h->dim - 1] = temp;

	Reservation *newArray = (Reservation*)malloc((h->dim - 1) * sizeof(Reservation));

	for (int i = 0; i < h->dim - 1; i++)
	{
		newArray[i] = h->reservations[i];
	}

	h->dim--;

	free(h->reservations);
	h->reservations = newArray;

	return temp;
}

void main()
{
	FILE* f;

	Heap minHeap;

	minHeap.dim = 0;
	minHeap.reservations = 0;

	Reservation res;
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

			insertElement(&minHeap, res);

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

	Reservation temp = extractElement(&minHeap);

	printf("\n");
}