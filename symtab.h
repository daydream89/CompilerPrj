#ifndef _SYMTAB_H_
#define _SYMTAB_H_

void st_insert(char *name, int lineno, int loc);

int st_lookup(char *name);

TreeNode *findDeclaration(char *name);
TreeNode *findLastFuncDec();

void insertDeclarationList(TreeNode *node, StmtKind type);

void removeInvalidDec();
void removeAllDeclarationList();

void printSymTab(FILE *listing);

#endif
