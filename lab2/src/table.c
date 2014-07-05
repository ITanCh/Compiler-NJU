#include"table.h"

FieldList hashTable[TABLESIZE];
Functype funcTable[TABLESIZE];
/*hash size=2^14*/
//void printName(char *name){
//	printf("%s\n",name);
//}
unsigned int hash_pjw(char* name)
{
	unsigned int val = 0, i;
	for (; *name; ++name)
	{
		val = (val << 2) + *name;
		if (i = val & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;	
	}
	return val;
}

void initTable() 
{
	int i;
	for(i=0;i<TABLESIZE;i++)
	{
		hashTable[i]=NULL;
		funcTable[i]=NULL;
	}
}

int insertTable(FieldList f)
{
	if(f->name==NULL)return 0;	//do not insert it
	unsigned int no= hash_pjw(f->name);
	if(hashTable[no]==NULL)
	{
		hashTable[no]=f;
	}
	else 
	{
		FieldList q=hashTable[no];
		if(strcmp(q->name,f->name)==0)return 1;	//redefine this id
		while(q->sameHash!=NULL)
		{
			q=q->sameHash;
			if(strcmp(q->name,f->name)==0)return 1;	//redefine this id
		}
		q->sameHash=f;
	}
	return 0;
}

int insertFunc(Functype f,int type)		//0:declare 1:define
{
	if(f->name==NULL)return 0;		
	unsigned int no= hash_pjw(f->name);
	if(funcTable[no]==NULL)
	{
		funcTable[no]=f;
		insertParam(f);
	}
	else 
	{
		Functype q=funcTable[no];
		if(strcmp(q->name,f->name)==0)
		{
			if(q->isDefined)
				return 1;	//redefine this func
			else
			{
				if(!typeEqual(q->retype,f->retype)||!paramEqual(q->param,f->param))
					return 2;	//Inconsistent declaration
				q->isDefined=type;
				return 0;
			}
		}
		while(q->sameHash!=NULL)
		{
			q=q->sameHash;
			if(strcmp(q->name,f->name)==0)
			{
				if(q->isDefined)
					return 1;	//redefine this func
				else
				{
					if(!typeEqual(q->retype,f->retype)||!paramEqual(q->param,f->param))
						return 2;	//Inconsistent declaration
					q->isDefined=type;
					return 0;
				}
			}
		}
		q->sameHash=f;
		insertParam(f);
	}
	return 0;
}

void insertParam(Functype f)
{
	FieldList param=f->param;
	int i=0;
	while(param!=NULL)
	{
		i=insertTable(param);
		if(i==1)
		{
			printf("Error type 3 at line %d: Redefined variable'%s'\n",f->row,param->name);
		}
		param=param->tail;
	}
}

//function params and struct field can use if to compare
bool paramEqual(FieldList f1,FieldList f2)
{
	if(f1==NULL&&f2==NULL)
		return true;
	if(f1==NULL||f2==NULL)
		return false;
	if(typeEqual(f1->type,f2->type))return paramEqual(f1->tail,f2->tail);
	else
		return false;
}


FieldList findSymbol(char *name){	
	unsigned int no=hash_pjw(name);
	if(hashTable[no]==NULL)return NULL;
	FieldList p=hashTable[no];
	while(p!=NULL){
		if(strcmp(p->name,name)==0)return p;
		p=p->sameHash;
	}
	return NULL;
}

Functype findFunc(char *name)
{
	unsigned int no=hash_pjw(name);
	if(funcTable[no]==NULL)return NULL;
	Functype p=funcTable[no];
	while(p!=NULL){
		if(strcmp(p->name,name)==0)return p;
		p=p->sameHash;
	}
	return NULL;
}

void checkFunc()
{
	int i;
	for(i=0;i<TABLESIZE;i++)
	{
		if(funcTable[i]!=NULL)
		{
			Functype p=funcTable[i];
			while(p!=NULL)
			{
				if(!p->isDefined)
					printf("Error type 18 at line %d: Undefined function '%s'\n",p->row,p->name);
				p=p->sameHash;
			}
		}
	}
}
/* non-terminal function*/
void Program(Node *n)
{
	//printName(n->name);
	ExtDefList(n->children);
	checkFunc();
}

void ExtDefList(Node *n)
{
	//printName(n->name);
	Node *child=n->children;
	if(child!=NULL)
	{
		ExtDef(child);
		ExtDefList(child->next);
	}
}


/*definition of variables*/
void ExtDef(Node *n){	
	//printName(n->name);
	Node*child=n->children;
	Type type;
	type=Specifier(child);	
	child=child->next;
	if(strcmp(child->name,"SEMI")==0)
		return;
	else if(strcmp(child->name,"ExtDecList")==0)
	{
		ExtDecList(child,type);
	}
	else
	{
		Functype f=FunDec(child,type);	//form param	

		child=child->next;
		int i=0;
		if(strcmp(child->name,"SEMI")==0)
		{
			if(f==NULL)return;
			f->isDefined=0;
			i=insertFunc(f,0);
			if(i==1)
				printf("Error type 4 at line %d: Redefined function '%s'\n",f->row,f->name);
			else if(i==2)
				printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n",f->row,f->name);
		}
		else{
			if(f!=NULL){
				f->isDefined=1;
				i=insertFunc(f,1);
				if(i==1)
					printf("Error type 4 at line %d: Redefined function '%s'\n",f->row,f->name);
				else if(i==2)
					printf("Error type 19 at line %d: Inconsistent declaration of function '%s'\n",f->row,f->name);

			}
			CompSt(child,type);		//give return type	
		}

	}

}

void ExtDecList(Node *n,Type type)
{
	//printName(n->name);
	Node*child=n->children;
	VarDec(child,type,1);
	child=child->next;
	if(child!=NULL)
	{
		child=child->next;
		ExtDecList(child,type);
	}
}

/*Specifiers*/
Type Specifier(Node* n)
{
	//printName(n->name);
	Node *child=n->children;
	Type type;
	if(strcmp(child->name,"TYPE")==0)		//basic type
	{
		type=malloc(sizeof(struct Type_));
		type->kind=0;
		if(strcmp(child->value,"int")==0)
		{
			type->u.basic=INTTYPE;
		}
		else if(strcmp(child->value,"float")==0)
		{
			type->u.basic=FLOATTYPE;
		}
	}
	else //if(strcmp(child->name,"StructSpecifier")==0) 
	{
		type=StructSpecifier(child);
	}
	return type;
}

//struct type
Type StructSpecifier(Node *n)
{
	//printName(n->name);
	Node *child=n->children;
	Type type=malloc(sizeof(struct Type_));
	type->kind=2;
	type->u.structure=malloc(sizeof(struct Structure_));
	type->u.structure->inList=NULL;
	FieldList f=malloc(sizeof(struct FieldList_));
	f->type=type;
	while(child!=NULL)
	{
		if(strcmp(child->name,"OptTag")==0)
		{
			if(child->children==NULL)
			{
				type->u.structure->name=NULL;
			}
			else{
				type->u.structure->name=malloc(sizeof(child->children->value));
				strcpy(type->u.structure->name,child->children->value);
				f->name=malloc(sizeof(child->children->value));
				strcpy(f->name,child->children->value);
			}
		}
		else if(strcmp(child->name,"Tag")==0)
		{
			FieldList structf=findSymbol(child->children->value);
			//printf("%s\n",child->children->value);
			if(structf==NULL||structf->type->kind!=2||strcmp(structf->name,structf->type->u.structure->name)!=0)
			{
				printf("Error type 17 at line %d: Undefined struct ‘%s’\n",child->row,child->children->value);
				return NULL;
			}
			return structf->type;
		}
		else if(strcmp(child->name,"DefList")==0)
		{
			type->u.structure->inList=DefList(child,2);	//struct field 
			//from=2,other=1
			if(f->type->u.structure->name==NULL)return type;	//s struct without name
			int i=insertTable(f);
			if(i==1)
			{
				printf("Error type 16 at line %d: Duplicated name ‘%s’\n",child->row,f->name);
				return NULL;
			}
			return type;
		}
		child=child->next;
	}
}

/*Declarators*/
FieldList VarDec(Node *n,Type type,int from)		//error type 3
	//redefined variable
{
	//printName(n->name);
	Node *child=n->children;
	FieldList f;
	if(strcmp(child->name,"ID")==0)
	{
		f=malloc(sizeof(struct FieldList_));
		f->name=malloc(sizeof(child->value));
		strcpy(f->name,child->value);
		f->type=type;
		f->tail=NULL;
		f->sameHash=NULL;
		if(from==3)return f;	//do not insert this  param now
		int i=insertTable(f);		//insert this ID
		//if redefined
		if(i==1)
		{
			if(from==1)
				printf("Error type 3 at line %d: Redefined variable'%s'\n",child->row,f->name);	
			else
				printf("Error type 15 at line %d: Redefined field ‘%s’\n",child->row,f->name);
			return NULL;
		}
		return f;
	}
	else
	{							//construct arry 
		f=VarDec(child,type,from);
		if(f==NULL)return NULL;
		Type temp=f->type;
		child=child->next;
		child=child->next;	//INT
		Type t=malloc(sizeof(struct Type_));
		t->kind=1;		//array
		t->u.array.size=atoi(child->value);
		t->u.array.elem=type;
		if(temp->kind!=1)
		{
			f->type=t;
			return f;
		}
		while(temp->u.array.elem->kind==1)	//find the end of this array
		{
			temp=temp->u.array.elem;
		}
		temp->u.array.elem=t;
		//printtype(f->type);
		return f;
	}
}

Functype FunDec(Node* n,Type type)
{
	//printName(n->name);
	Node* child=n->children;
	Functype f=malloc(sizeof(struct Functype_));
	f->name=malloc(sizeof(child->value));
	strcpy(f->name,child->value);
	f->isDefined=0;
	f->row=child->row;
	f->retype=type;
	f->sameHash=NULL;
	f->param=NULL;
	child=child->next;
	child=child->next;
	if(strcmp(child->name,"VarList")==0)
	{
		f->param=VarList(child);
	}
	return f;
}

FieldList VarList(Node *n)
{
	//printName(n->name);
	Node* child=n->children;
	FieldList f;
	f=ParamDec(child);
	child=child->next;
	if(child!=NULL)
	{
		FieldList p=f;
		child=child->next;
		if(p==NULL)f=VarList(child);
		else{
			while(p->tail!=NULL)p=p->tail;
			p->tail=VarList(child);
		}
	}
	return f;
}

FieldList ParamDec(Node*n)
{
	//printf("ParamDec\n");
	Node *child=n->children;
	FieldList f;
	Type type;
	type=Specifier(child);
	f=VarDec(child->next,type,3);		//from function param
	return f;
}

/*Statements*/
void CompSt(Node * n,Type retype)
{
	//printf("CompSt\n");
	Node *child=n->children;
	child=child->next;
	DefList(child,1);
	child=child->next;
	StmtList(child,retype);
}

void StmtList(Node *n,Type retype)
{
	//printf("StmtList\n");
	Node *child=n->children;
	if(child==NULL)return;
	Stmt(child,retype);
	child=child->next;
	StmtList(child,retype);
}

void Stmt(Node *n,Type retype)		//error type 8	return 
	//return type mismatched
{
	//printName(n->name);
	//TODO:more details
	Node*child=n->children;
	while(child!=NULL)
	{
		if(strcmp(child->name,"RETURN")==0)
		{
			child=child->next;
			Type t=Exp(child);
			if(retype==NULL||t==NULL)return;
			if(!typeEqual(retype,t))
			{
				printf("Error type 8 at line %d: The return type mismatched\n",child->row);
			}
			return;
		}
		else if(strcmp(child->name,"LP")==0)
		{
			child=child->next;
			Type t=Exp(child);
			if(t!=NULL&&!((t->kind==0||t->kind==3)&&t->u.basic==INTTYPE))
			{
				printf("Error type ? conditional statement wrong type\n");
			}
		}
		else if(strcmp(child->name,"Exp")==0)
		{
			Exp(child);
		}
		else if(strcmp(child->name,"Stmt")==0)
		{
			Stmt(child,retype);
		}
		child=child->next;
	}
}

/*Local Definitions*/
FieldList DefList(Node* n,int from)
{//printName(n->name);
	if(n->children==NULL)return NULL;
	FieldList f;
	Node *child=n->children;
	f=Def(child,from);
	FieldList t=f;
	child=child->next;
	if(t!=NULL){
		while(t->tail!=NULL)	//find the last field
		{
			t=t->tail;
		}
		t->tail=DefList(child,from);
	}
	else f=DefList(child,from);
	return f;
}

FieldList Def(Node *n,int from)
{//printName(n->name);
	Node* child=n->children;
	FieldList f;	//=malloc(sizeof(struct FieldList_));
	Type type=Specifier(child);
	child=child->next;
	f=DecList(child,type,from);	//inhre
	return f;
}

FieldList DecList(Node *n,Type type,int from)
{//printName(n->name);
	Node *child=n->children;
	FieldList f;
	f=Dec(child,type,from);
	child=child->next;
	if(child!=NULL){
		child=child->next;
		FieldList p=f;
		if(p!=NULL)
		{
			while(p->tail!=NULL)p=p->tail;
			p->tail=DecList(child,type,from);
		}
		else 
			f=DecList(child,type,from);
	}
	return f;
}

FieldList Dec(Node *n,Type type,int from)	//error type 5
	//type mismatched
{//printName(n->name);
	Node *child=n->children;
	FieldList f;
	f=VarDec(child,type,from);
	child=child->next;
	if(child!=NULL){		//assignop =
		if(from==2){	//struct cannot be initialized
			printf("Error type 15 at line %d: be initialized field ‘%s’\n",child->row,f->name);
			return f;
		}
		child=child->next;
		Type t=Exp(child);
		if(t!=NULL&&type!=NULL&&!typeEqual(type,t))
		{
			printf("Error type 5 at line %d: The type mismatched\n",child->row);
		}
	}
	return f;
}

/*Expressions*/
Type Exp(Node *n)
{//printName(n->name);
	Node *child=n->children;
	Type type;
	if(strcmp(child->name,"Exp")==0)
	{	
		Node *child2=child->next;
		//=
		if(strcmp(child2->name,"ASSIGNOP")==0)			
		{
			//left value
			Node *leftChild=child->children;
			Type leftType=NULL;
			//because of associative property and priority,it is right
			if(strcmp(leftChild->name,"ID")==0&&leftChild->next==NULL)
				leftType=Exp(child);
			else if(strcmp(leftChild->name,"Exp")==0&&leftChild->next!=NULL&&strcmp(leftChild->next->name,"LB")==0)	//array
				leftType=Exp(child);
			else if(strcmp(leftChild->name,"Exp")==0&&leftChild->next!=NULL&&strcmp(leftChild->next->name,"DOT")==0)	//struct
			{
				leftType=Exp(child);

			}
			else
				printf("Error type 6 at line %d: The left-hand side of an assignment must be a variable\n",child->row);
			child2=child2->next;
			Type rightType=Exp(child2);
			if(leftType==NULL||rightType==NULL)return NULL;
			if(typeEqual(leftType,rightType))return leftType;
			else
			{
				printf("Error type 5 at line %d: Type mismatched\n",child->row);
				return NULL;
			}
		}
		else if(strcmp(child2->name,"PLUS")==0||strcmp(child2->name,"MINUS")==0||strcmp(child2->name,"STAR")==0||strcmp(child2->name,"DIV")==0||strcmp(child2->name,"RELOP")==0)		//+ - * /
		{
			Type t=Exp(child);
			child2=child2->next;
			Type t2=Exp(child2);
			if(t==NULL||t2==NULL)return NULL;
			else if((t->kind==0||t->kind==3)&&(t2->kind==0||t2->kind==3)&&t->u.basic==t2->u.basic)return t;
			else
			{
				printf("Error type 7 at line %d: Operands type mismatched\n",child->row);
				return NULL;
			}
		}
		else if(strcmp(child2->name,"LB")==0)	//array
		{
			Type t1=Exp(child);
			//child's children must be a ID,
			if(t1==NULL)return NULL;
			if(t1->kind!=1)
			{
				printf("Error type 10 at line %d: '",child->row);
				printNode(child);
				printf("' must be an array\n");
				return NULL;
			}
			child2=child2->next;
			Type t2=Exp(child2);
			//printf("array back\n");
			if(t2==NULL)return NULL;
			if(!((t2->kind==0||t2->kind==3)&&t2->u.basic==INTTYPE))
			{
				printf("Error type 12 at line %d: Operands type mistaken\n",child2->row);
				return NULL;
			}
			return t1->u.array.elem;
		}
		else if(strcmp(child2->name,"DOT")==0)	//struct
		{
			Type t1=Exp(child);
			if(t1==NULL)return NULL;
			if(t1->kind!=2)
			{
				printf("Error type 13 at line %d: Illegal use of '.'\n",child->row);
				return NULL;
			}
			FieldList fl=t1->u.structure->inList;
			child2=child2->next;
			while(fl!=NULL)
			{
				if(strcmp(fl->name,child2->value)==0)
					return fl->type;
				fl=fl->tail;
			}
			printf("Error type 14 at line %d: Un-existed field '%s‘\n",child2->row,child2->value);
			return NULL;
		}

	}
	else if(strcmp(child->name,"LP")==0)	//() 
	{
		child=child->next;
		return Exp(child);
	}
	else if(strcmp(child->name,"MINUS")==0)	//-
	{
		child=child->next;
		Type t=Exp(child);
		if(t==NULL)return NULL;
		if(t->kind!=0)
		{
			printf("Error type 7 at line %d: Operands type mismatched\n",child->row);
			return NULL;
		}
		return t;
	}
	else if(strcmp(child->name,"NOT")==0)	//not
	{
		child=child->next;
		Type t=Exp(child);
		if(t==NULL)return NULL;
		if(t->kind==0&&t->u.basic==INTTYPE)return t;
		printf("Error type 7 at line %d: Operands type mismatched\n",child->row);
		return NULL;
	}
	else if(strcmp(child->name,"ID")==0&&child->next!=NULL)	//func
	{

		FieldList f1=findSymbol(child->value);
		Functype f=findFunc(child->value);
		if(f1!=NULL&&f==NULL)
		{
			printf("Error type 11 at line %d: '%s' must be a function\n",child->row,child->value);
			return NULL;
		}
		if(f==NULL||!f->isDefined){
			printf("Error type 2 at line %d: Undefined function '%s'\n",child->row,child->value);
			return NULL;
		}
		FieldList param=f->param;
		child=child->next;
		child=child->next;
		if(strcmp(child->name,"RP")==0)
		{
			if(param!=NULL)
			{
				printf("Error type 9 at line : The method '%s(",f->name);
				printparam(param);
				printf(")'is not applicable for the arguments '()'\n");
			}
		}
		else
		{
			if(!Args(child,param)){
				printf("Error type 9 at line : The method '%s(",f->name);
				printparam(param);
				printf(")'is not applicable for the arguments '(");
				printargs(child);
				printf(")'\n");
			}
		}
		return f->retype;
	}
	else if(strcmp(child->name,"ID")==0)
	{
		FieldList f=findSymbol(child->value);
		if(f==NULL)
		{
			printf("Error type 1 at line %d: Undefined variable '%s'\n",child->row,child->value);	
			return NULL;
		}
		return f->type;
	}
	else if(strcmp(child->name,"INT")==0)
	{
		Type t=malloc(sizeof(struct Type_));
		t->kind=3;
		t->u.basic=INTTYPE;
		return t;
	}
	else if(strcmp(child->name,"FLOAT")==0)
	{
		Type t=malloc(sizeof(struct Type_));
		t->kind=3;
		t->u.basic=FLOATTYPE;
		return t;
	}

}

bool Args(Node* n,FieldList f)
{//printName(n->name);
	if(n==NULL&&f==NULL)return true;
	else if(n==NULL||f==NULL)return false;
	Node *child=n->children;
	Type t=Exp(child);
	if(t==NULL)return true;		//don't need to report the mistake again
	if(!typeEqual(t,f->type))return false;
	if(child->next==NULL&&f->tail==NULL)return true;
	else if(child->next==NULL||f->tail==NULL)return false;
	return Args(child->next->next,f->tail);
}

//some useful function
void printparam(FieldList f)
{
	while(f!=NULL)
	{
		printtype(f->type);
		f=f->tail;
	}
}

void printargs(Node *n)
{
	Node *child=n->children;
	Type t=Exp(child);
	if(t==NULL)return;
	printtype(t);
	child=child->next;
	if(child==NULL)return;
	child=child->next;
	printargs(child);
}

void printtype(Type t){
	if((t->kind==0||t->kind==3)&&t->u.basic==INTTYPE)
		printf(" int ");
	else if((t->kind==0||t->kind==3)&&t->u.basic==FLOATTYPE)
		printf(" float ");
	else if(t->kind==2)
		printf("struct %s ",t->u.structure->name);
	else if(t->kind==1){
		printtype(t->u.array.elem);
		printf("[]");
	}
}

bool typeEqual(Type t1,Type t2)
{
	if(t1->kind==0&&t2->kind==3)     //basic and constant
	{
		if(t1->u.basic!=t2->u.basic)
		{
			return false;
		}
	}
	else if(t1->kind!=t2->kind)
	{
		return false;
	}
	else
	{
		if(t1->kind==0)	//basic
		{
			if(t1->u.basic!=t2->u.basic)
				return false;
		}
		else if(t1->kind==2)	//struct
		{
			//if a struct do not has  a name 
			if(t1->u.structure->name==NULL||t2->u.structure->name==NULL)
			{
				return paramEqual(t1->u.structure->inList,t2->u.structure->inList);								
			}
			if(strcmp(t1->u.structure->name,t2->u.structure->name)!=0)
				return false;
		}
		else if(t1->kind==1)        //array
		{
			return typeEqual(t1->u.array.elem,t2->u.array.elem);
		}
	}
	return true;
}

void printNode(Node *n)
{
	Node *child=n->children;
	if(child==NULL)
	{
		printf(" %s",n->value);
		return;
	}
	while(child!=NULL)
	{
		printNode(child);
		child=child->next;
	}
}
