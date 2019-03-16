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
 * 1. Реализовать простейшую хэш-функцию. На вход функции подается строка, на выходе сумма кодов символов.
 * 2. Переписать программу, реализующее двоичное дерево поиска.
 * а) Добавить в него обход дерева различными способами;
 * б) Реализовать поиск в двоичном дереве поиска;
 * в) *Добавить в программу обработку командной строки с помощью которой можно указывать
 * из какого файла считывать данные, каким образом обходить дерево.
 * 3. *Разработать базу данных студентов из двух полей “Имя”, “Возраст”, “Табельный номер” в которой использовать все знания, полученные на уроках.
 * Считайте данные в двоичное дерево поиска. Реализуйте поиск по какому-нибудь полю базы данных (возраст, вес)
 */ 

void fnTask1()
{
	char acString[100] = {0};

	printf("Enter string:");
	scanf("%s", acString);

	int iStringLength = strlen(acString);
	int iStringLinesCount = iStringLength / 7;
	int iStringLinesRemainder = iStringLength % 7;

	char acBaseVector[] = { 10, 33, 1, 45, 5, 77, 9 };
	char acHash[7] = {0};

	char acArray1[7] = {0};
	char acArray2[7] = {0};

	int iIndex=0;
	for (;iIndex<7;iIndex++) {
		int iStringIndex = iIndex % iStringLength;
		acArray1[iIndex] = acBaseVector[iIndex] * (acString[iStringIndex] + iIndex) * (iIndex + 1);
	}

	iIndex=0;
	for (;iIndex<7;iIndex++) {
		int iStringIndex = iIndex % iStringLength;
		iStringIndex = (iStringIndex + acString[iStringIndex]) % iStringLength;
		acArray2[iIndex] = acBaseVector[iIndex] + (acString[iStringIndex] + iIndex) * (iIndex + 1);
	}

	iIndex=0;
	for (;iIndex<7;iIndex++) {
		acHash[iIndex] = acArray1[iIndex] ^ acArray2[iIndex];
	}

	iIndex=0;
	for (;iIndex<iStringLinesCount;iIndex++) {
		int iHashIndex=0;
		for (;iHashIndex<7;iHashIndex++) {
			acHash[iHashIndex] = acHash[iHashIndex] ^ acString[iIndex*7 + iHashIndex];
		}
	}

	int iHashIndex=0;
	for (;iHashIndex<iStringLinesRemainder;iHashIndex++) {
		acHash[iHashIndex] = acHash[iHashIndex] ^ acString[iStringLinesCount*7 + iHashIndex];
	}

	printf("Result hash: ");
	iIndex=0;
	for (;iIndex<7;iIndex++) {
		printf("%02x ", (unsigned)(unsigned char) acHash[iIndex]);
	}
	printf("\n");
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
			case 0:
				printf("Bye-bye\n");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
