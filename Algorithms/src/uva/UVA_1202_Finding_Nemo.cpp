#include "CommonHeader.h"

#ifdef UVA_1202_FINDING_NEMO
READ_INPUT(UVA_1202_FINDING_NEMO)

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
#define MAXR 11
#define MAXN 405
#define INF 0x3f3f3f3fL
typedef long long ll;

int g[MAXN][MAXN];
int dist[MAXN][MAXN];
int dstX, dstY;
int N, M;

class State
{
public:
	State(int a, int b, int d)
	{
		x = a, y = b, dist = d;
	}

	bool operator == (const State &that) const
	{
		return (this->x == that.x && this->y == that.y);
	}

	int x, y, dist;
};

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		dist[i][j] = INF, g[i][j] = 0;
}

int dr[] = { 0, 0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };

#define MAXP 50

void PrintDist()
{
#ifdef DEBUG
	static int stepcount = 0;

	system("cls");
	for(int i = MAXP; i >= 0; i--)
	{
		FOR(j, 0, MAXP)
		{
			if(g[i][j] == 1)
				printf("d ");
			else if(g[i][j] == INF)
				printf("w ");
			else if(i == dstY && j == dstX)
				printf("D ");
			else if(dist[i][j] >= INF)
				printf("! ");
			else
				printf("%d ", dist[i][j]);
		}
		printf("\n");
	}
#endif
}

void PrintGraph()
{
#ifdef DEBUG
	for(int i = MAXP; i >= 0; i--)
	{
		FOR(j, 0, MAXP)
		{
			if(g[i][j] == 1)
				printf("d ");
			else if(g[i][j] == INF)
				printf("w ");
			else if(i == dstY && j == dstX)
				printf("D ");
			else
				printf("%d ", g[i][j]);
		}
		printf("\n");
	}

	printf("dstX=%d, dstY=%d \n", dstX, dstY);

	getch();
#endif
}

int t = 0;
int DEBUG_TC=10;

int dijkstra()
{
	queue<State> q[2];
	State dst(dstX,dstY,0);

	int qIndex = 0;

	q[qIndex].push(State(0,0,0));
	dist[0][0] = 0;

	while(q[qIndex].empty() == false)
	{
		while(q[qIndex].empty() == false)
		{
			State u = q[qIndex].front();
			q[qIndex].pop();

			if(u == dst)
				return dist[dstY][dstX] == INF? -1 : dist[dstY][dstX];

			FOR(i, 0, 4)
			{
				int nx = u.x + dc[i];
				int ny = u.y + dr[i];

				if( nx < 0 || ny < 0 ||  nx >= MAXN || ny >= MAXN) continue;

				if(g[ny][nx] == INF) continue;

				if(dist[ny][nx] > u.dist + g[ny][nx])
				{
					dist[ny][nx] = u.dist + g[ny][nx];
					State s1(nx, ny, dist[ny][nx]);



					if(g[ny][nx] == 1)
						q[qIndex ^ 1].push(s1);
					else
						q[qIndex].push(s1);
				}
			}
		}

		if(t == DEBUG_TC)
			PrintDist();

		qIndex ^= 1;
	}

	return -1;
}

int main()
{
	while(scanf("%d %d ", &M, &N))
	{
		if(M == -1 && N == -1)
			break;

		reset();
		t++;

		//Make walls
		FOR(i, 0, M)
		{
			int x, y, d, t;

			scanf("%d %d %d %d ", &x, &y, &d, &t);

			FOR(j, 0, 2*t+1)
			{
				if(d == 0)
					g[2*y][2*x+j] = INF;
				else
					g[2*y+j][2*x] = INF;
			}
		}

		//Make doors
		FOR(i, 0, N)
		{
			int x, y, d;

			scanf("%d %d %d ", &x, &y, &d);

			if(d == 0)
				g[2*y][2*x+1] = 1;
			else
				g[2*y+1][2*x] = 1;
		}

		double f1, f2;
		scanf("%lf %lf", &f1,&f2);
		int tx = (int) f1;
		int ty = (int) f2;

		//Make dst
		dstX = 2*tx+1;
		dstY = 2*ty+1;


		if(t == DEBUG_TC)
			PrintGraph();

		//printf("\n\n");

		if((dstX == 1 && dstY == 1) || (dstX >= MAXN || dstY >= MAXN))
			printf("0\n");
		else
		{
			int ans = dijkstra();
			printf("%d\n", ans);
		}
	}

	return 0;
}
#endif
