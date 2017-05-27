#include "globals.h"
#include "util.h"

TreeNode *CreateTempSymbolTable()
{
	TreeNode *syntaxTree = NULL;
	TreeNode *tempNode = NULL;
	TreeNode *siblingFinder = NULL;
	TreeNode *sibling = NULL;
	TreeNode *typeScopeNode = NULL;

	syntaxTree = newStmtNode(FunDecK);
	
	syntaxTree->child[0] = newExpNode(TypeK);
	syntaxTree->child[0]->attr.op = VOID;

	syntaxTree->child[1] = newExpNode(IdK);
	syntaxTree->child[1]->attr.name = copyString("main");

	syntaxTree->child[2] = newExpNode(TypeK);
	syntaxTree->child[2]->attr.op = VOID;

	syntaxTree->child[3] = newStmtNode(CompoundK);
	tempNode = syntaxTree->child[3];

	sibling = newStmtNode(VarDecK);
	sibling->child[0] = newExpNode(TypeK);
	sibling->child[0]->attr.op = INT;

	sibling->child[1] = newExpNode(IdK);
	sibling->child[1]->attr.name = copyString("a");
	
	typeScopeNode = sibling;

	tempNode->child[0] = sibling;
	
	//siblingFinder = tempNode->sibling;
	//while(siblingFinder != NULL)
	//	siblingFinder = siblingFinder->sibling;
	//siblingFinder->sibling = sibling;

	TreeNode *sibling2 = NULL;
	sibling2 = newExpNode(AssignK);
	sibling2->child[0] = newExpNode(IdK);
	sibling2->child[0]->attr.name = copyString("a");
	sibling2->child[1] = newExpNode(ConstK);
	sibling2->child[1]->attr.val = 1;
	
	//siblingFinder = tempNode->child[0]->sibling;
	//while(siblingFinder != NULL)
	//	siblingFinder = siblingFinder->sibling;
	//siblingFinder = sibling2;
	sibling->sibling = sibling2;

	TreeNode *sibling3 = NULL;
	sibling3 = newStmtNode(IterK);
	sibling3->child[0] = newExpNode(OpK);
	sibling3->child[0]->attr.op = LT;

	sibling3->child[0]->child[0] = newExpNode(IdK);
	sibling3->child[0]->child[0]->attr.name = copyString("a");
	sibling3->child[0]->child[0]->typeDecNode = typeScopeNode;
	
	sibling3->child[0]->child[1] = newExpNode(ConstK);
	sibling3->child[0]->child[1]->attr.val = 10;

	sibling3->child[1] = newExpNode(AssignK);
	sibling3->child[1]->child[0] = newExpNode(IdK);
	sibling3->child[1]->child[0]->attr.name = copyString("a");
	sibling3->child[1]->child[0]->typeDecNode = typeScopeNode;

	sibling3->child[1]->child[1] = newExpNode(OpK);
	sibling3->child[1]->child[1]->attr.op = PLUS;
	
	sibling3->child[1]->child[1]->child[0] = newExpNode(IdK);
	sibling3->child[1]->child[1]->child[0]->attr.name = copyString("a");
	sibling3->child[1]->child[1]->child[0]->typeDecNode = typeScopeNode;
	
	sibling3->child[1]->child[1]->child[1] = newExpNode(ConstK);
	sibling3->child[1]->child[1]->child[1]->attr.val = 1;

	//siblingFinder = tempNode->child[0]->sibling;
	//while(siblingFinder != NULL)
	//	siblingFinder = siblingFinder->sibling;
	//siblingFinder = sibling3;
	sibling2->sibling = sibling3;
	
	TreeNode *sibling4 = NULL;
	sibling4 = newStmtNode(ReturnK);

	//siblingFinder = tempNode->child[0]->sibling;
	//while(siblingFinder != NULL)
	//	siblingFinder = siblingFinder->sibling;
	//siblingFinder = sibling4;
	sibling3->sibling = sibling4;

	return syntaxTree;
}
