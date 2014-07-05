%{
	#include"node.h"
	#include"lex.yy.c"
	#include"table.h"
	#include"object.h"
	Node* root;
%}

/*types*/
%union {
	int type_int;              /* Constant integer value */
	float type_float;               /* Constant floating point value */
	char *type_str;              /* Ptr to constant string (strings are malloc'd) */
	Node* node;
    };

/*tokens*/
%token <node> INT FLOAT ID TYPE
%token <node> SEMI COMMA 
%token <node> LC RC
%token <node> IF 

%right <node> ASSIGNOP  
%left <node> OR 
%left <node> AND 
%left <node> RELOP
%left <node> PLUS MINUS 
%left <node> STAR DIV
%right <node> NOT
%left <node> LB RB LP RP
%left <node> DOT
%nonassoc <node> LOWER_THAN_ELSE 
%nonassoc <node> ELSE
%nonassoc <node> STRUCT RETURN WHILE

/*non-terminal*/
%type <node> Program ExtDefList ExtDef ExtDecList Specifier
%type <node> StructSpecifier OptTag Tag VarDec FunDec VarList
%type <node> ParamDec CompSt StmtList Stmt DefList Def DecList
%type <node> Dec Exp Args

%%

/*High-Level Definitions*/
Program	: 	ExtDefList	{$$=initNode("Program","");addChild($$,$1);root=$$;}
	;
ExtDefList	:	ExtDef ExtDefList	{$$=initNode("ExtDefList","");addChild($$,$2);addChild($$,$1);}
	   	|	/*empty*/		{$$=initNode("ExtDefList","");}	
		;
