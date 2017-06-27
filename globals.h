/*******************************************/
/* File: globals.h                         */
/* Global types and vars for TINY compiler */
/* must come before other include files    */
/*******************************************/


#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

/* MAXRESERVED = the number of reserved words */
#define MAXRESERVED 8


//typedef enum
	/* book-keeping tokens */
//	{ENDFILE,ERROR,
	/* reserved words */
//	ELSE,IF,INT,RETURN,VOID,WHILE,
	/* multicharacter tokens */
//	ID,NUM,
	/* special symbols */
//	PLUS,MINUS,TIMES,OVER,LT,LTOE,GT,GTOE,EQ,NEQ,ASSIGN,SEMI,
//	COMMA,LPAREN,RPAREN,LBRACE,RBRACE,LBRACK,RBRACK,
//	} TokenType;

typedef int TokenType;

extern FILE* source; /* source code text file */
extern FILE* listing; /* listing output text file */
extern FILE* code; /* code text file for TM simulator */

extern int lineno; /* source line number for listing */

extern int Error;

/****************************************************/
/***************** Syntax tree for parsing **********/
/****************************************************/

typedef enum {StmtK,ExpK} NodeKind;
//typedef enum {IfK, RepeatK, AssignK, ReadK, WriteK} StmtKind;
//typedef enum {OpK, ConstK, IdK} ExpKind;

/*******************************************/

typedef enum {ParaDecK,ParaArrDecK,VarDecK, FunDecK, ArrDecK, CompoundK, SelectK, IterK, ReturnK  } StmtKind;
typedef enum {OpK, ConstK, IdK, TypeK, AssignK, CallK, ArrK} ExpKind;

/* ExpType is used for type checking */
typedef enum {Void, Integer, Boolean} ExpType;

#define MAXCHILDREN 4

typedef struct treeNode{
	struct treeNode * child[MAXCHILDREN];
	struct treeNode * sibling;
	int lineno;
	NodeKind nodekind;
	union { StmtKind stmt; ExpKind exp;} kind;
	union { TokenType op;
		int val;
		char* name; } attr;
	ExpType type; /* for type checking of exps */
	struct treeNode *typeDecNode;	/* for pointing variable type declaration node */
	int loc;
	int local_val_size;
}TreeNode;

typedef enum {zero, at, v0, a0, a1, a2, a3, t0, t1, t2, t3, t4, t5, t6, t7, s0, s1, s2, s3, s4, s5, s6,
		s7, t8, t9, k0, k1, gp, sp, fp, ra} RegKind;

typedef struct gValueNode
{
	struct gValueNode *next;
	TreeNode *node;
}GValueNode;

static GValueNode *gs_globalVariableList;

/********************************************/
/*******         Flags for tracing      *****/
/********************************************/

extern int EchoSource;
extern int TraceScan;
extern int TraceParse;
extern int TraceAnalyse;
extern int TraceCode;
extern int Error;

#endif
