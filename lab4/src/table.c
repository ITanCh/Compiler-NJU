#include"table.h"
FieldList hashTable[TABLESIZE]; Functype funcTable[TABLESIZE]; /*hash size=2^14*/ 
//void printName(char *name){
//	printf("%s\n",name);
//}
unsigned int hash_pjw(char* name)
{
	unsigned int val = 0, i;
	for (; *name; ++name)
	{
		val = (val << 2) + *name;
		if ((i = val) & ~0x3fff) val = (val ^ (i >> 12)) & 0x3fff;	
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
	//insert function read() and write();
	Functype fr=malloc(sizeof(struct Functype_));
	fr->name=malloc(8);
	strcpy(fr->name,"read");
	fr->isDefined=true;
	fr->row=0;
	fr->retype=malloc(sizeof(struct Type_));
	fr->retype->kind=basic;
	fr->retype->u.basic=INTTYPE;
	fr->param=NULL;
	fr->sameHash=NULL;
	insertFunc(fr,1);

	Functype fw=malloc(sizeof(struct Functype_));
	fw->name=malloc(8);
	strcpy(fw->name,"write");
	fw->isDefined=true;
	fw->row=0;
	fw->retype=fr->retype;
	fw->param=malloc(sizeof(struct FieldList_));
	fw->param->name=malloc(16);
	strcpy(fw->param->name,"write_param");
	fw->param->type=fw->retype;
	fw->param->tail=NULL;
	fw->param->sameHash=NULL;
	fw->sameHash=NULL;
	insertFunc(fw,1);
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
				insertParam(f);
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
					insertParam(f);
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
				else
				{
					Operand funcop=malloc(sizeof(struct Operand_));
					funcop->kind=FUNCTION;
					funcop->u.value=f->name;
					InterCode code=malloc(sizeof(struct InterCode_));
					code->kind=FUNCTION_K;
					code->u.one.op=funcop;
					insertCode(code);		//funtion  :
					FieldList param=f->param;
					while(param!=NULL)
					{
						Operand pop=malloc(sizeof(struct Operand_));	//king of pop--MJ
						pop->kind=VARIABLE;
						pop->u.value=param->name;
						InterCode pcode=malloc(sizeof(struct InterCode_));
						pcode->kind=PARAM_K;
						pcode->u.one.op=pop;
						insertCode(pcode);
						param=param->tail;
					}
				}
			}
			CompSt(child,type);		//give return type	
		}

	}

}

void ExtDecList(Node *n,Type type)
{
	//printName(n->name);
	Node*child=n->children;
	FieldList f=VarDec(child,type,1);	//1:global variable
	if(f!=NULL)
	{
		if(f->type->kind==1)			//array
		{
			Operand op=malloc(sizeof(struct Operand_));
			op->kind=TEMPVAR;
			op->u.var_no=varCount++;

			InterCode deccode=malloc(sizeof(struct InterCode_));
			deccode->kind=DEC_K;
			deccode->u.dec.op=op;
			deccode->u.dec.size=typeSize(f->type);
			insertCode(deccode);

			Operand v=malloc(sizeof(struct Operand_));
			v->kind=VARIABLE;
			v->u.value=f->name;

			InterCode addrcode=malloc(sizeof(struct InterCode_));
			addrcode->kind=RIGHTAT_K;
			addrcode->u.assign.left=v;
			addrcode->u.assign.right=op;
			insertCode(addrcode);
		}
	}
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
	return NULL;
}

