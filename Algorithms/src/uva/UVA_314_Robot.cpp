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
#define MAXN 51
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

bool vis[MAXN][MAXN][4];

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

	bool operator < (const State &that) const
	{
		return this->dist > that.dist;
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

int bfs()
{
	queue<State> q;

	if (si < 1 || si >= M || sj < 1 || sj >= N)
		return -1;
	if (di < 1 || di >= M || dj < 1 || dj >= N)
		return -1;

	if (g[si][sj] || g[di][dj])
		return -1;

	q.push(State(si, sj, startDir, 0));
	vis[si][sj][startDir] = true;

	while(q.empty() == false)
	{
		State s = q.front();
		q.pop();

		if(s.i == di && s.j == dj)
			return s.dist;

		if(vis[s.i][s.j][nextDir[s.dir][0]] == false)
		{
			vis[s.i][s.j][nextDir[s.dir][0]] = true;
			q.push(State(s.i, s.j, nextDir[s.dir][0], s.dist + 1));
		}

		if(vis[s.i][s.j][nextDir[s.dir][1]] == false)
		{
			vis[s.i][s.j][nextDir[s.dir][1]] = true;
			q.push(State(s.i, s.j, nextDir[s.dir][1], s.dist + 1));
		}

		FOR(x, 1, 4)
		{
			int ni = s.i + dr[s.dir] * x;
			int nj = s.j + dc[s.dir] * x;

			if(ni < 1 || nj < 1 || ni > M-1 || nj > N-1)
				continue;

			if(g[ni][nj] == 1 || g[ni-1][nj] == 1 || g[ni][nj-1] == 1 || g[ni-1][nj-1] == 1)
				break;

			if(vis[ni][nj][s.dir])
				continue;

			vis[ni][nj][s.dir] = true;

			State s1 = State(ni, nj, s.dir, s.dist + 1);
			q.push(s1);
		}

	}

	return -1;
}

void reset()
{
	FOR(l, 0, MAXN)
		FOR(i, 0, MAXN)
		FOR(j, 0, 4)
		vis[l][i][j] = false;
}

int main()
{
	while(scanf("%d %d ", &M, &N), M, N)
	{
		reset();
		FOR(i, 0, M)
			FOR(j, 0, N)
		{
			scanf("%d ", &g[i][j]);
			if(g[i][j])
				g[i][j+1] = 1, g[i+1][j] = 1, g[i+1][j+1] = 1;
		}

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
