// Aadil Habibi
// aa466902
// COP 3502 - Szumlanski

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListyString.h"

double difficultyRating(void)
{
	return 4.0;
}

double hoursSpent(void)
{
	return 32.0;
}

int main(int argc, char **argv)
{
	processInputFile(argv[1]);
	return 0;
}

//Helper Function for New Nodes
ListyNode *createNode (char letter)
{
	ListyNode *newNode = malloc (sizeof(ListyNode));
	newNode->data = letter;
	newNode->next = NULL;

	return newNode;
}

int processInputFile (char *filename)
{
	char listyEntry[1024], buffer[1024], key[2];

	FILE *ifp = NULL;
	ifp = fopen (filename, "r");

	//Check to see if file opened
	if (ifp == NULL)
	{
		return 1;
	}

	//Scans firs tline of file and it is put into our ListyString
	fscanf(ifp, "%s", listyEntry);

	ListyString *listy = createListyString(listyEntry);

	//Go through entire file, and put each character into buffer until file is finished
	while(fscanf(ifp, "%s", buffer) != EOF)
	{
		switch (buffer[0])
		{
			case '@':
				fscanf(ifp, "%s %s", key, buffer);
				replaceChar(listy, key[0], buffer);
				break;

			case '+':
				fscanf(ifp, "%s", buffer);
				listyCat(listy, buffer);
				break;

			case '-':
				fscanf(ifp, "%s", key);
				replaceChar(listy, key[0], NULL);
				break;

			case '~':
				reverseListyString(listy);
				break;

			case '?':
				printf("%d\n", listyLength(listy));
				break;

			case '!':
				printListyString(listy);
				break;
		}
	}

	return 0;
}

ListyString *createListyString (char *str)
{
	int i;
	ListyNode *temp;

	//Check if string is NULL or empty
	if (str == NULL || str[0] == '\0')
	{
		//Creating Space for ListyString
		ListyString *listy = malloc(sizeof(ListyString));
		listy->head = NULL;
		listy->length = 0;
		return listy;
	}

	//Creating ListyString
	ListyString *listy = malloc(sizeof(ListyString));

	//Setting length of ListyString to length of string
	listy->length = strlen(str);

	//initializing head node
	listy->head = createNode(str[0]);

	//Temp variable equal to the head
	temp = listy->head;

	//Create Nodes until you reach NULL terminator from file
	for (i = 1; i < listy->length; i++)
	{
		temp->next = createNode(str[i]);
		temp = temp->next;
	}

	return listy;
}

ListyString *destroyListyString(ListyString *listy)
{
	ListyNode *delete, *temp;

	//If ListyString is empty or The Head is NULL then return NULL
	if (listy == NULL || listy->head == NULL)
	{
		return NULL;
	}

	//Setting up placeholders for the for loop
	delete = listy->head;
	temp = listy->head;

	//Looping through ListyString until head is NULL and freeing everything inside
	while(temp != NULL)
	{
		delete = temp->next;
		free(temp);
		temp = delete;
	}

	return NULL;
}

ListyString *cloneListyString (ListyString *listy)
{
	ListyNode *temp, *copyTemp;

	if (listy == NULL)
	{
		return NULL;
	}

	if (listy->head == NULL)
	{
		//Creating space for ListyString and initializing head and length
		ListyString *newListy = malloc(sizeof(ListyString));
		newListy->head = NULL;
		newListy->length = 0;
		return newListy;
	}

	//Malloc space for ListyString Copy
	ListyString *copyListy = malloc(sizeof(ListyString));

	//Setting length equal to original ListyString
	copyListy->length = listy->length;
	temp = listy->head;
	copyListy->head = createNode(temp->data);

	copyTemp = copyListy->head;
	temp = temp->next;

	//Looping through until end of ListyString
	while(temp->next = NULL)
	{
		copyTemp->next = createNode(temp->data);
		copyTemp = copyTemp->next;
		temp = temp->next;
	}
}

