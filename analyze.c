#include "globals.h"
//#include "symtab.h"
#include "analyze.h"
#include "cminus.tab.h"

#include "util.h"

#define DEBUG 0 

static int findMainFlag = FALSE;

static void traverse(TreeNode * t,
		void (* preProc) (TreeNode *),
		void (* postProc) (TreeNode *) )
{
	if (t != NULL){
		preProc(t);
		{
			int i;
			for (i=0;i<MAXCHILDREN;i++)
				traverse(t->child[i],preProc,postProc);
		}
		postProc(t);
		traverse(t->sibling,preProc,postProc);
	}
}

static void nullProc(TreeNode * t){
	if(t==NULL) return;
	else return;
}

static void typeError(TreeNode *t, char *message){
	fprintf(listing,"Type error at line %d: %s\n",t->lineno,message);
}

static void ParameterChecking(TreeNode *t,TreeNode *formal_para_list, TreeNode *actual_para_list){
	/* Parameter Checking */
	TreeNode* actual_para_dec;

	while(formal_para_list != NULL && actual_para_list != NULL){
		//printf("formal : %s\n",formal_para_list->child[1]->attr.name);
		//printf("actual : %s\n",actual_para_list->child[1]->attr.name);

		if(formal_para_list -> kind.stmt == ParaDecK
				&& actual_para_list -> type != Integer){
			typeError(t,"Formal Parameter is integer variable, but Actual Parameter is not integer");
			formal_para_list = formal_para_list->sibling;
			actual_para_list = actual_para_list->sibling;
			continue;
		}

		if(formal_para_list -> kind.stmt == ParaArrDecK){
			if(actual_para_list -> nodekind != ExpK){
				typeError(t,"Formal Parmaeter is Array, but Actual Parameter is not Array's Name");
				formal_para_list = formal_para_list->sibling;
				actual_para_list = actual_para_list->sibling;
				continue;
			}

			if(actual_para_list -> kind.exp != IdK){
				typeError(t,"Formal Parmaeter is Array, but Actual Parameter is not Array's Name");
				formal_para_list = formal_para_list->sibling;
				actual_para_list = actual_para_list->sibling;
				continue;
			}

			actual_para_dec = actual_para_list -> typeDecNode;
			if(actual_para_dec == NULL){
				typeError(t,"[PASS #1 ERROR] IdK is not connedted to any node");
				formal_para_list = formal_para_list->sibling;
				actual_para_list = actual_para_list->sibling;
				continue;
			}

			if(actual_para_dec -> nodekind != StmtK){
				typeError(t,"[PASS #1 ERROR] IdK is not connected to StmtK");
				formal_para_list = formal_para_list->sibling;
				actual_para_list = actual_para_list->sibling;
				continue;
			}

			if(actual_para_dec -> kind.stmt != ParaArrDecK
					&& actual_para_dec -> kind.stmt != ArrDecK){
				typeError(t,"Formal Parameter is Array, but Actual Parameter is not Array's Name");
				formal_para_list = formal_para_list->sibling;
				actual_para_list = actual_para_list->sibling;
				continue;
			}
		}

		formal_para_list = formal_para_list->sibling;
		actual_para_list = actual_para_list->sibling;
	}

	if(formal_para_list != NULL || actual_para_list != NULL){
		typeError(t,"Formal Parameter's number is not same as Actual Parameter's number");
	}
	/* End of Parameter Checking */
}

