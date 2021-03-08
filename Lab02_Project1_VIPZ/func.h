#ifndef FUNC_H
#define FUNC_H

typedef class myclass
{
public:
	char surname[30];
	char name[30];
	char bookname[30];
	int year;
	int pages;
	int price;
}BOOK;

typedef class list
{
public:
	BOOK book;
	class list* next;

}LIST;

void ReadBook(LIST** pHead, FILE* f);
void SortBook(LIST** pHead);
void AddFirstList(LIST** pHead, LIST* pNew);
void AddOthertList(LIST* pNew, LIST** pRun);
void AddLastList(LIST* pNew, LIST* pRun);
void AddList(LIST** pHead);
void DeleteFirstList(LIST** pHead);
void DeleteOtherList(LIST* pRun, LIST* pTemp);
void DeleteLastList(LIST* pRun, LIST* pTemp);
void DeleteList(LIST** pHead);
void PrintList(LIST* pHead);
void FreeList(LIST* pHead);
void DeleteYour(LIST** pHead, int n);
void BookInFile(LIST* pHead, FILE* fout);

#endif 

