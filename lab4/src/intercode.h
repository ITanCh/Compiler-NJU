#ifndef _INTERCODE_H
#define _INTERCODE_H
#include"stdlib.h"
#include"stdio.h"
#include"string.h"

#define TEMPVAR  0
#define VARIABLE 1
#define CONSTANT 2
#define VADDRESS  3
#define LABEL    4
#define FUNCTION 5 
#define TADDRESS 6 

#define ASSIGN_K 0
#define ADD_K 1
#define SUB_K 2
#define MUL_K 3
#define DIV_K 4
#define RETURN_K 5
#define LABEL_K  6
#define GOTO_K   7
#define IFGOTO_K 8
#define READ_K	9
#define WRITE_K 10
#define CALL_K	11
#define ARG_K	12
#define FUNCTION_K 13
#define PARAM_K	14
#define DEC_K 15
#define RIGHTAT_K  16 

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;
typedef struct Label_No_* Label_No;

//intermediate code struct
struct Operand_
{
	enum {
		tempvar,variable,cons,vaddress,label,
		function,taddress
	}kind;

	union{
		int var_no;		//tempvar,label,
		char* value;	//constant
		Operand name;   //vaddress,taddress
	}u;
	Operand next;		//arg use it
};

struct InterCode_
{
	enum{
		assign_k,add_k,sub_k,mul_k,div_k,return_k,label_k,goto_k,
		ifgoto_k,read_k,write_k,call_k,arg_k,function_k,param_k,dec_k,
		rightat_k
	}kind;

	union{
		struct{			//return ,label,goto,read,write,arg, function
			Operand op;		//param
		}one;
		struct{
			Operand left,right;	//call 
		}assign;	//assign	rightat

		struct{
			Operand result,op1,op2;	
		}binop;			//add sub mul div 

		struct{
			Operand t1;
			char *op;
			Operand t2,label;
		}triop;			//if_goto

		struct{
			Operand op;
			int size;
		}dec; //dec
	}u;

	InterCode pre,next;
};

struct Label_No_
{
	int no;
	Label_No next;
};

/*code node functions*/
void insertCode(InterCode c);
void deleteCode(InterCode c);
void printCode(char *fname);
void printOp(Operand op,FILE *fp);

extern InterCode code_h,code_t;
extern int varCount;
extern int labCount;

/*optimize code*/
void optIF();
void rmLabel();
int opEqual(Operand op1,Operand op2);
void rddCode();
void sameRight();
void lookCon();

#endif