static void checkNode(TreeNode * t){
	TreeNode* var_dec_node;
	//if(DEBUG) printf("CheckNode\n");

	switch(t->nodekind){
		case ExpK:
			switch (t->kind.exp){
				case OpK:
					if(DEBUG) printf("OpK\n");
					if((t->child[0] -> type != Integer) ||
							(t->child[1] -> type != Integer)){
						typeError(t,"Op applied to non-integer");
						if(t->child[0] -> type == Integer)
							printf("\t\t\toperand1 is not integer\n");
						else if(t->child[0] -> type == Integer)
							printf("\t\t\toperand2 is not integer\n");
						else
							printf("\t\t\tboth operand is not integer\n");
					}
					if((t->attr.op == EQ) || (t->attr.op == LT) || (t->attr.op == NEQ)
							|| (t->attr.op == LTOE) || (t->attr.op == GT) || (t->attr.op == GTOE))
						t->type = Boolean;
					else
						t->type = Integer;
					break;
				case ConstK:
					if(DEBUG) printf("const: %d\n",t->attr.val);
					t->type = Integer;
					break;
				case IdK:
					//if(DEBUG) printf("ConstK or IdK\n");
					var_dec_node = t->typeDecNode;
					if(DEBUG) printf("Id: %s\n",t->attr.name);

					if(var_dec_node == NULL){
						if(DEBUG) typeError(t,"[PASS #1 ERROR] IdK is not connected to any declaration node");
						t->type = Void;
						return;
					}

					switch(var_dec_node -> kind.stmt){
						case ParaDecK:
						case VarDecK:
							t->type = Integer;
							break;
						case ArrDecK:
						case ParaArrDecK:
						case FunDecK:
							t->type = Void;
							break;
						default:
							typeError(t,"[PASS #1 ERROR] IdK is not connected to ParaDecK,VarDecK,ArrDecK,ParaArrDecK,FunDecK");
					}	
					break;
				case TypeK:
					if(DEBUG) printf("TypeK\n");
					t->type = Void;
					break;
				case AssignK:
					if(DEBUG) printf("AssignK\n");
					/* child[0]이 variable인지 확인*/
					/*if(t->child[0] -> type != Integer)
						typeError(t,"Assign applied to non-integer");
					 */

					if(t->child[0]->kind.exp == IdK){
						var_dec_node = t->child[0]->typeDecNode;
					}
					else if(t->child[0]->kind.exp == ArrK){
						var_dec_node = t->child[0]->child[0]->typeDecNode;
					}
					else{
						typeError(t,"[PASS #1 ERROR] Assignment's lvalue is not IdK or ArrK");
						return;
					}

					if(var_dec_node == NULL){
						typeError(t,"[PASS #1 ERROR] AssignK node is not connected to any declaration node");
						return;
					}

					if(var_dec_node->nodekind != StmtK)
						typeError(t,"[PASS #1 ERROR] Variable is not connected statement kind");

					switch(var_dec_node->kind.stmt){
						case ParaDecK:
						case VarDecK:
						case ParaArrDecK:
						case ArrDecK:
							break;
						default:
							typeError(t,"Assign applied to non-variable");
					}
					if(t->child[0]->type != Integer)
						typeError(t,"L-value is not variable");
					else if(t->child[0]->type == Integer 
							&& (t->child[1]->type != Integer && t->child[1]->type != Boolean))
						typeError(t,"L-value's type is not same as R-value's type");
					
					t->type = t->child[0]->type;

					break;

				case CallK:
					if(DEBUG) printf("CallK\n");
					var_dec_node = t->child[0]->typeDecNode;
					if(var_dec_node == NULL){
						typeError(t,"[PASS #1 ERROR] Function Name is not connected to any declaration node");
						return;
					}
					if(var_dec_node -> nodekind != StmtK)
						typeError(t,"[PASS #1 ERROR] Function Name is not connected statement kind");

					if(var_dec_node -> kind.stmt != FunDecK)
						typeError(t,"Function Call by non-function");

					ParameterChecking(t,var_dec_node->child[2],t->child[1]);

					if(var_dec_node -> child[0] -> attr.op == INT)
						t->type = Integer;
					else
						t->type = Void;

					break;
				
				case InputK:
					t->type = Integer;
					break;

				case OutputK:
					if(t->child[0]->type != Integer)
						typeError(t,"Output value must be integer");
					t->type = Void;
					break;

				case ArrK:
					if(DEBUG) printf("ArrK\n");
					var_dec_node = t->child[0]-> typeDecNode;
					if(var_dec_node == NULL){
						typeError(t,"[PASS #1 ERROR] Array is not connected any declaration node");
						t->type = Integer;
						return;
					}

					if(var_dec_node -> nodekind != StmtK)
						typeError(t,"[PASS #1 ERROR] Array Expression is not connected Statement kind");

					if(var_dec_node -> kind.stmt != ParaArrDecK
							&& var_dec_node -> kind.stmt != ArrDecK)
						typeError(t,"Array expression is applied to non-array name");

					if(t->child[1] -> type != Integer)
						typeError(t,"Array index is not Integer");

					t->type = Integer;
					break;

				default:
					break;
			}
			break;
		case StmtK:
			if(DEBUG) printf("StmtK\n");
			switch(t->kind.stmt){
				case ParaDecK:
				case VarDecK:
				case ParaArrDecK:
				case ArrDecK:
					if(t->child[0]->attr.op == VOID)
						typeError(t,"Parameter, Variable or Array Declare in type Void");

					t->type = Void;
					break;

				case FunDecK:
					if(findMainFlag == TRUE)
						typeError(t,"main function must be declared at the end");

					if(strcmp(t->child[1]->attr.name,"main") == 0){
						/* find main function */
						findMainFlag = TRUE;

						if(t->child[0]->attr.op != VOID)
							typeError(t,"function main's return type must be void");

						if(t->child[2] != NULL && t->child[2]->attr.op != VOID)
							typeError(t,"function main can't have any parameter");
					}
				case CompoundK:
				case ExpStmtK:
					t->type = Void;
					break;

				case SelectK:
				case IterK:
					if(t->child[0]->type != Integer
							&& t->child[0]->type != Boolean)
						typeError(t,"Condition is not both Integer and Boolean");

					t->type = Void;
					break;

				case ReturnK:
					/* Need Function Declaration's infomation*/
					var_dec_node = t->typeDecNode;
					if(DEBUG) printf("Function Name: %s\n",var_dec_node->child[1]->attr.name);
					if(var_dec_node == NULL){
						typeError(t,"[PASS #1 ERROR] Return node is not connected to any declaration node");
						return;
					}

					if(var_dec_node->nodekind != StmtK
							|| var_dec_node->kind.stmt != FunDecK)
						typeError(t,"[PASS #1 ERROR] ReturnK node is not connected to FunDecK");

					if(var_dec_node->child[0]->attr.op == VOID) //return void
						typeError(t,"Function which of return type is void can't have return statement");

					if(t->child[0] != NULL){
						if(t->child[0] -> type != Integer)
							typeError(t,"Return value must be integer type");

						if(var_dec_node -> child[0] -> attr.op != INT)
							typeError(t,"Return value is integer value but Function Declaration's return type is not int");

					}

					t->type = Void;
					break;
				default:
					break;
			}
			break;
		default:
			break;
	}
}

void typeCheck(TreeNode * syntaxTree){
	traverse(syntaxTree, nullProc, checkNode);
}
