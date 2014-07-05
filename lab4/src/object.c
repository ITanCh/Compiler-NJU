#include "object.h"

/*这部分主要负责目标代码的生成*/
#define REGNUM 26
#define FSIZE 8	

reg_t reg[REGNUM];
int offset;
var_t *funList;
int argCount;

/*变量相关*/
void del_var()
{
	var_t*h=funList;
	while(h!=NULL)
	{
		funList=funList->next;
		free(h);
		h=funList;
	}
}

void add_var(var_t*v)
{
	if(v==NULL)
	{
		printf("add var error!\n");
		exit(1);
	}
	v->next=NULL;
	if(funList==NULL)
		funList=v;
	else
	{
		var_t*h=funList;
		while(h->next!=NULL)
			h=h->next;
		h->next=v;
	}
} 
/*寄存器相关*/
void initReg()
{
	int i;
	offset=0;
	argCount=0;
	funList=NULL;
	for(i=0;i<REGNUM;i++)
	{
		reg[i].var=NULL;
		reg[i].old=0;
	}
	reg[0].name[0]='t';
	reg[0].name[1]='0';
	reg[1].name[0]='t';
	reg[1].name[1]='1';
	reg[2].name[0]='t';
	reg[2].name[1]='2';
	reg[3].name[0]='t';
	reg[3].name[1]='3';
	reg[4].name[0]='t';
	reg[4].name[1]='4';
	reg[5].name[0]='t';
	reg[5].name[1]='5';
	reg[6].name[0]='t';
	reg[6].name[1]='6';
	reg[7].name[0]='t';
	reg[7].name[1]='7';
	reg[8].name[0]='t';
	reg[8].name[1]='8';
	reg[9].name[0]='t';
	reg[9].name[1]='9';

	reg[10].name[0]='s';
	reg[10].name[1]='0';
	reg[11].name[0]='s';
	reg[11].name[1]='1';
	reg[12].name[0]='s';
	reg[12].name[1]='2';
	reg[13].name[0]='s';
	reg[13].name[1]='3';
	reg[14].name[0]='s';
	reg[14].name[1]='4';
	reg[15].name[0]='s';
	reg[15].name[1]='5';
	reg[16].name[0]='s';
	reg[16].name[1]='6';
	reg[17].name[0]='s';
	reg[17].name[1]='7';

	reg[18].name[0]='f';
	reg[18].name[1]='p';

	reg[19].name[0]='s';
	reg[19].name[1]='p';

	reg[20].name[0]='r';
	reg[20].name[1]='a';

	reg[21].name[0]='v';
	reg[21].name[1]='0';

	reg[22].name[0]='a';
	reg[22].name[1]='0';
	reg[23].name[0]='a';
	reg[23].name[1]='1';
	reg[24].name[0]='a';
	reg[24].name[1]='2';
	reg[25].name[0]='a';
	reg[25].name[1]='3';
}

void resetST()
{
	int i;
	for(i=0;i<17;i++)
	{
		reg[i].var=NULL;
		reg[i].old=0;
	}
}