ExtDef	:	Specifier ExtDecList SEMI 	{$$=initNode("ExtDef","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}	
      	|	Specifier SEMI			{$$=initNode("ExtDef","");addChild($$,$2);addChild($$,$1);}
		|	Specifier FunDec SEMI	{$$=initNode("ExtDef","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
		|	Specifier FunDec CompSt		{$$=initNode("ExtDef","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	| 	error SEMI			{errorFlag=0;/*printf("%sExtDef:error SEMI\n",$$->value);i*/}
	;
ExtDecList	:	VarDec			{$$=initNode("ExtDecList","");addChild($$,$1);}
	   	|	VarDec COMMA ExtDecList	{$$=initNode("ExtDecList","");addChild($$,$3);addChild($$,$2);addChild($$,$1);} 
		;

/*Specifiers*/
Specifier	:	TYPE			{$$=initNode("Specifier","");addChild($$,$1);}
	  	|	StructSpecifier		{$$=initNode("Specifier","");addChild($$,$1);}
		;
StructSpecifier	:	STRUCT OptTag LC DefList RC {$$=initNode("StructSpecifier","");addChild($$,$5);addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}	
		|	STRUCT Tag		{$$=initNode("StructSpecifier","");addChild($$,$2);addChild($$,$1);}
		;
OptTag	:	ID	{$$=initNode("OptTag","");addChild($$,$1);}
       	|	/*empty*/{$$=initNode("OptTag","");}
	;
Tag	:	ID	{$$=initNode("Tag","");addChild($$,$1);}
    	;
/*Declarators*/
VarDec	:	ID	{$$=initNode("VarDec","");addChild($$,$1);}
       	| 	VarDec LB INT RB	 {$$=initNode("VarDec","");addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	;
FunDec	: 	ID LP VarList RP	 {$$=initNode("FunDec","");addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
       	|	ID LP RP		 {$$=initNode("FunDec","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	error RP		{errorFlag=0;/*printf("%sFunDec\n",$$->value);*/}
	;
VarList	:	ParamDec COMMA VarList	{$$=initNode("VarList","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	ParamDec		{$$=initNode("VarList","");addChild($$,$1);}
	;
ParamDec	:	Specifier VarDec	{$$=initNode("ParamDec","");addChild($$,$2);addChild($$,$1);}
		/*|	error COMMA	{errorFlag=0;/*printf("%sParamDec COMMA\n",$$->value);/}*/
		/*|	error RP	{errorFlag=0;/*printf("%sParamDec RB\n",$$->value);/}*/
		;
/*Statements*/	
CompSt	:	LC DefList StmtList RC		{$$=initNode("CompSt","");addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	| error RC	{errorFlag=0;/*printf("%sCompSt RC\n",$$->value);*/}
	;
StmtList	:	Stmt StmtList		{$$=initNode("StmtList","");addChild($$,$2);addChild($$,$1);}
	 	|	/*empty*/		{$$=initNode("StmtList","");}
		;		
Stmt	:	Exp SEMI		{$$=initNode("Stmt","");addChild($$,$2);addChild($$,$1);}
     	|	CompSt			{$$=initNode("Stmt","");addChild($$,$1);}
	|	RETURN Exp SEMI		{$$=initNode("Stmt","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	IF LP Exp RP Stmt	%prec LOWER_THAN_ELSE {$$=initNode("Stmt","");addChild($$,$5);addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	IF LP Exp RP Stmt ELSE Stmt	{$$=initNode("Stmt","");addChild($$,$7);addChild($$,$6);addChild($$,$5);addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	WHILE LP Exp RP Stmt	{$$=initNode("Stmt","");addChild($$,$5);addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	error RP		{errorFlag=0;}
	| 	error SEMI		{errorFlag=0;/*printf("%sStmt SEMI\n",$$->value);*/}
	;
/*Local Definitions*/
DefList	:	Def DefList		{$$=initNode("DefList","");addChild($$,$2);addChild($$,$1);}
	|	/*empty*/		{$$=initNode("DefList","");}	
	/*|	error SEMI		{errorFlag=0;/*printf("%sDef\n",$$->value);}*/
	;
Def	:	Specifier DecList SEMI	{$$=initNode("Def","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
    /*	error SEMI		{errorFlag=0;/*printf("%sDef\n",$$->value);*/
   	;
DecList	:	Dec			{$$=initNode("DecList","");addChild($$,$1);}
	|	Dec COMMA DecList	{$$=initNode("DecList","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	;
Dec	:	VarDec			{$$=initNode("Dec","");addChild($$,$1);}
    	|	VarDec ASSIGNOP Exp	{$$=initNode("Dec","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	;
/*Expressions*/
Exp 	:	Exp ASSIGNOP Exp	{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
     	|	Exp AND Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	| 	Exp OR Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp RELOP Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp PLUS Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp MINUS Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp STAR Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp DIV Exp		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	| 	LP Exp RP		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	MINUS Exp		{$$=initNode("Exp","");addChild($$,$2);addChild($$,$1);}
	|	NOT Exp			{$$=initNode("Exp","");addChild($$,$2);addChild($$,$1);}
	|	ID LP Args RP		{$$=initNode("Exp","");addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	ID LP RP		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp LB Exp RB		{$$=initNode("Exp","");addChild($$,$4);addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	Exp DOT ID		{$$=initNode("Exp","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
	|	ID			{$$=initNode("Exp","");addChild($$,$1);}	
	|	INT			{$$=initNode("Exp","");addChild($$,$1);}
	|	FLOAT			{$$=initNode("Exp","");addChild($$,$1);}
/*	|	error RP		{errorFlag=0;printf("%sExp RP\n",$$->value);}
/*	|	error RB		{errorFlag=0;printf("%sExp RB\n",$$->value);}
	|	error SEMI		{errorFlag=0;printf("%sExp SIME\n",$$->value);}*/
	;
Args	:	Exp COMMA Args		{$$=initNode("Args","");addChild($$,$3);addChild($$,$2);addChild($$,$1);}
     	|	Exp			{$$=initNode("Args","");addChild($$,$1);}
	;

%%

int main(int argc, char** argv)
{
 	if (argc <= 1) return -1;
	FILE* f = fopen(argv[1],"r");
	if (!f)
	{
		perror(argv[1]);
		return 1;
	}	
	root=NULL;
	yylineno=1;
	yyrestart(f);
	yyparse();
	if(errorFlag){
		//printTree(root,0);	
		initTable();
		Program(root);
		//optimize inter code
		optIF();	//label
		rmLabel();

		lookCon();		//temp
		rddCode();		//variable

		sameRight();
		if(argc<=2)	return 1;
		//printCode("out.ir");
		initReg();
		printAllCode(argv[2]);
	}
	return 0;
}

int yyerror(char* msg)
{
	printf("Error type B at line %d:%s===>unexpected near '%s'\n",yylineno,msg,yylval.node->value);
}
