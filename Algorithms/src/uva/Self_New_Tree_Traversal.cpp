#include "CommonHeader.h"

#ifdef SELF_NEW_TREE_TRAVERSAL
READ_INPUT(SELF_NEW_TREE_TRAVERSAL)

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
#define MAXN 100003
#define INF 0x3f3f3f3fL
typedef long long ll;

class Node;

Node *g_nodes[MAXN];

int FindLCA(int i, int j);

class Node
{
public:
	Node(int id) 
	{
		m_id = id; 
		firstChild = NULL, lastChild = NULL; 
		sibling = NULL; 
		level = 0;
	}

	int m_id;
	Node *firstChild;
	Node *lastChild;
	Node *sibling;
	int level;
	int childCnt;

	void insertChild (int id)
	{
		if(firstChild == NULL)
		{
			Node *n = new Node(id);
			n->level = level + 1;
			firstChild = lastChild = n;
			g_nodes[id] = n;
		}
		else
		{
			Node *n = new Node(id);
			n->level = level + 1;
			lastChild->sibling = n;
			lastChild = n;
			g_nodes[id] = n;
		}
	}
};

int N, idx;
int arrOccur[MAXN*2];
int arrDepth[MAXN*2];
int arrSeq[MAXN*2];

void dfs(int curr, int depth)
{
	arrOccur[curr] = idx;
	arrSeq[idx] = curr;
	arrDepth[idx++] = depth;

	Node* x = g_nodes[curr]->firstChild;

	if(x)
	{
		dfs(x->m_id, depth+1);
		arrSeq[idx] = curr;
		arrDepth[idx++] = depth;

		while(x->sibling)
		{
			x = x->sibling;
			dfs(x->m_id, depth+1);
			arrSeq[idx] = curr;
			arrDepth[idx++] = depth;
		}
	}
}

int bfs()
{
	queue<int> q;
	queue<int> seq;

	q.push(1);
	seq.push(1);

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		Node *x = g_nodes[u]->firstChild;

		if(x)
			q.push(x->m_id), seq.push(x->m_id);

		while(x && x->sibling)
		{
			x = x->sibling;
			q.push(x->m_id), seq.push(x->m_id);
		}
	}

	int sum = 0;
	int u = seq.front();
	seq.pop();

	while(!seq.empty())
	{
		int v = seq.front();
		seq.pop();

		int n1 = FindLCA(u, v);
		int level1 = g_nodes[u]->level - g_nodes[n1]->level;
		int level2 = g_nodes[v]->level - g_nodes[n1]->level;
		sum += (level1 + level2);
		u = v;
	}

	return sum;
}

void reset()
{
	FOR(i, 0, N+1)
		g_nodes[i] = NULL;
}

void PrintLCArr()
{
	FOR(i, 0, 2*N+1)
		printf("%2d ", arrOccur[i+1]);
	cout << endl;
	FOR(i, 0, 2*N+1)
		printf("%2d ", arrSeq[i+1]);
	cout << endl;
	FOR(i, 0, 2*N+1)
		printf("%2d ", arrDepth[i+1]);
	cout << endl;

}

void PrepareLCA()
{
	idx = 1;
	dfs(1, 0);
}


void DeleteTree(Node* curr)
{
	if(curr == NULL) 
		return;

	DeleteTree(curr->sibling);
	DeleteTree(curr->firstChild);
	delete curr;
}

Node* root = NULL;

void PrintBfs(Node * curr)
{
	if(curr == NULL) 
		return;

	cout << curr->m_id << "\t";
	PrintBfs(curr->sibling);
	PrintBfs(curr->firstChild);
}

int FindLCA(int i, int j)
{
	int S = arrOccur[i];
	int E = arrOccur[j];

	if(S > E)
		swap(S, E);

	int minD = MAXN;
	int minI = MAXN;

	FOR(x, S, E+1)
		if(minD > arrDepth[x])
			minD = arrDepth[x], minI = x;

	return arrSeq[minI];
}


int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		reset();

		root = new Node(1);
		g_nodes[1] = root;

		FOR(i, 0, N-1)
		{
			int p = 0;
			scanf("%d ", &p);

			if(g_nodes[p])
				g_nodes[p]->insertChild(i+2);
		}

		PrepareLCA();
		int sum = 0;

		sum = bfs();

		cout << "#" << t << " " << sum << endl;

		DeleteTree(root);
	}
	return 0;
}

#endif