void freeReg(int index)
{
	var_t*h=funList;
	while(h!=NULL)
	{
		if(h->reg==index)
			h->reg=-1;
		h=h->next;
	}
	reg[index].var=NULL;
	reg[index].old=0;
}
//查看变量是否在寄存器中，不在则分配寄存器
int allocReg(Operand op,FILE *fp)
{
	//printf("alloc!!kind:%d\n",op->kind);
	char* name=malloc(32);
	memset(name,0,32);
	var_t *head=funList;
	//printf("op kind%d\n",op->kind);
	if(op->kind==TEMPVAR)
	{
		//printf("");
		name[0]='t';
		//printf("opu.var_no%d\n",op->u.var_no);
		sprintf(name+1,"%d",op->u.var_no);
	}
	else if(op->kind==VARIABLE)
	{
		//printf("opvalue: %s\n",op->u.value);
		strcpy(name,op->u.value);
	}
	while(head!=NULL)
	{
		//printf("head name: %s   name: %s\n",head->name,name);
		if(strcmp(head->name,name)==0)
			break;
		head=head->next;	
	}
	int flag=0;
	if(head==NULL)	//在函数里第一次出现
	{
		head=malloc(sizeof(var_t));
		head->name=name;
		//printf("new name:%s\n",head->name);
		head->reg=-1;
		offset+=4;		//在栈中分配位置
		//fputs("subu $sp, $sp ,4\n",fp);
		head->offset=offset;
		flag=1;			//第一次分配内存
		head->next=NULL;
		add_var(head);
	}
	if(head->reg==-1)		//还未分配寄存器
	{
		int index=findReg(fp);
		head->reg=index;
		reg[index].var=head->name;
		if(head->offset>=0&&!flag)		//在内存中有值
		{
			fputs("subu $v1 ,$fp , ",fp);
			char temp[32];
			memset(temp,0,32);
			sprintf(temp,"%d",head->offset);
			fputs(temp,fp);

			fputs("\nlw ",fp);
			getReg(head->reg,fp);
			fputs(", 0($v1)\n",fp);	//fp偏移量计算
		}
	}
	reg[head->reg].old=0;
	return head->reg;
}
//找到空余寄存器
int findReg(FILE*fp)
{
	int i;
	for(i=0;i<17;i++)
	{
		if(reg[i].var!=NULL)
			reg[i].old++;
	}
	for(i=0;i<17;i++)
	{
		if(reg[i].var==NULL)
			return i;
	}
	int max=0;
	int old=0;
	for(i=0;i<17;i++)
	{
		if(reg[i].old>old)
		{
			old=reg[i].old;
			max=i;
		}
	}
	//fputs("sw ",fp);
	//getReg(max,fp);
	//fputs(", 0($sp)\n",fp);
	//offset+=4;
	var_t*h=funList;
	while(h!=NULL)
	{
		//printf("reg max:%s\n",reg[max].var);
		//printf("f name:%s\n",h->name);
		if(strcmp(reg[max].var,h->name)==0)
			break;
		h=h->next;
	}
	if(h!=NULL)
	{
		fputs("subu $v1, $fp , ",fp);
		char temp[32];
		memset(temp,0,32);
		sprintf(temp,"%d",h->offset);
		fputs(temp,fp);

		fputs("\nsw ",fp);
		getReg(max,fp);
		fputs(", 0($v1)\n",fp);	//fp偏移量计算
		h->reg=-1;
	}
	reg[max].var=NULL;
	reg[max].old=0;
	return max;
}
//打印寄存器
void getReg(int index,FILE*fp)
{
	fputs("$",fp);
	fputs(reg[index].name,fp);
}

/*打印所有汇编代码*/
void printAllCode(char* fname)
{
	FILE *fp=fopen(fname,"w");
	if(fp==NULL) 
	{
		printf("open file error\n");
		return;
	}
	fputs(".data\n_prompt: .asciiz \"Enter an integer:\"\n",fp);
	fputs("_ret: .asciiz \"\\n\"\n.globl main\n.text\n",fp);

	fputs("\nread:\n",fp);
	fputs("subu $sp, $sp, 4\n",fp); 
	fputs("sw $ra, 0($sp)\n",fp);
	fputs("subu $sp, $sp, 4\n",fp);
	fputs("sw $fp, 0($sp)\n",fp);
	fputs("addi $fp, $sp, 8\n",fp);

	fputs("li $v0, 4\nla $a0, _prompt\n",fp);
	fputs("syscall\nli $v0, 5\nsyscall\n",fp);
	fputs("subu $sp, $fp, 8\n",fp);
	fputs("lw $fp, 0($sp)\n",fp);
	fputs("addi $sp, $sp, 4\n",fp);
	fputs("lw $ra, 0($sp)\n",fp);
	fputs("addi $sp, $sp, 4\n",fp);

	fputs("jr $ra\n",fp);

	fputs("\nwrite:\n",fp);
	fputs("subu $sp, $sp, 4\n",fp); 
	fputs("sw $ra, 0($sp)\n",fp);
	fputs("subu $sp, $sp, 4\n",fp);
	fputs("sw $fp, 0($sp)\n",fp);
	fputs("addi $fp, $sp, 8\n",fp);
	fputs("li $v0, 1\nsyscall\nli $v0, 4\n",fp);
	fputs("la $a0, _ret\nsyscall\nmove $v0, $0\n",fp);
	fputs("subu $sp, $fp, 8\n",fp);
	fputs("lw $fp, 0($sp)\n",fp);
	fputs("addi $sp, $sp, 4\n",fp);
	fputs("lw $ra, 0($sp)\n",fp);
	fputs("addi $sp, $sp, 4\n",fp);

	fputs("jr $ra\n",fp);
	InterCode c=code_h;
	while(c!=NULL)
	{
		printObjCode(c,fp);
		c=c->next;
		//fflush(fp);
	}
}

