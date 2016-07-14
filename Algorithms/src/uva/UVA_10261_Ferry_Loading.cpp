#include "CommonHeader.h"

#ifdef UVA_10261_FERRY_LOADING
READ_INPUT(UVA_10261_FERRY_LOADING)

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
#define MAXN 505
#define MAXM 10205


int T;
int FerrLen = 0;
int cIndex = 0;
int CLen[MAXN];
int SumLen[MAXN];

int dp[205][10005];
int pre[205][10005];
int	maxID = 0;
int	maxLen = 0;

void reset()
{
	cIndex = 0;
	maxID = 0;
	maxLen = 0;
	FOR(i, 0, 205)
		FOR(j, 0, 10005)
		dp[i][j] = -1, pre[i][j] = 0;

}

void allocate(int id, int lVol)
{
	if(id > cIndex) 
		return;

	//if(dp[id][lVol] != -1)
	//	return;

	/*if(lVol > FerrLen || rVol > FerrLen) 
	return id-1;
	*/
	if(lVol+CLen[id] <= FerrLen)
	{
		dp[id][lVol] = 1;
		pre[id][lVol] = 0;
		maxID = max(maxID, id);
		maxLen = max(maxLen, lVol);

		printf("id:%d, lVol:%d, dp[id][lVol]: %d, pre[id][lVol]: %d\n",
			id, 
			lVol, 
			dp[id][lVol],
			pre[id][lVol]
		);	
		//Left	
		allocate(id + 1, lVol + CLen[id]);


	}

	if((SumLen[id] - lVol) <= FerrLen)
	{
		dp[id][lVol] = 1;
		pre[id][lVol] = 1;
		maxID = max(maxID, id);
		maxLen = max(maxLen, lVol);
		printf("id:%d, lVol:%d, dp[id][lVol]: %d, pre[id][lVol]: %d\n",
			id, 
			lVol, 
			dp[id][lVol],
			pre[id][lVol]
		);
		//Right
		allocate(id + 1, lVol);

	}
	return;
}

void solve()
{
	allocate(0, 0);
}

int main()
{
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d ", &FerrLen);

		//Initialize ferry length
		FerrLen *= 100;

		while(scanf("%d ", &CLen[cIndex]))
		{
			if(CLen[cIndex] == 0)
				break;

			if(cIndex == 0)
				SumLen[cIndex] = CLen[cIndex];
			else
				SumLen[cIndex] = CLen[cIndex] + SumLen[cIndex-1];

			cIndex++;
		}

		solve();
	}

	return 0;
}


#endif