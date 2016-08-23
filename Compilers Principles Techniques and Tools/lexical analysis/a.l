%{
//
//  词法分析.l
//  LEX
//  Created by 吴浩男 on 15/10/31.
//  Copyright © 2015年 吴浩男. All rights reserved.
//  Mr.Phoebe的专栏 http://blog.csdn.net/u013007900

#include <stdio.h>
int linenum = 1, wordnum = 0, charnum = 0, colunum = 0, id = 1;

%}

delim	[" "|\t]
whitespace	{delim}*
letter	[A-Z|a-z|_]
dight	[0-9]
id  	({letter})({letter}|{dight})*
num 	{dight}*(\.{dight}*)?(E[+\-]?{dight}*)?
comment	(\/\*(.)*\*\/)|("//"[^\n]*)
note 	\"(\\.|[^\\"])*\"
%%

{whitespace} {/*do nothing*/}

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"inc lude"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto "|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"size of"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"v oid"|"volatile"|"while"	{printf("(%s\t C_UDID)\n", yytext);charnum+=yyleng;wordnum++;}


{id}		{printf("(%s\t %d)\n", yytext,id);charnum+=yyleng;wordnum++;id++;}

{num}		{printf("(%s\t num)\n",yytext);charnum+=yyleng;}

{comment}	{printf("comment: %s\n",yytext);charnum+=yyleng;}

{note}		{printf("note %s\n",yytext);charnum+=yyleng;}

">>="|"<<="|"+="|"-="|"*="|"/="|"%="|"&="|"^="|"|="|">>"|"<<"|"++"|"--"|"&&"|"||"|"<="|">="|"=="|"!="|";"|"{"|"}" |":"|"="|"("|")"|"["|"]"|"."|"&"|"!"|"~"|"-"|"+"|"*"|"/"|"%"|"<"|">"|"^"|"|"|"?"|","|"#"{printf("(%s sign\n)",yytext);}

[\n]		{printf("(newline\t ---)");linenum++;colunum=charnum;charnum++;}

[\r]		{printf("(return\t ---)\n");charnum++;}

%%

int yywrap()
{
	return 1;
}

int main()
{
	if(!(yyin=fopen("data.txt","r")))
	{
		printf("No such file");
		exit(0);
	}
	yylex();
	printf("linenum = %d.\nwordnum = %d.\ncharnum = %d.\n",linenum,wordnum,charnum);
	fclose(yyin);
	return 0;
}