int countVar(InterCode c)
{
	c=c->next;
	int count=0;
	while(c!=NULL&&c->kind!=FUNCTION_K)
	{
		count++;
		c=c->next;
	}
	//printf("count var:%d\n",count*2*4);
	return count*3;
}

void printObjCode(InterCode c,FILE* fp)
{
	int kind=c->kind;
	//printf("kind:%d\n",kind);
	int r1,r2,r3;
	int i;
	int memCount=0;
	char temp[32];
	Operand left,right,result,op1,op2,label;
	InterCode cp;
	var_t *h;
	switch(kind)
	{
		case LABEL_K:	//语句块的开始
						//将寄存器刷回内存,空出寄存器
			h=funList;		
			while(h!=NULL)
			{
				if(h->reg>=0)
				{
					fputs("subu  $v1 ,$fp , ",fp);
					char temp[32];
					memset(temp,0,32);
					sprintf(temp,"%d",h->offset);
					fputs(temp,fp);

					fputs("\nsw ",fp);
					getReg(h->reg,fp);
					fputs(", 0($v1)\n",fp);	//fp偏移量计算
					reg[h->reg].var=NULL;
					reg[h->reg].old=0;
					h->reg=-1;
				}
				h=h->next;
			}
			printOp(c->u.one.op,fp);
			fputs(":\n",fp);
			break;
		case ASSIGN_K:
			left=c->u.assign.left;
			right=c->u.assign.right;
			if(left->kind==TEMPVAR||left->kind==VARIABLE)
			{
				switch(right->kind)
				{
					case CONSTANT:
						r1=allocReg(left,fp);
						fputs("li ",fp);
						getReg(r1,fp);
						fputs(" ",fp);
						fputs(right->u.value,fp);
						break; 
					case VARIABLE:
					case TEMPVAR:
						r1=allocReg(left,fp);
						r2=allocReg(right,fp);
						fputs("move ",fp);
						getReg(r1,fp);
						fputs(" ,",fp);
						getReg(r2,fp);
						break;
					case VADDRESS:
					case TADDRESS: 
						//printf("!!!left kind%d\n",left->kind);
						//printf("!!!right kind%d\n",right->u.name->kind);
						r1=allocReg(left,fp); 
						r2=allocReg(right->u.name,fp);
						fputs("lw ",fp);
						getReg(r1,fp);
						fputs(",0(",fp);
						getReg(r2,fp);
						fputs(")",fp);
						break;
					default:break;
				}
			}
			else if(left->kind==VADDRESS||left->kind==TADDRESS)
			{
				switch(right->kind)
				{
					case TEMPVAR:
					case VARIABLE:
						r1=allocReg(right,fp);
						r2=allocReg(left->u.name,fp);
						fputs("sw ",fp);
						getReg(r1,fp);
						fputs(",0(",fp);
						getReg(r2,fp);
						fputs(")",fp);
						break;
					case CONSTANT:
						op1=assCode(right,fp);
						r1=allocReg(op1,fp);
						r2=allocReg(left->u.name,fp);
						fputs("sw ",fp);
						getReg(r1,fp);
						fputs(",0(",fp);
						getReg(r2,fp);
						fputs(")",fp);
						//freeReg(r1);	//op所占的reg可以立即释放
						break;
					default:break;
				}
			}
			break;

		case ADD_K:
		case SUB_K:
		case MUL_K:
		case DIV_K:
			result=c->u.binop.result,op1=c->u.binop.op1,op2=c->u.binop.op2;
			switch(result->kind){
				case TEMPVAR:
				case VARIABLE:
					if((op1->kind==TEMPVAR||op1->kind==VARIABLE)&&(op2->kind==TEMPVAR||op2->kind==VARIABLE))
					{
						r1=allocReg(result,fp);
						r2=allocReg(op1,fp);
						r3=allocReg(op2,fp);
						if(kind==ADD_K)
							fputs("add ",fp);
						else if(kind==SUB_K) fputs("sub ",fp);
						else if(kind==MUL_K)
							fputs("mul ",fp);
						else if(kind==DIV_K)
							fputs("div ",fp);
						getReg(r1,fp);
						fputs(", ",fp);
						getReg(r2,fp);
						fputs(", ",fp);
						getReg(r3,fp);
					}
					else if((op1->kind==TEMPVAR||op1->kind==VARIABLE)&&(op2->kind==CONSTANT))
					{
						if(kind==ADD_K||kind==SUB_K)
						{
							r1=allocReg(result,fp);
							r2=allocReg(op1,fp);
							fputs("addi ",fp);
							getReg(r1,fp);
							fputs(", ",fp);
							getReg(r2,fp);
							fputs(", ",fp); 
							if(kind==SUB_K)
								fputs("-",fp);
							fputs(op2->u.value,fp);
						}
						else if(kind==MUL_K) {
							Operand t1=assCode(op2,fp);	
							r1=allocReg(t1,fp);
							r2=allocReg(result,fp);
							r3=allocReg(op1,fp);
							fputs("mul ",fp);
							getReg(r2,fp);
							fputs(", ",fp);
							getReg(r3,fp);
							fputs(", ",fp); 
							getReg(r1,fp);
						}
						else if(kind==DIV_K)
						{
							Operand t1=assCode(op2,fp);
							r1=allocReg(op1,fp);
							r2=allocReg(t1,fp);
							r3=allocReg(result,fp);
							fputs("div ",fp);
							getReg(r1,fp);
							fputs(", ",fp);
							getReg(r2,fp);
							fputs("\n",fp);
							fputs("mflo ",fp); 
							getReg(r3,fp);
						}
					}
					else if((op2->kind==TEMPVAR||op2->kind==VARIABLE)&&(op1->kind==CONSTANT))
					{
						if(kind==ADD_K)
						{
							r1=allocReg(result,fp);
							r2=allocReg(op2,fp);
							fputs("addi ",fp);
							getReg(r1,fp);
							fputs(", ",fp);
							getReg(r2,fp);
							fputs(", ",fp); 
							fputs(op1->u.value,fp);
						}
						else if(kind==SUB_K)
						{
							Operand t1=assCode(op1,fp);
							r1=allocReg(result,fp);
							r2=allocReg(t1,fp);
							r3=allocReg(op2,fp);
							fputs("sub ",fp);
							getReg(r1,fp);
							fputs(", ",fp);
							getReg(r2,fp);
							fputs(", ",fp);
							getReg(r3,fp);
						}
						else if(kind==MUL_K)
						{
							Operand t1=assCode(op1,fp);	
							r1=allocReg(result,fp);
							r2=allocReg(t1,fp);
							r3=allocReg(op2,fp);
							fputs("mul ",fp);
							getReg(r1,fp);
							fputs(", ",fp);
							getReg(r2,fp);
							fputs(", ",fp); 
							getReg(r3,fp);
						}
						else if(kind==DIV_K)
						{
							Operand t1=assCode(op1,fp);	
							r1=allocReg(t1,fp);
							r2=allocReg(op2,fp);
							r3=allocReg(result,fp);
							fputs("div ",fp);
							getReg(r1,fp);
							fputs(", ",fp);
							getReg(r2,fp);
							fputs("\n",fp);
							fputs("mflo ",fp); 
							getReg(r3,fp);
						}
					}
					else if((op1->kind==VADDRESS||op1->kind==TADDRESS)&&(op2->kind==TEMPVAR||op2->kind==VARIABLE))
					{
						Operand t1=assCode(op1,fp);
						InterCode c1=malloc(sizeof(struct InterCode_));
						c1->kind=kind;
						c1->u.binop.result=result;
						c1->u.binop.op1=t1;
						c1->u.binop.op2=op2;
						printObjCode(c1,fp);
					}
					else if((op2->kind==VADDRESS||op2->kind==TADDRESS)&&(op1->kind==TEMPVAR||op1->kind==VARIABLE))
					{
						Operand t1=assCode(op2,fp);
						InterCode c1=malloc(sizeof(struct InterCode_));
						c1->kind=kind;
						c1->u.binop.result=result;
						c1->u.binop.op1=op1;
						c1->u.binop.op2=t1;
						printObjCode(c1,fp);
					}
					else if((op2->kind!=VARIABLE&&op2->kind!=TEMPVAR)&&(op1->kind!=TEMPVAR&&op1->kind!=VARIABLE))
					{
						Operand t1=assCode(op1,fp);
						Operand t2=assCode(op2,fp);
						InterCode c1=malloc(sizeof(struct InterCode_));
						c1->kind=kind;
						c1->u.binop.result=result;
						c1->u.binop.op1=t1;
						c1->u.binop.op2=t2;
						printObjCode(c1,fp);
					}
					break;
				case TADDRESS:
				case VADDRESS:
					left=malloc(sizeof(struct Operand_));
					left->kind=TEMPVAR;
					left->u.var_no=varCount++;
					cp=malloc(sizeof(struct InterCode_));
					cp->kind=kind;
					cp->u.binop.result=left;
					cp->u.binop.op1=op1;
					cp->u.binop.op2=op2;
					printObjCode(cp,fp);

					cp->kind=ASSIGN_K;
					cp->u.assign.left=result;
					cp->u.assign.right=left;
					printObjCode(cp,fp);
					break;
				default:break;
			}
			break;
		case GOTO_K:	//语句块的结束
			h=funList;		
			while(h!=NULL)
			{
				if(h->reg>=0)
				{
					fputs("subu  $v1 ,$fp , ",fp);
					char temp[32];
					memset(temp,0,32);
					sprintf(temp,"%d",h->offset);
					fputs(temp,fp);

					fputs("\nsw ",fp);
					getReg(h->reg,fp);
					fputs(", 0($v1)\n",fp);	//fp偏移量计算
					reg[h->reg].var=NULL;
					reg[h->reg].old=0;
					h->reg=-1;
				}
				h=h->next;
			}
			fputs("j ",fp);
			printOp(c->u.one.op,fp);
			break;
		case IFGOTO_K:	//语句块的结束
			op1=c->u.triop.t1;
			op2=c->u.triop.t2;
			label=c->u.triop.label;
			char * op=c->u.triop.op;
			if(op1->kind!=TEMPVAR&&op1->kind!=VARIABLE)
				op1=assCode(op1,fp);
			if(op2->kind!=TEMPVAR&&op2->kind!=VARIABLE)
				op2=assCode(op2,fp);
			r1=allocReg(op1,fp);
			r2=allocReg(op2,fp);

			h=funList;		
			while(h!=NULL)
			{
				if(h->reg>=0)
				{
					fputs("subu  $v1 ,$fp , ",fp);
					char temp[32];
					memset(temp,0,32);
					sprintf(temp,"%d",h->offset);
					fputs(temp,fp);

					fputs("\nsw ",fp);
					getReg(h->reg,fp);
					fputs(", 0($v1)\n",fp);	//fp偏移量计算
				}
				h=h->next;
			}
			if(strcmp(op,"==")==0)
				fputs("beq ",fp);
			else if(strcmp(op,"!=")==0)
				fputs("bne ",fp);
			else if(strcmp(op,">")==0)
				fputs("bgt ",fp);
			else if(strcmp(op,"<")==0)
				fputs("blt ",fp);
			else if(strcmp(op,">=")==0)
				fputs("bge ",fp);
			else if(strcmp(op,"<=")==0)
				fputs("ble ",fp);
			getReg(r1,fp);
			fputs(", ",fp);
			getReg(r2,fp);
			fputs(", ",fp);
			printOp(label,fp);
			break;
		case ARG_K:
			argCount++;
			if(c->u.one.op->kind!=VARIABLE&&c->u.one.op->kind!=TEMPVAR)
			{
				op1=assCode(c->u.one.op,fp);
				//printf("op1 kind%d\n",op1->kind);
				c->u.one.op=op1;
			}
			else
				allocReg(c->u.one.op,fp);   //主要为了分配内存空间
			break;
		case READ_K:		
			fputs("jal read\n",fp);
			r1=allocReg(c->u.one.op,fp);
			fputs("move ",fp);
			getReg(r1,fp);
			fputs(", $v0",fp);
			break;
		case WRITE_K:
			if(c->u.one.op->kind!=VARIABLE&&c->u.one.op->kind!=TEMPVAR)
			{
				op1=assCode(c->u.one.op,fp);
				r1=allocReg(op1,fp);
			}
			else r1=allocReg(c->u.one.op,fp);
			fputs("move ",fp);
			fputs("$a0, ",fp);
			getReg(r1,fp);
			fputs("\njal write",fp);
			break;
		case CALL_K:
			h=funList;		
			//存储所有寄存器中的局域变量
			while(h!=NULL)
			{
				if(h->reg>=0)
				{
					fputs("subu $v1 ,$fp , ",fp);
					char temp[32];
					memset(temp,0,32);
					sprintf(temp,"%d",h->offset);
					fputs(temp,fp);

					fputs("\nsw ",fp);
					getReg(h->reg,fp);
					fputs(", 0($v1)\n",fp);	//fp偏移量计算

					/*//printf("local var:%s\n",h->name);
					fputs("subu $sp, $sp, 4\n",fp);
					fputs("sw ",fp);
					getReg(h->reg,fp);
					fputs(", 0($sp)\n",fp);
					offset+=4;
					h->offset=offset;*/
				}
				h=h->next;
			}

			cp=c;
			//将参数压站
			for(i=0;i<4&&i<argCount;i++)
			{
				cp=cp->pre;
				if(cp->kind!=ARG_K)continue;
				//printf("op ");
				if(cp->u.one.op->kind!=VARIABLE&&cp->u.one.op->kind!=TEMPVAR)
				{
					//	printf("op1 kind%d\n",op1->kind);
					printf("error arg\n");
				}
				else
					r1=allocReg(cp->u.one.op,fp);
				if(i==0)
					fputs("move $a0, ",fp);
				else if(i==1)
					fputs("move $a1, ",fp);
				else if(i==2)
					fputs("move $a2, ",fp);
				else if(i==3)
					fputs("move $a3, ",fp);
				getReg(r1,fp);
				fputs("\n",fp);
			}
			i=0;
			if(argCount-4>0)
			{
				i=argCount-4;
				i=i*4;
				fputs("subu $sp, $sp, ",fp);
				memset(temp,0,32);
				sprintf(temp,"%d",i);
				fputs(temp,fp);
				fputs("\n",fp);
				argCount=argCount-4;
				i=0;
				while(argCount>0)
				{
					cp=cp->pre;
					memset(temp,0,32);
					sprintf(temp,"%d",i*4);
					if(cp->u.one.op->kind!=VARIABLE&&cp->u.one.op->kind!=TEMPVAR)
					{
						//	op1=assCode(cp->u.one.op,fp);
						//r1=allocReg(op1,fp);
						printf("error arg\n");
					}
					else
						r1=allocReg(cp->u.one.op,fp);
					fputs("sw ",fp);
					getReg(r1,fp);
					fputs(", ",fp);
					fputs(temp,fp);
					fputs("($sp)\n",fp);
					i++;
					argCount--;
				}
			}
			//让出寄存器
			h=funList;
			while(h!=NULL)
			{
				if(h->reg>=0)
				{
					reg[h->reg].var=NULL;
					reg[h->reg].old=0;
					h->reg=-1;
				}
				h=h->next;
			}

			argCount=0;
			fputs("jal ",fp);
			printOp(c->u.assign.right,fp);
			fputs("\n",fp);
			fputs("addi $sp, $sp, ",fp);
			memset(temp,0,32);
			sprintf(temp,"%d",i*4);
			fputs(temp,fp);
			fputs("\n",fp);
			if(c->u.assign.left!=NULL)
			{
				r1=allocReg(c->u.assign.left,fp);
				fputs("move ",fp);
				getReg(r1,fp);
				fputs(", $v0",fp);
			}
			break;
		case RETURN_K:
			if(c->u.one.op->kind!=VARIABLE&&c->u.one.op->kind!=TEMPVAR)
			{
				op1=assCode(c->u.one.op,fp);
				r1=allocReg(op1,fp);
			}
			else
				r1=allocReg(c->u.one.op,fp);
			fputs("subu $sp, $fp, 8\n",fp);
			fputs("lw $fp, 0($sp)\n",fp);
			fputs("addi $sp, $sp, 4\n",fp);
			fputs("lw $ra, 0($sp)\n",fp);
			fputs("addi $sp, $sp, 4\n",fp);
			fputs("move $v0,",fp);
			getReg(r1,fp);
			fputs("\n",fp);
			fputs("jr $ra",fp);
			break;
		case PARAM_K:
			break;
		case FUNCTION_K:
			fputs("\n",fp);
			printOp(c->u.one.op,fp);
			fputs(":\n",fp);
			del_var();		//刷新局域变量
			resetST();		//重置某些寄存器结构的标
			//printf("fsize:%d\n",offset);
			offset=FSIZE;
			fputs("subu $sp, $sp, 4\n",fp); 
			fputs("sw $ra, 0($sp)\n",fp);
			fputs("subu $sp, $sp, 4\n",fp);
			fputs("sw $fp, 0($sp)\n",fp);
			fputs("addi $fp, $sp, 8\n",fp);
			memCount=countVar(c);			//预分配内存空间
			fputs("subu $sp,$sp,",fp);
			sprintf(temp,"%d",memCount*4);
			fputs(temp,fp);
			fputs("\n",fp);
			cp=c->next;
			if(cp==NULL)return;
			i=0;
			while(cp->kind==PARAM_K&&i<4)
			{
				r1=allocReg(cp->u.one.op,fp);
				fputs("\nmove ",fp);
				getReg(r1,fp);
				fputs(", ",fp);
				if(i==0)
					fputs("$a0",fp);
				else if(i==1)
					fputs("$a1",fp);
				else if(i==2)
					fputs("$a2",fp);
				else if(i==3)
					fputs("$a3",fp);
				i++;
				cp=cp->next;
				fputs("\n",fp);
			}
			i=0;
			while(cp->kind==PARAM_K)
			{
				r1=allocReg(cp->u.one.op,fp);
				fputs("\nlw ",fp);
				getReg(r1,fp);
				fputs(", ",fp);
				memset(temp,0,32);
				sprintf(temp,"%d",i*4);
				i++;
				fputs(temp,fp);
				fputs("($fp)",fp);
				cp=cp->next;
			}
			break;
		case DEC_K:
			break;
		case RIGHTAT_K:
			cp=c->pre;
			r1=allocReg(c->u.assign.left,fp);
			if(cp->kind!=DEC_K)
				printf("DEC_K MISS\n");
			sprintf(temp,"%d",cp->u.dec.size);
			fputs("subu $sp, $sp, ",fp);
			fputs(temp,fp);
			fputs("\n",fp);
			offset+=cp->u.dec.size;
			fputs("move ",fp);
			getReg(r1,fp);
			fputs(", $sp",fp);
			break;
		default:printf("miss kind%d\n",kind);
	}
	fputs("\n",fp);
		//fflush(fp);
}

//立即,地址数修改
Operand assCode(Operand con,FILE* fp)
{
	Operand op=malloc(sizeof(struct Operand_));
	op->kind=TEMPVAR;
	op->u.var_no=varCount++;
	InterCode code=malloc(sizeof(struct InterCode_));
	code->kind=ASSIGN_K;
	code->u.assign.left=op;
	code->u.assign.right=con;
	printObjCode(code,fp);
	return op;
}
