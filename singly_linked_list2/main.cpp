#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXNAME 256

struct Student
{
	int id;
	char* nume;
	char cnp[14];
	char forma[3];
	float inaltime;
};

struct Node
{
	Student s;
	Node* next;
};

Node* adaugaInceput(Node *list, Student s)
{
	Node *tmp = 0;

	if (list == 0) //lista este goala
	{
		tmp = (Node*)malloc(sizeof(Node));

		tmp->s = s;
		tmp->next = 0;

		return tmp;
	}
	else
	{
		tmp = (Node*)malloc(sizeof(Node));

		tmp->s = s;
		tmp->next = list;

		return tmp;
	}
}

Student cautaStudent(Node *list, int id)
{
	Node *tmp = list;

	Student temp;
	
	temp.id = -1;
	temp.nume = 0;
	temp.cnp[0] = '\0';
	temp.forma[0] = '\0';
	temp.inaltime = 0.0f;

	if (id < 0)
	{
		return temp;
	}
	else if (list == 0)
	{
		return temp;
	}
	
	if (tmp)
	{
		if (tmp->next == 0)
		{
			if (tmp->s.id == id)
			{
				return tmp->s;
			}
		}

		while (tmp->next)
		{
			tmp = tmp->next;
			if (tmp->s.id == id)
			{
				return tmp->s;
			}
		}
		
	}

	return temp;
}

Node* stergeStudent(Node *list, int id)
{
	if (id < 0 || list == 0)
	{
		return list;
	}

	Node *tmp = list;
	Node *prev;
	Node* aux;

	if (tmp)
	{
		if (tmp->s.id == id)
		{
			if (tmp->s.nume != 0)
				free(tmp->s.nume);
			aux = tmp->next;
			free(tmp);
			tmp = 0;
			return aux;
		}
		else
		{
			while (tmp->next != 0)
			{
				prev = tmp;
				tmp = tmp->next;

				if (tmp->s.id == id)
				{
					if (tmp->s.nume != 0)
						free(tmp->s.nume);
					prev->next = tmp->next;
					free(tmp);
					tmp = 0;
					return list;
				}
			}
		}
	}

	return list;
}

Node* eliberareMemorie(Node *list)
{
	Node *temp = list;
	Node* prev;

	if (temp)
	{
		if (temp->next == 0)
		{
			if (temp->s.nume != 0)
				free(temp->s.nume);
			free(temp);
			temp = 0;

			return temp;
		}

		while (temp->next)
		{
			prev = temp;
			temp = temp->next;

			if (prev->s.nume != 0)
				free(prev->s.nume);
			free(prev);
			prev = 0;
		}
		
		if (temp->s.nume != 0)
			free(temp->s.nume);
		free(temp);
		temp = 0;

		return temp;
	}

	return list;
}

Node* inserarePoz(Node *list, Student s, int poz)
{
	if (list == 0 || poz < 1)
	{
		return list;
	}

	Node * temp = list;

	if (temp)
	{
		if (poz == 1)
		{
			temp = adaugaInceput(temp, s);

			return temp;
		}

		// incercare pozitionare
		while (temp->next && poz > 2)
		{
			temp = temp->next;
			poz--;
		}

		if (temp->next)
		{
			Node *aux = (Node*)malloc(sizeof(Node));
			Node *nxt = temp->next->next;

			aux->s = s;

			temp->next = aux;
			aux->next = nxt;
		}
	}

	return list;
}

void main()
{
	FILE *f = 0;
	f = fopen("Studenti.txt", "r");

	Node *list = 0;
	Student s;

	if (f)
	{
		char buffer[MAXNAME];

		fscanf(f, "%d, %[^,], %[^,], %[^,], %f", &s.id, buffer, s.cnp, s.forma, &s.inaltime);

		while (!feof(f)) 
		{
			s.nume = (char*)malloc((strlen(buffer) + 1) * sizeof(char));
			strcpy(s.nume, buffer);
			list = adaugaInceput(list, s);

			fscanf(f, "%d, %[^,], %[^,], %[^,], %f", &s.id, buffer, s.cnp, s.forma, &s.inaltime);
		}
	}
	else
	{
		printf("\nEroare la deschiderea fisierului!");
		exit(0);
	}


	// afisare lista
	Node *rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);


	printf("\n_________________ CAUTARE IN LISTA SIMPLA + scriere");

	FILE* p;
	p = fopen("Lista.txt", "w");

	Student c = cautaStudent(list, 1);
	printf("\n%d %s", c.id, c.nume);
	fprintf(p, "%d,%s,%s,%s,%f\n", c.id, c.nume, c.cnp, c.forma, c.inaltime);

	c = cautaStudent(list, 2);
	printf("\n%d %s", c.id, c.nume);
	fprintf(p, "%d,%s,%s,%s,%f\n", c.id, c.nume, c.cnp, c.forma, c.inaltime);

	c = cautaStudent(list, 3);
	printf("\n%d %s", c.id, c.nume);
	fprintf(p, "%d,%s,%s,%s,%f\n", c.id, c.nume, c.cnp, c.forma, c.inaltime);

	c = cautaStudent(list, 4);
	printf("\n%d %s", c.id, c.nume);
	fprintf(p, "%d,%s,%s,%s,%f\n", c.id, c.nume, c.cnp, c.forma, c.inaltime);

	c = cautaStudent(list, 50);
	printf("\n%d %s", c.id, c.nume);
	fprintf(p, "%d,%s,%s,%s,%f\n", c.id, c.nume, c.cnp, c.forma, c.inaltime);
	

	printf("\n_________________ ADAUGARE pe pozitie data");
	Student add;
	add.id = 999;
	add.nume = 0;
	add.cnp[0] = 0;
	add.forma[0] = 0;
	add.inaltime = 2.0f;

	list = inserarePoz(list, add, 4);

	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);

	printf("\n_________________ STERGERE STUDENT DIN LISTA");
	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);

	printf("\nStergere student cu id 1");
	list = stergeStudent(list, 1);

	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);

	printf("\nStergere student cu id 5");
	list = stergeStudent(list, 5);

	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);

	printf("\nStergere student cu id 3");
	list = stergeStudent(list, 3);

	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);


	printf("\nStergere student cu id 999");
	list = stergeStudent(list, 999);

	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);


	printf("\nStergere student cu id -5");
	list = stergeStudent(list, -5);

	rec = list;
	while (rec->next)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}
	printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);

	printf("\n_________________ ELIBERARE MEMORIE");
	list = eliberareMemorie(list);

	rec = list;
	while (rec)
	{
		printf("\n%d %s %s %s %5.2f", rec->s.id, rec->s.nume, rec->s.cnp, rec->s.forma, rec->s.inaltime);
		rec = rec->next;
	}

	if (p)
	{
		fclose(p);
	}

	if (f)
	{
		fclose(f);
	}
}