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

void fnTask1()
{

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
