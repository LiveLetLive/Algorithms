#include "CommonHeader.h"


#ifdef UVA_12379_CENTRAL_POST_OFFICE
READ_INPUT(UVA_12379_CENTRAL_POST_OFFICE)

#include <iostream>
#include <cstdio>

using namespace std;

#define MAXN 10001
#define FOR(i, init, count) for(int i = init; i < count; i++)

int dist[MAXN];
int tree[MAXN][MAXN];
int cnt[MAXN];
bool vis[MAXN];
int T, N;

void reset()
{
	FOR(i, 0, N+1)
	{
		FOR(j, 0, N+1)
			tree[i][j] = 0;
		dist[i] = 0;
		cnt[i] = 0;
	}
}


void dfs1(int u)
{
	vis[u] = true;

	FOR(j, 0, cnt[u])
	{
		int v = tree[u][j];
		if(vis[v] == true) continue;
		dist[v] = dist[u] + 1;
		dfs1(v);
	}
}

int diameter()
{
	FOR(i, 0, N+1)
		vis[i] = false;

	dist[1] = 0;
	dfs1(1);

	int maxD = 0;
	int maxI = -1;

	FOR(i, 1, N+1)
		if(maxD < dist[i])
			maxD = dist[i], maxI = i;

	FOR(i, 0, N+1)
		vis[i] = false;

	dist[maxI] = 0;
	dfs1(maxI);

	maxD = 0;
	maxI = -1;

	FOR(i, 1, N+1)
		if(maxD < dist[i])
			maxD = dist[i], maxI = i;

	return maxD;
}

int main()
{
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		reset();
		FOR(i, 1, N+1)
		{
			int tmp;
			scanf("%d ", &tmp);
			FOR(j, 0, tmp)
			{
				int e;
				scanf("%d ", &e);
				tree[i][j] = e, cnt[i]++;
			}
		}

		// Twice of the visit per edge + relaxing diameter edges.
		printf("%d\n", (2 * (N-1)) - diameter());
	}

	return 0;
}


#endif