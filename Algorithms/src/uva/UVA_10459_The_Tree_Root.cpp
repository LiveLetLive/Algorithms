#include "CommonHeader.h"

#ifdef UVA_10459_THE_TREE_ROOT
READ_INPUT(UVA_10459_THE_TREE_ROOT)

#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <stack>
#include <bitset>

#define MAXN 5005
	int g[MAXN][MAXN];
int vis[MAXN];
int dist[MAXN];
#define FOR(i, init, count) for(int i = init; i < count; i++)
int N;
std::stack<int> s;

void reset()
{
	FOR(i, 0, N)
		FOR(j, 0, N)
		g[i][j] = 0;
}

void dfs1(int u)
{
	vis[u] = true;

	FOR(v, 0, N)
	{
		if(u == v) continue;

		if(g[u][v])
		{
			if(vis[v]) continue;
			dist[v] = dist[u] + 1;
			dfs1(v);
		}
	}

	s.push(u);
}

int diameter()
{
	while(!s.empty()) s.pop();
	dist[0] = 0;
	dfs1(0);
	
	int maxD = -1;
	int maxIdx = 0;
	
	FOR(i, 0, N)
		if(maxD < dist[i])
			maxD = dist[i], maxIdx = i;

	FOR(i, 0, N)
		dist[i] = 0, vis[i] = 0;

	while(!s.empty()) s.pop();
	dfs1(maxIdx);

	maxD = -1;
	int maxIdx1 = 0;
	
	FOR(i, 0, N)
	{
		if(maxD < dist[i])
			maxD = dist[i], maxIdx1 = i;
	}

	printf("%d", maxD);

	return maxD;
}

int main()
{
	while (scanf("%d ", &N) != EOF)
	{
		reset();
		FOR(i, 0, N)
		{
			int cnt, tmp;
			scanf("%d ", &cnt);

			FOR(j, 0, cnt)
				scanf("%d ", &tmp), g[i][tmp] = 1, g[tmp][i] = 1;
		}

		int d = diameter();

	}
	return 0;
}



#endif