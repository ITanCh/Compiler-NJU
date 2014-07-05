#ifndef _TABLE_H
#define _TABLE_H

#include"node.h"
/*symbol table and type  struct*/
#define TABLESIZE 32768
#define INTTYPE 0
#define FLOATTYPE 1
typedef enum {false, true}bool;
typedef struct Type_* Type;
typedef struct FieldList_* FieldList;
typedef struct Structure_* Structure;
typedef struct Functype_* Functype;

struct Type_
{
	enum { basic, array, structure,constant} kind;
	union
	{
		// 基本类型
		int basic;
		// 数组类型信息包括元素类型与数组大小构成
		struct { Type elem; int size; } array;
		// 结构体类型信息是一个链表
		Structure structure;
	} u;
};

struct Structure_
{
	char *name;
	FieldList inList;
};

struct FieldList_
{
	char* name;	// 域的名字
	Type type;	// 域的类型
	FieldList tail;	// 下一个域
	FieldList sameHash;
};

struct Functype_
{
	char*name;
	bool isDefined;
	int row;
	Type retype;
	FieldList param;
	Functype sameHash;
};

/*hash*/
unsigned int hash_pjw(char* name);

void initTable();
int insertTable(FieldList f);
int insertFunc(Functype f,int type);
void insertParam(Functype f);
FieldList findSymbol(char* name);
Functype findFunc(char* name);
void checkFunc();
bool paramEqual(FieldList f1,FieldList f2);

/*some traverse tree functions*/
void Program(Node *n);
void ExtDefList(Node *n);
void ExtDef(Node *n);
void ExtDecList(Node *n,Type type);

Type Specifier(Node* n);
Type StructSpecifier(Node* n);

FieldList VarDec(Node *n,Type type,int from);
Functype FunDec(Node *n,Type type);
FieldList VarList(Node *n);
FieldList ParamDec(Node *n);

void CompSt(Node *n,Type retype);
void StmtList(Node *n,Type retype);
void Stmt(Node *n,Type retype);

FieldList DefList(Node* n,int from);
FieldList Def(Node* n,int from);
FieldList DecList(Node *n,Type type,int from);
FieldList Dec(Node *n,Type type,int from);

Type Exp(Node *n);
bool Args(Node *n,FieldList f);

void printparam(FieldList f);
void printargs(Node *n);
void printtype(Type t);
bool typeEqual(Type t1,Type y2);
void printNode(Node* n);

#endif