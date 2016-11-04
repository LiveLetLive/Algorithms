#include "CommonHeader.h"

#ifdef UVA_985_ROUND_AND_ROUND_MAZE
READ_INPUT(UVA_985_ROUND_AND_ROUND_MAZE)

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
#define MAXN 503
#define INF 0x3f3f3f3fL
typedef long long ll;

		   // N, E, S, W
int dr[] = { -1, 0, 1,  0 };
int dc[] = {  0, 1, 0, -1 };

int g[MAXN][MAXN][4];
int R, C;
bool vis[MAXN][MAXN][4];

class Node
{
public:
	Node() {};
	Node(int i1, int j1, int step1, int stepCnt1) 
	{
		i = i1, j = j1, step = step1, stepCnt = stepCnt1;
	};
	int i, j, step, stepCnt;
};

void reset()
{
	FOR(i, 0, R+1)
		FOR(j, 0, C+1)
	{
		FOR(k, 0, 4)
			g[i][j][k] = 0, vis[i][j][k] = 0;
	}
}

int solve()
{
	queue<Node> q;
	q.push(Node(0, 0, -1, 0));

	while(q.empty() == false)
	{
		Node u = q.front();
		q.pop();

		if(u.i == R-1 && u.j == C-1)
			return u.stepCnt;

		int nStep = (u.step + 1 ) % 4;

		FOR(x, 0, 4)
		{
			int ni = u.i + dr[x];
			int nj = u.j + dc[x];

			if(ni < 0 || nj < 0 || ni > R-1 || nj > C-1 ) continue;

			int orgStep = (4 - nStep + x) % 4; 
			if( g[u.i][u.j][orgStep] == 0 ) continue;
			if( vis[ni][nj][nStep] ) continue;
			
			vis[ni][nj][nStep] = 1;
			q.push(Node(ni, nj, nStep, u.stepCnt+1));
		}
	}
	return INF;
}

int main()
{
	int T;
	while(scanf("%d %d", &R, &C) != EOF)
	{
		reset();
		FOR(i, 0, R*C-1)
		{
			char str[5];
			scanf("%s ", &str);

			FOR(j, 0, strlen(str))
			{
				if(str[j] == 'N') g[i/C][i%C][0] = 1;
				else if(str[j] == 'E') g[i/C][i%C][1] = 1;
				else if(str[j] == 'S') g[i/C][i%C][2] = 1;
				else if(str[j] == 'W') g[i/C][i%C][3] = 1;
			}
		}

		int ans = solve();
		if(ans >= INF)
			printf("no path to exit\n");
		else
			printf("%d\n", ans);

	}
	return 0;
}

#endif
