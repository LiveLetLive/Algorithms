#include "CommonHeader.h"

#ifdef UVA_11284_SHOPPING_TRIP
READ_INPUT(UVA_11284_SHOPPING_TRIP)

// Solved, all debug inputs are working well, but final submission is WA.

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 55
#define MAXP 13
#define INF 0x3FFFFFFF

int N, M, P;

double gas[MAXN][MAXN];

double save[MAXN];
double sSort[MAXP];
int sSortIndex[MAXP];

double dp[1<<MAXP][MAXP];

double gAns = 0;
void reset()
{
	gAns = 0;

	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		gas[i][j] = INF;

	FOR(p, 0, MAXN)
		save[p] = 0;

	FOR(p, 0, MAXP)
		save[p] = 0, sSort[p] = 0, sSortIndex[p] = 0;

	FOR(i, 0, (1<<MAXP))
		FOR(j, 0, (MAXP))
		dp[i][j] = -INF;
}

double solve(int remLoc, int curr, int n)
{
	if(remLoc == 0) return 0;

	if(dp[remLoc][curr] != -INF)
		return dp[remLoc][curr];

	double ans = -INF, tmp;

	FOR(i, 0, n+1)
		if((remLoc & (1 << i)) != 0 && i != curr)
		{
			tmp = solve(remLoc - (1 << curr), i, n);
			tmp += sSort[curr];
			tmp -= gas[sSortIndex[curr]][sSortIndex[i]];
			ans = max(ans , tmp);
		}

		if(remLoc == (1<<curr))
			ans = sSort[curr] - gas[sSortIndex[curr]][0];

		tmp = ans - gas[sSortIndex[curr]][0];

		if(gAns < tmp) 
		{
			gAns = tmp;
		}

		return dp[remLoc][curr] = ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	FOR(t, 0, T)
	{
		reset();
		scanf("%d %d ", &N, &M);

		FOR(i, 0, M)
		{
			int x, y;
			double c;
			scanf("%d %d %lf", &x, &y, &c);

			gas[x][y] = min(gas[x][y], c);
			gas[y][x] = gas[x][y];
		}

		scanf("%d ", &P);

		FOR(i, 0, P)
		{
			int x;
			double tmp;
			scanf("%d ", &x);
			scanf("%lf ", &tmp);
			save[x] += tmp;
		}

		int idx = 0;
		FOR(i, 1, N+1)
			if(save[i] != 0)
				idx++, sSort[idx] = save[i], sSortIndex[idx] = i;

		FOR(k, 0, N+1)
			FOR(i, 0, N+1)
			FOR(j, 0, N+1)
		{
			if(i == j) 
			{
				gas[i][j] = 0;
				continue;
			}
			gas[i][j] = min(gas[i][j], gas[i][k] + gas[k][j]);
		}

		gAns = 0.0;

		double ans = solve((1<<(idx+1))-1, 0, idx);

		if(gAns <= 0.0)
			printf("Don't leave the house\n");
		else
			printf("Daniel can save $%.2lf\n", gAns);
	}
	return 0; 
} 
#endif