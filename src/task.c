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

	printf("Hash\n");
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

typedef struct TreeNode
{
	int iValue;
	struct TreeNode *poLeft;
	struct TreeNode *poRight;
	struct TreeNode *poParent;
} TreeNode;

typedef struct BinaryTree
{
	TreeNode *poRoot;
} BinaryTree;

void fnBinaryTreeAddNode(BinaryTree *poTree, int iValue)
{
	if (!poTree->poRoot) {
		fnBinaryTreeInit(poTree, iValue);
		return;
	}

	fnTreeNodeAddChild(poTree->poRoot, iValue);
}

void fnBinaryTreeInit(BinaryTree *poTree, int iValue)
{
	TreeNode *poNewTreeNode = (TreeNode *) malloc(sizeof(TreeNode));
	poNewTreeNode->poParent = 0;
	poNewTreeNode->iValue = iValue;
	poNewTreeNode->poLeft = 0;
	poNewTreeNode->poRight = 0;

	poTree->poRoot = poNewTreeNode;

	//printf("Set root node %d\n", poTree->poRoot->iValue);
}

void fnTreeNodeAddChild(TreeNode *poTreeNode, int iValue)
{
	if (!poTreeNode) {
		return;
	}

	if (iValue == poTreeNode->iValue) {
		return;
	}

	if (iValue < poTreeNode->iValue && !poTreeNode->poLeft) {
		//printf("Add left node to %d\n", poTreeNode->iValue);
		TreeNode *poNewTreeNode = (TreeNode *) malloc(sizeof(TreeNode));
		poNewTreeNode->poParent = poTreeNode;
		poNewTreeNode->iValue = iValue;
		poNewTreeNode->poLeft = 0;
		poNewTreeNode->poRight = 0;
		poTreeNode->poLeft = poNewTreeNode;
	} else if (iValue < poTreeNode->iValue && poTreeNode->poLeft) {
		//printf("Step into left node of %d\n", poTreeNode->iValue);
		fnTreeNodeAddChild(poTreeNode->poLeft, iValue);
	} else if (poTreeNode->iValue < iValue && !poTreeNode->poRight) {
		//printf("Add right node to %d\n", poTreeNode->iValue);
		TreeNode *poNewTreeNode = (TreeNode *) malloc(sizeof(TreeNode));
		poNewTreeNode->poParent = poTreeNode;
		poNewTreeNode->iValue = iValue;
		poNewTreeNode->poLeft = 0;
		poNewTreeNode->poRight = 0;
		poTreeNode->poRight = poNewTreeNode;
	} else if (poTreeNode->iValue < iValue && poTreeNode->poRight) {
		//printf("Step into right node of %d\n", poTreeNode->iValue);
		fnTreeNodeAddChild(poTreeNode->poRight, iValue);
	}
}

void fnTreeNodeClear(TreeNode *poTreeNode)
{
	if (poTreeNode->poLeft) {
		fnTreeNodeClear(poTreeNode->poLeft);
		free(poTreeNode->poLeft);
		poTreeNode->poLeft = 0;
	}

	if (poTreeNode->poRight) {
		fnTreeNodeClear(poTreeNode->poRight);
		free(poTreeNode->poRight);
		poTreeNode->poRight = 0;
	}
}

void fnBinaryTreeClear(BinaryTree *poTree)
{
	if (!poTree->poRoot) {
		return;
	}

	fnTreeNodeClear(poTree->poRoot);
	free(poTree->poRoot);
	poTree->poRoot = 0;
}

void fnBinaryTreePrint(BinaryTree *poTree)
{
	printf("Root:\n");

	if (!poTree->poRoot) {
		return;
	}

	fnTreeNodePrint(poTree->poRoot, 0);
}

void fnTreeNodePrint(TreeNode *poTreeNode, int iLevel)
{
	fnPrintSpaces(iLevel);
	printf("Value: %d\n", poTreeNode->iValue);

	if (poTreeNode->poLeft) {
		fnPrintSpaces(iLevel);
		printf("Left:\n");
		fnTreeNodePrint(poTreeNode->poLeft, iLevel+1);
	}

	if (poTreeNode->poRight) {
		fnPrintSpaces(iLevel);
		printf("Right:\n");
		fnTreeNodePrint(poTreeNode->poRight, iLevel+1);
	}
}

void fnPrintSpaces(int iCount)
{
	int iIndex = 0;
	for (;iIndex<iCount;iIndex++) {
		printf(" ");
	}
}

TreeNode * fnTreeNodeSearchValue(TreeNode *poTreeNode, int iValue)
{
	if (iValue == poTreeNode->iValue) {
		return poTreeNode;
	}

	if (iValue < poTreeNode->iValue && poTreeNode->poLeft) {
		return fnTreeNodeSearchValue(poTreeNode->poLeft, iValue);
	} else if (iValue > poTreeNode->iValue && poTreeNode->poRight) {
		return fnTreeNodeSearchValue(poTreeNode->poRight, iValue);
	} else {
		return 0;
	}
}

