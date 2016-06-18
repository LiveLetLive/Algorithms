#include "CommonHeader.h"


#ifdef UVA_10480_SABOTAGE
READ_INPUT(UVA_10480_SABOTAGE)

#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <bitset>

using namespace std;
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 55
#define INF 0x1FFFFFFF

int n, m;
int dist[MAXN];
bool vis[MAXN];
int p[MAXN];
int g[MAXN][MAXN];
int bk[MAXN][MAXN];
int f, mf;

void reset()
{
	f = 0;
	mf = 0;
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = 0, bk[i][j] = 0;
		dist[i] = INF;
		p[i] = -1;
	}
}

void PrintGraph()
{
	//#define DEBUG
#ifdef DEBUG
	printf("\n");
	FOR(i, 1, n+1)
	{
		FOR(j, 1, n+1)
			printf("%02d ", g[i][j]);
		printf("\n");
	}
	printf("\n");
#endif
}

bitset<MAXN> dfsv;
set<int> leftG;

void dfs(int u) {
	dfsv.set(u);
	leftG.insert(u);
	for (int v = 1; v < n+1; v++) 
	{
		if(u == v) continue;
		if (!dfsv.test(v) && g[u][v] > 0) 
		{
			dfs(v);
		}
	}
}

void bfs2(int src, int dest)
{
	leftG.clear();
	for (int i = 0; i < MAXN; i++)
		dfsv.reset();
	dfs(src);
	set<int>::iterator it;

	for (it = leftG.begin(); it != leftG.end(); it++) 
	{
		int u = *it;
		for (int v = 1; v < n+1; v++) 
		{
			if (u == v)
				continue;
			if (leftG.count(v))
				continue;
			if (bk[u][v] && g[u][v] <= 0) {
				printf("%d %d\n", u, v);
			}
		}
	}
	printf("\n");
}

bool bfs(int src, int dest)
{
	FOR(i, 0, n+1)
		dist[i] = INF, p[i] = -1;

	queue<int> q;
	q.push(src);
	dist[src] = 0;

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		if(u == 2)
			return true;

		FOR(v, 1, n+1)
		{
			if (u == v) continue;
			if(dist[v] == INF && g[u][v] > 0)
			{
				dist[v] = dist[u] +1 ;
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
	while(bfs(1, 2))
	{
		PrintGraph();
		int f = INF;
		augment(2, f);
		mf += f;
		if(f == 0)
			break;
	}
}

int main()
{
	while(scanf("%d %d ", &n, &m), n, m)
	{
		reset();
		FOR(i, 0, m)
		{
			int x, y, c;
			scanf("%d %d %d ", &x, &y, &c);

			bk[x][y] += c;
			bk[y][x] += c;
			g[x][y] += c;
			g[y][x] += c;
		}

		maxflow();

		bfs2(1, 2);

	/*	FOR(i, 0, n+1)
			vis[i] = 0;

		while(!leftG.empty())
		{
			int x = leftG.front();
			leftG.pop();

			if(vis[x] == 0)
			{
				vis[x] = 1;

				FOR(j, 0, n+1)
				{
					if(bk[x][j] != 0 && g[x][j] <= 0)
						printf("%d %d\n", x, j);
				}
			}
		}*/
	}
	return 0;
}


#endif