#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main()
{
	FILE* f = fopen("Book.txt", "r"), * fout = fopen("BookOut.txt", "w");  // Файли для зчитування книг та їх запису
	LIST* pHead = NULL;
	int n = 0;

	if (!f)
	{
		printf("Error with file open ");
		return -1;
	}

	ReadBook(&pHead, f);     // Зчитування файлу

	AddList(&pHead);   // Додавання книги

	SortBook(&pHead);   // Сортування книг за кількістю сторінок

	PrintList(pHead);       // Вивід списка до видалення

	printf("\n\n\n%60s\n\n\n", "After Delete");

	DeleteList(&pHead);   // Видалення книг

	PrintList(pHead);    // Вивід списку книг після видалення

	do
	{
		getchar();
        printf("\n\nEnter index lista which will be delete  or enter 0 for exit from program :  \n");  
        scanf("%d \n", &n);                                                        

		DeleteYour(&pHead, n);           //Додаткова функція для редагування списку
		PrintList(pHead);                //яка дозволяє видаляти будь які книги за 
										 //їхніми індексами
	} while (n);
	
	BookInFile(pHead, fout);  //Записуємо відредаговані книги у файл

	FreeList(pHead);    // Очищення динамічної пам'яті

	return 0;
}
