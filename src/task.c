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
	StackItem* poLast;
} Stack;

void fnPushInt(Stack* poStack, int iValue)
{
	StackItem* poCurrent = (StackItem*) malloc(sizeof(StackItem));
	poCurrent->poPrevious = 0;
	poCurrent->iValue = iValue;
	
	if (poStack->poLast) {
		poCurrent->poPrevious = poStack->poLast;
		poStack->poLast = poCurrent;
	}
	poStack->poLast = poCurrent;
}

void fnPop(Stack* poStack)
{
	
}

void fnClear(Stack* poStack)
{
	StackItem* poCurrentItem = poStack->poLast;
	
	while (poCurrentItem) {
		poCurrentItem = poCurrentItem->poPrevious;
		free(poCurrentItem);
	}
}

void fnTask1()
{
	Stack* poStack = (Stack*) malloc(sizeof(Stack));
	poStack->poLast = 0;
	
	int iNumber = 0;
	
	printf("Enter number:\n");
	scanf("%d", &iNumber);
	
	fnPushInt(poStack, 1);
	
	printf("Result: ");
	
	StackItem* poCurrentItem = poStack->poLast;
	
	while (poCurrentItem) {
		printf("%d", poCurrentItem->iValue);
		poCurrentItem = poCurrentItem->poPrevious;
	}
	
	fnClear(poStack);
	free(poStack);
}

void fnTask2()
{

}

void fnTask3()
{

}

void fnTask4()
{

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
				printf("Bye-bye");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
