#include "CommonHeader.h"

#ifdef SELF_FIND_PATH_TO_DESTINATION
READ_INPUT(SELF_FIND_PATH_TO_DESTINATION)

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
#define MAXN 103
#define MAXM 1003
#define INF 0x3f3f3f3fL
typedef long long ll;

int N, M, E, B;

int b[MAXN];
int d[MAXN][MAXN];
int cnt[MAXN];
int vis[MAXN][MAXN];
int g[MAXN][MAXN];
int g1[MAXN][MAXN];
int dp[2][MAXN][MAXM];

void reset()
{
	FOR(i, 0, MAXN)
	{
		b[i] = 0, cnt[i] = 0;
		FOR(j, 0, MAXN)
			vis[i][j] = 0, g[i][j] = 0, d[i][j] = INF, g1[i][j] = INF;
	}

	FOR(k, 0, 2)
		FOR(i, 0, MAXN)
		FOR(j, 0, MAXM)
		dp[k][i][j] = INF;
}


int solve(int isBike, int remM, int idx)
{
	if(remM < 0)
		return INF;

	if(idx == N && isBike == 0)
		return 0;

	if(dp[isBike][idx][remM] < INF)
		return dp[isBike][idx][remM];

	int ans = INF;

	FOR(x, 0, cnt[idx])
	{
		int v = g[idx][x];
		int dis = d[idx][x];

		if(vis[idx][v])
			continue;

		if(isBike == 1)
		{
			vis[idx][v] = 1;
			//continue on bike
			int ans2 = 553*dis + solve(1, remM - 7*dis, v);
			ans = min(ans, ans2);

			//return bike
			if(b[v])
			{
				int ans4 = 553*dis + solve(0, remM - 7*dis, v);
				ans = min(ans, ans4);
			}
			vis[idx][v] = 0;
		}
		else
		{
			vis[idx][v] = 1;
			//Taxi
			int ans2 = 2110*dis + solve(0, remM - 3*dis, v);
			ans = min(ans, ans2);

			//foot
			int ans3 = solve(0, remM - 19*dis, v);
			ans = min(ans, ans3);
			vis[idx][v] = 0;

			if(b[idx])
			{
				//Take bike
				int ans4 = solve(1, remM, idx);
				ans = min(ans, ans4);
			}
		}
	}

	return dp[isBike][idx][remM] = ans;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d %d %d %d ", &N, &M, &E, &B);

		FOR(i, 0, E)
		{
			int x, y, dis;
			scanf("%d %d %d ", &x, &y, &dis);

			g1[x][y] = g1[y][x] = dis;

			g[x][cnt[x]] = y;
			d[x][cnt[x]++] = dis;

			g[y][cnt[y]] = x;
			d[y][cnt[y]++] = dis;
		}

		FOR(i, 0, B)
		{
			int idx = 0;
			scanf("%d ", &idx);
			b[idx] = 1;
		}

		FOR(k, 0, N+1)
			FOR(i, 0, N+1)
			FOR(j, 0, N+1)
			g1[i][j] = min(g1[i][j], g1[i][k] + g1[k][j]);

		if(19*g1[1][N] <= M)
		{
			printf("#%d 0\n", t+1);
			continue;
		}

		int ans = solve(0, M, 1);
		printf("#%d %d\n", t+1, ans >= INF ? -1 : ans);
	}
	return 0;
}

#endif
