%{
#define YYPARSER /* distinguishes Bison ouptut from other code files*/

#include "globals.h"
#include "util.h"
#include "scan.h"

#define YYSTYPE TreeNode *
static char * savedName; /* for use in assignments */
static int savedLineNo; /* ditto */
static TreeNode * savedTree; /* stores syntax tree for later return */

#if YYBISON
static int yylex();
int yyerror(char*);
#endif

%}

%token IF ELSE WHILE
%token ID NUM
%token ASSIGN EQ NEQ LT LTOE GT GTOE PLUS MINUS TIMES OVER LPAREN RPAREN LBRACE RBRACE LBRACK RBRACK SEMI COMMA INT RETURN VOID ENDFILE
%token ERROR

%right ASSIGN
%left EQ NEQ LT LTOE GT GTOE
%left PLUS MINUS
%left TIMES OVER
%nonassoc IFX
%nonassoc ELSE

%% /* Grammar for C- */

program           : declaration_list
                      { savedTree = $1; }
                  ;
declaration_list  : declaration_list declaration
                      { YYSTYPE t = $1;
                        if( t != NULL ){
                          while(t->sibling != NULL)
                            t = t->sibling;
                        t->sibling = $2;
                        $$ = $1;
                        }
                        else $$ = $2;
                      }
                  | declaration
                      { $$ = $1; }
                  ;
declaration       : var_declaration
                      { $$ = $1; }
                  | fun_declaration
                      { $$ = $1; }
                  ;