TreeNode * fnBinaryTreeSearchValue(BinaryTree *poTree, int iValue)
{
	if (!poTree->poRoot) {
		return 0;
	}

	return fnTreeNodeSearchValue(poTree->poRoot, iValue);
}

int fnBinaryTreeCountNodes(BinaryTree *poTree)
{
	if (!poTree->poRoot) {
		return 0;
	}

	return fnTreeNodeCountChildren(poTree->poRoot);
}

int fnTreeNodeCountChildren(TreeNode *poTreeNode)
{
	int iCount = 1;

	if (poTreeNode->poLeft) {
		iCount += fnTreeNodeCountChildren(poTreeNode->poLeft);
	}

	if (poTreeNode->poRight) {
		iCount += fnTreeNodeCountChildren(poTreeNode->poRight);
	}

	return iCount;
}

void fnBinaryTreeReadFromFile(BinaryTree *poTree, char *pcString)
{
	if (!pcString) {
		return;
	}

	if (!strlen(pcString)) {
		printf("File name too short\n");
		return;
	}

	FILE *poFileHandler = fopen(pcString, "r");

	if (!poFileHandler) {
		printf("Can't open file\n");
	}

	fnBinaryTreeClear(poTree);

	int iNodesCount = 0;

	fscanf(poFileHandler, "%d ", &iNodesCount);

	int iIndex = 0;

	for (;iIndex<iNodesCount; iIndex++) {
		int iNodeValue = 0;

		fscanf(poFileHandler, "%d ", &iNodeValue);

		fnBinaryTreeAddNode(poTree, iNodeValue);
	}

	fclose(poFileHandler);
}

void fnBinaryTreeWriteToFile(BinaryTree *poTree, char *pcString)
{
	if (!pcString) {
		return;
	}

	if (!strlen(pcString)) {
		printf("File name too short\n");
		return;
	}

	printf("Saving to file: %s\n", pcString);

	FILE *poFileHandler = fopen(pcString, "w");

	if (!poFileHandler) {
		printf("Can't open file\n");
	}

	fprintf(poFileHandler, "%d ", fnBinaryTreeCountNodes(poTree));

	if (poTree->poRoot) {
		fnTreeNodeWriteToFile(poTree->poRoot, poFileHandler);
	}

	fclose(poFileHandler);
}

void fnTreeNodeWriteToFile(TreeNode *poTreeNode, FILE *poFileHandler)
{
	fprintf(poFileHandler, "%d ", poTreeNode->iValue);

	if (poTreeNode->poLeft) {
		fnTreeNodeWriteToFile(poTreeNode->poLeft, poFileHandler);
	}

	if (poTreeNode->poRight) {
		fnTreeNodeWriteToFile(poTreeNode->poRight, poFileHandler);
	}
}

void fnTask2()
{
	BinaryTree *poTree = (BinaryTree *) malloc(sizeof(BinaryTree));

	int iSel = 0;

	printf("Binary tree\n");

	int iValue = 0;
	char acFileName[100] = {0};

	do
	{
		printf("\n");
		printf("0 - return to main menu\n");
		printf("1 - print tree\n");
		printf("2 - search element\n");
		printf("3 - clear tree\n");
		printf("4 - add element\n");
		printf("5 - clear element\n");
		printf("6 - load tree from file\n");
		printf("7 - save tree to file\n");
		printf("\nEnter command:");
		scanf("%i", &iSel);
		printf("\n");
		switch (iSel)
		{
			case 1:
				fnBinaryTreePrint(poTree);

				break;
			case 2:
				printf("Enter value for search: ");
				scanf("%d", &iValue);
				printf("\n");

				if (fnBinaryTreeSearchValue(poTree, iValue)) {
					printf("Value found\n");
				} else {
					printf("Value NOT found\n");
				}

				break;
			case 3:
				fnBinaryTreeClear(poTree);

				break;
			case 4:
				printf("Enter value to add: ");
				scanf("%d", &iValue);
				printf("\n");

				fnBinaryTreeAddNode(poTree, iValue);

				break;
			case 5:
				printf("Enter value of element to clear children: ");
				scanf("%d", &iValue);
				printf("\n");

				TreeNode *poTreeNode = fnBinaryTreeSearchValue(poTree, iValue);

				if (poTreeNode) {
					fnTreeNodeClear(poTreeNode);
				}
				break;
			case 6:
				printf("Enter file name to load from: ");
				scanf("%s", acFileName);
				printf("\n");

				fnBinaryTreeReadFromFile(poTree, acFileName);

				break;
			case 7:
				printf("Enter file name to save into: ");
				scanf("%s", acFileName);
				printf("\n");

				fnBinaryTreeWriteToFile(poTree, acFileName);

				break;
			case 0:
				printf("\n");
				break;
			default:
				printf("Wrong command\n");
		}
	} while (iSel != 0);
	fnBinaryTreeClear(poTree);
	free(poTree);
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
