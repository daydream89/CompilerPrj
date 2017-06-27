#ifndef _CODE_H_
#define _CODE_H_

#define pc 7

#define mp 6

#define gp 5

#define ac 0

#define ac1 1

/* Emit Register Only */
/* r : target */
/* s : first source , t : 2nd source */
/* c : comment to be printed */
void emitRO_3(char *op, char* r, char* s, char* t, char *c);
void emitRO_2(char *op, char* r, char* s,char *c);
void emitRO_1(char *op, char* r,char *c);

void emitRI_3(char *op, char* r, char* s, int t, char *c);
void emitRI_2(char *op, char* r, int s,char *c);

void emitRM(char* op, char* r, int d, char* s, char *c);
void emitRM_R(char* op, char* r, char* d, char* s, char *c);

int emitSkip(int howMany);

/* backs up to loc */
void emitBackup(int loc);

/* restores the current code position to the highest previously unemitted postion */
void emitRestore(void);

void emitComment(char *c);

/* absolute reference to a pc-relative reference */
/* t : target, a : absolute location in mem, c : commnet */
void emitRM_Abs(char *op, int r, int a, char* c);

void emitLabel(char*);

#endif
