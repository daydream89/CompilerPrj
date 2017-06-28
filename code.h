#ifndef _CODE_H_
#define _CODE_H_

void emitRO_3(char *op, char* r, char* s, char* t, char *c);
void emitRO_2(char *op, char* r, char* s,char *c);
void emitRO_1(char *op, char* r,char *c);

void emitRI_3(char *op, char* r, char* s, int t, char *c);
void emitRI_2(char *op, char* r, int s,char *c);

void emitRM(char* op, char* r, int d, char* s, char *c);

void emitComment(char *c);

void emitLabel(char*);

#endif
