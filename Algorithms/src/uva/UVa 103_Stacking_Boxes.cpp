#include "CommonHeader.h"


#ifdef UVA_103_STACKING_BOXES
READ_INPUT(UVA_103_STACKING_BOXES)

#include <iostream>
#include <queue>
#include <cstdio>
#include <algorithm>

using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define NINF -1000000

#define MAXK 31

int K, N;

queue<int> g_Queue;
queue<int> g_MaxQueue;

class Box
{
public: 
	int edge[10];
	int m_ID;
};


Box g_Boxes[MAXK];

int g_Graph[MAXK][MAXK];

bool g_Visit[MAXK];
int g_Dist[MAXK];
int lis[MAXK];
int g_Ind[MAXK];

bool isFit(int j, int k);

void reset()
{
	FOR(i, 0, MAXK)
	{
		FOR(j, 0, 10)
			g_Boxes[i].edge[j] = 0;

		FOR(j, 0, MAXK)
			g_Graph[i][j] = 0;

		g_Visit[i] = 0, g_Dist[i] = NINF;
	}

	while (!g_MaxQueue.empty()) g_MaxQueue.pop();
	while (!g_Queue.empty()) g_Queue.pop();
}
void SWP(int k, int l, int r)
{
	int tmp = g_Boxes[k].edge[l];
	g_Boxes[k].edge[l] = g_Boxes[k].edge[r];
	g_Boxes[k].edge[r] = tmp;
}
int partition(int k, int l, int r)
{
	int x = r;
	int i = l-1;

	FOR(j, l, r)
	{
		if(g_Boxes[k].edge[j] < g_Boxes[k].edge[x])
		{
			i++;
			SWP(k, i, j);
		}
	}

	SWP(k, i+1, r);
	return i+1;
}
void QSort(int k, int l, int r)
{
	if(l < r)
	{
		int p = partition(k, l, r);
		QSort(k, l, p-1);
		QSort(k, p+1, r);
	}
}

bool BxCompare(int j, int k)
{
	unsigned long long a1 = 1;
	unsigned long long a2 = 1;

	FOR(i, 0, N) a1 *= g_Boxes[j].edge[i];
	FOR(i, 0, N) a2 *= g_Boxes[k].edge[i];

	if(isFit(j,k) /*&& a1 < a2*/)
		return true;

	return false;
}
void BxSWP(int k, int j)
{
	Box tmp = g_Boxes[k];
	g_Boxes[k] = g_Boxes[j];
	g_Boxes[j] = tmp;
}
int Bxpartition(int l, int r)
{
	int x = r;
	int i = l-1;

	FOR(j, l, r)
	{
		if(BxCompare(j,x))
		{
			i++;
			BxSWP(i, j);
		}
	}

	BxSWP(i+1, r);
	return i+1;
}
void BxQSort(int l, int r)
{
	if(l < r)
	{
		int p = Bxpartition(l, r);
		BxQSort(l, p-1);
		BxQSort(p+1, r);
	}
}

// If j is smaller box than k
bool isFit(int j, int k)
{
	FOR(i, 0, N)
	{
		if(g_Boxes[j].edge[i] >=  g_Boxes[k].edge[i])
			return false;
	}
	return true;
}

int main()
{
	while (scanf("%d %d", &K, &N) != EOF)
	{
		reset();

		FOR(k, 0, K)
		{
			FOR(n, 0, N)
				scanf("%d", &g_Boxes[k].edge[n]);
			g_Boxes[k].m_ID = k+1;
			QSort(k, 0, N-1);
		}

		BxQSort(0,K-1);
	
		FOR(i, 0, K)
			lis[i] = 1;

		FOR(i, 1, K)
		{
			FOR(j, 0, i)
			{
				if(isFit(j, i) && lis[i] < lis[j] + 1)
					lis[i] = lis[j]+1, g_Ind[i] = j;
			}
		}
		
		int max = -1000000, maxI = -1;
		FOR(i, 0, K)
			if(max < lis[i]) max = lis[i], maxI = i;

		printf("%d\n", max);


		int RevID[MAXK];

		FOR(i, 0, max)
		{
			RevID[i] = g_Boxes[maxI].m_ID;
			maxI = g_Ind[maxI];
		}

		for(int i = max; i; --i)
		{
			printf("%d ", RevID[i-1]);
		}
		printf("\n");
	}

	return 0;
}

#endif