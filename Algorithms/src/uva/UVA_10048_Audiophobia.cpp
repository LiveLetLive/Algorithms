#include "CommonHeader.h"

#ifdef UVA_10048_AUDIOPHOBIA
READ_INPUT(UVA_10048_AUDIOPHOBIA)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN (1005*2)
#define INF 0x3f3f3f3f

class Edge
{
public:
	int x, y;
	int w;
};

Edge e[MAXN];

int g[MAXN][MAXN];
int p[MAXN];
bool vis[MAXN];
int rnk[MAXN];

int C, S, Q;


void reset()
{
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = 0;

		p[i] = -1;
		vis[i] = 0;
	}
}

bool comp(Edge& e1, Edge& e2)
{
	return e1.w < e2.w;
}

int find(int v)
{
	if(p[v] == -1) return v;
	else return p[v] = find(p[v]);
}

void Union(int v1, int v2)
{
	if(rnk[v1] > rnk[v2])
		p[v2] = v1;
	else
	{
		p[v1] = v2;
		if(rnk[v1] == rnk[v2]) rnk[v2]++;
	}
}

void mst()
{
	FOR(i, 0, S)
	{
		int v1 = e[i].x;
		int v2 = e[i].y;
		int w1 = e[i].w;

		int pv1 = find(v1);
		int pv2 = find(v2);

		if(pv1 == pv2) continue;

		g[v1][v2] = g[v2][v1] = w1;
		Union(pv1, pv2);
	}
}

int findMax(int u, int target, int& maxVal)
{
	if(u == target)
		return 1;

	vis[u] = true;
	int found = false;

	FOR(v, 0, C+1)
	{
		if(g[u][v] && vis[v] == 0)
		{
			found = findMax(v, target, maxVal);
			if(found != -1)
				return maxVal = max(maxVal, g[u][v]);
		}
	}

	return -1;
}

int main()
{
	while(scanf("%d %d %d ", &C, &S, &Q), C, S, Q)
	{
		static int tc  = 0;

		if(tc > 0)
			printf("\n");
		tc++;
		reset();

		printf("Case #%d\n", tc);

		FOR(i, 0, S)
		{
			int x, y, w;
			scanf("%d %d %d ", &x, &y, &w);

			e[i].x = x;
			e[i].y = y;
			e[i].w = w;
		}

		sort(e, e+S, comp);
		mst();

		FOR(i, 0, Q)
		{
			int x, y;
			scanf("%d %d ", &x, &y);

			if(find(x) != find(y))
			{
				printf("no path\n");
				continue;
			}
			else
			{
				int f = -1;

				FOR(j, 0, C+1) vis[j] = 0;

				int maxVal = findMax(x, y, f);

				FOR(j, 0, C+1) vis[j] = 0;

				if(maxVal == -1)
					maxVal = findMax(y, x, f);

				printf("%d\n", f);
			}
		}

	}

	return 0;
}

#endif