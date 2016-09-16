#include "CommonHeader.h"

#ifdef UVA_812_TRADE_ON_VERWEGGISTAN
READ_INPUT(UVA_812_TRADE_ON_VERWEGGISTAN)

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
#define MAXW 51
#define MAXB 21

#define INF 0x3f3f3f3fL
typedef long long ll;

int W;
int Bcnt[MAXW];
int profit[MAXW][MAXB];
int maxprofit[MAXW];
int cntIdx[MAXW];
int minLen[MAXW*MAXB];
int maxprofitIndex[MAXW][MAXB];
int maxprofitAns = 0;


void reset()
{
	FOR(i, 0, MAXW)
	{
		maxprofit[i] = 0;
		cntIdx[i] = 0;
		FOR(j, 0, MAXB)
			maxprofitIndex[i][j] = 0, profit[i][j] = 0;
	}

	maxprofitAns = 0;

	FOR(i, 0, MAXW*MAXB)
		minLen[i] = 0;
}

void FindMinLen(int idx, int sum)
{
	if(idx == W) 
		minLen[sum] = 1;
	else 
	{ 
		while(idx < W && cntIdx[idx] == 0)
			idx++;

		if(idx >= W) 
		{
			minLen[sum] = 1;
			return;
		}

		int count = cntIdx[idx];
		if(count > 10) count = 10;

		FOR(i, 0, count) 
		{
			FindMinLen(idx+1, sum + maxprofitIndex[idx][i]);
		}
	}
}

int main()
{
	int t = 1;
	while(scanf("%d ", &W), W)
	{
		reset();

		if(t>1) printf("\n");

		FOR(i, 0, W)
		{
			scanf("%d ", &Bcnt[i]);
			FOR(j, 0, Bcnt[i])
				scanf("%d ", &profit[i][j]), profit[i][j] = 10 - profit[i][j];
		}

		FOR(i, 0, W)
			FOR(j, 0, Bcnt[i])
		{
			if(j > 0) profit[i][j] += profit[i][j-1];

			if(maxprofit[i] < profit[i][j])
				maxprofit[i] = profit[i][j];
		}

		FOR(i, 0, W)
		{
			if(maxprofit[i] == 0)
				maxprofitIndex[i][cntIdx[i]++] = 0;
			
			FOR(j, 0, Bcnt[i]) 
				if( (maxprofit[i] == profit[i][j]))
					maxprofitIndex[i][cntIdx[i]++] = j+1;
		}

		FOR(i, 0, W)
			maxprofitAns += maxprofit[i];

		FindMinLen(0, 0);

		printf("Workyards %d\n", t++);
		printf("Maximum profit is %d.\n", maxprofitAns);
		printf("Number of pruls to buy:");

		int count = 0;
		FOR(i, 0, MAXW*MAXB)
		{
			if(minLen[i] == 1)
				printf(" %d", i), count++;
			if(count == 10)
				break;
		}

		printf("\n");
	}
	return 0;
}
#endif
