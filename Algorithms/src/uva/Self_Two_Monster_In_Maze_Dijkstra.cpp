#include "CommonHeader.h"

#ifdef SELF_TWO_MONSTER_IN_MAZE
READ_INPUT(SELF_TWO_MONSTER_IN_MAZE)

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
#define MAXN 25
#define INF 0x3f3f3f3fL
typedef long long ll;

int g[MAXN][MAXN];
int dis[MAXN][MAXN][MAXN][MAXN];
int s1r, s1c, d1r, d1c; 
int s2r, s2c, d2r, d2c;
int N;

int dr[] = { -1, -1, -1,  0, 0,  1, 1, 1, 0 };
int dc[] = { -1,  0,  1, -1, 1, -1, 0, 1, 0 };

class State
{
public:
	bool operator == (State& s)
	{
		return (i1 == s.i1 && i2 == s.i2 && j1 == s.j1 && j2 == s.j2);
	}

	bool operator < (const State& s) const
	{
		return (dis > s.dis);
	}

	State() {}
	State(int x1, int y1, int x2, int y2, int d)
	{	i1 = x1, j1 = y1, i2 = x2, j2 = y2; dis = d;}
	int i1, j1;
	int i2, j2;
	int dis;
};

class Queue
{
public:
	Queue() { top = -1; cnt = 0; }
	void reset() { top = -1; cnt = 0; }
	State m_queue[MAXN*MAXN*MAXN*MAXN];
	void push(State s)
	{
		m_queue[++top] = s;
		cnt++;
	}

	State pop()
	{
		cnt--;
		return m_queue[top--];
	}
	int top;
	int cnt;
	bool isEmpty() { return top == -1;}
};

inline bool isAttack(int x1, int y1, int x2, int y2)
{
	FOR(i, 0, 9)
		if(x1 + dr[i] == x2 && y1 + dc[i] == y2)
			return true;
	return false;
}

inline bool isValid(int x1, int y1)
{
	if(x1 < 0 || y1 < 0)
		return false;

	if(x1 >= N || y1 >= N)
		return false;

	if(g[x1][y1] == 1)
		return false;

	return true;
}

void reset()
{
	FOR(i, 0, N)
		FOR(j, 0, N)
		FOR(k, 0, N)
		FOR(l, 0, N)
		dis[i][j][k][l] = INF;
}

#if 0
void PrintSolution()
{
	State src(s1r, s1c, s2r, s2c, 0);
	State dst(d1r, d1c, d2r, d2c, 0);
	State s = dst;

	while(!(s == src))
	{
		gSol[s.i1][s.j1] = 1;
		gSol[s.i2][s.j2] = 2;
		printf("%d %d %d %d \n", s.i1, s.j1, s.i2, s.j2);
		s = sol[s.i1][s.j1][s.i2][s.j2];
	}
	gSol[s.i1][s.j1] = 1;
	gSol[s.i2][s.j2] = 2;
	printf("%d %d %d %d \n\n\n", s.i1, s.j1, s.i2, s.j2);

	FOR(i, 0, N)
	{
		FOR(j, 0, N)
		{
			if(i == s1r && j == s1c) printf("A ");
			else if(i == d1r && j == d1c) printf("B ");
			else if(i == s2r && j == s2c) printf("D ");
			else if(i == d2r && j == d2c) printf("E ");
			else printf("%d ", g[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

	FOR(i, 0, N)
	{
		FOR(j, 0, N)
			printf("%d ", gSol[i][j]);
		printf("\n");
	}

}
#endif
static int pushCounter = 0;

int dijkstra()
{
	State dst(d1r, d1c, d2r, d2c, 0);
	priority_queue<State> q;
	q.push(State(s1r, s1c, s2r, s2c, 0));
	dis[s1r][s1c][s2r][s2c] = 0;

	while(q.empty() == false)
	{
		//Find the least distance node first
		State s = q.top();
		q.pop();


		//Terminate on reaching desination at first shot.
		if(s == dst)
			break;

		if(dis[s.i1][s.j1][s.i2][s.j2] < s.dis)
			continue;

		//Find all 81 combinations
		FOR(x, 0, 9)
		{
			int ni = s.i1 + dr[x];
			int nj = s.j1 + dc[x];

			if(isValid(ni, nj) == false) continue;

			FOR(y, 0, 9)
			{
				//Skip coming to halt, when both monster doesnt move.
				if(x == 8 && y == 8) continue;

				int di = s.i2 + dr[y];
				int dj = s.j2 + dc[y];

				if(isValid(di, dj) == false) continue;
				if(isAttack(ni, nj, di, dj)) continue;

				//Minimize the distance table for this combination
				if(dis[ni][nj][di][dj] > (dis[s.i1][s.j1][s.i2][s.j2] + 1))
				{
					State ns(ni, nj, di, dj, (dis[s.i1][s.j1][s.i2][s.j2] + 1));
					q.push(ns);
					pushCounter++;
					dis[ni][nj][di][dj] = (dis[s.i1][s.j1][s.i2][s.j2] + 1);
				}
			}
		}
	}

	int ans;
	if(dis[d1r][d1c][d2r][d2c] == INF)
		ans = -1;
	else
		ans = dis[d1r][d1c][d2r][d2c];
	printf("%d\tpushCnt=%d\tremInQueue=%d\n", ans, pushCounter, q.size());
	pushCounter = 0;
	return 0;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		scanf("%d %d %d %d ", &s1r, &s1c, &d1r, &d1c);
		scanf("%d %d %d %d ", &s2r, &s2c, &d2r, &d2c);

		FOR(i, 0, N)
			FOR(j, 0, N)
			scanf("%d ", &g[i][j]);

		s1r--, s1c--, d1r--, d1c--, s2r--, s2c--, d2r--, d2c--;
		reset();
		dijkstra();

	}
	return 0;
}

#endif
