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
 * 1. Реализовать сортировку подсчетом.
 * 2. Реализовать быструю сортировку.
 * 3. *Реализовать сортировку слиянием.
 * 4. **Реализовать алгоритм сортировки со списком
 * 5. Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов. Заполнить таблицу (см. методичку)
 */ 

void fnPrintArray(int aiArray[])
{
	int iIndex = 0;
	for (;iIndex<9; iIndex++) {
		printf("%d ", aiArray[iIndex]);
	}
	printf("\n");
}

void fnCountingSort(int aiArray[])
{
	int iIndex = 0;
	int iCIndex = 0;
	int aiC[9] = {0};
	int iAIndex = 0;

	for (iIndex = 0;iIndex<9;iIndex++) {
		aiC[aiArray[iIndex]-1]++;
	}
	for (iCIndex = 1;iCIndex<10;iCIndex++) {
		for (iIndex = 0;iIndex<aiC[iCIndex-1];iIndex++) {
			aiArray[iAIndex] = iCIndex;
			iAIndex++;
		}
	}
}

void fnTask1()
{
	int aiArray[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

	printf("Counting sort\n");

	fnPrintArray(aiArray);

	fnCountingSort(aiArray);

	fnPrintArray(aiArray);
}

void fnQuickSort(int aiArray[])
{

}

void fnTask2()
{
	int aiArray[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

	printf("Quick sort\n");

	fnPrintArray(aiArray);

	fnQuickSort(aiArray);

	fnPrintArray(aiArray);
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
			case 0:
				printf("Bye-bye\n");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
