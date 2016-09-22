#include "CommonHeader.h"

#ifdef UVA_10154_WEIGHTS_AND_MEASURES
READ_INPUT(UVA_10154_WEIGHTS_AND_MEASURES)

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
#define MAXN 5610
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int w[MAXN];
int s[MAXN];
int N;
int dp[MAXN][50000];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, 10000)
		dp[i][j] = -1;
}

int solve(int idx, int sum)
{
	if(dp[idx][sum] != -1)
		return dp[idx][sum];

	if(idx >= N)
		return 0;

	int ans = -1;

	ans = solve(idx+1, sum);

	if(s[idx] >= sum + w[idx])
		ans = max(ans, 1 + solve(idx+1, sum + w[idx]));

	return dp[idx][sum] = ans;
}

int main()
{
	int idx = 0;

	while(scanf("%d %d ", &w[idx], &s[idx]) != EOF)
		idx++;

	reset();

	N = idx;

	FOR(i, 0, N)
		FOR(j, 0, N)
	{
		if(s[i] < s[j])
			swap(w[i],w[j]), swap(s[i], s[j]);
	}

	int ans = solve(0,0);

	printf("%d\n", ans);

	return 0;
}

#endif
