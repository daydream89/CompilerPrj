#include "globals.h"
#include "symtab.h"
#include "buildSymtab.h"
#include "cminus.tab.h"

static int location = 0;
static int global_location = 0;

static int AfterDec = FALSE;
static TreeNode* lastFuncDec = NULL;
static TreeNode* lastDec = NULL;
static int scope = 0;

static void nullProc(TreeNode *t)
{
	if (t == NULL)
		return;
	else
		return;
}

static void insertNode(TreeNode *t)
{
	if(t == NULL)
	{
		fprintf(listing, "TreeNode is NULL in insertNode function.\n");
		return;
	}

	switch(t->nodekind)
	{
		case StmtK:
		{
			switch(t->kind.stmt)
			{
				// 변수 선언.
				// TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case VarDecK:
				{
					AfterDec = TRUE;
					lastDec = t;
				}break;

				// 배열 변수 선언.
				// TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case ArrDecK:
				{
					AfterDec = TRUE;
					lastDec = t;
				}break;

				case ParaDecK:
				{
					AfterDec = TRUE;
					lastDec = t;
				}break;

				case ParaArrDecK:
				{
					AfterDec = TRUE;
					lastDec = t;
				}break;

				// 함수 선언.
				// TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case FunDecK:
				{
					AfterDec = TRUE;
					lastFuncDec = t;
					lastDec = t;
				}break;

				// {} 괄호 내부의 statement.
				case CompoundK:
				{
				}break;

				// return 문. 함수와 연결.
				case ReturnK:
				{
					TreeNode *decNode = lastFuncDec;
					if(decNode != NULL)
						t->typeDecNode = decNode;
				}break;

				default:
				break;
			}
		}break;

		case ExpK:
		{
			switch(t->kind.exp)
			{
				case IdK:
				{
					int array_size;
					ExpType type;
					TreeNode *decNode = NULL; /*findDeclaration(t->attr.name);*/

					if(AfterDec == TRUE){
						int array_size = 0;
						ExpType return_type=Integer;

						if(lastDec->kind.stmt == ArrDecK)
							array_size = lastDec->child[2]->attr.val;

						if(lastDec->kind.stmt == FunDecK && lastDec->child[0]->attr.op == VOID)
							return_type = Void;
						
						if(scope == 0)
							insertDeclaration(t->attr.name, t->lineno, global_location++,scope,lastDec->kind.stmt,array_size,return_type,lastDec);
						else
							insertDeclaration(t->attr.name, t->lineno, location++,scope,lastDec->kind.stmt,array_size,return_type,lastDec);
						
						lastDec = NULL;
						AfterDec = FALSE;

						return;
					}

					decNode = findDeclaration(t->attr.name);

					if(decNode == NULL)
					{
						fprintf(listing, "this id is not assigned! id:%s\n", t->attr.name);
						Error = TRUE;
						return;
					}

					if(decNode->kind.stmt == ArrDecK){
						array_size = decNode->child[2]->attr.val;
					}else{
						array_size = 0;
					}

					if(decNode->kind.stmt == FunDecK){
						switch(decNode->child[0]->attr.op){
							case INT: type = Integer; break;
							case VOID: type = Void; break;
							default: fprintf(listing, "Function's return type is not int and void");
						}
					}else{
						type = Integer;
					}

					st_insert(t->attr.name, t->lineno);
					
					t->typeDecNode = decNode;
				}break;

				default:
				break;
			}
		}break;

		default:
		break;
	}
}

static TreeNode *paramNode = NULL;

static void traverse(TreeNode *t, void(* preProc)(TreeNode *), void(* postProc)(TreeNode*))
{
	int i;
	if(Error)
		return;

	if(t != NULL)
	{
		unsigned int isCompound = FALSE;
		if(t->nodekind == StmtK && t->kind.stmt == CompoundK)
		{
			st_create();
			isCompound = TRUE;
			scope++;
			location=0;

			if(paramNode != NULL)
			{
				traverse(paramNode, preProc, postProc);
				if(Error) return;
				paramNode = NULL;
			}
		}

		// parameter를 scope 안으로 포함시키기 위해 탐색을 유보.
		if(paramNode == NULL)
		{
			if(t->nodekind == StmtK && (t->kind.stmt == ParaDecK || t->kind.stmt == ParaArrDecK))
			{
				paramNode = t;
				return;
			}
		}

		preProc(t);
		if(Error) return;

		for(i=0; i<MAXCHILDREN; ++i)
			traverse(t->child[i], preProc, postProc);

		postProc(t);
		
		if(isCompound == TRUE)
		{
			printSymTab(listing);
			st_remove();
			scope--;
		}

		traverse(t->sibling, preProc, postProc);
	}
}

void buildSymtab_pass1(TreeNode *syntaxTree)
{
	st_create();
	traverse(syntaxTree, insertNode, nullProc);
	printSymTab(listing);

	removeAllDeclarationList();
}
