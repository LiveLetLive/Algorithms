#include "CommonHeader.h"

#ifdef UVA_314_ROBOT
READ_INPUT(UVA_314_ROBOT)

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
#define MAXN 50
#define INF 0x3f3f3f3fL
typedef long long ll;

int g[MAXN][MAXN];
int M, N;
int si, sj, di, dj;
char chDir[20];
int startDir;

enum DIR
{
	LEFT = 0,
	RIGHT,
	UP,
	DOWN
};

int dc[] = { -1, 1,  0, 0 };
int dr[] = {  0, 0, -1, 1 };

int nextDir[4][3] = 
{
	// left	,Right
	{ DOWN, UP, RIGHT },
	{ UP, DOWN, LEFT },
	{ LEFT, RIGHT, DOWN },
	{ RIGHT, LEFT, UP },
};

int dist[MAXN][MAXN];
bool vis[MAXN][MAXN][MAXN][MAXN];

class State
{
public:
	State(int i1,int  j1,int dir1, int dist1)
	{
		i = i1, j = j1, dir = dir1, dist = dist1;
	}
	State()
	{
	}

	int i;
	int j;
	int dir;
	int dist;
};

State pred[MAXN][MAXN];

bool isValid(int i, int j)
{
	if(i < 1 || j < 1 || i > M-1 || j > N-1)
		return false;

	if(g[i][j] == 1 || g[i-1][j] == 1 || g[i][j-1] == 1 || g[i-1][j-1] == 1)
		return false;

	return true;
}

void PrintOutput(int i, int j)
{
	if(pred[i][j].i == si && pred[i][j].j == sj && pred[i][j].dir == startDir)
	{
		printf( "%d, %d, %d \n" , pred[i][j].i, pred[i][j].j ,  pred[i][j].dir);
		return;
	}
	PrintOutput(pred[i][j].i, pred[i][j].j);

	printf( "%d, %d, %d \n" , pred[i][j].i, pred[i][j].j ,  pred[i][j].dir);
}

int bfs()
{
	queue<State> q;

	q.push(State(si, sj, startDir, 0));
	q.push(State(si, sj, nextDir[startDir][0], 1));
	q.push(State(si, sj, nextDir[startDir][1], 1));
	q.push(State(si, sj, nextDir[startDir][2], 2));

	dist[si][sj] = 0;

	while(q.empty() == false)
	{
		State s = q.front();
		q.pop();

		if(s.i == di && s.j == dj)
			break;

		FOR(x, 1, 4)
		{
			int ni = s.i + dr[s.dir] * x;
			int nj = s.j + dc[s.dir] * x;

			if(isValid(ni, nj) == false)
				break;

			if(vis[s.i][s.j][ni][nj])
				continue;

			vis[s.i][s.j][ni][nj] = true;

			if(dist[ni][nj] > s.dist + 1)
			{
				State s1 = State(ni, nj, s.dir, s.dist + 1);
				q.push(s1);
				q.push(State(ni, nj, nextDir[s.dir][0], s.dist + 2));
				q.push(State(ni, nj, nextDir[s.dir][1], s.dist + 2));
				q.push(State(ni, nj, nextDir[s.dir][2], s.dist + 3));

				//pred[ni][nj] = s; 
				dist[ni][nj] = s.dist + 1;
			}
		}

	}

	//PrintOutput(di, dj);

	int ans = 0;
	if(dist[di][dj] >= INF)
		ans = -1;
	else
		ans = dist[di][dj];

	return ans;
}

void reset()
{
	FOR(l, 0, MAXN)
		FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		FOR(k, 0, MAXN)
		vis[l][i][j][k] = false;

	FOR(j, 0, MAXN)
		FOR(k, 0, MAXN)
		dist[j][k] = INF;
}

int main()
{
	int t = 0;
	while(scanf("%d %d ", &M, &N), M, N)
	{
		t++;
		reset();
		FOR(i, 0, M)
			FOR(j, 0, N)
			scanf("%d ", &g[i][j]);

		scanf("%d %d %d %d ", &si, &sj, &di, &dj);
		scanf("%s ", &chDir);

		if(chDir[0] == 's') startDir = DOWN;
		if(chDir[0] == 'n') startDir = UP;
		if(chDir[0] == 'e') startDir = RIGHT;
		if(chDir[0] == 'w') startDir = LEFT;

		printf("%d\n", bfs());
	}
	return 0;
}

#endif
