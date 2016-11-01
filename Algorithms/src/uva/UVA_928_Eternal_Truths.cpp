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
int dp[MAXN][MAXN][4][3];
bool vis[MAXN][MAXN][4][3];
int totalSteps;
int stepCnt;

void reset()
{
	totalSteps = INF;
	stepCnt = 0;
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		g[i][j] = 0;

	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		FOR(k, 0, 4)
		FOR(l, 0, 3)
		dp[i][j][k][l] = INF, vis[i][j][k][l] = 0;

}

int dr[] = { 0,  0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };

inline bool isValid(int i , int j)
{
	if(i < 0 || j < 0 || i >= R || j >= C) return false;
	if(g[i][j] == 0) return false;

	return true;
}

int solve(int i, int j, int dir, int step)
{
	if(i == ei && j == ej)
	{
		if(stepCnt < totalSteps)
			totalSteps = stepCnt;
		return stepCnt;
	}

	if(stepCnt > totalSteps)
		return INF;

	if(dp[i][j][dir][step] < INF)
		return dp[i][j][dir][step];

	int ans = INF;

	FOR(x, 0, 4)
	{
		int nStep = (((step) % 3) + 1);
		int ni = i + dr[x] * nStep;
		int nj = j + dc[x] * nStep;

		if(isValid(ni, nj))
		{
			if(nStep >= 2)
			{
				int ni1 = i + dr[dir] * (nStep-1);
				int nj1 = j + dc[dir] * (nStep-1);

				if(g[ni1][nj1] == 0) continue;

				if(nStep == 3)
				{
					int ni1 = i + dr[dir] * (nStep-2);
					int nj1 = j + dc[dir] * (nStep-2);

					if(g[ni1][nj1] == 0) continue;
				}
			}

			if(vis[ni][nj][x][nStep]) continue;

			vis[ni][nj][x][nStep] = 1;
			stepCnt++;
			ans = min(ans, solve(ni, nj, x, nStep)); 
			vis[ni][nj][x][nStep] = 0;
			stepCnt--;
		}
	}

	return dp[i][j][dir][step] = ans;
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

		int ans = solve(si, sj, 0, 0);
		if(totalSteps >= INF)
			printf("NO\n");
		else
			printf("%d\n", totalSteps);
	}
	return 0;
}

#endif
