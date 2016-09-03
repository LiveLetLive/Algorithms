#include "CommonHeader.h"

#ifdef UVA_11832_ACCOUNT_BOOK
READ_INPUT(UVA_11832_ACCOUNT_BOOK)

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
#define MAXN 41
#define MAXR 16000
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int N, F;
int val[MAXN];
int dp[MAXN][MAXR+MAXR]; //[+/-][N][Range -16000 -> +16000]
int varSet[MAXN][MAXR+MAXR]; //[+/-][N][Range -16000 -> +16000]

void reset()
{
	FOR(j, 0, MAXN)
		FOR(k, 0, MAXR+MAXR)
		dp[j][k] = -1, varSet[j][k] = 0;
}

int solve(int sign, int idx, int nVal)
{
	if(idx >= N && nVal != F)
		return 0;

	if(idx >= N && nVal == F)
		return 1;

	if(dp[idx][nVal+MAXR] != -1)
		return dp[idx][nVal+MAXR];

	int ans = solve(0, idx+1, nVal + val[idx]);
	int ans1 = solve(1, idx+1, nVal - val[idx]);

	if(ans == 0 && ans1 == 0)
		ans = varSet[idx][nVal+MAXR] = 0;
	else if(ans > 0 && ans1 == 0)
		ans = varSet[idx][nVal+MAXR] = 1;
	else if(ans == 0 && ans1 > 0)
		ans = varSet[idx][nVal+MAXR] = 2;
	else if(ans == 1 && ans1 == 1)
		ans = varSet[idx][nVal+MAXR] = 3;

	return dp[idx][nVal+MAXR] = ans;
}

int main()
{
	while(scanf("%d %d", &N, &F), N, F)
	{
		reset();

		FOR(i, 0, N)
			scanf("%d ", &val[i]);

		int ans = solve(0, 0, 0);

		//Find if there is even one idx which can determined 
		if(ans == 0)
			printf("*\n");
		else
		{
			char str[3] = { '+', '-', '?' };
			//FOR(i, 0, N)
			//	printf("%c", str[varSet[i]-1]);
			printf("\n");
		}
	}
	return 0;
}

#endif
