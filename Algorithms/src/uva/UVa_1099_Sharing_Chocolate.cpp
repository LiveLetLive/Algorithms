#include "CommonHeader.h"

#ifdef UVA_1099_SHARING_CHOCOLATE
READ_INPUT(UVA_1099_SHARING_CHOCOLATE)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;
#define INF 0x3FFFFFFF
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 16

int W, H, N;
int dp[100][1 << MAXN];
int size[MAXN];
int bitmask;

void reset()
{
	bitmask = 0;
	FOR(i, 0, 100)
		FOR(j, 0, (1 << MAXN))
		dp[i][j] = -1;

	FOR(i, 0, MAXN)
		size[i] = 0;
}


int solve(int bitmask, int currW)
{
	if(dp[currW][bitmask] != -1)
		return dp[currW][bitmask];

	int ans = 0;

	FOR(i, 0, N)
	{
		if(bitmask & (1 << i))
		{
		}
	}

	return dp[currW][bitmask] = ans;
}

int main()
{
	int t = 0;
	while(scanf("%d", &N), N)
	{
		reset();
		scanf("%d %d %d ", &W, &H);

		int sum = 0;

		FOR(i, 0, N)
			scanf("%d", &size[i]), sum += size[i];

		if((W*H) != sum)
		{
			printf("Case %d: %s\n", t+1, "No");
			continue;
		}
		printf("Case %d: %s\n", t+1, solve(bitmask, W) ? "Yes" : "No");
	}

	return 0;
}

#endif