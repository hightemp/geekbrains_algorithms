/*
 ============================================================================
 Name        : task1.c
 Author      : Anton PAnov
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 1. Реализовать перевод из 10 в 2 систему счисления с использованием стека.
 * 2. Добавить в программу “реализация стека на основе односвязного списка” проверку на выделение памяти. 
 * Если память не выделяется, то выводится соответствующее сообщение. 
 * Постарайтесь создать ситуацию, когда память не будет выделяться (добавлением большого количества данных).
 * 3. Написать программу, которая определяет, является ли введенная скобочная последовательность правильной. 
 * Примеры правильных скобочных выражений: (), ([])(), {}(), ([{}]), неправильных — )(, ())({), (, ])}), ([(]) для скобок [,(,{.
 * Например: (2+(2*2)) или [2/{5*(4+7)}]
 * 4. *Создать функцию, копирующую односвязный список (то есть создает в памяти копию односвязного списка, без удаления первого списка)
 * 5. **Реализовать алгоритм перевода из инфиксной записи арифметического выражения в постфиксную.
 * 6. *Реализовать очередь.
 */ 

typedef struct StackItem 
{
	struct StackItem* poPrevious;
	int iValue;
} StackItem;

typedef struct
{
	int iSize;
	StackItem* poLast;
} Stack;

int fnPushInt(Stack* poStack, int iValue)
{
	StackItem* poCurrent = (StackItem*) malloc(sizeof(StackItem));
	
	if (!poCurrent) {
		printf("Can't allocate memory. Stack size: %d\n", poStack->iSize);
		return 1;
	}
	
	poStack->iSize++;
	poCurrent->poPrevious = 0;
	poCurrent->iValue = iValue;
	
	if (poStack->poLast) {
		poCurrent->poPrevious = poStack->poLast;
		poStack->poLast = poCurrent;
	}
	poStack->poLast = poCurrent;
	
	return 0;
}

int fnPop(Stack* poStack)
{
	int iResult = 0;
	
	if (poStack->poLast) {
		poStack->iSize--;
		StackItem* poPrevious = poStack->poLast->poPrevious;
		iResult = poStack->poLast->iValue;
		free(poStack->poLast);
		poStack->poLast = poPrevious;
	}
	
	return iResult;
}

void fnClear(Stack* poStack)
{
	StackItem* poCurrentItem = poStack->poLast;
	
	while (poCurrentItem) {
		StackItem* poPrevious = poCurrentItem->poPrevious;
		free(poCurrentItem);
		poCurrentItem = poPrevious;
	}
}

void fnTask1()
{
	Stack* poStack = (Stack*) malloc(sizeof(Stack));
	poStack->poLast = 0;
	poStack->iSize = 0;
	
	int iNumber = 0;
	
	printf("Enter number:\n");
	scanf("%d", &iNumber);

	while (iNumber>0) {	
		fnPushInt(poStack, iNumber % 2);
		iNumber = iNumber / 2;
	}
	
	printf("Result: ");
	
	while (poStack->poLast) {
		printf("%d", fnPop(poStack));
	}
	
	fnClear(poStack);
	free(poStack);
}

void fnTask2()
{
	Stack* poStack = (Stack*) malloc(sizeof(Stack));
	poStack->poLast = 0;
	poStack->iSize = 0;
	
	while(!fnPushInt(poStack, 1)) {
		//
	}
	
	fnClear(poStack);
	free(poStack);
}

typedef struct BracketStackItem 
{
	struct BracketStackItem* poPrevious;
	char cValue;
} BracketStackItem;

typedef struct
{
	int iSize;
	BracketStackItem* poLast;
} BracketStack;

int fnPushBracket(BracketStack* poStack, char cValue)
{
	BracketStackItem* poCurrent = (BracketStackItem*) malloc(sizeof(BracketStackItem));
	
	if (!poCurrent) {
		printf("Can't allocate memory. Stack size: %d\n", poStack->iSize);
		return 1;
	}
	
	poStack->iSize++;
	poCurrent->poPrevious = 0;
	poCurrent->cValue = cValue;
	
	if (poStack->poLast) {
		poCurrent->poPrevious = poStack->poLast;
	}
	poStack->poLast = poCurrent;
	
	return 0;
}

void fnPopBracket(BracketStack* poStack)
{
	if (poStack->poLast) {
		poStack->iSize--;
		BracketStackItem* poPrevious = poStack->poLast->poPrevious;
		free(poStack->poLast);
		poStack->poLast = poPrevious;
	}
}

void fnClearBrackets(BracketStack* poStack)
{
	BracketStackItem* poCurrentItem = poStack->poLast;
	
	while (poCurrentItem) {
		BracketStackItem* poPrevious = poCurrentItem->poPrevious;
		free(poCurrentItem);
		poCurrentItem = poPrevious;
	}
}

