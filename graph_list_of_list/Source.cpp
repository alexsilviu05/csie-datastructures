//Romanian language used in this example

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>

enum Tip
{
	GRAU = 1,
	ORZ = 2,
	SECARA = 3,
	PORUMB = 4,
	OREZ = 5,
	ALTUL = 6
};

struct Depozit
{
	char* id;
	unsigned int capacitate;
	unsigned int incarcare;
	Tip tip;
};

struct ListaS
{
	Depozit info;
	ListaS* next;
};

struct ListaP
{
	int id;

	ListaS* cap;
	ListaP* next;
};

ListaS* put(ListaS* listaS, Depozit info)
{
	ListaS* elemNou = (ListaS*)malloc(sizeof(ListaS));
	elemNou->info = info;
	elemNou->next = 0;

	if (listaS == 0)
	{
		listaS = elemNou;
	}
	else
	{
		ListaS* temp = listaS;

		while (temp->next)
			temp = temp->next;

		temp->next = elemNou;
	}

	return listaS;
}

ListaP* put(ListaP* listaP, Depozit info, int id, char* legaturi)
{
	ListaP* depoNou = (ListaP*)malloc(sizeof(ListaP));
	depoNou->id = id;
	depoNou->next = 0;
	depoNou->cap = 0;

	// insereaza depozit
	depoNou->cap = put(depoNou->cap, info);
	// insereaza legaturi
	char* token;
	char separator[2] = ";";

	token = strtok(legaturi, separator);
	while (token != 0)
	{
		Depozit legatura;
		legatura.id = (char*)malloc((strlen(token) + 1) * sizeof(char));
		strcpy(legatura.id, token);

		depoNou->cap = put(depoNou->cap, legatura);

		token = strtok(0, separator);
	}

	// null
	if (listaP == 0)
	{
		listaP = depoNou;
	}
	else // not null
	{
		ListaP* temp = listaP;
		while (temp->next)
			temp = temp->next;

		temp->next = depoNou;
	}

	return listaP;
}

void printList(ListaS* list)
{
	if (list == 0)
	{
		printf("\nLista este goala!");
	}
	else
	{
		ListaS* temp = list;

		int count = 0;
		while (temp)
		{
			if (count == 0)
			{
				printf("\nDepozit [%s] : capacitate: %d, incarcare: %d, tip: %d",
					temp->info.id, temp->info.capacitate, temp->info.incarcare, temp->info.tip);
			}
			else
			{
				printf("\nLegatura cu depozit [%s]", temp->info.id);
			}
			count++;
			temp = temp->next;
		}
	}
}

void printGraph(ListaP* listaP)
{
	if (listaP == 0)
	{
		printf("\nGraful este gol!");
	}
	else
	{
		ListaP* tempP = listaP;

		while (tempP)
		{
			printf("\nNOD[%d]: ", tempP->id);
			printList(tempP->cap);

			tempP = tempP->next;
		}
	}
}

void modificaCantitate(ListaP* listaP, char* tip, int cantitateNoua)
{
	if (listaP)
	{
		ListaP* temp = listaP;

		while (temp)
		{
			switch (temp->cap->info.tip)
			{
			case GRAU:
				if (strcmp(tip, "grau") == 0)
				{
					temp->cap->info.incarcare = cantitateNoua;
				};
				break;
			case ORZ:
				if (strcmp(tip, "orz") == 0)
				{
					temp->cap->info.incarcare = cantitateNoua;
				};
				break;
			case SECARA:
				if (strcmp(tip, "secara") == 0)
				{
					temp->cap->info.incarcare = cantitateNoua;
				};
				break;
			case PORUMB:
				if (strcmp(tip, "porumb") == 0)
				{
					temp->cap->info.incarcare = cantitateNoua;
				};
				break;
			case OREZ:
				if (strcmp(tip, "orez") == 0)
				{
					temp->cap->info.incarcare = cantitateNoua;
				};
				break;
			default:
				break;
			}	

			temp = temp->next;
		}
	}
}

void adaugaDepozit(ListaP* depozite)
{
	Depozit d;

	char bufferId[64];

	printf("\nId depozit: ");
	scanf("%s", bufferId);
	d.id = (char*)malloc((strlen(bufferId) + 1) * sizeof(char));
	strcpy(d.id, bufferId);

	printf("\nCapacitate depozit: ");
	scanf("%d", &d.capacitate);

	printf("\nIncarcare depozit: ");
	scanf("%d", &d.incarcare);

	printf("\nTip depozit: [1 - GRAU, 2- ORZ, 3 - SECARA, 4 - PORUMB, 5 - OREZ]: ");
	scanf("%d", &d.tip);

	depozite = put(depozite, d, 555, 0);
}

void main()
{
	FILE* f;

	ListaP* depozite = 0;

	Depozit info;

	f = fopen("Depozite.txt", "r");

	if (f)
	{
		char bufferId[32];
		char bufferLegaturi[128];
		int counter = 1;

		fscanf(f, "%d,%[^,],%d,%d,%[^,\n]", 
				&info.capacitate, bufferId,&info.incarcare, &info.tip, bufferLegaturi);

		while (!feof(f))
		{
			info.id = (char*)malloc((strlen(bufferId) + 1) * sizeof(char));
			strcpy(info.id, bufferId);

			depozite = put(depozite, info, counter, bufferLegaturi);

			// read next line
			fscanf(f, "%d,%[^,],%d,%d,%[^,\n]",
				&info.capacitate, bufferId, &info.incarcare, &info.tip, bufferLegaturi);
			counter++;
		}
	}
	else
	{
		perror("[EROARE] Depozite.txt");
	}

	fclose(f);

	// afisare graph
	printGraph(depozite);

	// modifica cantitati
	modificaCantitate(depozite, "grau", 500);

	// afisare graph
	printf("\nModificare cantitate depozite grau: ");
	printGraph(depozite);

	// adaugare depozit nou
	adaugaDepozit(depozite);
	printf("\nAdaugare depozit nou: ");
	printGraph(depozite);
}