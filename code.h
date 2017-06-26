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
void emitRo(char *op,int r, int s, int t, char *c);

/* Emit register to memory */
/* r : target, d = offset, s = base register */
void emitRM(char* op,int r, int d, int s, char *c);

/* backs up to loc */
void emitBackup(int loc);

/* restores the current code position to the highest previously unemitted postion */
void emitRestore(void);

void emitCommnet(char *c);

/* absolute reference to a pc-relative reference */
/* t : target, a : absolute location in mem, c : commnet */
void emitRM_Abs(char *op, int r, int a, char* c);
