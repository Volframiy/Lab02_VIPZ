#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

int main()
{
	FILE* f = fopen("Book.txt", "r"), * fout = fopen("BookOut.txt", "w");  // ����� ��� ���������� ���� �� �� ������
	LIST* pHead = NULL;
	int n = 0;

	if (!f)
	{
		printf("Error with file open ");
		return -1;
	}

	ReadBook(&pHead, f);     // ���������� �����

	AddList(&pHead);   // ��������� �����

	SortBook(&pHead);   // ���������� ���� �� ������� �������

	PrintList(pHead);       // ���� ������ �� ���������

	printf("\n\n\n%60s\n\n\n", "After Delete");

	DeleteList(&pHead);   // ��������� ����

	PrintList(pHead);    // ���� ������ ���� ���� ���������

	do
	{
		getchar();
        printf("\n\nEnter index lista which will be delete  or enter 0 for exit from program :  \n");  
        scanf("%d \n", &n);                                                        

		DeleteYour(&pHead, n);           //��������� ������� ��� ����������� ������
		PrintList(pHead);                //��� �������� �������� ���� �� ����� �� 
										 //����� ���������
	} while (n);
	
	BookInFile(pHead, fout);  //�������� ����������� ����� � ����

	FreeList(pHead);    // �������� �������� ���'��

	return 0;
}
