#include "CommonHeader.h"

#ifdef UVA_928_ETERNAL_TRUTHS
READ_INPUT(UVA_928_ETERNAL_TRUTHS)

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
#define MAXN 303
#define INF 0x3f3f3f3fL
typedef long long ll;

int R, C;
int si, sj, ei, ej;
int g[MAXN][MAXN];
bool vis[MAXN][MAXN][3];

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
		FOR(l, 0, 3)
		vis[i][j][l] = 0;
}

int dr[] = { 0,  0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };

int solve1()
{
	queue<Node> q;
	q.push(Node(si, sj, 0, 0));

	while(q.empty() == false)
	{
		Node u = q.front();
		q.pop();

		if(u.i == ei && u.j == ej)
			return u.stepCnt;

		int nStep = (((u.step) % 3) + 1);

		FOR(x, 0, 4)
		{
			int ni = u.i + dr[x] * nStep;
			int nj = u.j + dc[x] * nStep;

			if(ni < 0 || nj < 0 || ni >= R || nj >= C) continue;
			if(vis[ni][nj][nStep]) continue;

			int jump = 0, bad = 0;

			for(jump = 1; jump <=nStep && bad == 0; jump++)
				bad = bad || g[u.i+dr[x]*jump][u.j+dc[x]*jump] == 0;

			if(bad) continue;

			vis[ni][nj][nStep] = 1;
			q.push(Node(ni, nj, nStep, u.stepCnt+1));
		}
	}

	return INF;
}


int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();
		scanf("%d %d ", &R, &C);
		FOR(i, 0, R)
		{
			char str[MAXN] = { 0 };
			scanf("%s ", &str);
			FOR(j, 0, C)
			{
				if(str[j] == 'S') si = i, sj = j, g[i][j] = 1;
				else if(str[j] == 'E') ei = i, ej = j, g[i][j] = 1;
				else if(str[j] == '#') g[i][j] = 0;
				else if(str[j] == '.') g[i][j] = 1;
			}
		}

		int ans = solve1();
		if(ans >= INF)
			printf("NO\n");
		else
			printf("%d\n", ans);
	}
	return 0;
}

#endif
