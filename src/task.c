/*
 ============================================================================
 Name        : task1.c
 Author      : Anton PAnov
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * 1. Написать функции, которые считывают матрицу смежности из файла и выводят ее на экран
 * 2. Написать рекурсивную функцию обхода графа в глубину.
 * 3. Написать функцию обхода графа в ширину.
 * 4. *Создать библиотеку функций для работы с графами.
 */

typedef struct AdjacencyMatrix {
	int *piArray;
	int iSize;
} AdjacencyMatrix;

AdjacencyMatrix* fnAdjacencyMatrixCreate(int iSize)
{
	AdjacencyMatrix* poResult = (AdjacencyMatrix*) malloc(sizeof(AdjacencyMatrix));
	poResult->piArray = (int*) malloc(sizeof(int)*iSize*iSize);
	poResult->iSize = iSize;
}

void fnAdjacencyMatrixClear(AdjacencyMatrix* poAdjacencyMatrix)
{
	free(poAdjacencyMatrix->piArray);
}

AdjacencyMatrix* fnAdjacencyMatrixLoadFromFile(char* pcFilePath)
{
	FILE* poFileHandler = fopen(pcFilePath, "r");
	
	if (!poFileHandler) {
		printf("Can't open file\n");
		return 0;
	}
	
	int iSize = 0;

	fscanf(poFileHandler, "%d ", &iSize);

	AdjacencyMatrix* poAdjacencyMatrix = fnAdjacencyMatrixCreate(iSize);
	
	while (!feof(poFileHandler)) {
		int iX = 0;
		int iY = 0;

		fscanf(poFileHandler, "%d %d ", &iX, &iY);
		
		poAdjacencyMatrix->piArray[iY*poAdjacencyMatrix->iSize+iX] = 1;
		poAdjacencyMatrix->piArray[iX*poAdjacencyMatrix->iSize+iY] = 1;
	}
	
	return poAdjacencyMatrix;
}

void fnAdjacencyMatrixPrint(AdjacencyMatrix* poAdjacencyMatrix)
{
	int iX = 0;
	int iY = 0;
	
	for (iY=0;iY<poAdjacencyMatrix->iSize;iY++) {
		for (iX=0;iX<poAdjacencyMatrix->iSize;iX++) {
			printf("%d ", poAdjacencyMatrix->piArray[iY*poAdjacencyMatrix->iSize+iX]);
		}
		printf("\n");
	}
}

void fnTask1()
{
	printf("Reading adjacency matrix from file..\n");
	
	AdjacencyMatrix* poAdjacencyMatrix = fnAdjacencyMatrixLoadFromFile("am.txt");
	
	fnAdjacencyMatrixPrint(poAdjacencyMatrix);

	fnAdjacencyMatrixClear(poAdjacencyMatrix);
	
	printf("\n");
}

void fnPrintSpaces(int iCount)
{
	int iIndex = 0;
	for (;iIndex<iCount; iIndex++) {
		printf(" ");
	}
}

void fnDFS(AdjacencyMatrix* poAdjacencyMatrix, int iStartVertexIndex, int* iVisitedVertexes, int iDepthLevel)
{
	int bFirstRun = !iVisitedVertexes;
	
	if (bFirstRun) {
		iVisitedVertexes = (int*) malloc(sizeof(int)*poAdjacencyMatrix->iSize);
		memset(iVisitedVertexes, 0, sizeof(int)*poAdjacencyMatrix->iSize);
	}
	
	iVisitedVertexes[iStartVertexIndex] = 1;
	
	fnPrintSpaces(iDepthLevel);
	printf("Vertex %d\n", iStartVertexIndex);
	
	int iY = 0;
	
	for (iY = 0; iY<poAdjacencyMatrix->iSize; iY++) {
		if (iY==iStartVertexIndex) {
			continue;
		}
		
		int iIndex = iY*poAdjacencyMatrix->iSize+iStartVertexIndex;
		
		if (poAdjacencyMatrix->piArray[iIndex] && !iVisitedVertexes[iY]) {
			fnDFS(poAdjacencyMatrix, iY, iVisitedVertexes, iDepthLevel+1);
		}
	}
	
	if (bFirstRun) {
		free(iVisitedVertexes);
	}
}

void fnTask2()
{
	printf("DFS\n");
	printf("Reading adjacency matrix from file..\n");
	
	AdjacencyMatrix* poAdjacencyMatrix = fnAdjacencyMatrixLoadFromFile("am.txt");
	
	printf("Start with 0\n");
	fnDFS(poAdjacencyMatrix, 0, 0, 0);

	printf("\n");
	printf("Start with 3\n");
	fnDFS(poAdjacencyMatrix, 3, 0, 0);

	fnAdjacencyMatrixClear(poAdjacencyMatrix);
	
	printf("\n");
}

void fnBFS(AdjacencyMatrix* poAdjacencyMatrix, int iStartVertexIndex, int* iVisitedVertexes, int iDepthLevel)
{
	
}

void fnTask3()
{
	printf("BFS\n");
	printf("Reading adjacency matrix from file..\n");
	
	AdjacencyMatrix* poAdjacencyMatrix = fnAdjacencyMatrixLoadFromFile("am.txt");
	
	printf("Start with 0\n");
	fnBFS(poAdjacencyMatrix, 0, 0, 0);

	printf("\n");
	printf("Start with 3\n");
	fnBFS(poAdjacencyMatrix, 3, 0, 0);

	fnAdjacencyMatrixClear(poAdjacencyMatrix);
	
	printf("\n");
}

void fnTask4()
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
			case 0:
				printf("Bye-bye");
				break;
			default:
				printf("Wrong selected\n");
		}
	} while (iSel != 0);

	return EXIT_SUCCESS;
}
