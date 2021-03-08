#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include "func.h"
//Констаннта яка дорівнює початковій кількості книг
#define SIZEBOOK 10
//Констаннта яка дорівнює максимальній довжині стрічки для зчитування книг
#define SIZESTR 200

//*****************************************************************************
//Функція яка зчитує книги з текстового файлу

void ReadBook(LIST** pHead, FILE* f)
{
	char AllBook[SIZESTR] = "", * lexsema = NULL;
	LIST* pNew = (LIST*)malloc(sizeof(LIST));

	if (!pNew)
	{
		printf("Error with dynamically memory ");
		return;
	}

	fgets(AllBook, SIZESTR, f);

	lexsema = strtok(AllBook, ",");
	strcpy(pNew->book.surname, lexsema);

	lexsema = strtok(NULL, ",");
	strcpy(pNew->book.name, lexsema);

	lexsema = strtok(NULL, ",");
	strcpy(pNew->book.bookname, lexsema);

	lexsema = strtok(NULL, ",");
	pNew->book.year = atoi(lexsema);

	lexsema = strtok(NULL, ",");
	pNew->book.pages = atoi(lexsema);

	lexsema = strtok(NULL, ",");
	pNew->book.price = atoi(lexsema);

	if (!(*pHead))
		*pHead = pNew;

	for (int i = 0; i < SIZEBOOK - 1; i++)
	{
		LIST* pTemp = (LIST*)malloc(sizeof(LIST));

		if (!pTemp)
		{
			printf("Error with dynamically memory ");
			return;
		}

		pNew->next = pTemp;
		pNew = pTemp;
		pNew->next = NULL;

		fgets(AllBook, SIZESTR, f);

		lexsema = strtok(AllBook, ",");
		strcpy(pNew->book.surname, lexsema);

		lexsema = strtok(NULL, ",");
		strcpy(pNew->book.name, lexsema);

		lexsema = strtok(NULL, ",");
		strcpy(pNew->book.bookname, lexsema);

		lexsema = strtok(NULL, ",");
		pNew->book.year = atoi(lexsema);

		lexsema = strtok(NULL, ",");
		pNew->book.pages = atoi(lexsema);

		lexsema = strtok(NULL, ",");
		pNew->book.price = atoi(lexsema);
	}

	return;
}
//*****************************************************************************
//Сортує бульбашкою список книг за їхньою ціною

void SortBook(LIST** pHead)
{
	LIST* pTemp = *pHead, * pTempNext = pTemp->next, * pForSwap = NULL, *pTempPrev = NULL;
	int k = 0;

	for (int i = 0; i < SIZEBOOK - 1; i++)
	{
		while (pTempNext)
		{
			if (pTemp->book.pages > pTempNext->book.pages)
			{
				pTemp->next = pTempNext->next;
				pTempNext->next = pTemp;

				pForSwap = pTemp;
				pTemp = pTempNext;
				pTempNext = pForSwap;

				if (!k)
					*pHead = pTemp;
				if (k)
					pTempPrev->next = pTemp;

				pTempPrev = pTemp;
				pTemp = pTemp->next;
				pTempNext = pTempNext->next;
			}
			else
			{
				pTempPrev = pTemp;
				pTemp = pTemp->next;
				pTempNext = pTempNext->next;
			}
			k++;
		}
		k = 0;
		pTemp = *pHead;
		pTempNext = pTemp->next;
	}
}
//*****************************************************************************
//Записує всі книги після видалення у новий файл

void BookInFile(LIST* pHead, FILE* fout)
{
	LIST* pTemp = pHead;

	while (pTemp)
	{
		fprintf(fout, "%s %s", pTemp->book.surname , ",");
		fprintf(fout, "%s %s", pTemp->book.name , ",");
		fprintf(fout, "%s %s", pTemp->book.bookname , ",");
		fprintf(fout, "%d %s", pTemp->book.year , ",");
		fprintf(fout, "%d %s", pTemp->book.pages , ",");
		fprintf(fout, "%d %s", pTemp->book.price , "\n");
		
		pTemp = pTemp->next;
	}

}
//*****************************************************************************
//Додавання нової книги на початок

void AddFirstList(LIST** pHead, LIST* pNew)
{
	pNew->next = *pHead;
	*pHead = pNew;
	return;
}
//*****************************************************************************
//Додавання нової книги в середину

void AddOthertList(LIST* pNew, LIST** pRun)
{
	pNew->next = (*pRun)->next;
	(*pRun)->next = pNew;
	return;
}
//*****************************************************************************
//Додавання нової книги в кінець

void AddLastList(LIST* pNew, LIST* pRun)
{
	pRun->next = pNew;
	pNew->next = NULL;
	return;
}
//*****************************************************************************
//Загальна функція додавання в якій вже відбуваються виклики функцій додавання в різні місця

