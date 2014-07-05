%{
	#include"node.h"
	#include"la.tab.h"
	int errorFlag=1;
%}

delim [ \t]
ws {delim}+
digit [0-9]
digit_ [1-9]
letter_ [A-Za-z_]
integer ({digit_}{digit}*)|0
sfloat (({digit}+\.{digit}*)|({digit}*\.{digit}+))[Ee][+-]?{digit}+
float {sfloat}|((({digit_}{digit}*)|0)\.{digit}+)
id {letter_}({letter_}|{digit})*
%option yylineno

%%
{ws} 		{/*space*/}
{integer} 	{yylval.node=initNode("INT",yytext);return INT;}
{float} 	{/*printf("float:%s\n",yytext)*/yylval.node=initNode("FLOAT",yytext);return FLOAT;}
";" 		{yylval.node=initNode("SEMI",yytext);return SEMI;}
"," 		{yylval.node=initNode("COMMA",yytext);return COMMA;}
"=" 		{yylval.node=initNode("ASSIGNOP",yytext);return ASSIGNOP;}
">" 		{yylval.node=initNode("RELOP",yytext);return RELOP;}
"<" 		{yylval.node=initNode("RELOP",yytext);return RELOP;}
">=" 		{yylval.node=initNode("RELOP",yytext);return RELOP;}
"<=" 		{yylval.node=initNode("RELOP",yytext);return RELOP;}
"==" 		{yylval.node=initNode("RELOP",yytext);return RELOP;}
"!=" 		{yylval.node=initNode("RELOP",yytext);return RELOP;}
"+" 		{yylval.node=initNode("PLUS",yytext);return PLUS;}
"-" 		{yylval.node=initNode("MINUS",yytext);return MINUS;}
"*" 		{yylval.node=initNode("STAR",yytext);return STAR;}
"/" 		{yylval.node=initNode("DIV",yytext);return DIV;}
"&&" 		{yylval.node=initNode("AND",yytext);return AND;}
"||" 		{yylval.node=initNode("OR",yytext);return OR;}
"." 		{yylval.node=initNode("DOT",yytext);return DOT;}
"!" 		{yylval.node=initNode("NOT",yytext);return NOT;}
int|float 	{yylval.node=initNode("TYPE",yytext);return TYPE;}
"(" 		{yylval.node=initNode("LP",yytext);return LP;}
")" 		{yylval.node=initNode("RP",yytext);return RP;}
"[" 		{yylval.node=initNode("LB",yytext);return LB;}
"]" 		{yylval.node=initNode("RB",yytext);return RB;}
"{" 		{yylval.node=initNode("LC",yytext);return LC;}
"}" 		{yylval.node=initNode("RC",yytext);return RC;}
struct 		{yylval.node=initNode("STRUCT",yytext);return STRUCT;}
return 		{yylval.node=initNode("RETURN",yytext);return RETURN;}
if			{yylval.node=initNode("IF",yytext);return IF;}
else 		{yylval.node=initNode("ELSE",yytext);return ELSE;}
while 		{yylval.node=initNode("WHILE",yytext);return WHILE;}	
\n			{/*line end*/}
{id} 		{yylval.node=initNode("ID",yytext);return ID;}
.			{errorFlag=0;printf("Error type A at line %d: Mysterious character '%s'\n",yylineno,yytext);}
%%

int yywrap(){
   return 1;
}
