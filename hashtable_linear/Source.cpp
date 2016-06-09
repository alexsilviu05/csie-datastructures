#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HT_SIZE 255

enum Paying
{
	Shop = 1,
	Online = 2,
	Other = 3
};

enum State
{
	EMPTY = 1,
	OCCUPIED = 2,
	DELETED = 3
};

struct Bill
{
	char* clientName;
	char* clientCode;
	float value;
	char* date;
	Paying payingMode;
	State state;
};

int hash(char *string, int size)
{
	int position;
	int temp=0;

	for (unsigned int i = 0; i < strlen(string); i++)
	{
		temp += string[i];
	}

	position = temp % size;

	return position;
}

int insertElement(Bill *HTable, Bill bill, int size)
{
	int position;
	int placed = 0;

	position = hash(bill.clientCode,size);

	// case 1: slot empty
	if (HTable[position].state == EMPTY)
	{
		HTable[position] = bill;
		HTable[position].state = OCCUPIED;
		placed = 1;
	}
	else if (HTable[position].state == OCCUPIED) // colision
	{
		int i = position;

		while (i < size && placed == 0)
		{
			if (HTable[i].state == EMPTY)
			{
				HTable[i] = bill;
				HTable[i].state = OCCUPIED;
				placed = 1;
			}
			
			i++;
		}

		if (!placed)
		{
			i = 0;
			while (i < position && placed == 0)
			{
				if (HTable[i].state == EMPTY)
				{
					HTable[i] = bill;
					HTable[i].state = OCCUPIED;
					placed = 1;
				}

				i++;
			}
		}
	}

	return placed;
}

void main()
{
	FILE* f;
	Bill bill;

	Bill *HTable;
	int chunks = 1;
	int placed;

	HTable = (Bill*)malloc((chunks * HT_SIZE) * sizeof(bill));
	for (int i = 0; i < chunks * HT_SIZE; i++)
	{
		HTable[i].state = EMPTY;
	}

	f = fopen("Bills.txt", "r");

	if (f)
	{
		char nameBuffer[64];
		char codeBuffer[64];
		char dateBuffer[64];

		fscanf(f, "%f,%[^,],%[^,],%[^,],%d",
			&bill.value, nameBuffer, codeBuffer, dateBuffer, &bill.payingMode);

		while (!feof(f))
		{
			bill.clientName = (char*)malloc((strlen(nameBuffer) + 1) * sizeof(char));
			strcpy(bill.clientName, nameBuffer);

			bill.clientCode = (char*)malloc((strlen(codeBuffer) + 1) * sizeof(char));
			strcpy(bill.clientCode, codeBuffer);

			bill.date = (char*)malloc((strlen(dateBuffer) + 1) * sizeof(char));
			strcpy(bill.date, dateBuffer);

			// TO DO Inseration here
			placed = insertElement(HTable, bill, chunks*HT_SIZE);

			if (placed == 0) // the structure is full
			{
				chunks++;

				Bill* newTable = (Bill*)malloc((chunks * HT_SIZE) * sizeof(Bill));
				for (int i = 0; i < (chunks - 1)*HT_SIZE; i++)
					newTable[i] = HTable[i];

				free(HTable);

				HTable = newTable;

				placed = insertElement(HTable, bill, chunks*HT_SIZE);
			}

			fscanf(f, "%f,%[^,],%[^,],%[^,],%d",
				&bill.value, nameBuffer, codeBuffer, dateBuffer, &bill.payingMode);
		}
	}
	else
	{
		perror("[ERROR] Bills.txt");
	}
}