#include "MySet.H"
#include <stdio.h>
#include <string.h>

typedef struct elem
{
	int num;
} elem;

char* MyPrint(struct elem* el, char* str)
{
	int n, i;
	char tmp[11], * tmp2;

	for (i = 0; i < 11; i++)
	{
		tmp[i] = 0;
	}

	n = el->num;
	snprintf(tmp, 11, "%i", n);
	i = 0;

	while (tmp[i] != 0)
	{
		tmp2 = str;
		str = realloc(str, _msize(str) + sizeof(char));
		if (str == NULL)
		{
			str = tmp2;
			return str;
		}
		(str[_msize(str) / sizeof(char) - 2]) = tmp[i];
		(str[_msize(str) / sizeof(char) - 1]) = 0;

		i++;
	}

	tmp2 = str;
	str = realloc(str, _msize(str) + sizeof(char));
	if (str == NULL)
	{
		str = tmp2;
		return str;
	}
	str[_msize(str) / sizeof(char) - 2] = '\n';
	str[_msize(str) / sizeof(char) - 1] = 0;

	return str;
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

void set_tAdd__EmptySet(void)
{
	set_t set1;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tPrint(set1, &tmp, MyPrint);
	set_tDestroy(set1);

	if (strcmp(tmp, "1\n") == 0)
	{
		printf("set_tAdd__EmptySet: SUCCESS\n");
	}
	else
	{
		printf("set_tAdd__EmptySet: ERROR\n");
	}
	free(tmp);
}

void set_tAdd__IdenticalElem(void)
{
	set_t set1;
	elem* numb;
	char* tmp;
	int returnvalue;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 1);
	returnvalue = set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tPrint(set1, &tmp, MyPrint);
	set_tDestroy(set1);
	if (returnvalue == -1 && strcmp(tmp, "1\n") == 0)
	{
		printf("set_tAdd__IdenticalElement: SUCCESS\n");
	}
	else
	{
		printf("set_tAdd__IdenticalElement: ERROR\n");
	}
	free(numb);
	free(tmp);
}

void set_tAdd__AnotherElem(void)
{
	set_t set1;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tPrint(set1, &tmp, MyPrint);
	set_tDestroy(set1);

	if (strcmp(tmp, "1\n2\n") == 0)
	{
		printf("set_tAdd__AnotherElement: SUCCESS\n");
	}
	else
	{
		printf("set_tAdd__AnotherElement: ERROR\n");
	}
	free(tmp);
}

void set_tCheck__EmptySet(void)
{
	set_t set1;
	elem* numb;
	int returnvalue;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	returnvalue = set_tCheck(set1, numb, MyCompare);
	set_tDestroy(set1);

	if (returnvalue == 0)
	{
		printf("set_tCheck__EmpySet: SUCCESS\n");
	}
	else
	{
		printf("set_tCheck__EmpySet: ERROR\n");
	}
	free(numb);
}

void set_tCheck__NonEmptySet(void)
{
	set_t set1;
	elem* numb;
	int returnvalue;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	returnvalue = set_tCheck(set1, numb, MyCompare);
	set_tDestroy(set1);

	if (returnvalue == 0)
	{
		printf("set_tCheck__NonEmpySet: SUCCESS\n");
	}
	else
	{
		printf("set_tCheck__NonEmpySet: ERROR\n");
	}
	free(numb);
}

void set_tCheck__ExistingElem(void)
{
	set_t set1;
	elem* numb;
	int returnvalue;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	returnvalue = set_tCheck(set1, numb, MyCompare);
	set_tDestroy(set1);

	if (returnvalue == 1)
	{
		printf("set_tCheck__ExistingElement: SUCCESS\n");
	}
	else
	{
		printf("set_tCheck__ExistingElement: ERROR\n");
	}
	free(numb);
}

void set_tRemove__NonExistingElem(void)
{
	set_t set1;
	elem* numb;
	int returnvalue;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	returnvalue = set_tRemove(set1, numb, MyCompare);
	set_tDestroy(set1);

	if (returnvalue == 0)
	{
		printf("set_tRemove__NonExistingElement: SUCCESS\n");
	}
	else
	{
		printf("set_tRemove__NonExistingElement: ERROR\n");
	}
	free(numb);
}

