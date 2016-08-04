
#include "CommonHeader.h"

#ifdef UVA_674_COIN_CHANGE
READ_INPUT(UVA_674_COIN_CHANGE)

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
#define MAXN 5
#define MAXV 8000
#define MAXC 105
#define INF 0x3fffffff

int dp[5][MAXV];
int c[MAXN] = { 1, 5, 10, 25, 50 };
int S;

void reset()
{
	FOR(i, 0, 5)
		FOR(j, 0, MAXV)
		dp[i][j] = -1;
}

int ways(int idx, int rem)
{
	if(rem < 0)
		return 0;

	if(rem == 0)
		return 1;

	if(idx == 5)
		return 0;

	if(dp[idx][rem] != -1)
		return dp[idx][rem];

	int ans = 0;

	ans =  ways(idx, rem - c[idx]) + ways(idx+1, rem);

	return dp[idx][rem] = ans;
}


int main()
{
	reset();

	while(scanf("%d ", &S) != EOF)
	{
		if(S == 0) 
		{
			printf("1\n");
			continue;
		}

		int ans = ways(0, S);
		printf("%d\n", ans);
	}

	return 0;
}


#endif