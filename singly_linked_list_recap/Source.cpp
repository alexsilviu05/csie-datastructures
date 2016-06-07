#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
* Singly linked list
*
* Operations implemented:
* List creation : done;
* Node insertion : done;
* List crossing : done;
* Search : done;
* Node interchange (adress interchange) : done (non/adjacent);
* Node deletion : done (recursively);
* List deletion;
* List sorting : done;
* List concatenation : done;
* List interclasation : pending;
*/

struct Date
{
	int day;
	int month;
	int year;
};

struct Student
{
	const int id;
	char* name;
	Date birthDay;
	char* faculty;
	short int year;
	short int group;
};

struct Node
{
	Student* info; //made it pointer because of Student' constant id
	Node* next;
};

// front insertion
Node* frontInsertion(Node* list, Student* info)
{
	Node* newNode = (Node*)malloc(sizeof(Node*));
	newNode->info = info;

	if (!list) // list is empty
	{
		newNode->next = 0;
	}
	else
	{
		newNode->next = list;
	}

	return newNode;
}

// rear insertion
Node* rearInsertion(Node* list, Student* info)
{
	Node* newNode = (Node*)malloc(sizeof(Node));
	newNode->info = info;

	Node* temp = list;

	if (!list)
	{
		newNode->next = 0;

		return newNode;
	}
	else
	{
		while (temp->next)
			temp = temp->next;

		temp->next = newNode;
		newNode->next = 0;

		return list;
	}
}

void printList(Node* list)
{
	if (list)
	{
		Node* temp = list;
		while (temp)
		{
			printf("\n[STUDENT] %d : %s (%d-%d-%d) %s , year: %d", 
					temp->info->id, temp->info->name, 
					temp->info->birthDay.day,
					temp->info->birthDay.month,
					temp->info->birthDay.year,
					temp->info->faculty,
					temp->info->year);

			temp = temp->next;
		}
	}
	else
	{
		printf("\nThe list is empty!");
	}
}

// print a student to a text file
void printFile(char* fileName, Student* stud)
{
	FILE* f;

	f = fopen(fileName, "a");

	if (f)
	{

		char buffer[256];

		snprintf(buffer, sizeof(buffer), "%d-%d-%d",
						 stud->birthDay.day, stud->birthDay.month, stud->birthDay.year);

		fprintf(f, "%d, %s, %s, %s, %d, %d \n", 
				   stud->id, stud->name, buffer, stud->faculty, stud->year, stud->group);
	}
	else
	{
		printf("[WARNING]Couldn't open the %s file!", fileName);
	}

	fclose(f);
}

// search the students that have the fate like then given one and
// print them to a text file
void searchStudent(Node* list, char* fate)
{
	if (fate && list)
	{
		Node* temp = list;

		if (strcmp(fate, "fate1") == 0)
		{
			//printFile("filename", stud);
			while (temp)
			{
				if (temp->info->birthDay.month > 0 && temp->info->birthDay.month < 5)
				{
					printFile("fate.txt", temp->info);
				}

				temp = temp->next;
			}
		}
		else if (strcmp(fate, "fate2") == 0)
		{
			while (temp)
			{
				if (temp->info->birthDay.month > 4 && temp->info->birthDay.month < 9)
				{
					printFile("fate.txt", temp->info);
				}

				temp = temp->next;
			}
		}
		else if (strcmp(fate, "fate3") == 0)
		{
			while (temp)
			{
				if (temp->info->birthDay.month > 8 && temp->info->birthDay.month < 13)
				{
					printFile("fate.txt", temp->info);
				}

				temp = temp->next;
			}
		}
		else
		{
			printf("[WARNING]Unknown fate!");
		}
	}
	else
	{
		printf("[WARNING]Fate not specified or the list is empty!");
	}
}

/**
* poz : variable indicating if the lastName is located at start or end
* poz values: 1 for start, 2 for end
*
* functional module
*/
Node* deleteStudent(Node* currentNode, char* lastName, int poz)
{
	// if we are at the end of the list
	if (currentNode == 0)
		return 0;

	// check if the current node is the one for deletion
	if (poz == 1)
	{
		char* token;
		char separator[2] = " ";

		char nameBuffer[256];
		strcpy(nameBuffer, currentNode->info->name);

		token = strtok(nameBuffer, separator);

		if (strcmp(token, lastName) == 0)
		{
			Node* nextElement = currentNode->next;

			if (currentNode->info->name != 0)
				free(currentNode->info->name);
			if (currentNode->info->faculty != 0)
				free(currentNode->info->faculty);

			free(currentNode);

			return nextElement;
		}

		currentNode->next = deleteStudent(currentNode->next, lastName, poz);
	}

	return currentNode;
}

// this function has memory leaks
/*
Node* deleteElement(Node* element, char* name)
{
	if (element == 0)
		return 0;

	if (strcmp(element->info->name, name) == 0)
	{
		Node* nextElement = element->next;
		free(element);
		return nextElement;
	}

	element->next = deleteElement(element->next, name);

	return element;
}
*/

// search in list
Student* searchElement(Node* element, char* name)
{
	if (element)
	{
		if (strcmp(element->info->name, name) == 0)
			return element->info;
		else
			return searchElement(element->next,name);
	}
	else
		return 0;
}

