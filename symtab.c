#include "globals.h"

#include <stdio.h>

#define SIZE 211

#define SHIFT 4

static int hash(char *key)
{
	int temp = 0;
	int i = 0;
	while (key[i] != '\0')
	{
		temp = ((temp << SHIFT) + key[i]) % SIZE;
		++i;
	}

	return temp;
}

typedef struct LineListRec
{
	int lineno;
	struct LineListRec *next;
}* LineList;

typedef struct BucketListRec
{
	char *name;
	LineList lines;
	int memloc;
	struct BucketListRec *next;
}* BucketList;

typedef struct ExpandHash
{
	struct ExpandHash *next;
	BucketList *hash;
}ExpandHash;

typedef struct DeclarationList
{
	char *name;
	StmtKind type;
	TreeNode *node;
	struct DeclarationList *next;
}DeclarationList;

static ExpandHash gs_expandHashTable;

static DeclarationList gs_decList;

void st_create()
{
	ExpandHash *expandHashNode = (ExpandHash *)malloc(sizeof(ExpandHash));
	BucketList *hashTable = (BucketList *)malloc(SIZE*sizeof(BucketList));
	expandHashNode->hash = hashTable;

	if(gs_expandHashTable.next != NULL)
	{
		ExpandHash *nextHash = gs_expandHashTable.next;
		gs_expandHashTable.next = expandHashNode;
		expandHashNode->next = nextHash;
	}
	else
		gs_expandHashTable.next = expandHashNode;
}

void removeHash(BucketList *hash)
{
	hash;
}

void st_remove()
{
	if(gs_expandHashTable.next != NULL)
	{
		ExpandHash *exHash = gs_expandHashTable.next;
		if(exHash->next != NULL)
		{
			ExpandHash *exNext = exHash->next;
			removeHash(exHash->hash);
			free(exHash);
			gs_expandHashTable.next = exNext;
		}
		else
		{
			removeHash(exHash->hash);
			free(exHash);
			gs_expandHashTable.next = NULL;
		}
	}
}

void st_insert(char *name, int lineno, int loc)
{
	int h = hash(name);
	ExpandHash *exHash = gs_expandHashTable.next;
	if(exHash == NULL)
	{
		fprintf(listing, "exand hash table is NULL!\n");
		return;
	}

	while(exHash != NULL)
	{
		BucketList l = exHash->hash[h];

		while((l != NULL) && (strcmp(name, l->name) != 0))
			l = l->next;
	
		if(l != NULL)
		{
			LineList t = l->lines;
			while(t->next != NULL)
				t = t->next;
			
			if(t->lineno != lineno)
			{
				t->next = (LineList)malloc(sizeof(struct LineListRec));
				t->next->lineno = lineno;
				t->next->next = NULL;
			}

			return;
		}
	
		exHash = exHash->next;
	}
	
	BucketList l = gs_expandHashTable.next->hash[h];

	l = (BucketList)malloc(sizeof(struct BucketListRec));
	l->name = name;
	l->lines = (LineList)malloc(sizeof(struct LineListRec));
	l->lines->lineno = lineno;
	l->memloc = loc;
	l->lines->next = NULL;
	l->next = gs_expandHashTable.next->hash[h];
	gs_expandHashTable.next->hash[h] = l;

}

int st_lookup(char *name)
{
	int h = hash(name);
	ExpandHash *exHash = gs_expandHashTable.next;
	BucketList l = NULL;
	while(exHash != NULL)
	{
		unsigned int isFound = FALSE;
		BucketList l = exHash->hash[h];
		while(l != NULL)
		{
			if(strcmp(name, l->name) == 0)
			{
				isFound = TRUE;
				break;
			}
			else
				l = l->next;
		}

		if(isFound == TRUE)
			break;
		else
			exHash = exHash->next;
	}

	if(l == NULL)
		return -1;
	else
		return l->memloc;
}

TreeNode *findDeclaration(char *name)
{
	DeclarationList *list = gs_decList.next;
	while(list != NULL)
	{
		if(strcmp(name, list->name) == 0)
			return list->node;
		else
			list = list->next;
	}

	return NULL;
}

TreeNode *findLastFuncDec()
{
	TreeNode *decNode = NULL;
	DeclarationList *list = gs_decList.next;
	while(list != NULL)
	{
		if((list->type == FunDecK))
			decNode = list->node;

		list = list->next;
	}

	return decNode;
}

// VarDecK와 FunDecK node를 받아서 gs_decList에 저장한다.
// 중복에 대한 에러 처리도 함께 한다.
void insertDeclarationList(TreeNode *node, StmtKind type)
{
	if(node == NULL)
		return;

	if(node->child[1] == NULL)
		return;

	TreeNode *checkNode = findDeclaration(node->child[1]->attr.name);
	if(checkNode != NULL)
	{
		if(checkNode->nodekind == node->nodekind)
		{
			// declaration duplicate error!
			fprintf(listing, "Declaration duplicated! name:%s\n", node->child[1]->attr.name);
			return;
		}
	}

	DeclarationList *decNode = (DeclarationList *)malloc(sizeof(DeclarationList));
	if(decNode != NULL)
	{
		decNode->name = copyString(node->child[1]->attr.name);
		decNode->type = type;
		decNode->node = node;

		DeclarationList *list = &gs_decList;
		while(list->next != NULL)
			list = list->next;

		list->next = decNode;
	}
}

void removeAllDeclarationList()
{
	while(gs_decList.next != NULL)
	{
		DeclarationList *tmp = gs_decList.next;
		if(tmp->next != NULL)
		{
			DeclarationList *tmp2 = tmp->next;
			free(tmp);
			gs_decList.next = tmp2;
		}
		else
		{
			free(tmp);
			gs_decList.next = NULL;
		}
	}
}

void printSymTab(FILE *listing)
{
	int i;
	fprintf(listing, "Variable Name Location Line Numbers\n");
	fprintf(listing, "------------- -------- ------------\n");

	ExpandHash *exHash = gs_expandHashTable.next;
	if(exHash == NULL)
	{
		fprintf(listing, "expand hash for print is null");
		return;
	}

	for(i=0; i<SIZE; ++i)
	{
		if(exHash->hash[i] != NULL)
		{
			BucketList l = exHash->hash[i];
			while(l != NULL)
			{
				LineList t = l->lines;
				fprintf(listing, "%-14s ", l->name);
				fprintf(listing, "%-8d  ", l->memloc);

				while(t != NULL)
				{
					fprintf(listing, "%4d", t->lineno);
					t = t->next;
				}

				fprintf(listing, "\n");
				l = l->next;
			}
		}
	}
}