/*Declarators*/
FieldList VarDec(Node *n,Type type,int from)		//error type 3
{
	//printName(n->name);
	//1:variable 2:sturct field 3:param
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

		if(from==1&&type->kind==2)		//struct should print DEC code
		{
			Operand op=malloc(sizeof(struct Operand_));
			op->kind=TEMPVAR;
			op->u.var_no=varCount++;

			InterCode deccode=malloc(sizeof(struct InterCode_));
			deccode->kind=DEC_K;
			deccode->u.dec.op=op;
			deccode->u.dec.size=typeSize(type);
			insertCode(deccode);

			Operand v=malloc(sizeof(struct Operand_));
			v->kind=VARIABLE;
			v->u.value=child->value;

			InterCode addrcode=malloc(sizeof(struct InterCode_));
			addrcode->kind=RIGHTAT_K;
			addrcode->u.assign.left=v;
			addrcode->u.assign.right=op;
			insertCode(addrcode);
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

void Stmt(Node *n,Type retype)		//error type 8	return //return type mismatched
{
	//printName(n->name);
	//TODO:more details
	Node*child=n->children;
	if(child==NULL)return;
	if(strcmp(child->name,"Exp")==0)
	{
		Exp(child,NULL);
		return;
	}
	else if(strcmp(child->name,"CompSt")==0)
	{
		CompSt(child,retype);	
		return;
	}
	else if(strcmp(child->name,"RETURN")==0)
	{
		child=child->next;
		//new temp
		Operand op=malloc(sizeof(struct Operand_));
		op->kind=TEMPVAR;
		op->u.var_no=varCount++;
		Type t=Exp(child,op);
		if(retype==NULL||t==NULL)return;
		if(!typeEqual(retype,t))
		{
			printf("Error type 8 at line %d: The return type mismatched\n",child->row);
			return;
		}
		InterCode code=malloc(sizeof(struct InterCode_));
		code->kind=RETURN_K;
		code->u.one.op=op;
		insertCode(code);
		return;
	}
	else if(strcmp(child->name,"IF")==0)
	{
		child=child->next->next;
		//new temp
		Operand lb1=malloc(sizeof(struct Operand_));
		lb1->kind=LABEL;
		lb1->u.var_no=labCount++;
		Operand lb2=malloc(sizeof(struct Operand_));
		lb2->kind=LABEL;
		lb2->u.var_no=labCount++;
		Type t=Exp_Cond(child,lb1,lb2);	//TODO:this function
		if(t!=NULL&&!((t->kind==0||t->kind==3)&&t->u.basic==INTTYPE))
		{
			printf("Error type ? conditional statement wrong type\n");
		}
		//print label1
		InterCode code1=malloc(sizeof(struct InterCode_));
		code1->kind=LABEL_K;
		code1->u.one.op=lb1;
		insertCode(code1);
		child=child->next->next;
		Stmt(child,retype);//code2

		InterCode lb2code=malloc(sizeof(struct InterCode_));
		lb2code->kind=LABEL_K;
		lb2code->u.one.op=lb2;
		if(child->next!=NULL)
		{
			Operand lb3=malloc(sizeof(struct Operand_));
			lb3->kind=LABEL;
			lb3->u.var_no=labCount++;
			InterCode code2=malloc(sizeof(struct InterCode_));
			code2->kind=GOTO_K;
			code2->u.one.op=lb3;
			insertCode(code2);			//goto label3
			insertCode(lb2code);		//label2
			child=child->next->next;
			Stmt(child,retype);			//code3
			InterCode lb3code=malloc(sizeof(struct InterCode_));
			lb3code->kind=LABEL_K;
			lb3code->u.one.op=lb3;
			insertCode(lb3code);		//label3
		}
		else
			insertCode(lb2code);
	}
	else if(strcmp(child->name,"WHILE")==0)
	{
		Operand lb1=malloc(sizeof(struct Operand_));
		lb1->kind=LABEL;
		lb1->u.var_no=labCount++;
		Operand lb2=malloc(sizeof(struct Operand_));
		lb2->kind=LABEL;
		lb2->u.var_no=labCount++;
		Operand lb3=malloc(sizeof(struct Operand_));
		lb3->kind=LABEL;
		lb3->u.var_no=labCount++;
		child=child->next->next;

		InterCode lb1code=malloc(sizeof(struct InterCode_));
		lb1code->kind=LABEL_K;
		lb1code->u.one.op=lb1;
		insertCode(lb1code);		//label 1
		Type t=Exp_Cond(child,lb2,lb3);	//code1
		if(t!=NULL&&!((t->kind==0||t->kind==3)&&t->u.basic==INTTYPE))
		{
			printf("Error type ? conditional statement wrong type\n");
		}

		InterCode lb2code=malloc(sizeof(struct InterCode_));
		lb2code->kind=LABEL_K;
		lb2code->u.one.op=lb2;
		insertCode(lb2code);		//label 2
		child=child->next->next;
		Stmt(child,retype);			//code2
		InterCode gotolb1=malloc(sizeof(struct InterCode_));
		gotolb1->kind=GOTO_K;
		gotolb1->u.one.op=lb1;
		insertCode(gotolb1);		//goto label1
		InterCode lb3code=malloc(sizeof(struct InterCode_));
		lb3code->kind=LABEL_K;
		lb3code->u.one.op=lb3;
		insertCode(lb3code);		//label3
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

	if(f->type->kind==1&&from==1)
	{
		//array space
		Operand op=malloc(sizeof(struct Operand_));
		op->kind=TEMPVAR;
		op->u.var_no=varCount++;

		InterCode deccode=malloc(sizeof(struct InterCode_));
		deccode->kind=DEC_K;
		deccode->u.dec.op=op;
		deccode->u.dec.size=typeSize(f->type);
		insertCode(deccode);

		Operand v=malloc(sizeof(struct Operand_));
		v->kind=VARIABLE;
		v->u.value=f->name;

		InterCode addrcode=malloc(sizeof(struct InterCode_));
		addrcode->kind=RIGHTAT_K;
		addrcode->u.assign.left=v;
		addrcode->u.assign.right=op;
		insertCode(addrcode);
	}

	if(f==NULL)return NULL;
	child=child->next;
	if(child!=NULL){		//assignop =
		if(from==2){	//struct cannot be initialized
			printf("Error type 15 at line %d: be initialized field ‘%s’\n",child->row,f->name);
			return f;
		}
		//assignop left operand
		//此处有代码优化trick
		Operand place=malloc(sizeof(struct Operand_));
		place->kind=VARIABLE;
		place->u.value=f->name;
		child=child->next;
		Type t=Exp(child,place);
		if(t!=NULL&&type!=NULL&&!typeEqual(type,t))
		{
			printf("Error type 5 at line %d: The type mismatched\n",child->row);
		}
		if(place->kind!=VARIABLE||place->u.value!=f->name)
		{
			Operand left=malloc(sizeof(struct Operand_));
			left->kind=VARIABLE;
			left->u.value=f->name;

			InterCode asscode=malloc(sizeof(struct InterCode_));
			asscode->kind=ASSIGN_K;
			asscode->u.assign.left=left;
			asscode->u.assign.right=place;
			insertCode(asscode);
		}
	}
	return f;
}

/*Expressions*/
Type Exp(Node *n,Operand place)
{//printName(n->name);
	Node *child=n->children;
	if(strcmp(child->name,"Exp")==0)
	{	
		Node *child2=child->next;
		//=
		if(strcmp(child2->name,"ASSIGNOP")==0)			
		{
			//left value
			Node *leftChild=child->children;
			Type leftType=NULL;
			//new temp
			Operand leftOp=malloc(sizeof(struct Operand_));
			leftOp->kind=TEMPVAR;
			leftOp->u.var_no=varCount++;
			//because of associative property and priority,it is right
			if(strcmp(leftChild->name,"ID")==0&&leftChild->next==NULL)
				leftType=Exp(child,leftOp);
			else if(strcmp(leftChild->name,"Exp")==0&&leftChild->next!=NULL&&strcmp(leftChild->next->name,"LB")==0)	//array
				leftType=Exp(child,leftOp);
			else if(strcmp(leftChild->name,"Exp")==0&&leftChild->next!=NULL&&strcmp(leftChild->next->name,"DOT")==0)	//struct
				leftType=Exp(child,leftOp);
			else
			{
				printf("Error type 6 at line %d: The left-hand side of an assignment must be a variable\n",child->row);
				return NULL;
			}

			child2=child2->next;
			//new temp
			Operand rightOp=malloc(sizeof(struct Operand_));
			rightOp->kind=TEMPVAR;
			rightOp->u.var_no=varCount++;
			int temp_no=rightOp->u.var_no;		//trick
			Type rightType=Exp(child2,rightOp);

			if(leftType==NULL||rightType==NULL)return NULL;
			if(typeEqual(leftType,rightType))
			{
				//print code here
				if(rightOp->kind==TEMPVAR&&rightOp->u.var_no==temp_no&&(leftOp->kind==TEMPVAR||leftOp->kind==VARIABLE))
					memcpy(rightOp,leftOp,sizeof(struct Operand_));
				else
				{
					InterCode code1=malloc(sizeof(struct InterCode_));
					code1->kind=ASSIGN_K;
					code1->u.assign.left=leftOp;
					code1->u.assign.right=rightOp;
					insertCode(code1);
				}
				InterCode code2=malloc(sizeof(struct InterCode_));
				code2->kind=ASSIGN_K;
				code2->u.assign.left=place;
				code2->u.assign.right=rightOp;
				if(place!=NULL)
					insertCode(code2);
				return leftType;
			}
			else
			{
				printf("Error type 5 at line %d: Type mismatched\n",child->row);
				return NULL;
			}
		}
		else if(strcmp(child2->name,"PLUS")==0||strcmp(child2->name,"MINUS")==0||strcmp(child2->name,"STAR")==0||strcmp(child2->name,"DIV")==0)		//+ - * /
		{
			//new temp
			Operand op1=malloc(sizeof(struct Operand_));
			op1->kind=TEMPVAR;
			op1->u.var_no=varCount++;
			Type t=Exp(child,op1);

			//new temp
			Operand op2=malloc(sizeof(struct Operand_));
			op2->kind=TEMPVAR;
			op2->u.var_no=varCount++;
			Node *child3=child2;
			child2=child2->next;
			Type t2=Exp(child2,op2);
			if(t==NULL||t2==NULL)return NULL;
			else if((t->kind==0||t->kind==3)&&(t2->kind==0||t2->kind==3)&&t->u.basic==t2->u.basic)
			{
				if(place==NULL)return t;
				InterCode code=malloc(sizeof(struct InterCode_));
				code->u.binop.result=place;
				code->u.binop.op1=op1;
				code->u.binop.op2=op2;
				if(strcmp(child3->name,"PLUS")==0)
					code->kind=ADD_K;
				else if(strcmp(child3->name,"MINUS")==0)
					code->kind=SUB_K;
				else if(strcmp(child3->name,"STAR")==0)
					code->kind=MUL_K;
				else if(strcmp(child3->name,"DIV")==0)
					code->kind=DIV_K;
				if(place!=NULL)
					insertCode(code);
				return t;
			}
			else
			{
				printf("Error type 7 at line %d: Operands type mismatched\n",child->row);
				return NULL;
			}
		}
		else if(strcmp(child2->name,"AND")==0||strcmp(child2->name,"OR")==0||strcmp(child2->name,"RELOP")==0)//and or /
		{
			//new temp
			Operand lb1=malloc(sizeof(struct Operand_));
			lb1->kind=LABEL;
			lb1->u.var_no=labCount++;
			Operand lb2=malloc(sizeof(struct Operand_));
			lb2->kind=LABEL;
			lb2->u.var_no=labCount++;

			if(place!=NULL){
				InterCode code0=malloc(sizeof(struct InterCode_));
				code0->kind=ASSIGN_K;
				code0->u.assign.left=place;
				Operand c0=malloc(sizeof(struct Operand_));
				c0->kind=CONSTANT;
				c0->u.value=malloc(32);
				strcpy(c0->u.value,"0");
				code0->u.assign.right=c0;
				insertCode(code0);	//code0
			}
			Type t=Exp_Cond(n,lb1,lb2);	//code1

			InterCode lb1code=malloc(sizeof(struct InterCode_));
			lb1code->kind=LABEL_K;
			lb1code->u.one.op=lb1;
			insertCode(lb1code);	//label 1

			Operand c1=malloc(sizeof(struct Operand_));
			c1->kind=CONSTANT;
			c1->u.value=malloc(32);
			strcpy(c1->u.value,"1");
			InterCode code2=malloc(sizeof(struct InterCode_));
			code2->kind=ASSIGN_K;
			code2->u.assign.left=place;
			code2->u.assign.right=c1;
			if(place!=NULL)
				insertCode(code2);		//code2

			InterCode lb2code=malloc(sizeof(struct InterCode_));
			lb2code->kind=LABEL_K;
			lb2code->u.one.op=lb2;
			insertCode(lb2code);
			return t;
		}
		else if(strcmp(child2->name,"LB")==0)	//array
		{
			Operand aop=malloc(sizeof(struct Operand_));
			aop->kind=TEMPVAR;
			aop->u.var_no=varCount++;
			Type t1=Exp(child,aop);	//array 
			//child's children must be a ID,
			if(t1==NULL)return NULL;
			if(t1->kind!=1)
			{
				printf("Error type 10 at line %d: '",child->row);
				printNode(child);
				printf("' must be an array\n");
				return NULL;
			}

			Operand subs=malloc(sizeof(struct Operand_));
			subs->kind=TEMPVAR;
			subs->u.var_no=varCount++;

			child2=child2->next;
			Type t2=Exp(child2,subs);
			//printf("array back\n");
			if(t2==NULL)return NULL;
			if(!((t2->kind==0||t2->kind==3)&&t2->u.basic==INTTYPE))
			{
				printf("Error type 12 at line %d: Operands type mistaken\n",child2->row);
				return NULL;
			}

			Operand offset=malloc(sizeof(struct Operand_));
			offset->kind=TEMPVAR;
			offset->u.var_no=varCount++;
			
			Operand intsize=malloc(sizeof(struct Operand_));
			intsize->kind=CONSTANT;
			intsize->u.value=malloc(32);
			memset(intsize->u.value,0,32);
			Type subtype=t1->u.array.elem;
			sprintf(intsize->u.value,"%d",typeSize(subtype));

			InterCode addrcode=malloc(sizeof(struct InterCode_));
			addrcode->kind=MUL_K;
			addrcode->u.binop.result=offset;
			addrcode->u.binop.op1=subs;
			addrcode->u.binop.op2=intsize;
			insertCode(addrcode);
			
			Operand temp=malloc(sizeof(struct Operand_));
			temp->kind=TEMPVAR;
			temp->u.var_no=varCount++;

			InterCode code1=malloc(sizeof(struct InterCode_));
			code1->kind=ADD_K;

			if(subtype->kind==0){
				place->kind=TADDRESS;
				place->u.name=temp;
				code1->u.binop.result=temp;
			}
			else
				code1->u.binop.result=place;

			//if(aop->kind==VADDRESS)
			//	aop->kind=VARIABLE;
			//else if(aop->kind==TADDRESS)
			//	aop->kind=TEMPVAR;
			code1->u.binop.op1=aop;
			code1->u.binop.op2=offset;
			insertCode(code1);

			return t1->u.array.elem;
		}
		else if(strcmp(child2->name,"DOT")==0)	//struct
		{
			Operand op1=malloc(sizeof(struct Operand_));
			op1->kind=TEMPVAR;
			op1->u.var_no=varCount++;
			Type t1=Exp(child,op1);
			if(t1==NULL)return NULL;
			if(t1->kind!=2)
			{
				printf("Error type 13 at line %d: Illegal use of '.'\n",child->row);
				return NULL;
			}
			FieldList fl=t1->u.structure->inList;
			child2=child2->next;
			int size=0;
			while(fl!=NULL)
			{
				if(strcmp(fl->name,child2->value)==0)
				{
					if(size==0)
					{
						if(op1->kind==VARIABLE||op1->kind==VADDRESS)
						{
							if(fl->type->kind==0)
							{
								place->kind=VADDRESS;
								place->u.name=op1;
							}
							else
							{
								place->kind=VARIABLE;
								place->u.value=op1->u.value;
							}
						}
						else if(op1->kind==TEMPVAR||op1->kind==TADDRESS)
						{
							if(fl->type->kind==0)
							{
								place->kind=TADDRESS;
								place->u.name=op1;
							}
							else
							{
								place->kind=TEMPVAR;
								place->u.var_no=op1->u.var_no;
							}
						}
					}
					else
					{
						Operand temp=malloc(sizeof(struct Operand_));
						temp->kind=TEMPVAR;
						temp->u.var_no=varCount++;

						Operand conOp=malloc(sizeof(struct Operand_));
						conOp->kind=CONSTANT;
						conOp->u.value=malloc(32);
						memset(conOp->u.value,0,32);
						sprintf(conOp->u.value,"%d",size);

						InterCode code1=malloc(sizeof(struct InterCode_));
						code1->kind=ADD_K;

						if(fl->type->kind==0)
						{
							place->kind=TADDRESS;
							place->u.name=temp;
							code1->u.binop.result=temp;
						}
						else
							code1->u.binop.result=place;
						//if(op1->kind==TADDRESS)
						//	op1->kind=TEMPVAR;
						//else if(op1->kind==VADDRESS)
						//	op1->kind=VARIABLE;
						code1->u.binop.op1=op1;
						code1->u.binop.op2=conOp;
						insertCode(code1);
					}
					return fl->type;
				}
				size+=typeSize(fl->type);
				fl=fl->tail;
			}
			printf("Error type 14 at line %d: Un-existed field '%s‘\n",child2->row,child2->value);
			return NULL;
		}

	}
	else if(strcmp(child->name,"LP")==0)	//() 
	{
		child=child->next;
		return Exp(child,place);
	}
	else if(strcmp(child->name,"MINUS")==0)	//-
	{
		//new temp
		child=child->next;
		Operand op=malloc(sizeof(struct Operand_));
		op->kind=TEMPVAR;
		op->u.var_no=varCount++;
		Type t=Exp(child,op);
		if(t==NULL)return NULL;
		if(t->kind!=0&&t->kind!=3)
		{
			printf("Error type 7 at line %d: Operands type mismatched1\n",child->row);
			return NULL;
		}

		//print code here
		Operand op2=malloc(sizeof(struct Operand_));
		op2->kind=CONSTANT;
		op2->u.value=malloc(4);
		strcpy(op2->u.value,"0");
		InterCode code=malloc(sizeof(struct InterCode_));
		code->kind=SUB_K;
		code->u.binop.result=place;
		code->u.binop.op1=op2;
		code->u.binop.op2=op;
		if(place!=NULL)
			insertCode(code);

		return t;
	}
	else if(strcmp(child->name,"NOT")==0)	//not
	{
		//child=child->next;
		//Type t=Exp(child);
		//if(t==NULL)return NULL;
		//if(t->kind==0&&t->u.basic==INTTYPE)return t;
		//printf("Error type 7 at line %d: Operands type mismatched\n",child->row);
		//return NULL;
		//new temp
		Operand lb1=malloc(sizeof(struct Operand_));
		lb1->kind=LABEL;
		lb1->u.var_no=labCount++;
		Operand lb2=malloc(sizeof(struct Operand_));
		lb2->kind=LABEL;
		lb2->u.var_no=labCount++;

		InterCode code0=malloc(sizeof(struct InterCode_));
		code0->kind=ASSIGN_K;
		code0->u.assign.left=place;
		Operand c0=malloc(sizeof(struct Operand_));
		c0->kind=CONSTANT;
		c0->u.value=malloc(32);
		strcpy(c0->u.value,"0");
		code0->u.assign.right=c0;
		if(place!=NULL)
			insertCode(code0);	//code0
		Type t=Exp_Cond(n,lb1,lb2);	//code1

		InterCode lb1code=malloc(sizeof(struct InterCode_));
		lb1code->kind=LABEL_K;
		lb1code->u.one.op=lb1;
		insertCode(lb1code);	//label 1

		Operand c1=malloc(sizeof(struct Operand_));
		c1->kind=CONSTANT;
		c1->u.value=malloc(32);
		strcpy(c1->u.value,"1");
		InterCode code2=malloc(sizeof(struct InterCode_));
		code2->kind=ASSIGN_K;
		code2->u.assign.left=place;
		code2->u.assign.right=c1;
		if(place!=NULL)
			insertCode(code2);		//code2
InterCode lb2code=malloc(sizeof(struct InterCode_)); lb2code->kind=LABEL_K; lb2code->u.one.op=lb2;
		insertCode(lb2code);
		return t;
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
				printf("Error type 9 at line%d : The method '%s(",child->row,f->name);
				printparam(param);
				printf(")'is not applicable for the arguments '()'\n");
			}
			if(strcmp(f->name,"read")==0)
			{
				InterCode rpcode=malloc(sizeof(struct InterCode_));
				rpcode->kind=READ_K;
				rpcode->u.one.op=place;
				if(place!=NULL)
					insertCode(rpcode);		//read place
			}
			else
			{
				Operand fop=malloc(sizeof(struct Operand_));
				fop->kind=FUNCTION;
				fop->u.value=f->name;
				InterCode cfcode=malloc(sizeof(struct InterCode_));
				cfcode->kind=CALL_K;
				cfcode->u.assign.left=place;//TODO:NULL?
				cfcode->u.assign.right=fop;
				insertCode(cfcode);			//call func
			}
		}
		else
		{
			Operand arg_list_head=malloc(sizeof(struct Operand_));
			arg_list_head->next=NULL;
			if(!Args(child,param,arg_list_head)){
				printf("Error type 9 at line%d : The method '%s(",child->row,f->name);
				printparam(param);
				printf(")'is not applicable for the arguments '(");
				//printargs(child);
				printf(")'\n");
			}
			else
			{
				if(strcmp(f->name,"write")==0)
				{
					InterCode wacode=malloc(sizeof(struct InterCode_));
					wacode->kind=WRITE_K;
					wacode->u.one.op=arg_list_head->next;
					insertCode(wacode);			//write arg
				}
				else
				{
					arg_list_head=arg_list_head->next;
					while(arg_list_head!=NULL)
					{
						InterCode argcode=malloc(sizeof(struct InterCode_));
						argcode->kind=ARG_K;
						argcode->u.one.op=arg_list_head;
						insertCode(argcode);		//Arg arg
						arg_list_head=arg_list_head->next;
					}
					Operand fop=malloc(sizeof(struct Operand_));
					fop->kind=FUNCTION;
					fop->u.value=f->name;
					InterCode cfcode=malloc(sizeof(struct InterCode_));
					cfcode->kind=CALL_K;
					cfcode->u.assign.left=place;
					cfcode->u.assign.right=fop;
					insertCode(cfcode);		//call func
				}
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

		//print code here
		place->kind=VARIABLE;
		place->u.value=child->value;

		return f->type;
	}
	else if(strcmp(child->name,"INT")==0)		
	{
		Type t=malloc(sizeof(struct Type_));
		t->kind=3;
		t->u.basic=INTTYPE;
		//print code here
		if(place!=NULL)
		{
			place->kind=CONSTANT;
			place->u.value=child->value;
		}
		return t;
	}
	else if(strcmp(child->name,"FLOAT")==0)
	{
		Type t=malloc(sizeof(struct Type_));
		t->kind=3;
		t->u.basic=FLOATTYPE;
		if(place!=NULL)
		{
			place->kind=CONSTANT;
			place->u.value=child->value;
		}
		return t;
	}
	return NULL;
}

//exp condition
Type Exp_Cond(Node *n,Operand label_true,Operand label_false)
{//printName(n->name);
	Node *child=n->children;
	Type type;
	if(strcmp(child->name,"Exp")==0)
	{	
		Node *child2=child->next;
		if(strcmp(child2->name,"RELOP")==0)//< >
		{
			//new temp
			Operand t1=malloc(sizeof(struct Operand_));
			t1->kind=TEMPVAR;
			t1->u.var_no=varCount++;
			Operand t2=malloc(sizeof(struct Operand_));
			t2->kind=TEMPVAR;
			t2->u.var_no=varCount++;

			Node* child3=child2;
			child2=child2->next;
			Type tp=Exp(child,t1);	//code1
			Type tp2=Exp(child2,t2);	//code2
			if(tp==NULL||tp2==NULL)return NULL;
			else if((tp->kind==0||tp->kind==3)&&(tp2->kind==0||tp2->kind==3)&&tp->u.basic==tp2->u.basic)
			{
				InterCode code3=malloc(sizeof(struct InterCode_));
				code3->kind=IFGOTO_K;
				code3->u.triop.t1=t1;
				code3->u.triop.op=child3->value;
				code3->u.triop.t2=t2;
				code3->u.triop.label=label_true;
				insertCode(code3);		//code3

				InterCode gotolbf=malloc(sizeof(struct InterCode_));
				gotolbf->kind=GOTO_K;
				gotolbf->u.one.op=label_false;
				insertCode(gotolbf);		//goto label false
				return tp;
			}
			else
			{
				printf("Error type 7 at line %d: Operands type mismatched!\n",child->row);
				return NULL;
			}

		}
		else if(strcmp(child2->name,"AND")==0)
		{
			//new temp
			Operand lb1=malloc(sizeof(struct Operand_));
			lb1->kind=LABEL;
			lb1->u.var_no=labCount++;

			Type t=Exp_Cond(child,lb1,label_false);	//code1

			InterCode lb1code=malloc(sizeof(struct InterCode_));
			lb1code->kind=LABEL_K;
			lb1code->u.one.op=lb1;
			insertCode(lb1code);		//label 1
				
			child2=child2->next;
			Type t2=Exp_Cond(child2,label_true,label_false);	//code2
			if(t==NULL||t2==NULL)return NULL;
			else if((t->kind==0||t->kind==3)&&(t2->kind==0||t2->kind==3)&&t->u.basic==t2->u.basic)
								return t;
			else
			{
				printf("Error type 7 at line %d: Operands type mismatched!!\n",child->row);
				return NULL;
			}

		}
		else if(strcmp(child2->name,"OR")==0)
		{
			//new temp
			Operand lb1=malloc(sizeof(struct Operand_));
			lb1->kind=LABEL;
			lb1->u.var_no=labCount++;

			child2=child2->next;
			Type t=Exp_Cond(child,label_true,lb1);	//code1

			InterCode lb1code=malloc(sizeof(struct InterCode_));
			lb1code->kind=LABEL_K;
			lb1code->u.one.op=lb1;
			insertCode(lb1code);		//label 1

			Type t2=Exp_Cond(child2,label_true,label_false);	//code2
			if(t==NULL||t2==NULL)return NULL;
			else if((t->kind==0||t->kind==3)&&(t2->kind==0||t2->kind==3)&&t->u.basic==t2->u.basic)
				return t;
			else
			{
				printf("Error type 7 at line %d: Operands type mismatched!!!\n",child->row);
				return NULL;
			}

		}

	}
	if(strcmp(child->name,"NOT")==0)	//not
	{
		child=child->next;
		Type t=Exp_Cond(child,label_false,label_true);
		if(t==NULL)return NULL;
		if(t->kind==0&&t->u.basic==INTTYPE)return t;
		printf("Error type 7 at line %d: Operands type mismatched\n",child->row);
		return NULL;
	}
	Operand t1=malloc(sizeof(struct Operand_));
	t1->kind=TEMPVAR;
	t1->u.var_no=varCount++;
	type=Exp(n,t1);		//code1
	InterCode code2=malloc(sizeof(struct InterCode_));
	code2->kind=IFGOTO_K;
	code2->u.triop.t1=t1;
	code2->u.triop.op=malloc(2);
	strcpy(code2->u.triop.op,"!=");
	Operand t2=malloc(sizeof(struct Operand_));
	t2->kind=CONSTANT;
	t2->u.value=malloc(32);
	strcpy(t2->u.value,"0");
	code2->u.triop.t2=t2;
	code2->u.triop.label=label_true;
	insertCode(code2);		//code2

	InterCode gotolbf=malloc(sizeof(struct InterCode_));
	gotolbf->kind=GOTO_K;
	gotolbf->u.one.op=label_false;
	insertCode(gotolbf);		//goto label false
	return type;
}


bool Args(Node* n,FieldList f,Operand arg_list)
{//printName(n->name);
	if(n==NULL&&f==NULL)return true;
	else if(n==NULL||f==NULL)return false;
	Operand t1=malloc(sizeof(struct Operand_));
	t1->kind=TEMPVAR;
	t1->u.var_no=varCount++;
	Node *child=n->children;
	Type t=Exp(child,t1);			//code1
	t1->next=arg_list->next;
	arg_list->next=t1;
	if(t==NULL)return true;		//don't need to report the mistake again
	if(!typeEqual(t,f->type))return false;
	if(child->next==NULL&&f->tail==NULL)return true;
	else if(child->next==NULL||f->tail==NULL)return false;
	return Args(child->next->next,f->tail,arg_list);	//code2
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
	Type t=Exp(child,NULL);
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
	if((t1->kind==0&&t2->kind==3)||(t1->kind==3&&t2->kind==0))    //basic and constant			
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

int typeSize(Type type)
{
	if(type->kind==0||type->kind==3)
	{
		if(type->u.basic==INTTYPE)
			return 4;
		else return 8;
	}
	else if(type->kind==2)	//struct
	{
		int size=0;
		FieldList f=type->u.structure->inList;
		while(f!=NULL)
		{
			size+=typeSize(f->type);
			f=f->tail;
		}
		return size;
	}
	else if(type->kind==1)		//array
	{
		//高维数组
		if(type->u.array.elem->kind==1)
		{
			printf("Can not translate the code: Contain multidimensional array and function parameters of array type!\n");
			exit(-1);
		}
		return	type->u.array.size*typeSize(type->u.array.elem); 
	}
	printf("type size error!\n");
	return 0;
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


