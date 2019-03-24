/*
 ============================================================================
 Name        : task1.c
 Author      : Anton PAnov
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

/**
 * 1. Реализовать сортировку подсчетом.
 * 2. Реализовать быструю сортировку.
 * 3. *Реализовать сортировку слиянием.
 * 4. **Реализовать алгоритм сортировки со списком
 * 5. Проанализировать время работы каждого из вида сортировок для 100, 10000, 1000000 элементов. Заполнить таблицу (см. методичку)
 */ 

void fnPrintArray(int aiArray[], int iLength)
{
	int iIndex = 0;
	for (;iIndex<iLength; iIndex++) {
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

	fnPrintArray(aiArray, 9);

	fnCountingSort(aiArray);

	fnPrintArray(aiArray, 9);
}

int64_t fnQuickSort(int aiArray[], int iLength)
{
	int iLIndex = 0;
	int iRIndex = iLength-1;
	int iMiddleValue = aiArray[iLength/2];
	int iTemp = 0;
	int64_t iComp = 0;

	do {
		while(aiArray[iLIndex]<iMiddleValue) {
			iLIndex++;
		}
		while(iMiddleValue<aiArray[iRIndex]) {
			iRIndex--;
		}

		if (iLIndex <= iRIndex) {
			iTemp = aiArray[iLIndex];
			aiArray[iLIndex] = aiArray[iRIndex];
			aiArray[iRIndex] = iTemp;
			iLIndex++;
			iRIndex--;
		}
		iComp++;
	} while(iLIndex <= iRIndex);

	if (0<iRIndex)
		iComp += fnQuickSort(aiArray, iRIndex);
	if (iLIndex<iLength)
		iComp += fnQuickSort(aiArray+iLIndex, iLength-iLIndex);

	return iComp;
}

void fnTask2()
{
	int aiArray[9] = {9, 8, 7, 6, 5, 4, 3, 2, 1};

	printf("Quick sort\n");

	fnPrintArray(aiArray, 9);

	fnQuickSort(aiArray, 9);

	fnPrintArray(aiArray, 9);
}

void fnTask3()
{

}

void fnTask4()
{

}

int64_t fnShellsSort(int* aiArray, int iLength)
{
	int iK = 0;
	int iI = 0;
	int iJ = 0;
	int iTemp = 0;
	int64_t iComp = 0;

	for (iK = iLength / 2; iK > 0; iK /= 2) {
		for(iI = iK; iI < iLength; iI++) {
			iTemp = aiArray[iI];
			for(iJ = iI; iJ >= iK; iJ -= iK) {
				if(iTemp < aiArray[iJ - iK])
					aiArray[iJ] = aiArray[iJ - iK];
				else
					break;
				iComp++;
			}
			aiArray[iJ] = iTemp;
		}
	}

	return iComp;
}

int64_t fnMerge(int* aiArray, int iLeft, int iMid, int iRight)
{
	int64_t iComp = 0;
	int iIt1 = 0;
	int iIt2 = 0;
	int aiResult[iRight - iLeft];
	int iIndex = 0;

	while (iLeft + iIt1 < iMid && iMid + iIt2 < iRight) {
		if (aiArray[iLeft + iIt1] < aiArray[iMid + iIt2]) {
			aiResult[iIt1 + iIt2] = aiArray[iLeft + iIt1];
			iIt1 += 1;
		} else {
			aiResult[iIt1 + iIt2] = aiArray[iMid + iIt2];
			iIt2 += 1;
		}
		iComp++;
	}

	while (iLeft + iIt1 < iMid) {
		aiResult[iIt1 + iIt2] = aiArray[iLeft + iIt1];
		iIt1 += 1;
	}

	while (iMid + iIt2 < iRight) {
		aiResult[iIt1 + iIt2] = aiArray[iMid + iIt2];
		iIt2 += 1;
	}

	for (iIndex = 0;iIndex<iIt1 + iIt2;iIndex++) {
		aiArray[iLeft + iIndex] = aiResult[iIndex];
	}
}

int64_t fnMergeSort(int* aiArray, int iLeft, int iRight)
{
	int64_t iComp = 1;

	if (iLeft + 1 >= iRight)
		return iComp;

	int iMid = (iLeft + iRight) / 2;
	iComp += fnMergeSort(aiArray, iLeft, iMid);
	iComp += fnMergeSort(aiArray, iMid, iRight);
	iComp += fnMerge(aiArray, iLeft, iMid, iRight);

	return iComp;
}

int* fnGenerateArray(int iLength)
{
	int* iResult = (int*) malloc(iLength*sizeof(int));
	int iIndex;

	for (iIndex=0;iIndex<iLength;iIndex++) {
		iResult[iIndex] = rand() % iLength;
	}

	return iResult;
}

int64_t fnGetMicroseconds()
{
	struct timespec tms;

	if (clock_gettime(CLOCK_REALTIME,&tms)) {
		printf("Error: clock_gettime");
		return -1;
	}

	int64_t micros = tms.tv_sec * 1000000;
	micros += tms.tv_nsec/1000;
	if (tms.tv_nsec % 1000 >= 500) {
		++micros;
	}

	return micros;
}

int* fnCopyArray(int* aiArray, int iLength)
{
	int* piResult = malloc(iLength*sizeof(int));
	memcpy(piResult, aiArray, iLength);
	return piResult;
}

void fnTask5()
{
	int64_t lliStartTime = 0;
	int64_t lliEndTime = 0;
	int64_t iComp = 0;
	int64_t lliResultTime = 0;

	int* aiArray = 0;
	int* aiSortArray = 0;
	int aiArrayLengths[] = {100, 10000, 1000000};
	int iArrayLengthsIndex = 0;

	for (iArrayLengthsIndex=0; iArrayLengthsIndex<3; iArrayLengthsIndex++) {
		int iLength = aiArrayLengths[iArrayLengthsIndex];

		aiArray = fnGenerateArray(iLength);

		aiSortArray = fnCopyArray(aiArray, iLength);

		lliStartTime = fnGetMicroseconds();
		iComp = fnQuickSort(aiSortArray, iLength);
		lliEndTime = fnGetMicroseconds();
		lliResultTime = lliEndTime - lliStartTime;

		printf("Array of %d elements: Quick sort: Time: %lli us Compares: %lli \n", iLength, lliResultTime, iComp);

		free(aiSortArray);

		aiSortArray = fnCopyArray(aiArray, iLength);

		lliStartTime = fnGetMicroseconds();
		iComp = fnShellsSort(aiSortArray, iLength);
		lliEndTime = fnGetMicroseconds();
		lliResultTime = lliEndTime - lliStartTime;

		printf("Array of %d elements: Shell sort: Time: %lli us Compares: %lli \n", iLength, lliResultTime, iComp);

		free(aiSortArray);

		aiSortArray = fnCopyArray(aiArray, iLength);

		lliStartTime = fnGetMicroseconds();
		iComp = fnMergeSort(aiSortArray, 0, iLength);
		lliEndTime = fnGetMicroseconds();
		lliResultTime = lliEndTime - lliStartTime;

		printf("Array of %d elements: Merge sort: Time: %lli us Compares: %lli \n", iLength, lliResultTime, iComp);

		free(aiSortArray);

		free(aiArray);
	}
}

int main(void)
{
	//srand(time(NULL));

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
