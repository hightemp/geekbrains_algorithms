/*
 ============================================================================
 Name        : task.c
 Author      : Anton PAnov
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**
 * 1. *Количество маршрутов с препятствиями. Реализовать чтение массива с препятствием и нахождение количество маршрутов.
 * Например, карта:
 * 3 3
 * 1 1 1
 * 0 1 0
 * 0 1 0
 * 2. Решить задачу о нахождении длины максимальной последовательности с помощью матрицы.
 * 3. ***Требуется обойти конём шахматную доску размером NxM, пройдя через все поля доски по одному разу.
 * Здесь алгоритм решения такой же как и в задаче о 8 ферзях. Разница только в проверке положения коня.
 */

int fnFoundPaths(char caField[], char caVisitedFields[], int iaLengths[], int iLengthsIndex, int iStartX, int iStartY, int iFinishX, int iFinishY)
{
	caVisitedFields[iStartY*5+iStartX] = 1;

	int iLengthsOldIndex = iLengthsIndex;
	int bFinishFound = 0;
	int bChildrenFinishFound = 0;

	printf("%d %d %d\n", iLengthsIndex, iStartX, iStartY, iStartY*5+iStartX-1);

	if (iStartX-1>0) {
		if (caVisitedFields[iStartY*5+iStartX-1] != 1) {
			iLengthsIndex++;
			iaLengths[iLengthsIndex]++;
			if (iStartX-1==iFinishX && iStartY==iFinishY) {
				bFinishFound = 1;
			} else {
				bChildrenFinishFound = fnFoundPaths(caField, caVisitedFields, iaLengths, iLengthsIndex, iStartX-1, iStartY, iFinishX, iFinishY);
			}
		}
	}
	if (iStartX+1<5) {
		if (caVisitedFields[iStartY*5+iStartX+1] != 1) {
			iLengthsIndex++;
			iaLengths[iLengthsIndex]++;
			if (iStartX+1==iFinishX && iStartY==iFinishY) {
				bFinishFound = 1;
			} else {
				bChildrenFinishFound = fnFoundPaths(caField, caVisitedFields, iaLengths, iLengthsIndex, iStartX+1, iStartY, iFinishX, iFinishY);
			}
		}
	}
	if (iStartY-1>0) {
		if (caVisitedFields[(iStartY-1)*5+iStartX] != 1) {
			iLengthsIndex++;
			iaLengths[iLengthsIndex]++;
			if (iStartX==iFinishX && iStartY-1==iFinishY) {
				bFinishFound = 1;
			} else {
				bChildrenFinishFound = fnFoundPaths(caField, caVisitedFields, iaLengths, iLengthsIndex, iStartX, iStartY-1, iFinishX, iFinishY);
			}
		}
	}
	if (iStartY+1<5) {
		if (caVisitedFields[(iStartY+1)*5+iStartX] != 1) {
			iLengthsIndex++;
			iaLengths[iLengthsIndex]++;
			if (iStartX==iFinishX && iStartY+1==iFinishY) {
				bFinishFound = 1;
			} else {
				bChildrenFinishFound = fnFoundPaths(caField, caVisitedFields, iaLengths, iLengthsIndex, iStartX, iStartY+1, iFinishX, iFinishY);
			}
		}
	}

	caVisitedFields[iStartY*5+iStartX] = 0;

	if (bFinishFound) {
		return bFinishFound;
	}

	iaLengths[iLengthsOldIndex] = 0;

	return bChildrenFinishFound;
}

void fnTask1()
{
	char caField[] = {
		1, 1, 1, 1, 1,
		1, 0, 1, 0, 1,
		1, 1, 1, 1, 1,
		1, 0, 1, 0, 1,
		1, 1, 1, 1, 1
	};

	char caVisitedFields[25] = {0};

	int iStartX = 0;
	int iStartY = 0;

	int iFinishX = 4;
	int iFinishY = 4;

	int iaLengths[100000] = {0};
	int iLengthsIndex = 0;

	printf("Start position X: %d\n", iStartX);
	printf("Start position Y: %d\n", iStartY);
	printf("End position X: %d\n", iFinishX);
	printf("End position Y: %d\n", iFinishY);

	printf("Field: \n");
	for (int iIndexX=0; iIndexX<5; iIndexX++) {
		for (int iIndexY=0; iIndexY<5; iIndexY++) {
			printf("%d ", caField[iIndexY*5+iIndexX]);
		}
		printf("\n");
	}

	fnFoundPaths(caField, caVisitedFields, iaLengths, iLengthsIndex, iStartX, iStartY, iFinishX, iFinishY);

	printf("\n");

	int iCount = 0;

	for (int iIndex=0; iIndex<100000; iIndex++) {
		//printf("%d ", iaLengths[iIndex]);
		if (iaLengths[iIndex]>0) {
			iCount++;
		}
	}
	printf("\n");

	printf("Found paths: %d\n", iCount);
}

char* maxLCS(char* caArray1, int iArray1Length, char* caArray2, int iArray2Length)
{
	int iaLengths[iArray1Length+1][iArray2Length+1];

	for (int iIndexI=0; iIndexI<iArray1Length+1; iIndexI++) {
		for (int iIndexJ=0; iIndexJ<iArray2Length+1; iIndexJ++) {
			iaLengths[iIndexI][iIndexJ] = 0;
		}
	}

	for (int iIndexI=0; iIndexI<iArray1Length; iIndexI++) {
		for (int iIndexJ=0; iIndexJ<iArray2Length; iIndexJ++) {
			if (caArray1[iIndexI]==caArray2[iIndexJ]) {
				iaLengths[iIndexI+1][iIndexJ+1] = iaLengths[iIndexI][iIndexJ] + 1;
			} else {
				iaLengths[iIndexI+1][iIndexJ+1] = iaLengths[iIndexI+1][iIndexJ] > iaLengths[iIndexI][iIndexJ+1] ? iaLengths[iIndexI+1][iIndexJ] : iaLengths[iIndexI][iIndexJ+1];
			}
		}
	}

	int iCnt = iaLengths[iArray1Length][iArray2Length];
	char* sResult = (char*) malloc(iCnt+1);
	memset(sResult, 0, iCnt+1);

	for (int iIndexI=iArray1Length-1, iIndexJ=iArray2Length-1; iIndexI >= 0 && iIndexJ>=0;) {
		if (caArray1[iIndexI]==caArray2[iIndexJ]) {
			--iCnt;
			sResult[iCnt] = caArray1[iIndexI];
			--iIndexI;
			--iIndexJ;
		} else if (iaLengths[iIndexI+1][iIndexJ] > iaLengths[iIndexI][iIndexJ+1]) {
			--iIndexJ;
		} else {
			--iIndexI;
		}
	}

	return sResult;
}

void fnTask2()
{
	char* caArray1 = "GEEKBRAINS";
	int iArray1Length = 10;
	char* caArray2 = "GEEKMINDS";
	int iArray2Length = 9;
	printf("string 1: %s\n", caArray1);
	printf("string 2: %s\n", caArray2);
	printf("max LCS: %s\n", maxLCS(caArray1, iArray1Length, caArray2, iArray2Length));
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
				printf("Bye-bye");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
