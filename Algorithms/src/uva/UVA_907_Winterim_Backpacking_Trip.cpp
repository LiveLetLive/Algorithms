#include "CommonHeader.h"

#ifdef UVA_907_WINTERIM_BACKPACKING_TRIP
READ_INPUT(UVA_907_WINTERIM_BACKPACKING_TRIP)

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
#define MAXN 605
#define MAXK 305
#define INF 0x3f3f3f3fL
typedef long long ll;
int N, K;
int arr[MAXN];
int dp[MAXN][MAXK];

void reset()
{
	FOR(i, 0, N+2)
		FOR(j, 0, K+1)
		dp[i][j] = -1;
}

int solve(int idx, int len,	int maxLen, int remK)
{
	if(idx == N+1)
		return 0;

	if(remK == 0)
	{
		int ans = 0;
		FOR(i, idx, N+1)
			ans += arr[i];
		return ans;
	}

	if(dp[idx][remK] != -1)
		return dp[idx][remK];

	int ans = INF;
	int r1 = INF;

	if(remK)
	{
		int m1 = max(maxLen, len + arr[idx]);
		r1 = solve(idx + 1, 0, m1, remK - 1);
	}

	int m2 = max(maxLen, len + arr[idx]);
	int r2 = arr[idx] + solve(idx + 1, len + arr[idx], m2, remK);

	ans = min(ans, r1);
	ans = min(ans, r2);

	return dp[idx][remK] = ans;
}

int main()
{
	while(scanf("%d %d ", &N, &K) != EOF)
	{
		FOR(i, 0, N+1)
			scanf("%d ", &arr[i]);

		reset();

		int a1 = solve(0, 0, 0, K);

		printf("%d\n", a1);
	}
	return 0;
}

#endif
