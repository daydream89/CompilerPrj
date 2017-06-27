#include "globals.h"
#include "code.h"

/* current instruction emission */
static int emitLoc = 0;

static int highEmitLoc = 0;

void emitComment(char *c){
	if (TraceCode) fprintf(code, "# %s\n",c);
}

/* register only */
void emitRO_3(char *op,char* r,char* s,char* t,char* c){
	fprintf(code,"\t%5s		%s,\t%s,\t%s",op,r,s,t);
	if(TraceCode) fprintf(code, "\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;

}

void emitRO_2(char *op,char* r,char* s,char* c){
	fprintf(code,"\t%5s		%s,\t%s",op,r,s);
	if(TraceCode) fprintf(code, "\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;

}

void emitRO_1(char *op,char* r,char* c){
	fprintf(code,"\t%5s		%s",op,r);
	if(TraceCode) fprintf(code, "\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;

}

/* contain immediate value */
void emitRI_3(char *op,char* r,char* s,int t,char* c){
	fprintf(code,"\t%5s		%s,\t%s,\t%d",op,r,s,t);
	if(TraceCode) fprintf(code, "\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;

}

void emitRI_2(char *op,char* r,int s,char* c){
	fprintf(code,"\t%5s		%s,\t%d",op,r,s);
	if(TraceCode) fprintf(code, "\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;

}

/* s : base, d = offset */
void emitRM(char *op,char* r,int d,char* s,char* c){
	fprintf(code,"\t%5s		%s,\t%d(%s) ",op,r,d,s);
	if(TraceCode) fprintf(code,"\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;
}

void emitRM_R(char *op,char* r,char* d,char* s,char* c){
	fprintf(code,"\t%5s		%s,\t%s(%s) ",op,r,d,s);
	if(TraceCode) fprintf(code,"\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;
}

int emitSkip(int howMany){
	int i = emitLoc;
	emitLoc += howMany;
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;
	return i;
}

void emitBackup(int loc){
	if(loc > highEmitLoc) emitComment("BUG in emitBackup");
	emitLoc = loc;
}

void emitRestore(void){
	emitLoc = highEmitLoc;
}

void emitRM_Abs(char* op, int r, int a, char * c){
	fprintf(code,"\t%5s		%d,%d(%d) ",op,r,a-(emitLoc+1),pc);
	++emitLoc;
	if(TraceCode)fprintf(code, "\t# %s",c);
	fprintf(code,"\n");
	if(highEmitLoc < emitLoc) highEmitLoc = emitLoc;
}

void emitLabel(char* label){
	fprintf(code,"%s:\n",label);
}

