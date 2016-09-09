#include "CommonHeader.h"

#ifdef UVA_10271_CHOPSTICKS
READ_INPUT(UVA_10271_CHOPSTICKS)

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
#define MAXK 1009
#define MAXN 5001
#define INF 0x3fffffffL
typedef long long ll;
int K, N;

int L[MAXN];
int dp[MAXK][MAXN];

void reset()
{
	FOR(i, 0, K+9)
		FOR(j, 0, N+1)
		dp[i][j] = INF;
}

int solve(int pos, int remK)
{
	if(dp[remK][pos] != INF)
		return dp[remK][pos];

	if(pos < ((3*remK)-1))
		return INF;

	if(remK == 0)
		return 0;

	int ans = INF;

	ans = min(ans, solve(pos-1, remK));
	ans = min(ans, solve(pos-2, remK-1) + ((L[pos] - L[pos-1]) * (L[pos] - L[pos-1])));

	return dp[remK][pos] = ans;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d %d ", &K, &N);

		for(int i = N-1; i >= 0; i--)
			scanf("%d ", &L[i]);

		reset();

		printf("%d\n", solve(N-1, K+8));

	}
	return 0;
}


// Failed Bottom-up
//dp[0][0] = 0;

//	FOR(k, 1, K+8)
//	{
//		FOR(n, 2, N)
//		{
//		//	dp[0][n] = 0;

//			int bad = (L[n] - L[n-1]) * (L[n] - L[n-1]);

//			if(n > 0)
//				dp[k][n] = min(dp[k][n], dp[k][n-1]);

//			if(k > 0 && n > 1)
//				dp[k][n] += min(dp[k][n], dp[k-1][n-2] + bad);
//		}
//	}

//	printf("%d\n", dp[K-1+8][N-1]);


#endif
