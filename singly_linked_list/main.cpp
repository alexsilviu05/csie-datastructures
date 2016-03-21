#define _CRT_SECURE_NO_WARNINGS

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KYEL  "\x1B[33m"
#define KGRN  "\x1B[32m"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Angajat
{
	int id;
	char* nume;
	char* dataAngajare;
	char* departament;
	float salariul;
	int nrOre;
};

struct Nod
{
	Angajat item;
	Nod* next;
};

void IOProblem()
{
	printf("\n%s[EROARE]: Fisierul nu a putut fi deschis!\n%s", KRED, KNRM);
	exit(0);
}

void InvalidLaunchArguments()
{
	printf("\n%s[EROARE]: Argumente invalide date la lansarea aplicatiei!\n%s", KRED, KNRM);
	exit(0);
}

FILE* open(int nrArgumente, char** argumente)
{
	FILE* f = NULL;
	char buffer[256];

	if (nrArgumente == 1)
	{
		printf("\n%s[ATENTIE]: Numele fisierului nu a fost dat ca argument in momentul lansarii aplicatiei!%s", KYEL, KNRM);
		printf("\nVa rugam introduceti numele fisierului: ");
		scanf("%s", buffer);

		f = fopen(buffer, "r+");

		if (f != NULL)
		{
			return f;
		}
		else
		{
			IOProblem();
		}
	}
	else if (nrArgumente == 2)
	{
		f = fopen(argumente[1], "r+");

		if (f != NULL)
		{
			return f;
		}
		else
		{
			IOProblem();
		}
	}
	else
	{
		InvalidLaunchArguments();
	}

	// fix warning C4715: not all control paths return a value
	return f;
}


Nod* adaugaNodLaInceput(Nod* lista, Angajat ang)
{
	Nod* aux = (Nod*)malloc(1 * sizeof(Nod));
	
	aux->item = ang;
	aux->next = lista;

	return aux;
}

Nod* stergeNodSfarsit(Nod* lista)
{
	Nod* aux = lista;
	Nod* prev;

	if (lista ->next)
	{
		while (aux->next)
		{
			prev = aux;
			aux = aux->next;
		}

		printf("\n%sAngajatul cu id [%d] a fost sters!%s",KYEL, aux->item.id, KNRM);
		if (aux->item.nume != NULL)
			free(aux->item.nume);
		if (aux->item.dataAngajare != NULL)
			free(aux->item.dataAngajare);
		if (aux->item.departament != NULL)
			free(aux->item.departament);

		if (prev->next != NULL)
			free(prev->next);
		prev->next = NULL;

		return lista;
	}
	else if ((lista) && (lista->next == NULL))
	{
		printf("\n%sAngajatul cu id [%d] a fost sters!%s", KYEL, aux->item.id, KNRM);

		if (aux->item.nume != NULL)
			free(aux->item.nume);
		if (aux->item.dataAngajare != NULL)
			free(aux->item.dataAngajare);
		if (aux->item.departament != NULL)
			free(aux->item.departament);

		free(aux);
		aux = NULL;
		
		return aux;
	}
	else if (lista == NULL)
	{
		return lista;
	}
}

void afisareLista(Nod* lista)
{
	printf("\n%sAfisare angajati: %s", KGRN, KNRM);
	if (lista != NULL)
	{
		while (lista->next)
		{
			printf("\n[id: %d] %s: data angajare (%s), departament (%s), salariul (%5.2f), numar ore (%d)",
				lista->item.id, lista->item.nume, lista->item.dataAngajare, lista->item.departament, lista->item.salariul, lista->item.nrOre);

			lista = lista->next;
		}

		printf("\n[id: %d] %s: data angajare (%s), departament (%s), salariul (%5.2f), numar ore (%d)",
			lista->item.id, lista->item.nume, lista->item.dataAngajare, lista->item.departament, lista->item.salariul, lista->item.nrOre);
	}
	else
	{
		printf("\nNu exista angajati in lista!");
	}
}

Nod* stergeNodId(Nod* lista, int _id)
{
	Nod* aux = lista;

	if (aux)
	{
		if (aux->next == NULL)
		{
			if (aux->item.id == _id)
			{
				if (aux->item.nume != NULL)
					free(aux->item.nume);
				if (aux->item.dataAngajare!= NULL)
					free(aux->item.dataAngajare);
				if (aux->item.departament != NULL)
					free(aux->item.departament);

				printf("\n%sAngajatul cu id [%d] a fost sters!%s", KYEL, aux->next->item.id, KNRM);

				free(aux);
				aux = NULL;

				return aux;
			}
			else
			{
				return aux;
			}
		}
		else
		{
			while (aux->next != NULL)
			{
				if (aux->next->item.id == _id)
				{
					Nod* next = aux->next->next;

					if (aux->next->item.nume != NULL)
						free(aux->next->item.nume);
					if (aux->next->item.dataAngajare != NULL)
						free(aux->next->item.dataAngajare);
					if (aux->next->item.departament != NULL)
						free(aux->next->item.departament);

					printf("\n%sAngajatul cu id [%d] a fost sters!%s", KYEL, aux->next->item.id, KNRM);
					free(aux->next);
					aux->next = next;

					return lista;
				}

				aux = aux->next;
			}
		}
	}
}

