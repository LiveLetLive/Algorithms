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
int maxprofitIndex[MAXW][MAXB];
int maxprofitAns = 0;
void reset()
{
	FOR(i, 0, W)
	{
		maxprofit[i] = 0;
		cntIdx[i] = 0;
		FOR(j, 0, Bcnt[i])
			maxprofitIndex[i][j] = -INF;
	}
	maxprofitAns = 0;

}

int main()
{
	int t = 0;
	while(scanf("%d ", &W), W)
	{
		FOR(i, 0, W)
		{
			scanf("%d ", &Bcnt[i]);
			FOR(j, 0, Bcnt[i])
				scanf("%d ", &profit[i][j]), profit[i][j] = 10 - profit[i][j];
		}

		reset();

		FOR(i, 0, W)
			FOR(j, 0, Bcnt[i])
		{
			if(j > 0) profit[i][j] += profit[i][j-1];

			if(maxprofit[i] < profit[i][j])
				maxprofit[i] = profit[i][j];
		}
		
		FOR(i, 0, W)
			FOR(j, 0, Bcnt[i])
			if(maxprofit[i] == profit[i][j])
				maxprofitIndex[i][cntIdx[i]++] = j+1;
		
		FOR(i, 0, W)
			maxprofitAns += maxprofit[i];

		printf("Workyards %d\n", t+1);
		printf("Maximum profit is %d.\n", maxprofitAns);
		printf("Number of pruls to buy: \n");
	}
	return 0;
}

#endif