void set_tRemove__ExistingElem(void)
{
	set_t set1;
	elem* numb;
	int returnvalue;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	returnvalue = set_tRemove(set1, numb, MyCompare);
	set_tPrint(set1, &tmp, MyPrint);
	set_tDestroy(set1);

	if (returnvalue == 1 && strcmp(tmp, "1\n") == 0)
	{
		printf("set_tRemove__ExistingElement: SUCCESS\n");
	}
	else
	{
		printf("set_tRemove__ExistingElement: ERROR\n");
	}
	free(numb);
	free(tmp);
}

void set_tIntersection__2EmptySets(void)
{
	set_t set1, set2, set3;
	char* tmp;

	set_tCreate(&set1);
	set_tCreate(&set2);
	set_tCreate(&set3);

	set_tIntersection(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);
	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "") == 0)
	{
		printf("set_tIntersection__2EmptySets: SUCCESS\n");
	}
	else
	{
		printf("set_tIntersection__2EmptySets: ERROR\n");
	}
	free(tmp);
}

void set_tIntersection__1EmptySet(void)
{
	set_t set1, set2, set3;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set2);
	set_tCreate(&set3);

	set_tIntersection(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);

	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "") == 0)
	{
		printf("set_tIntersection__1EmptySet: SUCCESS\n");
	}
	else
	{
		printf("set_tIntersection__1EmptySet: ERROR\n");
	}
	free(tmp);
}

void set_tIntersection__WithoutIntersection(void)
{
	set_t set1, set2, set3;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set2);
	CreateElem(&numb, 2);
	set_tAdd(set2, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set3);

	set_tIntersection(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);

	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "") == 0)
	{
		printf("set_tIntersection__WithoutIntersection: SUCCESS\n");
	}
	else
	{
		printf("set_tIntersection__WithoutIntersection: ERROR\n");
	}
	free(tmp);
}

void set_tIntersection__WithIntersection(void)
{
	set_t set1, set2, set3;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set2);
	CreateElem(&numb, 2);
	set_tAdd(set2, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 3);
	set_tAdd(set2, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set3);

	set_tIntersection(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);

	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "2\n") == 0)
	{
		printf("set_tIntersection__WithIntersection: SUCCESS\n");
	}
	else
	{
		printf("set_tIntersection__WithIntersection: ERROR\n");
	}
	free(tmp);
}

void set_tUnion__2EmptySets(void)
{
	set_t set1, set2, set3;
	char* tmp;

	set_tCreate(&set1);
	set_tCreate(&set2);
	set_tCreate(&set3);

	set_tUnion(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);
	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "") == 0)
	{
		printf("set_tUnion__2EmptySets: SUCCESS\n");
	}
	else
	{
		printf("set_tUnion__2EmptySets: ERROR\n");
	}
	free(tmp);
}

void set_tUnion__1EmptySet(void)
{
	set_t set1, set2, set3;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set2);
	set_tCreate(&set3);

	set_tUnion(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);

	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "1\n") == 0)
	{
		printf("set_tUnion__1EmptySet: SUCCESS\n");
	}
	else
	{
		printf("set_tUnion__1EmptySet: ERROR\n");
	}
	free(tmp);
}

void set_tUnion__WithoutIntersection(void)
{
	set_t set1, set2, set3;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set2);
	CreateElem(&numb, 2);
	set_tAdd(set2, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set3);

	set_tUnion(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);

	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "1\n2\n") == 0)
	{
		printf("set_tUnion__WithoutIntersection: SUCCESS\n");
	}
	else
	{
		printf("set_tUnion__WithoutIntersection: ERROR\n");
	}
	free(tmp);
}

void set_tUnion__WithIntersection(void)
{
	set_t set1, set2, set3;
	elem* numb;
	char* tmp;

	set_tCreate(&set1);
	CreateElem(&numb, 1);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 2);
	set_tAdd(set1, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set2);
	CreateElem(&numb, 2);
	set_tAdd(set2, numb, sizeof(struct elem), MyCompare);
	CreateElem(&numb, 3);
	set_tAdd(set2, numb, sizeof(struct elem), MyCompare);
	set_tCreate(&set3);

	set_tUnion(&set3, set1, set2, MyCompare);
	set_tPrint(set3, &tmp, MyPrint);

	set_tDestroy(set1);
	set_tDestroy(set2);
	set_tDestroy(set3);

	if (strcmp(tmp, "1\n2\n3\n") == 0)
	{
		printf("set_tUnion__WithIntersection: SUCCESS\n");
	}
	else
	{
		printf("set_tUnion__WithIntersection: ERROR\n");
	}
	free(tmp);
}
