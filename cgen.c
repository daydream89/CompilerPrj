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

char TempRegName[10][4] = {"$t0","$t1","$t2","$t3","$t4","$t5","$t6","$t7","$t8","$t9"};

static void cGen(TreeNode * tree,char* return_label);

/* Need To Fix */
// 1. 숫자 출력 hex와 dec 혼동되어 있으니 dec가 가능하면 dec로 통일할 것
// 2. Array Accessing은 indirect로 변경(parameter declrae인 경우에만)
// 3. Argument의 Location 값은 일괄적으로 44씩 더하자(teempReg를 위한 40byte, 저장된 fp를 위한 4byte)
static int getLocation(TreeNode* dec_node){
	switch(dec_node->kind.stmt){
		case ParaDecK:
		case ParaArrDecK:
			return dec_node->child[1]->loc + 40;
			break;
		case ArrDecK:
		case VarDecK:
			return dec_node->child[1]->loc;
			break;
		default:
			printf("ERROR: decNode is not declaration\n");
			exit(1);
			break;
	}
}

static int _is_global(TreeNode* node){
	return node->is_global;
}

static int tempReg = 0; //사용되지 않은 tempReg 중 가장 작은 idx

static int nextTempReg(void){
	if(tempReg == 10){
		return -1;
	}else{
		return tempReg++;
	}
}

//현재 사용중인 tempReg중 가장 큰 값
static int currentTempReg(void){
	return tempReg-1;	
}

static void removeTempReg(int val){
	tempReg = tempReg - val;
	if(tempReg < 0){
		printf("ERROR: tempReg < 0");
		exit(1);
	}
}

static void removeAllTempReg(void){
	tempReg = 0;
}

static int savedTempReg[100];
static int savedTempRegIdx = 0;

static void saveTempReg(void){
	int i;

	savedTempReg[savedTempRegIdx++] = tempReg;

	emitRI_3("addi","$sp","$sp",NUMOFTMPREG*WORDSIZE,"add: reserve space for save temp register");
	for(i=0;i<NUMOFTMPREG;i++){
		int loc;
		loc = (NUMOFTMPREG-i-1) * WORDSIZE; 
		emitRM("sw",TempRegName[i],loc,"$sp","save temp register");
	}

	tempReg = 0;
}

static void retriveTempReg(void){
	int i;

	tempReg = savedTempReg[--savedTempRegIdx];

	for(i=0;i<NUMOFTMPREG;i++){
		int loc;
		loc = (NUMOFTMPREG-i-1) * WORDSIZE;
		emitRM("lw",TempRegName[i],loc,"$sp","retrive temp register");
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
	int cur_temp;

	cGen(tree,NULL);

	cur_temp = currentTempReg();

	while(tree){
		num++;
		tree = tree->sibling;
	}

	if(num)
		emitRI_3("addi","$sp","$sp",-num*WORDSIZE,"add: retrive space for pushing argument");

	for(i=num-1;i>=0;i--){
		emitRM("sw",TempRegName[cur_temp-i],(num-1-i)*WORDSIZE,"$sp","push argument");
	}

	removeTempReg(num);
	
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

static int tempOffset = 0;


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
			cGen(tree->child[1],return_label);
			if(TraceCode) emitComment("<- Compound Statement");
			break;

		case ExpStmtK:
			//if(TraceCode) emitComment("-> Expression Statement");
			cGen(tree->child[0],return_label);
			removeAllTempReg();
			//if(TraceCode) emitComment("<- Expression Statement");
			break;

		case SelectK:
			if(TraceCode) emitComment("-> Selection Statement");
			if(tree->child[2] == NULL){// if then
				getLabel(label1);

				cGen(tree->child[0],NULL);
				emitRO_2("beqz",TempRegName[currentTempReg()],label1,"branch if condition is false");
				removeTempReg(1);

				cGen(tree->child[1],return_label);
				emitLabel(label1);
			}else{//if then else
				getLabel(label1);
				getLabel(label2);

				cGen(tree->child[0],NULL);
				emitRO_2("beqz",TempRegName[currentTempReg()],label1,"branch if condition is false");
				removeTempReg(1);

				cGen(tree->child[1],return_label);
				emitRO_1("b",label2,"branch to end of selection statement");
				emitLabel(label1);
				cGen(tree->child[2],return_label);
				emitLabel(label2);
			}
			if(TraceCode) emitComment("<- Selection Statement");
			break;

		case IterK:
			if(TraceCode) emitComment("-> Iteration Statement");
			getLabel(label1);
			getLabel(label2);

			emitLabel(label1);
			cGen(tree->child[0],NULL);
			emitRO_2("beqz",TempRegName[currentTempReg()],label2,"branch if condition is false");
			removeTempReg(1);

			cGen(tree->child[1],return_label);
			emitRO_1("b",label1,"branch to end of iteration statement");
			emitLabel(label2);			
			if(TraceCode) emitComment("<- Iteration Statement");
			break;

		case ReturnK:
			if(TraceCode) emitComment("-> Return Statement");
			
			cGen(tree->child[0],NULL);
			emitRO_2("move","$v0",TempRegName[currentTempReg()],"save function return value in v0");
			removeTempReg(1);
			emitRO_1("j",return_label,"jump to function end process");

			if(TraceCode) emitComment("<- Return Statement");
			break;

		default:
			break;
	}
}

