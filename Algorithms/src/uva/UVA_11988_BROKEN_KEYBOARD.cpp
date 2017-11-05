#include "CommonHeader.h"

#ifdef UVA_11988_BROKEN_KEYBOARD
READ_INPUT(UVA_11988_BROKEN_KEYBOARD)

#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 1003
#define INF 0x3f3f3f3fL
typedef long long ll;


class Node;

class Node
{
public:
	Node()
	{
		p = NULL, n = NULL;
		sidx = eidx = 0;
	}
	Node *p;
	Node *n;
	int sidx;
	int eidx;
};

Node* getFirst(Node *n)
{
	while(n && n->p)
		n = n->p;

	return n;
}

Node* getLast(Node *n)
{
	while(n && n->n)
		n = n->n;

	return n;
}

Node* root = NULL;
char s[100005];

void reset()
{
	memset(s, 0, sizeof(s));

	Node *n = getFirst(root);

	if(n)
	{
		while(n && n->n)
		{
			Node* tmp = n->n;
			delete n;
			n = tmp;
		}
	}

	root = new Node;
}

int main()
{
	//freopen("out.txt", "w", stdout);
	while(1)
	{
		reset();
		int ans = scanf("%s ", &s);

		if(ans == EOF)
			break;

		int len = strlen(s);
		int idx = 0;

		Node* n = root;

		FOR(i, 0, len)
		{
			if(s[idx] == '[')
			{
				Node *tmp = getFirst(n);

				/*if((n != tmp) || ((n->eidx - n->sidx) > 0))*/
				{
					n->eidx = i-1;
					Node* next = new Node;
					next->n = tmp;
					tmp->p = next;
					next->sidx = i+1;
					n = next;
				}
			}
			else if(s[idx] == ']')
			{
				Node *tmp = getLast(n);

				if(n != tmp)
				{
					n->eidx = i-1;
					Node* next = new Node;
					next->p = tmp;
					tmp->n = next;
					next->sidx = i+1;
					n = next;
				}
			}

			idx++;
		}

		n->eidx = idx-1;
		n = getFirst(n);

		while(n)
		{
			FOR(i, n->sidx, n->eidx+1)
				if(s[i] == '[' || s[i] == ']')
					continue;
				else	
					printf("%c", s[i]);

			n = n->n;
		}

		printf("\n");
	}

	return 0;
}

#endif
