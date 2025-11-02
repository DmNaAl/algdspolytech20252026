#include "MySet.H"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//struct elem;
struct MySet
{
	unsigned int size;
	struct elem* data;
	struct MySet* next;
} MySet;

struct MySetShell
{
	int size;
	struct MySet* first;
} MySetShell;



int set_tCreate(set_t *set1_var)
{
	*set1_var = malloc(sizeof(struct MySetShell));

	if ((*set1_var) == NULL)
	{
		return 0;
	}

	(*set1_var)->size = 0;
	(*set1_var)->first = NULL;

	return 1;
}

int set_tAdd(set_t set1, struct elem* udata, unsigned int size, int (*Compare)(struct elem*, struct elem*))
{
	struct MySet** tmp;
	struct MySet* tmp2;
	int flag;

	tmp = &(set1->first);
	flag = 0;
	while (!(*tmp == NULL))
	{
		flag = (*Compare)(udata, (*tmp)->data);
		if (flag >= 0)
		{
			break;
		}
		tmp = &((*tmp)->next);
	}
	if (*tmp == NULL)
	{
		*tmp = malloc(sizeof(struct MySet));
		if (*tmp == NULL)
		{
			return 0;
		}
		(*tmp)->size = size;
		(*tmp)->data = udata;
		(*tmp)->next = NULL;
	}
	else if (flag == 0)
	{
		return -1;
	}
	else
	{
		tmp2 = *tmp;
		*tmp = malloc(sizeof(struct MySet));
		if (*tmp == NULL)
		{
			*tmp = tmp2;
			return 0;
		}
		(*tmp)->size = size;
		(*tmp)->data = udata;
		(*tmp)->next = tmp2;
	}
	set1->size += 1;

	return 1;
}

int set_tCheck(set_t set1, struct elem* udata, int (*Compare)(struct elem*, struct elem*))
{
	struct MySet** tmp;
	int flag;

	tmp = &(set1->first);
	flag = 1;
	while (!(*tmp == NULL))
	{
		flag = (*Compare)(udata, (*tmp)->data);
		if (flag >= 0)
		{
			break;
		}
		tmp = &((*tmp)->next);
	}

	return !flag;
}

int set_tRemove(set_t set1, struct elem* udata, int (*Compare)(struct elem*, struct elem*))
{
	struct MySet** tmp;
	struct MySet* tmp2;
	int flag;

	tmp = &(set1->first);
	flag = 0;
	while (!(*tmp == NULL))
	{
		flag = (*Compare)(udata, (*tmp)->data);
		if (flag >= 0)
		{
			break;
		}
		tmp = &((*tmp)->next);
	}
	if (*tmp == NULL)
	{
	}
	else if (flag == 0)
	{
		tmp2 = *tmp;
		*tmp = tmp2->next;
		tmp2->next = NULL;
		free(tmp2->data);
		free(tmp2->next);
		free(tmp2);
		set1->size -= 1;

		return 1;
	}	

	return 0;
}

int set_tIntersection(set_t* res, set_t set1, set_t set2, int (*Compare)(struct elem*, struct elem*))
{
	int flag;
	struct MySet* a;
	struct MySet* b;
	struct elem* tmp;

	set_tDestroy(*res);
	set_tCreate(res);

	a = set1->first;
	b = set2->first;
	while (!(a == NULL) && !(b == NULL))
	{
		flag = (*Compare)(a->data, b->data);
		if (flag == -1)
		{
			b = b->next;
		}
		else if (flag == 1)
		{
			a = a->next;
		}
		else
		{
			tmp = malloc(a->size);
			if (tmp == NULL)
			{
				return 0;
			}

			memcpy(tmp, a->data, a->size);
			set_tAdd(*res, tmp, a->size, Compare);
			a = a->next;
			b = b->next;
		}
	}

	return 1;
}

int set_tUnion(set_t* res, set_t set1, set_t set2, int (*Compare)(struct elem*, struct elem*))
{
	unsigned int i;
	struct MySet* a;
	struct MySet* b;
	struct elem* tmp;

	set_tDestroy(*res);
	set_tCreate(res);

	a = set1->first;
	b = set2->first;

	for (i = 0; i < set1->size; i++)
	{
		if (!set_tCheck(*res, a->data, Compare))
		{
			tmp = malloc(a->size);
			if (tmp == NULL)
			{
				return 0;
			}

			memcpy(tmp, a->data, a->size);
			set_tAdd(*res, tmp, a->size, Compare);
		}
		a = a->next;
	}

	for (i = 0; i < set2->size; i++)
	{
		if (!set_tCheck(*res, b->data, Compare))
		{
			tmp = malloc(b->size);
			if (tmp == NULL)
			{
				return 0;
			}

			memcpy(tmp, b->data, b->size);
			set_tAdd(*res, tmp, b->size, Compare);
		}
		b = b->next;
	}

	return 1;
}

int set_tDestroy(set_t set1)
{
	struct MySet* cur, *nxt;
	int i;

	cur = NULL;
	nxt = set1->first;
	for (i = 0; i < set1->size; i++)
	{
		cur = nxt;
		nxt = cur->next;
		free(cur->data);
		free(cur);
	}
	free(set1);

	return 1;
}

void set_tPrint(set_t set1, char **res, char* (*Printing)(struct elem*, char*))
{
	unsigned int i;
	struct MySet* cur;

	*res = malloc(sizeof(char));
	if (*res == NULL)
	{
		return;
	}

	**res = 0;
	cur = set1->first;
	for (i = 0; i < set1->size; i++)
	{
		*res = (*Printing)(cur->data, *res);
		cur = cur->next;
	}
}

int set_tGetSize(set_t set1)
{
	return set1->size;
}