static void genExp(TreeNode * tree,char* return_label){
	int loc;
	TreeNode * p1, *p2;
	int tempRegNum,tempRegNum2,cur_temp;
	char hex[14];
	TreeNode* decNode;
	int argument_size;

	if(DEBUG) printf("genExp\n");

	switch(tree->kind.exp){
		case ConstK:
			tempRegNum = nextTempReg();
			if(tempRegNum == -1){
				printf("ERROR: Full of Temp Reg\n");
				exit(1);
			}

			emitRI_2("li",TempRegName[tempRegNum],tree->attr.val,"const: immediate value to tempReg");
			break;

		case IdK:
			decNode = tree->typeDecNode;
			loc = getLocation(decNode); 
			tempRegNum = nextTempReg();
			if(tempRegNum == -1){
				printf("ERROR: Full of Temp Reg\n");
				exit(1);
			}

			if(_is_global(decNode))
				emitRM("lw",TempRegName[tempRegNum],loc,"$gp","id: variable value to tempReg");
			else
				emitRM("lw",TempRegName[tempRegNum],loc,"$fp","id: variable value to tempReg");

			break;

		case OpK:
			if(TraceCode) emitComment("-> Op");
			p1 = tree->child[0];
			p2 = tree->child[1];

			cGen(p1,NULL); //결과가 tn에 있다면,
			cGen(p2,NULL); //결과는 tn+1에 있다.

			cur_temp = currentTempReg();
			
			switch(tree->attr.op){
				case PLUS:
					emitRO_3("add",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"add: add two operand");
					break;
				case MINUS:
					emitRO_3("sub",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"sub: subtract two operand");
					break;
				case TIMES:
					emitRO_3("mul",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"mul: multiply two operand");
					break;
				case OVER:
					emitRO_3("div",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"div: divide two operand");
					break;

				case EQ:
					emitRO_3("seq",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"seq: set 1 if equal");
					break;
				case NEQ:
					emitRO_3("sne",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"sne: set 1 if not equal");
					break;
				case LT:
					emitRO_3("slt",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"slt: set 1 if less than");
					break;
				case LTOE:
					emitRO_3("sle",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"sle: set 1 if less or equal");
					break;
				case GT:
					emitRO_3("sgt",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"sgt: set 1 if greater than");
					break;
				case GTOE:
					emitRO_3("sge",TempRegName[cur_temp-1],TempRegName[cur_temp-1],TempRegName[cur_temp],"sge: set 1 if grater or equal");
					break;
				default:
					emitComment("BUG: Unknown operator");
					break;
			}
			removeTempReg(1);
			if(TraceCode) emitComment("<- Op");
			break;
		
		case AssignK:
			if(TraceCode) emitComment("-> Assign");
			/* r-value가 immediate value일 경우와 register일 경우를 구분 */
			p1 = tree->child[0];
			p2 = tree->child[1];

			cGen(p2,NULL); //마지막 tempReg에 p2의 결과가 저장되어 있음.

			if(_isId(p1)){	//Variable Accessing
				decNode = p1->typeDecNode;
				loc = getLocation(decNode);
				if(_is_global(decNode))
					emitRM("sw",TempRegName[currentTempReg()],loc,"$gp","store word: r-value to l-value");
				else
					emitRM("sw",TempRegName[currentTempReg()],loc,"$fp","store word: r-value to l-value");
			}else{	//Array Accessing
				decNode = p1->child[0]->typeDecNode;
				
				cGen(p1->child[1],NULL);
				
				tempRegNum = nextTempReg();

				emitRI_2("li",TempRegName[tempRegNum],WORDSIZE,"li: load word size");
				emitRO_3("mul",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],TempRegName[tempRegNum],"mul: value * wordsize");
				if(_is_global(decNode))
					emitRO_3("add",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],"$gp","add: calculate address of l-value");
				else
					emitRO_3("add",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],"$fp","add: calculate address of l-value");
				emitRM_R("sw",TempRegName[tempRegNum-2],"",TempRegName[tempRegNum-1],"store word: r-value to l-value");
				
				removeTempReg(1);
			}
			
			removeTempReg(1);
			if(TraceCode) emitComment("<- Assign");
			break;

		case ArrK:
			if(TraceCode) emitComment("-> Array Accessing");
			p1 = tree->child[0];
			p2 = tree->child[1];

			decNode = p1->typeDecNode;
			
			cGen(p2,NULL);

			if(decNode->kind.stmt == ParaArrDecK){
				loc = getLocation(decNode);

				tempRegNum = nextTempReg();
				tempRegNum2 = nextTempReg();	

				/* array[val]에서 val은 tempRegNum-1에 있음 */

				if(_is_global(decNode))
					emitRM("lw",TempRegName[tempRegNum],loc,"$gp","lw: load array base address");
				else
					emitRM("lw",TempRegName[tempRegNum],loc,"$fp","lw: load array base address");
				emitRI_2("li",TempRegName[tempRegNum2],WORDSIZE,"li: load word size");
				emitRO_3("mul",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],TempRegName[tempRegNum2],"mul: value * wordsize");
				emitRO_3("add",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],TempRegName[tempRegNum],"add: calculate address of element");
				emitRM_R("lw",TempRegName[tempRegNum-1],"",TempRegName[tempRegNum],"array accessing: array element to tempReg");
				removeTempReg(2);
			}else{ //ArrDecK
				tempRegNum = nextTempReg();

				emitRI_2("li",TempRegName[tempRegNum],WORDSIZE,"li: load word size");
				emitRO_3("mul",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],TempRegName[tempRegNum],"mul: value * wordsize");
				if(_is_global(decNode))
					emitRM_R("lw",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],"$gp","array accessing: array element to tempReg");
				else
					emitRM_R("lw",TempRegName[tempRegNum-1],TempRegName[tempRegNum-1],"$fp","array accessing: array element to tempReg");

				removeTempReg(1);
			}
			
			if(TraceCode) emitComment("<- Array Accessing");
			break;

		case CallK:
			if(TraceCode) emitComment("-> Call Function");

			p1 = tree->child[0];
			p2 = tree->child[1];

			tempRegNum = nextTempReg();
			
			argument_size = argumentPush(p2);
			saveTempReg();
			emitRO_1("jal",p1->attr.name,"jump to function body");

			//Caller로 돌아왔을 때 후처리
			retriveTempReg();
			emitRI_3("addi","$sp","$sp",argument_size,"addi: remove space for argument");
			emitRO_2("move",TempRegName[tempRegNum],"$v0","move: v0 to tempReg(function result save)");

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

static void makeDataArea(void){
	GValueNode* ptr;

	printf("In Here!\n");

	if(gs_globalVariableList != NULL){
		fprintf(code,"\t\t\t.data\n");
		
		ptr = gs_globalVariableList;

		while(ptr){
			TreeNode* node = ptr->node;
			switch(node->kind.stmt){
				case ArrDecK:
					fprintf(code,".space	%d\n",WORDSIZE*node->child[2]->attr.val);
					break;
				case VarDecK:
					fprintf(code,".space	%d\n",WORDSIZE);
					break;
				default:
					emitComment("ERROR: there exist non declaration node in globalVariableList");
			}

			ptr = ptr->next;
		}
	}
}

void codeGen(TreeNode* syntaxTree,char* codefile){
	char* s = malloc(strlen(codefile)+7);
	strcpy(s,"File: ");
	strcat(s,codefile);
	emitComment("C-- Compilation to SPIM Code");
	emitComment(s);

	makeDataArea();
	emitComment("Standard prelude:");
	fprintf(code,"\t\t.text\n");
	emitComment("End of standard prelude.");

	cGen(syntaxTree,NULL);

	emitComment("End of execution.");
}


