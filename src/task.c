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
 * 1. 1. Попробовать оптимизировать пузырьковую сортировку.
 * Сравнить количество операций сравнения оптимизированной и не оптимизированной программы.
 * Написать функции сортировки, которые возвращают количество операций.
 * 2. *Реализовать шейкерную сортировку.
 * 3. Реализовать бинарный алгоритм поиска в виде функции,
 * которой передается отсортированный массив.
 * Функция возвращает индекс найденного элемента или -1, если элемент не найден.
 * 4. *Подсчитать количество операций для каждой из сортировок и сравнить его с асимптотической сложностью алгоритма.
 * Записывайте в начало программы условие и свою фамилию.
 * Все решения создавайте в одной программе.
 * Со звёздочками выполняйте в том случае,
 * если вы решили задачи без звёздочек.
 */

int fnBubbleSort(int aiArray[10])
{
	printf("before sort: ");
	for (int iIndex=0; iIndex<10; iIndex++) {
		printf("%d ", aiArray[iIndex]);
	}
	printf("\n");

	int iOperations = 0;

	for (int iIndex=0; iIndex<9; iIndex++) {
		iOperations += 2;

		iOperations += 1;
		if (aiArray[iIndex]>aiArray[iIndex+1]) {
			int iTempIndex = iIndex+1;
			iOperations += 2;

			do {
				int Temp = aiArray[iTempIndex];
				aiArray[iTempIndex] = aiArray[iTempIndex-1];
				aiArray[iTempIndex-1] = Temp;
				iTempIndex--;

				iOperations += 9;
			} while (iTempIndex>0 && aiArray[iTempIndex-1]>aiArray[iTempIndex]);
		}
	}

	printf("after sort: ");
	for (int iIndex=0; iIndex<10; iIndex++) {
		printf("%d ", aiArray[iIndex]);
	}
	printf("\n");

	return iOperations;
}

int fnOptimizedBubbleSort(int aiArray[10])
{
	int iOperations = 0;

	return iOperations;
}

void fnTask1()
{
	int aiArray[10] = {3, 2, 1, 5, 6, 7, 4, 9, 8, 10};
	//int aiArray2[10] = {3, 2, 1, 5, 6, 7, 4, 9, 8, 10};

	printf("bubble sort operations: %d\n", fnBubbleSort(aiArray));
	printf("optimized bubble sort operations: %d\n", fnOptimizedBubbleSort(aiArray));
}

void fnTask2()
{

}

void fnTask3()
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
				fnTask3();
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
