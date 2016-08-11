#include "CommonHeader.h"

#ifdef UVA_11407_SQUARES
READ_INPUT(UVA_11407_SQUARES)

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

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 10001
#define INF 0x3f3f3f3f3f
typedef long long ll;
int N;

int dp[MAXN];

int main()
{
	int T;
	scanf("%d ", &T);

	FOR(j, 0, MAXN)
		dp[j] = INF;

	dp[0] = 0;
	FOR(i, 1, 101)
	{
		FOR(j, 1, 10001)
		{
			if((j - (i*i)) >= 0)
				dp[j] = min(dp[j], 1 + dp[j - (i*i)]);
		}
	}

	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		printf("%d\n", dp[N]);
	}
	return 0;
}


#endif