var_declaration   : type_specifier dec_var SEMI
                      { $$ = newStmtNode(VarDecK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
                      }
                  | type_specifier dec_var LBRACK arr_size RBRACK SEMI
                      { $$ = newStmtNode(ArrDecK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
												$$->child[2] = $4;
                      }
                  ;
dec_var						:	ID
											{	$$ = newExpNode(IdK);
												$$->attr.name = copyString(tokenString);
											}
									;
arr_size					:	NUM
											{	$$ = newExpNode(ConstK);
												$$->attr.val = atoi(tokenString);
											}
									;			

type_specifier    : INT
                      { $$ = newExpNode(TypeK);
                        $$->attr.op = INT;
                      }
                  | VOID
                      { $$ = newExpNode(TypeK);
                        $$->attr.op = VOID;
                      }
                  ;
fun_declaration   : type_specifier dec_var LPAREN params RPAREN compound_stmt
                      { $$ = newStmtNode(FunDecK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
                        $$->child[2] = $4;
                        $$->child[3] = $6;
                      }
                  ;
params            : param_list
                      { $$ = $1; }
                  | VOID
                      { $$ = newExpNode(TypeK);
                        $$->attr.op = VOID;
                      }
                  ;
param_list        : param_list COMMA param
                      { YYSTYPE t = $1;
                        if( t != NULL ){
                          while(t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $3;
                          $$ = $1;
                        }
                        else $$ = $3;
                      }
                  | param { $$ = $1; }
                  ;
param             : type_specifier dec_var
                      { $$ = newStmtNode(ParaDecK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
                      }
                  | type_specifier dec_var LBRACK RBRACK
                      { $$ = newStmtNode(ParaArrDecK);
                        $$->child[0] = $1;
                        $$->child[1] = $2;
                      }
                  ;
compound_stmt     : LBRACE local_declarations statement_list RBRACE
                      { $$ = newStmtNode(CompoundK);
                        $$->child[0] = $2;
                        $$->child[1] = $3;
                      }
                  ;
local_declarations: local_declarations var_declaration
                      { YYSTYPE t = $1;
                        if( t != NULL ){
                          while(t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $2;
                          $$ = $1;
                        }
                        else $$ = $2;
                      }
                  | 
                      { $$ = NULL; }
                  ;
statement_list    : statement_list statement
                      { YYSTYPE t = $1;
                        if( t != NULL ){
                          while(t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $2;
                          $$ = $1;
                        }
                        else $$ = $2;
                      }
                  | 
                      { $$ = NULL; }
                  ;
statement					: expression_stmt { $$ = $1; }
                  | selection_stmt	{ $$ = $1; }
									| compound_stmt { $$ = $1; }
                  | iteration_stmt  { $$ = $1; }
                  | return_stmt { $$ = $1; }
                  ;
expression_stmt   : expression SEMI
                      { $$ = $1; }
                  | SEMI
                      { $$ = NULL; }
                  ;
selection_stmt    : IF LPAREN expression RPAREN statement %prec IFX
                      { $$ = newStmtNode(SelectK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                      }
                  | IF LPAREN expression RPAREN statement ELSE statement
                      { $$ = newStmtNode(SelectK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
												$$->child[2] = $7;
                      }
                  ;
iteration_stmt    : WHILE LPAREN expression RPAREN statement
                      { $$ = newStmtNode(IterK);
                        $$->child[0] = $3;
                        $$->child[1] = $5;
                      }
                  ;
return_stmt       : RETURN SEMI
                      { $$ = newStmtNode(ReturnK); }
                  | RETURN expression SEMI
                      { $$ = newStmtNode(ReturnK);
                        $$->child[0] = $2;
                      }
                  ;
expression        : var ASSIGN expression
                      { $$ = newExpNode(AssignK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                      }
                  | simple_expression
                      { $$ = $1; }
                  ;
var               : dec_var
											{	$$ = $1; }
                  | dec_var LBRACK expression RBRACK
                      { $$ = newExpNode(ArrK);
												$$->child[0] = $1;
												$$->child[2] = $3;
                      }
                  ;
simple_expression : additive_expression LTOE additive_expression
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = LTOE;
                      }
                  | additive_expression LT additive_expression
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = LT;
                      }
                  | additive_expression GT additive_expression
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = GT;
                      }
                  | additive_expression GTOE additive_expression
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = GTOE;
                      }
                  | additive_expression EQ additive_expression
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = EQ;
                      }
                  | additive_expression NEQ additive_expression
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = NEQ;
                      }
                  | additive_expression
                      { $$ = $1; }
                  ;
additive_expression : additive_expression PLUS term
                        { $$ = newExpNode(OpK);
                          $$->child[0] = $1;
                          $$->child[1] = $3;
                          $$->attr.op = PLUS;
                        }
                    | additive_expression MINUS term
                        { $$ = newExpNode(OpK);
                          $$->child[0] = $1;
                          $$->child[1] = $3;
                          $$->attr.op = MINUS;
                        }
                    | term
                        { $$ = $1; }
                    ;
term              : term TIMES factor
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = TIMES;
                      }
                  | term OVER factor
                      { $$ = newExpNode(OpK);
                        $$->child[0] = $1;
                        $$->child[1] = $3;
                        $$->attr.op = OVER;
                      }
                  | factor
                      { $$ = $1; }
                  ;
factor            : LPAREN expression RPAREN
                      { $$ = $2; }
                  | var
                      { $$ = $1; }
                  | call 
                      { $$ = $1; }
                  | NUM
                      { $$ = newExpNode(ConstK);
                        $$->attr.val = atoi(tokenString);
                      }
                  ;
call              : dec_var LPAREN args RPAREN
                      { $$ = newExpNode(CallK);
                        $$->child[0] = $1;
												$$->child[1] = $3;
                      }
                  ;
args              : arg_list
                      { $$ = $1; }
                  |
                      { $$ = NULL; }
                  ;
arg_list          : arg_list COMMA expression
                      { YYSTYPE t = $1;
                        if( t != NULL ){
                          while(t->sibling != NULL)
                            t = t->sibling;
                          t->sibling = $3;
                          $$ = $1;
                        }
                        else $$ = $3;
                      }
                  | expression { $$ = $1; }
                  ;
%%

int yyerror(char * message){
  fprintf(listing, "Syntax error at line %d: %s\n", lineno, message);
  fprintf(listing, "Current token: ");
  printToken(yychar, tokenString);
  Error = TRUE;
  return 0;
}


/* yylex calls getToken to make Yacc/Bison output
 * compatible with earlier versions of
 * the TINY scanner
 */


static int yylex(void){
  return getToken();
}

TreeNode * parse(void){
  printf("Start of parse\n");
	yyparse();
	printf("End of parse\n");
  return savedTree;
}


