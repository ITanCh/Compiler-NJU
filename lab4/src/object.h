#ifndef _OBJECT_H
#define _OBJECT_H

#include "intercode.h"
typedef struct _reg_t
{
	char name[2];
	char *var;
	int old;
}reg_t;

typedef struct _var_t
{
	char *name;
	int reg;
	int offset;
	struct _var_t* next;
}var_t;

void del_var();
void add_var(var_t*v);
void initReg();
void resetSt();
void freeReg(int index);
int allocReg(Operand op,FILE*fp);
int findReg(FILE*fp);
void getReg(int index,FILE*fp);
void printAllCode(char*fname);
void printObjCode(InterCode c,FILE* fp);
Operand assCode(Operand con,FILE*fp);
#endif
