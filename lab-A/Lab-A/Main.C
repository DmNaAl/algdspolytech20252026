#include "MySet.H"
#include <stdio.h>

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

typedef struct elem
{
	int num;
} elem;

void MyPrint(struct elem* el)
{
	printf("%i\n", el->num);
}

int MyCompare(struct elem* el1, struct elem* el2)
{
	if (el1->num > el2->num)
	{
		return -1;
	}
	else if (el1->num == el2->num)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

int CreateElem(elem** numb, int n)
{
	*numb = malloc(sizeof(struct elem));
	if (*numb == NULL)
	{
		return 0;
	}
	(*numb)->num = n;

	return 1;
}

int main(void)
{
	set_t first, second, third;
	elem *numb;

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);

	set_tCreate(&first);

	CreateElem(&numb, 5);
	set_tAdd(first, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	set_tAdd(first, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 4);
	set_tAdd(first, numb, sizeof(struct elem), MyCompare);


	set_tCreate(&second);

	CreateElem(&numb, 4);
	set_tAdd(second, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 5);
	set_tAdd(second, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 7);
	set_tAdd(second, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 8);
	set_tAdd(second, numb, sizeof(struct elem), MyCompare);


	set_tCreate(&third);

	printf("Intersection:\n");
	set_tIntersection(&third, first, second, MyCompare);
	set_tPrint(third, MyPrint);
	set_tIntersection(&third, first, second, MyCompare);
	set_tPrint(third, MyPrint);
	printf("Union:\n");
	set_tUnion(&third, first, second, MyCompare);
	set_tPrint(third, MyPrint);
	//set_tUnion(third, first, second, MyCompare);
	//set_tPrint(third, MyPrint);


	set_tDestroy(first);
	set_tDestroy(second);
	set_tDestroy(third);

	return 0;
}
