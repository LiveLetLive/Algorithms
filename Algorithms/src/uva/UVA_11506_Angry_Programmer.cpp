#include "CommonHeader.h"


#ifdef UVA_11506_ANGRY_PROGRAMMER
READ_INPUT(UVA_11506_ANGRY_PROGRAMMER)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;


#define MAXN (51*2)
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define INF 1000000000
int g[MAXN][MAXN];
int p[MAXN];
int dist[MAXN];

int M, W, mf;
int s , t;

void reset()
{
	mf = 0;
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = 0;

		p[i] = -1;
		dist[i] = INF;
	}
}

bool bfs()
{
	queue<int>q;

	FOR(i, 0, 2*M+1)
		dist[i] = INF;

	dist[1] = 0;
	q.push(1);

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		if(u == M)
			return true;

		FOR(v, 0, 2*M+1)
		{
			if(u == v) continue;
			if(dist[v] == INF && g[u][v] > 0)
			{
				dist[v] = dist[u] + 1;
				p[v] = u;
				q.push(v);
			}
		}
	}

	return false;
}

void augment(int v, int& minEdge)
{
	if(p[v] == -1) return;

	int pu = p[v];

	if(minEdge > g[pu][v])
		minEdge = g[pu][v];

	augment(pu, minEdge);

	g[pu][v] -= minEdge;
	g[v][pu] += minEdge;
}

void maxflow()
{
	while(bfs())
	{
		int f = INF;
		augment(M, f);

		if(f == 0)
			break;

		mf += f;
	}
}

int main()
{
	while(scanf("%d %d ", &M, &W), M, W)
	{
		static int tt = 0;
		tt++;
		reset();

		g[1][M+1] = INF;
		g[M][M+M] = INF;

		FOR(i, 0, M-2)
		{
			int n, cost;
			scanf("%d %d ", &n, &cost);

			g[n][M+n] = cost;
		}

		FOR(i, 0, W)
		{
			int j, k, cost;
			scanf("%d %d %d ", &j, &k, &cost);

			g[M+j][k] = g[M+k][j] = cost;
		}


		s = 1;
		t = M;
		maxflow();

		printf("%d\n", mf);
	}

	return 0;
}



#endif