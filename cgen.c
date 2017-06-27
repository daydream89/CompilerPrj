#include "globals.h"
#include "symtab.h"
#include "code.h"
#include "cgen.h"
#include "cminus.tab.h"

#define DEBUG 1

#define WORDSIZE 4
#define NUMOFTMPREG 10

char RegName[32][6] = {"$zero", "$at", "$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
	    "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$s0", "$s1", "$s2", "$s3", "$s4",
	    "$s5", "$s6", "$s7", "$t8", "$t9", "$k0", "$k1", "$gp", "$sp", "$fp" ,"$ra"};

char TmpRegName[10][4] = {"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9"};

static void cGen(TreeNode * tree,char* return_label);

/* Need To Fix */
// 1. 숫자 출력 hex와 dec 혼동되어 있으니 dec가 가능하면 dec로 통일할 것
// 2. Array Accessing은 indirect로 변경(parameter declrae인 경우에만)
// 3. Argument의 Location 값은 일괄적으로 44씩 더하자(teempReg를 위한 40byte, 저장된 fp를 위한 4byte)
static int tmpReg = 0; //사용되지 않은 tmpReg 중 가장 작은 idx

static int nextTempReg(void){
	if(tmpReg == 10){
		return -1;
	}else{
		return tmpReg++;
	}
}

//현재 사용중인 tmpReg중 가장 큰 값
static int currentTmpReg(void){
	return tmpReg-1;	
}

static void removeTmpReg(int val){
	tmpReg = tmpReg - val;
	if(tmpReg < 0){
		printf("ERROR: tmpReg < 0");
		exit(1);
	}
}

static int savedTmpReg[100];
static int savedTmpRegIdx = 0;

static void saveTmpReg(void){
	int i;

	savedTmpReg[savedTmpRegIdx++] = tmpReg;

	emitRI_3("addi","$sp","$sp",NUMOFTMPREG*WORDSIZE,"add: reserve space for save temp register");
	for(i=0;i<NUMOFTMPREG;i++){
		int loc;
		loc = (NUMOFTMPREG-i-1) * WORDSIZE; 
		emitRM("sw",TmpRegName[i],loc,"$sp","save tmp register");
	}
}

static void retriveTmpReg(void){
	int i;

	tmpReg = savedTmpReg[--savedTmpRegIdx];

	for(i=0;i<NUMOFTMPREG;i++){
		int loc;
		loc = (NUMOFTMPREG-i-1) * WORDSIZE;
		emitRM("lw",TmpRegName[i],loc,"$sp","retrive tmp register");
	}

	emitRI_3("addi","$sp","$sp",NUMOFTMPREG*WORDSIZE,"add: retrive space for saved temp register");
}

/* Callee 시작 시 호출되어야 할 함수 */
static void save_FP_RA(void){
	emitRI_3("addi","$sp","$sp",-2*WORDSIZE,"add: reserve space for fp, ra");
	emitRM("sw","$fp",WORDSIZE,"$sp","save fp");
	emitRM("sw","$ra",0,"$sp","save ra");
}

/* Callee 종료 전 호출되어야 할 함수 */
static void retrive_FP_RA(void){
	emitRM("lw","$ra",0,"$sp","retrive ra");
	emitRM("lw","$fp",WORDSIZE,"$sp","retrive fp");
	emitRI_3("addi","$sp","$sp",2*WORDSIZE,"add: remove space for fp,ra");
}

static int argumentPush(TreeNode* tree){
	int num=0;
	int i;
	int cur_tmp;

	cGen(tree,NULL);

	cur_tmp = currentTmpReg();

	while(tree){
		num++;
		tree = tree->sibling;
	}

	if(num)
		emitRI_3("addi","$sp","$sp",-num*WORDSIZE,"add: retrive space for pushing argument");

	for(i=num-1;i>=0;i--){
		emitRM("sw",TmpRegName[cur_tmp-i],(num-1-i)*WORDSIZE,"$sp","push argument");
	}
	
	return num*WORDSIZE;
}

static int _isConst(TreeNode* tree){
	if(tree->nodekind == ExpK && tree->kind.exp == ConstK)
		return 1;
	else return 0;
}

static int _isId(TreeNode* tree){
	if(tree->nodekind == ExpK && tree->kind.exp == IdK)
		return 1;
	else return 0;
}

static int labelNum = 0;

static void getLabel(char* label){
	sprintf(label,"_lab_%d",labelNum++);
}

static void returnLabel(int howMany){
	labelNum -= howMany;
	if(labelNum < 0){
		printf("ERROR: label number < 0");
		exit(1);
	}
}

static int tmpOffset = 0;


