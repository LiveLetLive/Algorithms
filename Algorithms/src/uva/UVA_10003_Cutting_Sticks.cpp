#include "CommonHeader.h"

#ifdef UVA_10003_CUTTING_STICKS
READ_INPUT(UVA_10003_CUTTING_STICKS)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 55
#define INF 0x3f3f3f3f

int N;
int L;
int Pnt[MAXN];
int dp[MAXN][MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		dp[i][j] = INF, Pnt[i] = 0;
}

int cut(int l, int r)
{
	if(dp[l][r] != INF)
		return dp[l][r];

	if(l+1 == r)
		return 0;

	int ans = INF;

	FOR(i, l+1, r)
		ans = min(ans, cut(l, i) + cut(i, r) + (Pnt[r] - Pnt[l]));

	return dp[l][r] = ans;
}

int main()
{
	while(scanf("%d", &L), L)
	{
		reset();
		scanf("%d", &N);

		FOR(i, 1, N+1)
			scanf("%d", &Pnt[i]);

		Pnt[0] = 0;
		Pnt[N+1] = L;

		printf("The minimum cutting is %d.\n", cut(0, N+1));
	}
	return 0;
}

#endif