void modificareNume(Nod* lista, char* initial, char* final)
{
	Nod* aux = lista;

	if (aux)
	{
		while (aux->next)
		{
			if (strcmp(aux->item.nume, initial) == 0)
			{
				printf("\n%sSchimbare nume: %s -> %s ! %s", KYEL, aux->item.nume, final, KNRM);

				if (aux->item.nume != NULL)
				{
					free(aux->item.nume);
				}

				aux->item.nume = (char*)malloc((strlen(final) + 1) * sizeof(char));
				strcpy(aux->item.nume,final);
			}
			aux = aux->next;
		}
	}
}

int numarAngajati(Nod* lista, char* anAngajare)
{
	if ((anAngajare == NULL) || (strlen(anAngajare) != 4))
	{
		printf("\n%s[ATENTIE]: Anul trimis ca argument la apelarea functiei este invalid!%s", KYEL, KNRM);
		return 0;
	}

	int counter = 0;
	Nod* aux = lista;


	while (aux->next)
	{
		if (char* ptr = strstr(aux->item.dataAngajare,anAngajare))
		{
			counter++;
		}
		aux = aux->next;
	}

	if (char* ptr = strstr(aux->item.dataAngajare, anAngajare))
	{
		counter++;
	}
	aux = aux->next;

	printf("\n%sNumar angajati cu anul angajarii %s : %d %s", KGRN, anAngajare, counter, KNRM);

	return counter;
}

void eliberare(Nod** list)
{
	Nod* _previous;
	if ((*list))
	{
		if ((*list)->next == NULL)
		{
			if ((*list)->item.nume != NULL)
				free((*list)->item.nume);
			if ((*list)->item.dataAngajare != NULL)
				free((*list)->item.dataAngajare);
			if ((*list)->item.departament != NULL)
				free((*list)->item.departament);
		}
		else
		{
			while ((*list)->next)
			{
				_previous = *list;
				*list = (*list)->next;

				if (_previous->item.nume != NULL)
					free(_previous->item.nume);
				if (_previous->item.dataAngajare != NULL)
					free(_previous->item.dataAngajare);
				if (_previous->item.departament != NULL);
				free(_previous);
				_previous = NULL;
			}

			if ((*list)->item.nume != NULL)
				free((*list)->item.nume);
			if ((*list)->item.dataAngajare != NULL)
				free((*list)->item.dataAngajare);
			if ((*list)->item.departament != NULL);
			free(*list);

			*list = NULL;
		}
	}
}

void main(int argc, char** argv)
{
	Nod* lista = NULL;
	Angajat ang;

	FILE* file;
	file = open(argc, argv);

	char bufferNume[64];
	char bufferAngajare[9];
	char bufferDepartament[64];

	fscanf(file, "%d,%[^,],%[^,],%[^,],%f,%d", &ang.id, bufferNume, bufferAngajare, bufferDepartament, &ang.salariul, &ang.nrOre);
	while (!feof(file))
	{
		// angajat' dynamic fields : malloc/copy
		ang.nume = (char*)malloc((strlen(bufferNume) + 1) * (sizeof(char)));
		strcpy(ang.nume, bufferNume);

		ang.dataAngajare = (char*)malloc((strlen(bufferAngajare) + 1) * (sizeof(char)));
		strcpy(ang.dataAngajare, bufferAngajare);
		
		ang.departament = (char*)malloc((strlen(bufferDepartament) + 1) * (sizeof(char)));
		strcpy(ang.departament, bufferDepartament);

		// adaugare nod in lista
		lista = adaugaNodLaInceput(lista, ang);

		fscanf(file, "%d,%[^,],%[^,],%[^,],%f,%d", &ang.id, bufferNume, bufferAngajare, bufferDepartament, &ang.salariul, &ang.nrOre);
	}

	// afisare lista intreaga
	afisareLista(lista);

	// sterge ultimult nod
	lista = stergeNodSfarsit(lista);

	// afisare lista intreaga
	afisareLista(lista);

	// sterge in functie de id
	lista = stergeNodId(lista, 2);
	lista = stergeNodId(lista, 3);
	lista = stergeNodId(lista, 4);

	// afisare lista intreaga
	afisareLista(lista);

	// modificare nume angajati: nume vechi, nume nou
	modificareNume(lista, "Undefined", "Vasile");
	modificareNume(lista, "Lucian Dan", "Lucian Sebastian");

	// afisare lista intreaga
	afisareLista(lista);

	int count = 0;

	// determinare numar angajati cu anul angajarii specificat {format: yyyy: 2005}
	count = numarAngajati(lista, "abcdefgijklm"); // testare validare
	count = numarAngajati(lista, "2005");	// ar trebui returnat 2

	// functie dezalocare lista simpla
	eliberare(&lista);

	// GUI Extra
	printf("\n");
}