static void genStmt(TreeNode * tree,char* return_label){
	TreeNode * p1, *p2, *p3;
	int savedLoc1, savedLoc2, currentLoc;
	int loc;
	char label1[10],label2[10],label3[10];

	if(DEBUG) printf("genStmt\n");

	switch(tree->kind.stmt){
		/*
		case SelectK:
			if(TraceCode) emitComment("-> if");
			p1 = tree->child[0];
			p2 = tree->child[1];
			p3 = tree->child[2];

			cGen(p1);
			savedLoc1 = emitSkip(1);

			cGen(p2);
			savedLoc2 = emitSkip(1);
			emitComment("if: jump to end belongs here");
			currentLoc = emitSkip(0);
			emitBackup(savedLoc1);
			emitRM_Abs("JEQ",ac,currentLoc,"if: jmp to else");
			emitRestore();

			cGen(p3);
			currentLoc = emitSkip(0);
			emitBackup(savedLoc2);
			emitRM_Abs("LDA",pc,currentLoc,"jmp to emd");
			emitRestore();
			if(TraceCode) emitComment("<- if");
			break;

		case IterK:
			if(TraceCode) emitComment("-> repeat");
			p1 = tree->child[0];
			p2 = tree->child[1];
			savedLoc1 = emitSkip(0);
			emitComment("repeat: jump after body comes back here");

			cGen(p1);

			cGen(p2);

			emitRM_Abs("JEQ",ac,savedLoc1,"repeat: jmp back to body");
			if(TraceCode) emitComment("<- repeat");
			break;

		case AssignK:
			if(TraceCode) emitComment("-> assign");
			cGen(tree->child[0]);

			loc = st_lookup(tree->attr.name);
			emitRM("ST",ac,loc,gp,"assign: store value");
			if(TraceCode) emitComment("<- assign");
			break;

			*/

		case FunDecK:
			if(TraceCode) emitComment("-> Function Declaration");
		
			fprintf(code,".globl %s\n",tree->child[1]->attr.name);
			emitLabel(tree->child[1]->attr.name);
			getLabel(label1);
			
			save_FP_RA();

			emitRI_3("addi","$fp","$sp",WORDSIZE,"addi : setting fp");

			//Local 변수를 위한 공간 할당
			emitRI_3("addi","$sp","$sp",-(tree->local_val_size),"addi: reserve space for local variable");

			cGen(tree->child[3],label1);

			emitLabel(label1);
			
			emitRI_3("addi","$sp","$sp",tree->local_val_size,"addi: remove space for local variable");
			retrive_FP_RA();
			emitRO_1("jr","$ra","return to caller");

			if(TraceCode) emitComment("<- Function Declaration");
			break;

		case CompoundK:
			if(TraceCode) emitComment("-> Compound Statement");
			cGen(tree->child[1],NULL);
			if(TraceCode) emitComment("<- Compound Statement");
			break;

		case SelectK:
			break;

		case IterK:
			break;

		case ReturnK:

			break;

		default:
			break;
	}
}

