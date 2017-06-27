%{
#include "globals.h"
#include "cminus.tab.h"
#include "util.h"

/* scan.h's definition */
#define MAXTOKENLEN 40

/* lexeme of idntifier of reserved word */
char tokenString[MAXTOKENLEN+1];
%}

digit				[0-9]
number			{digit}+
letter			[a-zA-Z]
identifier	{letter}+
newline			\n
whitespace	[ \t]+

%%

"output"	{return OUTPUT;}
"input"		{return INPUT;}
"else"		{return ELSE;}
"if"		{return IF;}
"int"		{return INT;}
"return"	{return RETURN;}
"void"		{return VOID;}
"while"		{return WHILE;}
"="		{return ASSIGN;}
"=="		{return EQ;}
"!="		{return NEQ;}
"<"		{return LT;}
"<="		{return LTOE;}
">"		{return GT;}
">="		{return GTOE;}
"+"		{return PLUS;}
"-"		{return MINUS;}
"*"		{return TIMES;}
"/"		{return OVER;}
"("		{return LPAREN;}
")"		{return RPAREN;}
";"		{return SEMI;}
","		{return COMMA;}
"{"		{return LBRACE;}
"}"		{return RBRACE;}
"["		{return LBRACK;}
"]"		{return RBRACK;}
"/*"		{	register int c;
			while(1){
				/* *이나 EOF일 때까지 c를 무시하고, \n일 경우에만 LineNumber를 증가 */
				while((c = input()) != '*' && c != EOF){
					if(c == '\n') lineno++;
				}

				/* 만약 *이면 반복된 *를 무시하고 이어서 /가 입력되면 주석의 끝으로 인식하고 종료 */
				if(c=='*'){
					while((c = input()) == '*')
						;
					if(c=='\n') lineno++;
					if(c=='/') 
						break; /*found the end*/
				}

				/* 주석이 끝나기 전에 EOF를 만나면 error를 반환하고 lexeme에 "Comment Error"를 저장한다. */
				if(c==EOF){
					strcpy(yytext,"Comment Error");
					return ERROR;
				}
			}
		}

{number}	{return NUM;}
{identifier}	{return ID;}
{newline}	{lineno++;}
{whitespace}	{/* skip whitespace */}
.		{return ERROR;}

%%

TokenType getToken(void){
	static int firstTime = TRUE;
	TokenType currentToken;
	if(firstTime){
		firstTime = FALSE;
		lineno++;
		yyin = source;
		yyout = listing;
		/* Print Format */
		if(TraceScan){
			fprintf(listing,"\tline number\t\t\ttoken\t\t\tlexeme\n");
			fprintf(listing,"------------------------------------------------------------------------------------\n");
		}
	}
	currentToken = yylex();
	strncpy(tokenString,yytext,MAXTOKENLEN);

	if(TraceScan){
		fprintf(listing,"\t   %d\t\t\t\t",lineno);
		printToken(currentToken,tokenString);
	}
	return currentToken;
}
