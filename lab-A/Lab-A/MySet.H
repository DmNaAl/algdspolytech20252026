#pragma once
#include <malloc.h>

struct elem;
typedef struct MySetShell* set_t;

int set_tCreate(set_t* set1_var);
int set_tAdd(set_t set1, struct elem* udata, unsigned int size, int (*Compare)(struct elem*, struct elem*));
int set_tCheck(set_t set1, struct elem* udata, int (*Compare)(struct elem*, struct elem*));
int set_tRemove(set_t set1, struct elem* udata, int (*Compare)(struct elem*, struct elem*));
int set_tIntersection(set_t* res, set_t set1, set_t set2, int (*Compare)(struct elem*, struct elem*));
int set_tUnion(set_t* res, set_t set1, set_t set2, int (*Compare)(struct elem*, struct elem*));
int set_tDestroy(set_t set1);
void set_tPrint(set_t set1, char **res, char* (*Printing)(struct elem*, char*));
int set_tGetSize(set_t set1);