// interchange adjacent nodes
Node* interchangeNodesAdj(Node* list, int first, int second)
{
	if (first == second - 1 || first == second + 1)
	{
		if (list && list->next)
		{
			Node* temp = list;

			if (first == 1 || second == 1)
			{
				Node* p = list;
				Node* q = list->next;

				p->next = q->next;
				q->next = p;

				return q;
			}

			// positioning try
			while (temp->next->next && first > 2)
			{
				temp = temp->next;
				first--;
			}

			if (temp->next->next)
			{
				Node* p;
				Node* q;
				Node* r;

				p = temp;
				q = p->next;
				r = q->next;

				p->next = r;
				q->next = r->next;
				r->next = q;
			}

		}
		else
		{
			printf("\nCannot interchange! The given list is empty or having only 1 element!");
			return list;
		}
	}

	printf("\nGiven positions are not adjacents!");
	return list;
}

// interchange nodes
Node* interchangeNodes(Node* list, int pos1, int pos2)
{
	if (list && list->next)
	{
		if (pos1 == pos2 - 1)
		{
			return interchangeNodesAdj(list, pos1, pos2);
		}

		if (pos1 == 1)
		{
			Node* temp = list;

			while (temp->next && pos2 > 2)
			{
				temp = temp->next;
				pos2--;
			}

			if (temp->next)
			{
				Node* p = list;
				Node* x = list->next;
				Node* q = temp;
				Node* r = temp->next;

				p->next = r->next;
				q->next = p;
				r->next = x;

				return r;
			}
		}
	}
	else
	{
		printf("\n[INTERCHANGE]The list is empty or has only one element!");
	}

	return list;
}

void swap(Node* a, Node* b)
{
	Node* temp = (Node*)malloc(sizeof(Node));

	temp->info = a->info;
	a->info = b->info;
	b->info = temp->info;

	free(temp);
}

void sortList(Node** list)
{
	if (*(list))
	{
		int swapped;
		Node* temp;

		do
		{
			swapped = 0;
			temp = *list;

			while (temp->next)
			{
				if (temp->info->year > temp->next->info->year)
				{
					swap(temp, temp->next);
					swapped = 1;
				}

				temp = temp->next;
			}

			temp = 0;

		} while (swapped);
	}
	else
	{
		printf("\nThe list is empty!");
	}
}

Node* concatenateList(Node* listA, Node* listB)
{
	if (listA && listB)
	{
		Node* temp = listA;

		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = listB;
	}

	else
	{
		printf("\nOne of the list is empty!");
	}

	return listA;
}

// list deletion
Node* deleteList(Node* list)
{
	if (list == 0)
		return 0;
	
	Node* temp = list->next;

	if (list->info->name)
		free(list->info->name);
	if (list->info->faculty)
		free(list->info->faculty);
	free(list);
	list = 0;

	deleteList(temp);
}

void main()
{
	Node* list = 0;
	Node* secondList = 0;

	Student* stud = 0;

	FILE *f;
	f = fopen("Students.csv", "r");

	if (f)
	{
		stud = (Student*)malloc(sizeof(Student));

		// buffers
		char name[256];
		char birth[256];
		char faculty[256];

		// pattern: 1,John Smith,10-10-1990,Faculty of Computer Sciene,1,1008
		fscanf(f, "%d, %[^,], %[^,], %[^,], %hd, %hd",
			&(stud->id), name, birth, faculty, &stud->year, &stud->group);

		while (!feof(f))
		{
			stud->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
			strcpy(stud->name, name);

			char* token;

			// solving date field
			char separator[2] = "-";
			token = strtok(birth, separator);
			stud->birthDay.day = atoi(token);

			token = strtok(0, separator);
			stud->birthDay.month = atoi(token);

			token = strtok(0, separator);
			stud->birthDay.year = atoi(token);


			// solving name field
			stud->name = (char*)malloc((strlen(name) + 1) * sizeof(char));
			strcpy(stud->name, name);

			// solving faculty
			stud->faculty = (char*)malloc((strlen(faculty) + 1) * sizeof(char));
			strcpy(stud->faculty, faculty);

			// INSERTION HERE:
			//list = frontInsertion(list, stud);
			list = rearInsertion(list, stud);
			secondList = frontInsertion(secondList, stud);

			// allocate new student && read next line from csv file
			stud = (Student*)malloc(sizeof(Student));
			fscanf(f, "%d, %[^,], %[^,], %[^,], %hd, %hd",
				&(stud->id), &name, &birth, &faculty, &stud->year, &stud->group);
		}
	}
	else
	{
		perror("[FILE ERROR]");
	}

	printList(list);
	searchStudent(list, "fate1");
	searchStudent(list, "fate2");
	searchStudent(list, "fate3");

	list = deleteStudent(list, "Max", 1);
	//list = deleteElement(list, "Philip Rafaello");
	printf("\nList after deletion of Max: ");

	printList(list);

	// search for a student in list
	Student* searched = searchElement(list, "John Smith");
	if (searched)
	{
		printf("\nStudent found: %s", searched->name);
	}
	else
	{
		printf("\nStudent not found!");
	}

	// interchange adjacent nodes in list
	list = interchangeNodesAdj(list, 3, 4);
	printf("\nList after adjacent interchange: ");
	printList(list);

	// interchange nodes in list
	list = interchangeNodes(list, 1, 5);
	printf("\nList after adjacent interchange: ");
	printList(list);

	// sort list by year
	printf("\nSorting the list: ");
	sortList(&list);
	printList(list);

	// list concatenation
	printf("\nFirst list: ");
	printList(list);
	printf("\nSecond list: ");
	printList(secondList);

	//Node* concatenatedList = concatenateList(list, secondList);
	//printf("\nResult: ");
	//printList(concatenatedList);

	deleteList(list);

	// testing some things
	int a = 0x5;

	a = 0xA;
	a = 0xB;
	a = 0xC;

	printf("\nHex: %x", a);


	// finally
	fclose(f);
	printf("\n");
}