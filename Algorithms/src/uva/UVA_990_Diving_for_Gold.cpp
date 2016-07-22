#include "CommonHeader.h"

#ifdef UVA_990_DIVING_FOR_GOLD
READ_INPUT(UVA_990_DIVING_FOR_GOLD)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>
#include <math.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXT 1005
#define MAXTR 31

int t, w;

class AnsSet
{
public:
	AnsSet() {}
	AnsSet(int e) { earn = e; count = 0; }
	int earn;
	int count;
};

int d[MAXTR];
int v[MAXTR];
int trcnt;
AnsSet dp[MAXTR][MAXT];
int taken[MAXTR][MAXT];
int timeReq[MAXTR];

void reset()
{
	FOR(i, 0, MAXTR)
	{
		FOR(j, 0, MAXT)
		{
			taken[i][j] = 0;
			dp[i][j].earn = -1;
			dp[i][j].count = 0;
		}
		timeReq[i] = 0;
		d[i] = 0;
	}
}

AnsSet solve(int tid, int remT)
{
	if(tid >= trcnt || remT < 0)
		return AnsSet(0);

	if(timeReq[tid] > remT)
		return solve(tid+1, remT);

	if(dp[tid][remT].earn != -1) 
		return dp[tid][remT];

	AnsSet ans = solve(tid + 1, remT);
	AnsSet ans2 = solve(tid + 1, remT - timeReq[tid]);

	if(ans.earn < ans2.earn + v[tid])
	{
		taken[tid][remT] = 1;
		dp[tid][remT].earn = ans2.earn + v[tid];
		dp[tid][remT].count = ans2.count + 1;
	}
	else
	{
		dp[tid][remT].earn = ans.earn;
		dp[tid][remT].count = ans.count;
	}

	return dp[tid][remT];
}

int main()
{
	int first = 0;
	while(scanf("%d %d ", &t, &w) != EOF)
	{
		reset();
		scanf("%d", &trcnt);

		FOR(i, 0, trcnt)
			scanf("%d %d ", &d[i], &v[i]), timeReq[i] = 3*w*d[i];

		AnsSet ans = solve(0,t);

		if(first)   
			puts("");
		first = 1;

		printf("%d\n", ans.earn);
		printf("%d\n", ans.count);

		int j = t;
		FOR(i, 0, trcnt)
		{
			if(taken[i][j] == 1)
			{
				printf("%d %d\n", d[i], v[i]);
				j -= timeReq[i];
			}
		}
	}
	return 0; 
}
#endif