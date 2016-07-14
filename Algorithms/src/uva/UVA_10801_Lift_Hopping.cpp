#include "CommonHeader.h"


#ifdef UVA_10801_LIFT_HOPPING
READ_INPUT(UVA_10801_LIFT_HOPPING)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;


#define MAXN 105
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define INF 1000000000
int g[MAXN][MAXN];
int dist[MAXN];
bool in_queue[MAXN];

int M, W, mf;
int s , t, k, n;

void reset()
{
	mf = 0;
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = INF;
		dist[i] = INF;
	}
}

int spfa()
{
	FOR(i, 0, MAXN)
		dist[i] = INF, in_queue[i] = false;
	queue<int> q;
	dist[0] = 0;
	q.push(0);
	in_queue[0] = true;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		in_queue[u] = false;
		FOR(v, 0, 99)
		{
			if(u == v) continue;
			if(g[u][v] == INF) continue;

			if(dist[v] > dist[u] + g[u][v] + 60) 
			{
				dist[v] = dist[u] + g[u][v] + 60;
				if(in_queue[v] == false)
					in_queue[v] = true, q.push(v);
			}
		}
	}

	return dist[k];
}

void PrintGraph()
{
#ifdef DEBUG
	FOR(u, 0, 99)
	{
		bool found = false;
		FOR(v, 0, 99)
		{
			if(u == v) continue;
			if(g[u][v] == INF) continue;
			found = true;
			printf("(u=%d, v=%d, guv=%d) ", u, v, g[u][v]);
		}
		if(found)
			printf("\n");
	}
	printf("\n");
	printf("\n");
#endif
}
int main()
{
	while(scanf("%d %d ", &n, &k) == 2)
	{
		int T[5] = { 0, };
		reset();
		FOR(i, 0, n)
			scanf("%d ", &T[i]);

		FOR(i, 0, n)
		{
			char str1[1000];
			int idx[100] = {0};
			int index = 0;
			int node = 0;

			gets(str1);
			string str(str1);

			while(1)
			{
				int cnt = str.find(' ');

				if(cnt == -1) break;

				sscanf(str.c_str(), "%d ", &node);
				str = str.substr(cnt+1);
				idx[index++] = node;
			}

			sscanf(str.c_str(), "%d ", &node);
			idx[index++] = node;

			FOR(k, 0, index)
				FOR(j, k+1, index)
			{
				int u = idx[k];
				int v = idx[j];

				g[u][v] = min(g[u][v], abs(u-v)*T[i]);
				g[v][u]  = g[u][v];
			}
		}


		PrintGraph();
		int ans = spfa();

		if(k == 0) printf("%d\n", 0);
		else if(dist[k] == INF) printf("IMPOSSIBLE\n");
		else printf("%d\n", ans - 60);
	}
	return 0;
}
#endif