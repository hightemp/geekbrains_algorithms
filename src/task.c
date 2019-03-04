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
 * 1. Реализовать функцию перевода из 10 системы в двоичную используя рекурсию.
 * 2. Реализовать функцию возведения числа a в степень b:
 * a. без рекурсии;
 * b. рекурсивно;
 * c. *рекурсивно, используя свойство чётности степени.

 * 3. Исполнитель Калькулятор преобразует целое число, записанное на экране. У исполнителя две команды, каждой команде присвоен номер:
 * 1. Прибавь 1
 * 2. Умножь на 2
 * Первая команда увеличивает число на экране на 1, вторая увеличивает это число в 2 раза.
 * Сколько существует программ, которые число 3 преобразуют в число 20? а) с использованием массива; б) с использованием рекурсии.
 * Записывайте в начало программы условие и свою фамилию.
 * Все решения создавайте в одной программе.
 * Со звёздочками выполняйте в том случае, если вы решили задачи без звёздочек.
 */

void fnPrint(unsigned int uiN)
{
	if (uiN) {
	   fnPrint(uiN >> 1);
	   printf("%lu", (uiN & 1));
	}
}

void fnTask1()
{
	unsigned int uiN = 0;
	printf("Enter number [0-inf):");
	scanf("%u", &uiN);

	fnPrint(uiN);
}

unsigned int fnPow(unsigned int uiA, unsigned int uiB)
{
	unsigned int uiResult = 1;

	for (int iIndex=0; iIndex<uiB; iIndex++) {
		uiResult *= uiA;
	}

	return uiResult;
}

unsigned int fnPowRecursion(unsigned int uiA, unsigned int uiB)
{
	return uiB ? uiA*fnPowRecursion(uiA, uiB-1) : 1;
}

void fnTask2()
{
	unsigned int uiA = 0;
	unsigned int uiB = 0;

	printf("Enter number a:");
	scanf("%u", &uiA);
	printf("Enter number b:");
	scanf("%u", &uiB);

	printf("Function 1: %u\n", fnPow(uiA, uiB));
	printf("Function 2: %u\n", fnPowRecursion(uiA, uiB));
}

unsigned int fnGetVariants()
{
	unsigned int auiCount[100] = {0};
	unsigned int auiCommand[100] = {0};
	unsigned int auiSum[100] = {0};
	unsigned int auiN[100] = {0};
	unsigned int auiCountIndex[100] = {0};
	unsigned int uiIndex = 0;
	unsigned int uiIndexesIndex = 0;
	unsigned int uiCommand = 1;
	unsigned int uiNumber = 3;

	//do {
		//if () {

		//}

	//} while();

	unsigned int uiCountCount = 0;

	for (int iIndex=0; iIndex<100; iIndex++) {
		if (auiCount[iIndex]>0) {
			uiCountCount++;
		}
	}

	return uiCountCount;
}

unsigned int fnGetVariantsRecursion(unsigned int uiN, unsigned int uiCountIndex, unsigned int uiCount, unsigned int iCommand)
{
	static unsigned int auiCount[1000] = {0};

	if (uiN==20) {
		auiCount[uiCountIndex] = uiCount;
		return uiCountIndex;
	} else if (uiN>20) {
		auiCount[uiCountIndex] = 0;
		return uiCountIndex;
	}

	if (iCommand==1) {
		uiN += 1;
		uiCount++;
		auiCount[uiCountIndex] = uiCount;
	}
	if (iCommand==2) {
		uiN *= 2;
		uiCount++;
		uiCountIndex++;
		auiCount[uiCountIndex] = uiCount;
	}

	uiCountIndex = fnGetVariantsRecursion(uiN, uiCountIndex, uiCount, 1);
	uiCountIndex = fnGetVariantsRecursion(uiN, uiCountIndex, uiCount, 2);

	if (iCommand==0) {
		unsigned int uiCountCount = 0;

		for (int iIndex=0; iIndex<1000; iIndex++) {
			if (auiCount[iIndex]>0) {
				uiCountCount++;
			}
		}
		return uiCountCount;
	}

	return uiCountIndex;
}

void fnTask3()
{
	printf("a) variants: %u\n", fnGetVariants());
	printf("b) variants: %u\n", fnGetVariantsRecursion(3, 0, 0, 0));
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
			case 0:
				printf("Bye-bye");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