void AddList(LIST** pHead)
{
	char str[SIZESTR] = "", * lexsema;
	LIST* pNew = (LIST*)malloc(sizeof(LIST));
	LIST* pRun = *pHead;

	if (!pNew)
	{
		printf("Error with dynamically memory ");
		return;
	}

	printf("Enter <Surname>,<Name>,<Bookname>,<Year>,<Pages>,<Price> : \n");
	scanf("%s ", str);
	getchar();
	lexsema = strtok(str, ",");

	strcpy(pNew->book.surname, lexsema);
	lexsema = strtok(NULL, ",");

	strcpy(pNew->book.name, lexsema);
	lexsema = strtok(NULL, ",");

	strcpy(pNew->book.bookname, lexsema);
	lexsema = strtok(NULL, ",");

	pNew->book.year = atoi(lexsema);
	lexsema = strtok(NULL, ",");

	pNew->book.pages = atoi(lexsema);
	lexsema = strtok(NULL, ",");

	pNew->book.price = atoi(lexsema);
	lexsema = strtok(NULL, ",");

	while (1)
	{
		if (strcmp(pNew->book.surname, (*pHead)->book.surname) == -1)
		{
			AddFirstList(pHead, pNew);
			break;
		}

		if (strcmp(pNew->book.surname, pRun->book.surname) == 1 && pRun->next == NULL)
		{
			AddLastList(pNew, pRun);
			break;
		}

		if (strcmp(pNew->book.surname, pRun->next->book.surname) == -1 && strcmp(pNew->book.surname, pRun->book.surname) == 1)
		{
			AddOthertList(pNew, &pRun);
			break;
		}

		pRun = pRun->next;
	}

	return;
}
//*****************************************************************************
//Видалення першої книги

void DeleteFirstList(LIST** pHead)
{
	LIST* pTemp = *pHead;
	(*pHead) = (*pHead)->next;

	free(pTemp);

	return;
}
//*****************************************************************************
//Видалення книги з середини

void DeleteOtherList(LIST* pRun, LIST* pTemp)
{
	pTemp->next = pRun->next;

	free(pRun);

	return;
}
//*****************************************************************************
//Видалення книги з кінця

void DeleteLastList(LIST* pRun, LIST* pTemp)
{
	pTemp->next = NULL;

	free(pRun);

	return;
}
//*****************************************************************************
//Додаткова функція видалення яка видаляє книги по індексу

void DeleteYour(LIST** pHead, int n)   
{
	LIST* pTemp = *pHead;
	LIST* pPrevTemp = NULL;
	int temp = 1;

	pPrevTemp = pTemp;
	pTemp = pTemp->next;

	while (pTemp)
	{
		temp++;
		if (pTemp->next)
		{
			pPrevTemp = pTemp;
		}
		pTemp = pTemp->next;
	}

	if (n > temp)
	{
		printf("There is no book with such an index ");
		return;
	}

	if (n == 1)
	{
		DeleteFirstList(pHead);
		return;
	}

	if (n == temp)
	{
		DeleteLastList(pPrevTemp->next, pPrevTemp);
		return;
	}
	else
	{
		pTemp = *pHead;
		for (int i = 2; i < n; i++)
		{
			pTemp = pTemp->next;
		}
		pPrevTemp = pTemp->next;
		pTemp->next = pTemp->next->next;
		free(pPrevTemp);
		return;
	}
}  
//*****************************************************************************
//Загальна функція видалення яка вже викликає функції видалення книг в різних місцях

void DeleteList(LIST** pHead)
{
	while (1)
	{
		if ((*pHead)->book.surname[0] == 'A' || (*pHead)->book.surname[0] == 'B' || (*pHead)->book.surname[0] == 'C' || (*pHead)->book.surname[0] == 'D')
		{
			DeleteFirstList(pHead);
			continue;
		}
		break;
	}

	LIST* pRun = *pHead;
	LIST* pTemp = pRun;  //Попередній до pRun

	pRun = pRun->next;

	while (pRun)
	{

		if ((pRun->book.surname[0] == 'A' || pRun->book.surname[0] == 'B' || pRun->book.surname[0] == 'C' || pRun->book.surname[0] == 'D') && pRun->next == NULL)
		{
			DeleteLastList(pRun, pTemp);
			break;
		}

		if (pRun->book.surname[0] == 'A' || pRun->book.surname[0] == 'B' || pRun->book.surname[0] == 'C' || pRun->book.surname[0] == 'D')
		{
			DeleteOtherList(pRun, pTemp);
			pRun = pTemp->next;
			continue;
		}

		pTemp = pTemp->next;
		pRun = pTemp->next;
	}
}
//*****************************************************************************
//Функція виводу на екран всіх книг

void PrintList(LIST* pHead)
{
	LIST* pRun = pHead;

	for (int i = 0; i < 109; i++)
		printf("-");
	printf("\n");

	printf("| %-15s | %-15s | %-15s | %-15s | %-15s | %-15s |\n", "Surname", "Name", "Bookname", "Year", "Pages", "Price");

	for (int i = 0; i < 109; i++)
		printf("-");
	printf("\n");

	while (pRun)
	{
		printf("| %-15s | %-15s | %-15s | %-15d | %-15d | %-15d | \n", \
			pRun->book.surname, pRun->book.name, pRun->book.bookname, pRun->book.year, pRun->book.pages, pRun->book.price);

		for (int i = 0; i < 109; i++)
			printf("-");
		printf("\n");

		pRun = pRun->next;

	}
	return;
}
//*****************************************************************************
//Очищення динамічної памяті

void FreeList(LIST* pHead)
{
	LIST* pTemp = pHead;

	while (pTemp)
	{
		pHead = pHead->next;
		free(pTemp);
		pTemp = pHead;
	}
	return;
}