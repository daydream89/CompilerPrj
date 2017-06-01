#include "globals.h"
#include "symtab.h"
#include "buildSymtab.h"

static int location = 0;

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
					insertDeclarationList(t, VarDecK);
				}break;

				// 배열 변수 선언.
				// TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case ArrDecK:
				{
					insertDeclarationList(t, ArrDecK);
				}break;

				case ParaDecK:
				{
					insertDeclarationList(t, ParaDecK);
				}break;

				case ParaArrDecK:
				{
					insertDeclarationList(t, ParaArrDecK);
				}break;

				// 함수 선언.
				// TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case FunDecK:
				{
					insertDeclarationList(t, FunDecK);
				}break;

				// {} 괄호 내부의 statement.
				case CompoundK:
				{
				}break;

				// return 문. 함수와 연결.
				case ReturnK:
				{
					TreeNode *decNode = findLastFuncDec();
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
					if(st_lookup(t->attr.name) == -1)
						st_insert(t->attr.name, t->lineno, location++);
					else
						st_insert(t->attr.name, t->lineno, 0);
					
					TreeNode *decNode = findDeclaration(t->attr.name);
					if(decNode != NULL)
						t->typeDecNode = decNode;
					else
						fprintf(listing, "this id is not assigned! id:%s\n", t->attr.name);
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

	if(t != NULL)
	{
		unsigned int isCompound = FALSE;
		if(t->nodekind == StmtK && t->kind.stmt == CompoundK)
		{
			st_create();
			isCompound = TRUE;

			if(paramNode != NULL)
			{
				traverse(paramNode, preProc, postProc);
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

		for(i=0; i<MAXCHILDREN; ++i)
			traverse(t->child[i], preProc, postProc);

		postProc(t);
		
		if(isCompound == TRUE)
		{
			printSymTab(listing);
			st_remove();
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
