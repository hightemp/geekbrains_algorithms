/*
 ============================================================================
 Name        : task1.c
 Author      : Anton PAnov
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void fnTask1()
{
	float fMass = 0;
	float fHeight = 0;

	printf("enter mass (kg):\n");
	scanf("%f", &fMass);

	printf("enter height (m):\n");
	scanf("%f", &fHeight);

	float fIndex = fMass/(fHeight*fHeight);

	printf("I=m/(h*h)=%f\n", fIndex);
}

void fnTask2()
{
	float fN1, fN2, fN3, fN4, fMax = 0;

	printf("enter number 1:\n");
	scanf("%f", &fN1);

	printf("enter number 2:\n");
	scanf("%f", &fN2);

	printf("enter number 3:\n");
	scanf("%f", &fN3);

	printf("enter number 4:\n");
	scanf("%f", &fN4);

	fMax = (fN1>fN2?fN1:fN2);
	fMax = (fN3>fMax?fN3:fMax);
	fMax = (fN4>fMax?fN4:fMax);

	printf("maximum is: %f\n", fMax);
}

void fnTask3()
{
	int iNumber1 = 10;
	int iNumber2 = 20;
	int iTemp = 0;

	printf("%d %d\n", iNumber1, iNumber2);

	iTemp = iNumber1;
	iNumber1 = iNumber2;
	iNumber2 = iTemp;

	printf("a %d %d\n", iNumber1, iNumber2);

	iNumber1 = iNumber1 + iNumber2;
	iNumber2 = iNumber1 - iNumber2;
	iNumber1 = iNumber1 - iNumber2;

	printf("b %d %d\n", iNumber1, iNumber2);

	iNumber1 = iNumber1 ^ iNumber2;
	iNumber2 = iNumber1 ^ iNumber2;
	iNumber1 = iNumber1 ^ iNumber2;

	printf("b %d %d\n", iNumber1, iNumber2);
}

void fnTask4()
{
	float fA = 0, fB = 0, fC = 0, fD = 0;

	// fA*x^2 + fB*x + fC = 0

	printf("Enter a:\n");
	scanf("%f", &fA);

	printf("Enter b:\n");
	scanf("%f", &fB);

	printf("Enter c:\n");
	scanf("%f", &fC);

	if (fA==0) {
		printf("x0 = %f\n", -fC/fB);
	} else {
		fD = fB*fB - 4*fA*fC;

		if (fD==0) {
			printf("x0 = %f\n", (-fB)/(2*fA));
		} else if (fD>0) {
			printf("x1 = %f\n", (-fB+sqrt(fD))/(2*fA));
			printf("x2 = %f\n", (-fB-sqrt(fD))/(2*fA));
		} else {
			printf("no roots\n");
		}
	}
}

void fnTask5()
{
	int iMonth = 0;

	printf("enter month number:\n");
	scanf("%d", &iMonth);

	if (iMonth==12 || iMonth<3) {
		printf("winter");
	}
	if (iMonth>2 && iMonth<6) {
		printf("spring");
	}
	if (iMonth>5 && iMonth<9) {
		printf("summer");
	}
	if (iMonth>8 && iMonth<12) {
		printf("autumn");
	}
}

void fnTask6()
{
	int iAge = 0;

	scanf("%d", &iAge);

	int iR1 = iAge % 100;
	int iR2 = iR1 % 10;

	if (iR1>10 && iR1<20) {
		printf("%d лет", iAge);
	} else {
		if (iR2>1 && iR2<5) {
			printf("%d года", iAge);
		} else {
			if (iR2==1) {
				printf("%d год", iAge);
			} else {
				printf("%d лет", iAge);
			}
		}
	}
}

void fnTask7()
{
	int iX1, iX2, iY1, iY2;

	printf("x1:");
	scanf("%d", &iX1);
	printf("y1:");
	scanf("%d", &iY1);
	printf("x2:");
	scanf("%d", &iX2);
	printf("y2:");
	scanf("%d", &iY2);

	int iColor1 = (iY1%2+iX1)%2;
	int iColor2 = (iY2%2+iX2)%2;

	printf("Color 1 - %s\n", !iColor1 ? "black" : "white");
	printf("Color 2 - %s\n", !iColor2 ? "black" : "white");
	printf("Result: %s\n", iColor1==iColor2 ? "yes" : "no");
}

void fnTask8()
{
	int iA, iB;

	printf("A:");
	scanf("%d", &iA);
	printf("B:");
	scanf("%d", &iB);

	printf("x^2: ");
	for (int iIndex=iA; iIndex<=iB; iIndex++) {
		printf("%d ", iIndex*iIndex);
	}
	printf("\nx^3: ");
	for (int iIndex=iA; iIndex<=iB; iIndex++) {
		printf("%d ", iIndex*iIndex*iIndex);
	}
}

void fnTask9()
{
	int iN, iK;

	printf("N:");
	scanf("%d", &iN);
	printf("K:");
	scanf("%d", &iK);

	int iD = 0;
	int iR = 0;

	while (iN>=iK) {
		iD++;
		iN -= iK;
	}

	iR = iN;

	printf("%d %d", iD, iR);
}

void fnTask10()
{
	int iN, iR;

	printf("N:");
	scanf("%d", &iN);

	while (iN>0) {
		iR = iN % 10;
		if (iR % 2) {
			printf("True");
			return;
		}
		iN = iN / 10;
	}

	printf("False");
}

void fnTask11()
{
	int iN, iS = 0, iC = 0;

	do {
		scanf("%d", &iN);
		if (iN>0 && iN % 10 == 8) {
			iC++;
			iS += iN;
		}
	} while (iN!=0);

	if (iC>0) {
		printf("%f", (float) iS/iC);
	}
}

void fnTask12()
{
	int max(int iN1, int iN2, int iN3) {
		int iMax = (iN1 > iN2 ? iN1 : iN2);
		return (iN3 > iMax ? iN3 : iMax);
	}

	int iN1, iN2, iN3;

	printf("N1:");
	scanf("%d", &iN1);
	printf("N2:");
	scanf("%d", &iN2);
	printf("N3:");
	scanf("%d", &iN3);

	printf("%d", max(iN1, iN2, iN3));
}

void fnTask13()
{
	int rand1()
	{
		time_t t;
		srand((unsigned) time(&t));
		return rand() % 100 + 1;
	}

	int rand2()
	{
		time_t t;
		return (time(&t)/100) * (time(&t)%100) % 100 + 1;
	}

	printf("%d %d", rand1(), rand2());
}

void fnTask14()
{
	int fnIsAmorth(int iN)
	{
		int iNumbers = log10(iN) + 1;
		int iSquare = iN*iN;

		for (int iIndex=0; iIndex<iNumbers;iIndex++) {
			if (iSquare % 10 != iN % 10) {
				return 0;
			}
			iSquare = iSquare / 10;
			iN = iN / 10;
		}
		return 1;
	}

	int iN;

	printf("N:");
	scanf("%d", &iN);

	for (int iIndex=1; iIndex<=iN; iIndex++) {
		if (fnIsAmorth(iIndex))
			printf("%d %d\n", iIndex, iIndex*iIndex);
	}
}

int main(void) {

	int iSel = 0;
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
			case 7:
				fnTask7();
				break;
			case 8:
				fnTask8();
				break;
			case 9:
				fnTask9();
				break;
			case 10:
				fnTask10();
				break;
			case 11:
				fnTask11();
				break;
			case 12:
				fnTask12();
				break;
			case 13:
				fnTask13();
				break;
			case 14:
				fnTask14();
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
