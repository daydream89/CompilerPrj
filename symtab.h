#ifndef _SYMTAB_H_
#define _SYMTAB_H_

void st_create();
void st_remove();

void st_insert(char *name, int lineno, int loc, int scope, StmtKind type, int arr_size, ExpType return_type);

int st_lookup(char *name);

TreeNode *findDeclaration(char *name);
TreeNode *findLastFuncDec();

void insertDeclarationList(TreeNode *node, StmtKind type);

void removeAllDeclarationList();

void printSymTab(FILE *listing);

#endif
