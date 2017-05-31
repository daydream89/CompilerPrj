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
				case AssignK:
				{
					if(st_lookup(t->attr.name) == -1)
						st_insert(t->attr.name, t->lineno, location++);
					else
						st_insert(t->attr.name, t->lineno, 0);

					TreeNode *decNode = findDeclaration(t->attr.name);
					if(decNode != NULL)
						t->typeDecNode = decNode;
				}break;

				// 변수 선언. TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case VarDecK:
				{
					insertDeclarationList(t);
				}break;

				// 함수 선언. TreeNode를 저장해두고 st_insert할 때 typeDecNode에 넣어준다.
				case FunDecK:
				{
					insertDeclarationList(t);
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
				}break;

				default:
				break;
			}
		}break;

		default:
		break;
	}
}

static void traverse(TreeNode *t, void(* preProc)(TreeNode *), void(* postProc)(TreeNode*))
{
	int i;

	if(t != NULL)
	{
		preProc(t);

		for(i=0; i<MAXCHILDREN; ++i)
			traverse(t->child[i], preProc, postProc);

		postProc(t);

		traverse(t->child[i], preProc, postProc);
	}
}

void buildSymtab_pass1(TreeNode *syntaxTree)
{
	traverse(syntaxTree, insertNode, nullProc);
	printSymTab(listing);
}
