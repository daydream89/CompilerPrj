/************************************/
/* File: main.c                     */
/* Main program for TINY coimpiler  */
/************************************/



#include "globals.h"
//#include "lex.yy.c"
#include "util.h"
#include "scan.h"
#include "buildSymtab.h"
#include "cminus.tab.h"
#include "analyze.h"

/* parse.h inside */
TreeNode* parse(void);

/* allocate global variables */
int lineno = 0;
FILE * source;	//C-Language Source File
FILE * listing;	//Output Stream

/* allocate and set racing flags */
int EchoSource = TRUE;
int TraceScan = FALSE;
int TraceParse = FALSE;
int TraceAnalyse = TRUE;
int TraceCode = TRUE;

int Error = FALSE;	//프로그램 진행 중 error가 발생할 경우 true로 설정

int main (int argc, char* argv[]){
	TreeNode * syntaxTree;
	char pgm[20]; /* source code file name */
	
	/* 잘못된 실행 방법으로 프로그램을 실행했을 때 */
	if (argc != 2){
		fprintf(stderr,"usage: %s <filename>\n",argv[0]);
		exit(1);
	}

	strcpy(pgm,argv[1]);
	if(strchr(pgm, '.') == NULL)
		strcat(pgm,".tny");
	source = fopen(pgm,"r");
	
	/* 입력한 C-Language Source File이 존재하지 않을 경우 */
	if(source == NULL){
		fprintf(stderr,"File %s not found\n",pgm);
		exit(1);
	}

	listing = stdout; /* send linting to screen */
	
	syntaxTree = parse();
	if(TraceParse){
		fprintf(listing,"\nStnyax tree:\n");
		printTree(syntaxTree);
	}

	fprintf(listing, "\nBuilding Symbol Table...\n");
	buildSymtab_pass1(syntaxTree);		// pass1

	if(!Error){
		fprintf(listing,"\nSymantic Analyze Start...\n");
		typeCheck(syntaxTree);	
	}
	return 0;
}

