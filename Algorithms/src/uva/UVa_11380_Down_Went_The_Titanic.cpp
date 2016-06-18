#include "CommonHeader.h"


#ifdef UVA_11380_DOWN_WENT_THE_TITANIC
READ_INPUT(UVA_11380_DOWN_WENT_THE_TITANIC)

#include <iostream>
#include <cstdio>
#include <queue>
#include <set>
#include <bitset>

	using namespace std;
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 1805
#define MAXNODE 900
#define T (MAXNODE*2+1)
#define MAXG 31
#define INF 10000

int n;
int X, Y, P;
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

		if(u == T)
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
	while(bfs(0, T))
	{
		int f = INF;
		augment(T, f);
		mf += f;
		if(f == 0)
			break;
	}
}

int dc[] = { 0, 0, 1, -1 };
int dr[] = { 1,-1, 0,  0 };

bool isSafe(int i, int j)
{
	if(i < 0 || j < 0 || i >= X || j >= Y)
		return false;
	return true;
}

char grid[MAXG][MAXG];

inline int GetIdx(int i, int j)
{
	return (i*Y+j)+1;
}

void PrintGraph()
{
	FOR(i, 0, 62)
	{
		FOR(j, 0, 62)
		{
			if(g[i][j] == INF) printf("!");
			else printf("%d ", g[i][j]);
		}

		printf("\n");
	}
}

void AddVEdge(int i, int j)
{
	int s = GetIdx(i, j);

	if(grid[i][j] == '*' || grid[i][j] == '.')
		g[s][s+MAXNODE+1] = 1;
	else if(grid[i][j] == '#' || grid[i][j] == '@')
		g[s][s+MAXNODE+1] = INF;

	if(grid[i][j] == '*')
		g[0][s] = 1;
	else if(grid[i][j] == '#')
		g[s][T] = P;
}
void AddEdge(int i, int j, int x, int y)
{
	if(grid[i][j] == '~' || grid[x][y] == '~')
		return;

	int s = GetIdx(i, j);
	int s1 = GetIdx(x, y);
	g[s+MAXNODE+1][s1] = INF;
}

int main()
{
	while(scanf("%d %d %d", &X, &Y, &P) != EOF)
	{
		reset();

		FOR(i, 0, X)
			scanf("%s ", &grid[i]);

		FOR(i, 0, X)
		{
			FOR(j, 0, Y)
			{
				AddVEdge(i, j);
				FOR(x, 0, 4)
				{
					if(isSafe(i+dr[x], j+dc[x]))
					{
						AddEdge(i, j, i+dr[x], j+dc[x]);
					}
				}
			}
		}

		//PrintGraph();

		n=T;
		maxflow();
		printf("%d\n", mf);
	}
	return 0;
}



#endif