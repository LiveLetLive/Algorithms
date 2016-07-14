
#include "CommonHeader.h"

#ifdef UVA_4106_ACORN
READ_INPUT(UVA_4106_ACORN)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXH 2005
#define MAXT 2005

int t,h,f;

int corn[MAXT][MAXH];
int mcorn[MAXT][MAXH];
int dp[MAXH];

void reset()
{
	FOR(i, 0, t+1)
	{
		FOR(j, 0, h+1)
			corn[i][j] = 0, mcorn[i][j] = -1, dp[j] = 0;
	}
}

int go(int tr, int ht)
{
	if(ht <= 0) return 0;

	if(mcorn[tr][ht] != -1) return mcorn[tr][ht];

	int ans = -1;

	FOR(i, 0, t)
	{
		ans = max(ans, corn[tr][ht] + max(go(tr, ht - 1), go(i, ht - f)));
	}

	return mcorn[tr][ht] = ans;
}

// This is TLE
int findMax()
{
	int maxVal = -1;

	FOR(i, 0,t)
		maxVal = max(maxVal, go(i, h));
	return maxVal;
}

int findMaxEffDP()
{
	//Init DP table
	FOR(i, 0, h)
		FOR(j, 0, t)
		dp[i] = max(dp[i], corn[j][i]);

	FOR(ht, 0, h+1)
	{
		FOR(tr, 0, t)
		{
			if((ht - f) >= 0)
				corn[tr][ht] += max(corn[tr][ht-1] , dp[ht - f]);
			else
				corn[tr][ht] += corn[tr][ht-1];

			dp[ht] = max(dp[ht], corn[tr][ht]); 
		}
	}

	return dp[h];
}

int main()
{
	int T;
	scanf("%d ", &T);

	FOR(t1, 0, T)
	{
		scanf("%d %d %d ", &t, &h, &f);
		reset();
		FOR(i, 0, t)
		{
			int a, tmp;
			scanf("%d ", &a);
			FOR(j, 0, a)
			{	
				scanf("%d ", &tmp);
				corn[i][tmp]++;
			}
		}

		printf("%d\n", findMaxEffDP());
		//printf("%d\n", findMax());
	}
	return 0;
}

#endif