void fnTask3()
{
	BracketStack* poBracketStack = (BracketStack*) malloc(sizeof(BracketStack));
	poBracketStack->poLast = 0;
	poBracketStack->iSize = 0;
	
	char sExpression[100] = "\0";
	
	printf("Enter expression:\n");
	
	scanf("%s", sExpression);
	
	int iIndex = 0;
	int bResult = 1;
	
	char caBrackets[] = {'(', ')', '[', ']', '{', '}'};
	
	while (sExpression[iIndex]) {
		if (sExpression[iIndex]=='(' || sExpression[iIndex]=='{' || sExpression[iIndex]=='[') {
			fnPushBracket(poBracketStack, sExpression[iIndex]);
		}
		
		int iBracketIndex=0;
		
		for (iBracketIndex=0; iBracketIndex<6; iBracketIndex+=2) {
			if (sExpression[iIndex]==caBrackets[iBracketIndex+1]) {
				if (!poBracketStack->poLast) {
					bResult = 0;
					goto END;
				}
				if (poBracketStack->poLast->cValue!=caBrackets[iBracketIndex]) {
					bResult = 0;
					goto END;
				}
				fnPopBracket(poBracketStack);
				break;
			}
		}
		iIndex++;
	}
	END:
	
	if (bResult) {
		printf("The sequence is correct\n");
	} else {
		printf("The sequence is not correct\n");
	}
	
	fnClearBrackets(poBracketStack);
	free(poBracketStack);
}

typedef struct ListItem
{
	int iValue;
	struct ListItem *poNext;
} ListItem;

typedef struct List
{
	int iSize;
	ListItem* poFirst;
	ListItem* poLast;
} List;

void fnListInsert(List* poList, int iValue, int iPosition)
{
	ListItem* poCurrentItem = poList->poFirst;
	int iCurrentPosition = iPosition;
	
	do {
		if (!iCurrentPosition) {
			ListItem* poListItem = (ListItem*) malloc(sizeof(ListItem));
			
			if (!poListItem) {
				printf("Can't allocate memory. Stack size: %d\n", poList->iSize);
				return;
			}
			
			poListItem->iValue = iValue;
			if (poCurrentItem) {
				poListItem->poNext = poCurrentItem;
			} else {
				poListItem->poNext = 0;
			}
			poList->iSize++;

			if (!poList->poFirst) {
				poList->poFirst = poListItem;
			} else {
				if (!iPosition) {
					poList->poFirst = poListItem;
				}
			}
			return;
		}
		if (poCurrentItem) {
			poCurrentItem = poCurrentItem->poNext;
			iCurrentPosition--;
		}
	} while(poCurrentItem);
}

void fnListPush(List* poList, int iValue)
{
	ListItem* poCurrent = (ListItem*) malloc(sizeof(ListItem));
	
	if (!poCurrent) {
		printf("Can't allocate memory. Stack size: %d\n", poList->iSize);
		return;
	}
	
	poList->iSize++;
	poCurrent->poNext = 0;
	poCurrent->iValue = iValue;
	
	if (poList->poLast) {
		poList->poLast->poNext = poCurrent;
		poList->poLast = poCurrent;
	}
	
	poList->poLast = poCurrent;
	
	if (!poList->poFirst) {
		poList->poFirst = poCurrent;
	}
}

void fnListCopy(List* poList, List* poList2)
{
	ListItem* poCurrentItem = poList->poFirst;
	
	while (poCurrentItem) {
		fnListPush(poList2, poCurrentItem->iValue);
		poCurrentItem = poCurrentItem->poNext;
	}
}

void fnListPrint(List* poList)
{
	ListItem* poCurrentItem = poList->poFirst;
	
	while (poCurrentItem) {
		printf("%d ", poCurrentItem->iValue);
		poCurrentItem = poCurrentItem->poNext;
	}
}

void fnListClear(List* poList)
{
	ListItem* poCurrentItem = poList->poFirst;
	
	while (poCurrentItem) {
		ListItem* poNext = poCurrentItem->poNext;
		free(poNext);
		poCurrentItem = poNext;
	}
}

void fnTask4()
{
	List* poList = (List*) malloc(sizeof(List));
	poList->poFirst = 0;
	poList->iSize = 0;

	int iIndex = 0;
	
	for (;iIndex<10;iIndex++) {
		fnListPush(poList, iIndex);
	}

	List* poList2 = (List*) malloc(sizeof(List));
	poList2->poFirst = 0;
	poList2->iSize = 0;

	fnListCopy(poList, poList2);
	
	printf("List 1: ");
	fnListPrint(poList);
	printf("\n");
	printf("List 2: ");
	fnListPrint(poList2);
	printf("\n");
	
	fnListClear(poList2);
	fnListClear(poList);
	free(poList2);
	free(poList);
}

void fnTask5()
{

}

void fnTask6()
{

}

int main(void) {

	int iSel = 0;

	printf("Author: Anton Panov\n");

	do
	{
		printf("\nSelect task:");
		scanf("%i", &iSel);
		printf("\n");
		switch (iSel)
		{
			case 1:
				fnTask1();
				break;
			case 2:
				fnTask2();
				break;
			case 3:
				fnTask3();
				break;
			case 4:
				fnTask4();
				break;
			case 5:
				fnTask5();
				break;
			case 6:
				fnTask6();
				break;
			case 0:
				printf("Bye-bye\n");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