void replaceChar(ListyString *listy, char key, char *str)
{
	ListyNode *current, *prev = NULL, *temp, *newReplacement;
	int i, repLength;

	if (listy == NULL || listy->head == NULL)
	{
		return;
	}

	if (str != NULL)
	{
		repLength = strlen(str);
	}

	current = listy->head;

	//Looping through to find if Key is found
	while (current != NULL)
	{
		if (current ->data == key)
		{
			//If String was NULL or empty
			if (str == NULL || str[0] == '\0')
			{
				//move current forward
				if (prev == NULL)
				{
					////Go through and free space
					temp = current;
					current = current->next;
					listy->head = current;
					free(temp);
				}
				//if current->next is last node
				else if (current->next == NULL)
				{
					//Go through and free space, while decreasing length
					temp = current;
					prev->next = current->next;
					current = current->next;
					free(temp);
					listy->length--;
				}
				else
				{
					//Go through and free space, while decreasing length
					temp = current;
					prev->next = temp->next;
					current = prev->next;
					free(temp);
					listy->length--;
				}
			}
			//If String was non-empty
			else
			{
				current->data = str[0];
				for (i = 1; i < repLength; i++)
				{
					newReplacement = createNode(str[i]);
					newReplacement->next = current->next;
					current->next = newReplacement;
					current = current->next;
					listy->length++;
				}

				prev = current;
				current = current->next;
			}
		}
		else
		{
			prev = current;
			current = current->next;
		}
	}
}

void reverseListyString(ListyString *listy)
{
	ListyNode *current, *temp, *prev;

	if (listy == NULL || listy->head == NULL)
	{
		return;
	}

	current = listy->head;
	prev = NULL;

	//Loop through while the listyhead doesn't equal NULL
	while (current != NULL)
	{
		//Setting up temporary variables in order to switch values
		temp = current->next;
		current->next = prev;
		prev = current;
		current = temp;
	}
	listy->head = prev;
}

ListyString *listyCat(ListyString *listy, char *str)
{
	ListyNode *catTemp;
	int catLen, i;

	if (str == NULL || str[0] == '\0')
	{
		return listy;
	}

	catLen = strlen(str);

	//Checking to see if ListyString is NULL
	if (listy == NULL)
	{
		//If not check if string is Empty
		if (str[0] == '\0')
		{
			//Create node for Head and set temp equal to Head
			listy->head = createNode(str[0]);
			catTemp = listy->head;

			for (i = 1; i < catLen; i++)
			{
				catTemp->next = createNode(str[i]);
				catTemp = catTemp->next;
			}

			return listy;
		}

		else if (str == NULL)
		{
			return NULL;
		}
	}
	else if (listy->head == NULL)
	{
		//If original ListyString's head is null, create a Node
		listy->head = createNode(str[0]);
		catTemp = listy->head;

		for (i = 1; i < catLen; i++)
		{
			catTemp->next = createNode(str[i]);
			catTemp = catTemp->next;
		}
		listy->length = listy->length + catLen;
		return listy;
	}

		//While not Null, cat the string
		catTemp = listy->head;
		while (catTemp->next != NULL)
		{
			catTemp = catTemp->next;
		}

		for (i = 0; i < catLen; i++)
		{
			catTemp->next = createNode(str[i]);
			catTemp = catTemp->next;
		}

		listy->length = listy->length + catLen;
		return listy;
}

int listyCmp(ListyString *listy1, ListyString *listy2)
{
	ListyNode *tempListy1, *tempListy2;
	int lenOne, lenTwo;

	//Comparing pointers, for both ListyStrings
	if (listy1 == listy2)
	{
		return 0;
	}

	if (listy1 == NULL || listy2 == NULL)
	{
		return 1;
	}

	if (listy1->head == listy2->head)
	{
		return 0;
	}

	lenOne = listy1->length;
	lenTwo = listy2->length;

	//If lengths not equal, then neither are strings
	if (lenOne != lenTwo)
	{
		return 1;
	}

	tempListy1 = listy1->head;
	tempListy2 = listy2->head;

	while (tempListy1->data == tempListy2->data)
	{
		if (tempListy1->next == NULL || tempListy2->next == NULL)
		{
			return 0;
		}

		tempListy1 = tempListy1->next;
		tempListy2 = tempListy2->next;
	}

	return 1;
}

int listyLength (ListyString *listy)
{
	if (listy == NULL)
	{
		return -1;
	}
	else if (listy->head == NULL)
	{
		return 0;
	}

	//Return the length of ListryString
	return listy->length;
}

void printListyString(ListyString *listy)
{
	//If ListryString is empty or Head is Null
	if (listy == NULL || listy->length == 0 || listy->head == NULL)
	{
		printf("(empty string)\n");
		return;
	}

	ListyNode *temp = listy->head;

	//go through entire Temp until you hit NULL and print out each letter and set
	//Node to next
	while (temp != NULL)
	{
		printf("%c", temp->data);
		temp = temp->next;
	}
	printf("\n");
}
