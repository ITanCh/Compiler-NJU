#include"stdlib.h"
#include"stdio.h"
#include"string.h"
#include"intercode.h"

InterCode code_h=NULL;
InterCode code_t=NULL;

int varCount=1;
int labCount=1;


/* code node functions*/
void insertCode(InterCode c)
{
	c->pre=NULL;
	c->next=NULL;
	if(code_h==NULL)
	{
		code_h=c;
		code_t=c;
	}
	else
	{
		c->pre=code_t;
		code_t->next=c;
		code_t=c;
	}
}

void deleteCode(InterCode c)
{
	if(c==code_h&&c==code_t)
	{
		code_h=NULL;
		code_t=NULL;
	}
	else if(c==code_h)
	{
		if(c->next!=NULL)
			c->next->pre=NULL;
		code_h=c->next;
	}
	else if(c==code_t)
	{
		if(c->pre!=NULL)
			c->pre->next=NULL;
		code_t=c->pre;
	}
	else
	{
		if(c->next!=NULL)
			c->next->pre=c->pre;
		if(c->pre!=NULL)
			c->pre->next=c->next;
	}
}

//print code in file
void printCode(char* fname)
{
	FILE *fp=fopen(fname,"w");
	if(fp==NULL)
	{
		printf("open file error\n");
		return;
	}
	InterCode c=code_h;
	while(c!=NULL)
	{
		switch(c->kind)
		{
			case ASSIGN_K:
				printOp(c->u.assign.left,fp);
				fputs(":=	",fp);
				printOp(c->u.assign.right,fp);
				break;
			case ADD_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("+	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case SUB_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("-	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case MUL_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("*	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case DIV_K:
				printOp(c->u.binop.result,fp);
				fputs(":=	",fp);
				printOp(c->u.binop.op1,fp);
				fputs("/	",fp);
				printOp(c->u.binop.op2,fp);
				break;
			case RETURN_K:
				fputs("RETURN	",fp);
				printOp(c->u.one.op,fp);
				break;
			case LABEL_K:
				fputs("LABEL	",fp);
				printOp(c->u.one.op,fp);
				fputs(":	",fp);
				break;
			case GOTO_K:
				fputs("GOTO	",fp);
				printOp(c->u.one.op,fp);
				break;
			case IFGOTO_K:
				fputs("IF	",fp);
				printOp(c->u.triop.t1,fp);
				fputs(c->u.triop.op,fp);
				fputs("	",fp);
				printOp(c->u.triop.t2,fp);
				fputs("GOTO	",fp);
				printOp(c->u.triop.label,fp);
				break;
			case READ_K:
				fputs("READ	",fp);
				printOp(c->u.one.op,fp);
				break;
			case WRITE_K:
				fputs("WRITE	",fp);
				printOp(c->u.one.op,fp);
				break;
			case CALL_K:
				printOp(c->u.assign.left,fp);
				fputs(":=	CALL	",fp);
				printOp(c->u.assign.right,fp);
				break;
			case ARG_K:
				fputs("ARG	",fp);
				printOp(c->u.one.op,fp);
				break;
			case FUNCTION_K:
				fputs("FUNCTION	",fp);
				printOp(c->u.one.op,fp);
				fputs(":",fp);
				break;
			case PARAM_K:
				fputs("PARAM	",fp);
				printOp(c->u.one.op,fp);
				break;
			case RIGHTAT_K:
				printOp(c->u.assign.left,fp);
				fputs(":=	&",fp);
				printOp(c->u.assign.right,fp);
				break;
			case DEC_K:
				fputs("DEC	",fp);
				printOp(c->u.dec.op,fp);
				char size[32];
				sprintf(size,"%d",c->u.dec.size);
				fputs(size,fp);
				break;
		}
		fputs("\n",fp);
		c=c->next;
	}
	fclose(fp);
}

void printOp(Operand op,FILE* fp)
{
	if(op==NULL)
	{
		fputs("t0	",fp);//t0 is use less but can avoid some error
		return;
	}

	char var[32];
	memset(var,0,sizeof(var));
	switch(op->kind)
	{
		case TEMPVAR:
			fputs("t",fp);
			sprintf(var,"%d",op->u.var_no);
			fputs(var,fp);
			break;
		case VARIABLE:
			fputs(op->u.value,fp);
			break;
		case CONSTANT:
			fputs("#",fp);
			fputs(op->u.value,fp);
			break;
		case LABEL:
			fputs("label",fp);
			sprintf(var,"%d",op->u.var_no);
			fputs(var,fp);
			break;
		case FUNCTION:
			fputs(op->u.value,fp);
			break;
		case TADDRESS: fputs("*t",fp);
			sprintf(var,"%d",op->u.name->u.var_no);
			fputs(var,fp);
			break;
		case VADDRESS:
			fputs("*",fp);
			fputs(op->u.name->u.value,fp);
			break;
	}
	fputs("	",fp);
}

/*optimize code*/
void optIF()
{
	InterCode c=code_h;
	while(c!=NULL)
	{
		if(c->kind==IFGOTO_K)
		{
			InterCode c1=c;
			InterCode c2=c->next;
			if(c2==NULL)continue;
			InterCode c3=c2->next;
			if(c3==NULL)continue;
			if(c2->kind==GOTO_K&&c3->kind==LABEL_K&&c1->u.triop.label==c3->u.one.op)
			{
				c1->u.triop.label=c2->u.one.op;
				deleteCode(c2);
				if(strcmp(c1->u.triop.op,"==")==0)
				{
					c1->u.triop.op=malloc(4);
					memset(c1->u.triop.op,0,4);
					strcpy(c1->u.triop.op,"!=");
				}
				else if(strcmp(c1->u.triop.op,"!=")==0)
				{
					c1->u.triop.op=malloc(4);
					memset(c1->u.triop.op,0,4);
					strcpy(c1->u.triop.op,"==");
				}
				else if(strcmp(c1->u.triop.op,">=")==0)
				{
					c1->u.triop.op=malloc(4);
					memset(c1->u.triop.op,0,4);
					strcpy(c1->u.triop.op,"<");
				}
				else if(strcmp(c1->u.triop.op,"<")==0)
				{
					c1->u.triop.op=malloc(4);
					memset(c1->u.triop.op,0,4);
					strcpy(c1->u.triop.op,">=");
				}
				else if(strcmp(c1->u.triop.op,">")==0)
				{
					c1->u.triop.op=malloc(4);
					memset(c1->u.triop.op,0,4);
					strcpy(c1->u.triop.op,"<=");
				}
				else if(strcmp(c1->u.triop.op,"<=")==0)
				{
					c1->u.triop.op=malloc(4);
					memset(c1->u.triop.op,0,4);
					strcpy(c1->u.triop.op,">");
				}
			}
		}
		else if(c->kind==GOTO_K)
		{
			InterCode c1=c;
			InterCode c2=c->next;
			if(c2!=NULL&&c2->kind==LABEL_K&&c1->u.one.op==c2->u.one.op)
			{
				c=c->next;
				deleteCode(c1);
			}
		}
		c=c->next;	
	}
}

//remove useless label
void rmLabel()
{
	Label_No head=malloc(sizeof(struct Label_No_));
	head->no=-1;
	head->next=NULL;
	Label_No tail=head;
	InterCode c=code_h;
	//count label no.
	while(c!=NULL)
	{
		if(c->kind==GOTO_K)
		{
			Label_No temp=malloc(sizeof(struct Label_No_));
			temp->no=c->u.one.op->u.var_no;
			temp->next=NULL;
			tail->next=temp;
			tail=temp;
		}
		else if(c->kind==IFGOTO_K)
		{
			Label_No temp=malloc(sizeof(struct Label_No_));
			temp->no=c->u.triop.label->u.var_no;
			temp->next=NULL;
			tail->next=temp;
			tail=temp;
		}
		c=c->next;
	}

	c=code_h;
	while(c!=NULL)
	{
		if(c->kind==LABEL_K)
		{
			int no=c->u.one.op->u.var_no;
			Label_No ln=head;
			while(ln!=NULL)
			{
				if(ln->no==no)break;
				ln=ln->next;
			}
			InterCode c1=c;
			c=c->next;
			if(ln==NULL)
				deleteCode(c1);
		}
		else
			c=c->next;
	}

	tail=NULL;
	while(head!=NULL)
	{
		Label_No ln=head;
		head=head->next;
		free(ln);
	}
}

int opEqual(Operand op1,Operand op2)
{
	if(op1==NULL||op2==NULL)return 0;
	if(op1->kind==TEMPVAR||op1->kind==VARIABLE||op1->kind==CONSTANT);
	else	return 0;
	if(op1==op2)return 1;
	if(op1->kind==TEMPVAR&&op2->kind==TEMPVAR&&op1->u.var_no==op2->u.var_no)
		return 1;
	if(op1->kind==VARIABLE&&op2->kind==VARIABLE&&strcmp(op1->u.value,op2->u.value)==0)
		return 1;
	if(op1->kind==CONSTANT&&op2->kind==CONSTANT)
	{
		int p1=atoi(op1->u.value);
		int p2=atoi(op2->u.value);
		//printf("!!!!!%d!!!!!!%d!!!!!\n",p1,p2);
		if(p1==p2)//||op1->u.value==op2->u.value||strcpy(op1->u.value,op2->u.value)==0)
			return 1;
	}
	return 0;
}

void rddCode()
{
	InterCode top=code_t;
	InterCode bottom=code_t;
	//from buttom to top
	while(1)
	{
		//find a block
		bottom=top->pre;
		if(bottom==NULL)break;
		top=bottom->pre;
		if(top==NULL)break;
		while(top!=NULL)
		{
			if(top->kind==RETURN_K||top->kind==GOTO_K||top->kind==IFGOTO_K||top->kind==CALL_K)
			{
				top=top->next;
				break;
			}
			else if(top->kind==LABEL_K||top->kind==FUNCTION_K)
				break;
			top=top->pre;
		}
		if(top==NULL)top=code_h;
		if(bottom==top)continue;

		//deal with this block
		while(bottom!=NULL&&bottom!=top->pre)
		{
			Operand noAct=NULL;
			InterCode p=bottom;
			int flag=0;
			if(p->kind==ASSIGN_K)
			{
				if(p->u.assign.left->kind==VARIABLE&&!opEqual(p->u.assign.left,p->u.assign.right))
				{
					noAct=p->u.assign.left;
					flag=1;
				}
			}
			else if(p->kind==ADD_K||p->kind==SUB_K||p->kind==MUL_K||p->kind==DIV_K)
			{
				if(p->u.binop.result->kind==VARIABLE&&!opEqual(p->u.binop.result,p->u.binop.op1)&&!opEqual(p->u.binop.result,p->u.binop.op2))
				{
					noAct=p->u.binop.result;
					flag=1;
				}
			}

			if(flag)
			{
				p=p->pre;
				while(p!=NULL&&p!=top->pre)
				{
					if(p->kind==ASSIGN_K||p->kind==CALL_K)
					{
						if(opEqual(noAct,p->u.assign.right)||p->u.assign.left->kind==VADDRESS)break;
						if(p->u.assign.right->kind==VADDRESS||p->u.assign.right->kind==TADDRESS)break;
						if(opEqual(noAct,p->u.assign.left))
						{
							InterCode temp=p;
							p=p->pre;
							deleteCode(temp);
							continue;
						}
					}
					else if(p->kind==ADD_K||p->kind==SUB_K||p->kind==MUL_K||p->kind==DIV_K)
					{
						if(opEqual(noAct,p->u.binop.op1)||opEqual(noAct,p->u.binop.op2))
							break;
						if(p->u.binop.result->kind==VADDRESS)break;
						if(p->u.binop.op1->kind==VADDRESS||p->u.binop.op1->kind==TADDRESS)break;
						if(p->u.binop.op2->kind==VADDRESS||p->u.binop.op2->kind==TADDRESS)break;
						if(opEqual(noAct,p->u.binop.result))
						{
							InterCode temp=p;
							p=p->pre;
							deleteCode(temp);
							continue;
						}
					}
					else if(p->kind==READ_K)
					{
						if(p->u.one.op->kind==VADDRESS)break;
						if(opEqual(noAct,p->u.one.op))
						{
							InterCode temp=p;
							p=p->pre;
							deleteCode(temp);
							continue;
						}
					}
					else if(p->kind==WRITE_K||p->kind==ARG_K||p->kind==PARAM_K)
					{
						if(opEqual(noAct,p->u.one.op)||p->u.one.op->kind==VADDRESS||p->u.one.op->kind==TADDRESS)
							break;
					}
					else if(p->kind==RIGHTAT_K)
					{
						if(opEqual(noAct,p->u.assign.right)||p->u.assign.left->kind==VADDRESS)break;
						if(p->u.assign.right->kind==VADDRESS||p->u.assign.right->kind==TADDRESS)break;
						if(opEqual(noAct,p->u.assign.left))
						{
							InterCode temp=p;
							p=p->pre;
							deleteCode(temp);
							continue;
						}
					}
					p=p->pre;
				}
			}
			bottom=bottom->pre;
		}
	}
}

//find constants and　figure them
void lookCon()
{
	InterCode h=code_h;
	while(h!=NULL)
	{
		if(h->kind==ADD_K||h->kind==SUB_K||h->kind==MUL_K||h->kind==DIV_K)
		{
			if(h->u.binop.result->kind==TEMPVAR&&h->u.binop.op1->kind==CONSTANT&&h->u.binop.op2->kind==CONSTANT)
			{
				int c1=atoi(h->u.binop.op1->u.value);
				int c2=atoi(h->u.binop.op2->u.value);
				int r=0;
				switch(h->kind){
					case ADD_K:r=c1+c2;break;
					case SUB_K:r=c1-c2;break;
					case MUL_K:r=c1*c2;break;
					case DIV_K:r=c1/c2;break;
					default:break;
				}
				h->u.binop.result->kind=CONSTANT;
				h->u.binop.result->u.value=malloc(32);
				sprintf(h->u.binop.result->u.value,"%d",r);
				InterCode temp=h;
				h=h->next;
				deleteCode(temp);
				continue;
			}
		}
		h=h->next;
	}
}

void sameRight()
{
	InterCode h=code_h;
	while(h!=NULL)
	{
		if(h->kind==ADD_K||h->kind==SUB_K||h->kind==MUL_K||h->kind==DIV_K)
		{
			if(h->u.binop.result->kind==TEMPVAR)
			{
				Operand r=h->u.binop.result;
				Operand op1=h->u.binop.op1;
				Operand op2=h->u.binop.op2;
				InterCode p=h->next;
				while(p!=NULL&&p->kind!=RETURN_K&&p->kind!=GOTO_K&&p->kind!=IFGOTO_K&&p->kind!=CALL_K&&p->kind!=LABEL_K&&p->kind!=FUNCTION_K)
				{
					if(p->kind==READ_K&&(p->u.one.op->kind==TADDRESS||p->u.one.op->kind==VADDRESS||opEqual(p->u.one.op,op1)||opEqual(p->u.one.op,op2)))break;
					if((p->kind==CALL_K||p->kind==ASSIGN_K||p->kind==RIGHTAT_K)&&(p->u.assign.left->kind==TADDRESS||p->u.assign.left->kind==VADDRESS||opEqual(p->u.assign.left,op1)||opEqual(p->u.assign.left,op2)))break;
					if((p->kind==ADD_K||p->kind==SUB_K||p->kind==MUL_K||p->kind==DIV_K)&&(p->u.binop.result->kind==TADDRESS||p->u.binop.result->kind==VADDRESS||opEqual(p->u.binop.result,op1)||opEqual(p->u.binop.result,op2)))break;
					if(p->kind==h->kind&&p->u.binop.result->kind==TEMPVAR&&opEqual(p->u.binop.op1,op1)&&opEqual(p->u.binop.op2,op2))
					{
						p->u.binop.result->u.var_no=r->u.var_no;
						InterCode temp=p;
						p=p->next;
						deleteCode(temp);
						continue;
					}
					p=p->next;
				}
			}
		}
		h=h->next;
	}
}
