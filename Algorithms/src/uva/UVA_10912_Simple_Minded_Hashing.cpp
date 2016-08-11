#include "CommonHeader.h"

#ifdef UVA_10912_SIMPLE_MINDED_HASHING
READ_INPUT(UVA_10912_SIMPLE_MINDED_HASHING)

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
#define MAXA 27
#define MAXN 10001
#define INF 0x3f3f3f3f3f
typedef long long ll;
int N, L;

int dp[MAXA+1][MAXA+1][MAXN];

//vector<vector< vector<int> > > dp(MAXA+1, vector< vector<int> >(MAXA+1, vector<int>(MAXN)));

int main()
{
	dp[0][0][0] = 1;

	FOR(i, 1, MAXA+1)
	{
		FOR(j, 0, MAXA+1)
			FOR(k, 0, MAXN)
		{
			dp[i][j][k] = dp[i-1][j][k];

			if(j > 0 && (k - i) >= 0)
				dp[i][j][k] += dp[i-1][j - 1][k - i];
		}
	}
	int t = 0;
	while(scanf("%d %d",&L, &N), L, N)
	{
		if(L > 26 || N > 351)
			printf("Case %d: 0\n", ++t);
		else
			printf("Case %d: %d\n", ++t, dp[26][L][N]);
	}
	return 0;
}


#endif