static void genExp(TreeNode * tree,char* return_label){
	int loc;
	TreeNode * p1, *p2;
	int tmpRegNum,tmpRegNum2,cur_tmp;
	char hex[14];
	TreeNode* decNode;
	int argument_size;

	if(DEBUG) printf("genExp\n");

	switch(tree->kind.exp){
		case ConstK:
			tmpRegNum = nextTempReg();
			if(tmpRegNum == -1){
				printf("ERROR: Full of Tmp Reg\n");
				exit(1);
			}

			emitRI_2("li",TmpRegName[tmpRegNum],tree->attr.val,"const: immediate value to tmpReg");
			break;

		case IdK:
			loc = tree->typeDecNode->loc;
			tmpRegNum = nextTempReg();
			if(tmpRegNum == -1){
				printf("ERROR: Full of Tmp Reg\n");
				exit(1);
			}

			emitRM("lw",TmpRegName[tmpRegNum],loc,"$fp","id: variable value to tmpReg");

			break;

		case OpK:
			if(TraceCode) emitComment("-> Op");
			p1 = tree->child[0];
			p2 = tree->child[1];

			cGen(p1,NULL); //결과가 tn에 있다면,
			cGen(p2,NULL); //결과는 tn+1에 있다.

			cur_tmp = currentTmpReg();
			
			switch(tree->attr.op){
				case PLUS:
					emitRO_3("add",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"add: add two operand");
					break;
				case MINUS:
					emitRO_3("sub",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"sub: subtract two operand");
					break;
				case TIMES:
					emitRO_3("mul",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"mul: multiply two operand");
					break;
				case OVER:
					emitRO_3("div",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"div: divide two operand");
					break;

				case EQ:
					emitRO_3("seq",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"seq: set 1 if equal");
					break;
				case NEQ:
					emitRO_3("sne",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"sne: set 1 if not equal");
					break;
				case LT:
					emitRO_3("slt",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"slt: set 1 if less than");
					break;
				case LTOE:
					emitRO_3("sle",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"sle: set 1 if less or equal");
					break;
				case GT:
					emitRO_3("sgt",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"sgt: set 1 if greater than");
					break;
				case GTOE:
					emitRO_3("sge",TmpRegName[cur_tmp-1],TmpRegName[cur_tmp-1],TmpRegName[cur_tmp],"sge: set 1 if grater or equal");
					break;
				default:
					emitComment("BUG: Unknown operator");
					break;
			}
			removeTmpReg(1);
			if(TraceCode) emitComment("<- Op");
			break;
		
		case AssignK:
			if(TraceCode) emitComment("-> Assign");
			/* r-value가 immediate value일 경우와 register일 경우를 구분 */
			p1 = tree->child[0];
			p2 = tree->child[1];

			cGen(p2,NULL); //마지막 tmpReg에 p2의 결과가 저장되어 있음.

			if(_isId(p1)){	//Variable Accessing
				decNode = p1->typeDecNode;
				loc = decNode->loc;
				emitRM("sw",TmpRegName[currentTmpReg()],loc,"$fp","store word: r-value to l-value");
			}else{	//Array Accessing
				decNode = p1->child[0]->typeDecNode;
				
				cGen(p1->child[1],NULL);
				
				tmpRegNum = nextTempReg();

				emitRI_2("li",TmpRegName[tmpRegNum],WORDSIZE,"li: load word size");
				emitRO_3("mul",TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum],"mul: value * wordsize");
				emitRM_R("sw",TmpRegName[tmpRegNum-2],TmpRegName[tmpRegNum-1],"$fp","store word: r-value to l-value");
				
				removeTmpReg(1);
			}
			
			removeTmpReg(1);
			if(TraceCode) emitComment("<- Assign");
			break;

		case ArrK:
			if(TraceCode) emitComment("-> Array Accessing");
			p1 = tree->child[0];
			p2 = tree->child[1];

			decNode = p1->typeDecNode;
			
			cGen(p2,NULL);

			if(decNode->kind.stmt == ParaArrDecK){
				loc = decNode->loc;

				tmpRegNum = nextTempReg();
				tmpRegNum2 = nextTempReg();	

				/* array[val]에서 val은 tmpRegNum-1에 있음 */

				emitRM("lw",TmpRegName[tmpRegNum],loc,"$fp","lw: load array base address");
				emitRI_2("li",TmpRegName[tmpRegNum2],WORDSIZE,"li: load word size");
				emitRO_3("mul",TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum2],"mul: value * wordsize");
				emitRM_R("lw",TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum],"array accessing: array element to tmpReg");
				removeTmpReg(2);
			}else{ //ArrDecK
				tmpRegNum = nextTempReg();

				emitRI_2("li",TmpRegName[tmpRegNum],WORDSIZE,"li: load word size");
				emitRO_3("mul",TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum],"mul: value * wordsize");
				emitRM_R("lw",TmpRegName[tmpRegNum-1],TmpRegName[tmpRegNum-1],"$fp","array accessing: array element to tmpReg");

				removeTmpReg(1);
			}
			
			if(TraceCode) emitComment("<- Array Accessing");
			break;

		case CallK:
			if(TraceCode) emitComment("-> Call Function");

			p1 = tree->child[0];
			p2 = tree->child[1];

			tmpRegNum = nextTempReg();
			
			argument_size = argumentPush(p2);
			saveTmpReg();
			emitRO_1("jal",p1->attr.name,"jump to function body");

			//Caller로 돌아왔을 때 후처리
			retriveTmpReg();
			emitRI_3("addi","$sp","$sp",argument_size,"addi: remove space for argument");
			emitRO_2("move",TmpRegName[tmpRegNum],"$v0","move: v0 to tempReg(function result save)");

			if(TraceCode) emitComment("<- Call Function");
			break;
		default:
			break;
	}
}

static void cGen(TreeNode * tree,char* return_label){
	if(tree!= NULL){
		switch(tree->nodekind){
			case StmtK:
				genStmt(tree,return_label);
				break;
			case ExpK:
				genExp(tree,return_label);
				break;
			default:
				break;
		}
		cGen(tree->sibling,return_label);
	}
}

void codeGen(TreeNode* syntaxTree,char* codefile){
	char* s = malloc(strlen(codefile)+7);
	strcpy(s,"File: ");
	strcat(s,codefile);
	emitComment("C-- Compilation to SPIM Code");
	emitComment(s);

	emitComment("Standard prelude:");
	fprintf(code,"	.text\n");
	emitComment("End of standard prelude.");

	cGen(syntaxTree,NULL);

	emitComment("End of execution.");
}


