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
int alloc[205][10005];
int	maxID = 0;
int	maxLen = 0;

void reset()
{
	cIndex = 0;
	maxID = 0;
	maxLen = 0;
	FOR(i, 0, 205)
		FOR(j, 0, 10005)
		dp[i][j] = -1, alloc[i][j] = -1;
}

int allocate(int id, int lVol, int d)
{
	if(id > cIndex)
		return d-1;

	if(lVol > FerrLen || ((SumLen[id-1] - lVol) > FerrLen))
		return d-1;

	if(dp[id][lVol] != -1)
		return dp[id][lVol];

	int ans1 = 0, ans2 = 0;

	ans1 = allocate(id + 1, lVol + CLen[id], d+1);
	ans2 = allocate(id + 1, lVol, d+1);

	if(ans1 > ans2)
		alloc[id][lVol] = 0, dp[id][lVol] = ans1;
	else
		alloc[id][lVol] = 1, dp[id][lVol] = ans2;

	return dp[id][lVol];
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

		int ans = 0;
		if(cIndex == 0 || FerrLen == 0)
		{
			if(t) puts("");
			printf("%d\n", ans);
		}
		else
		{
			ans = allocate(1, CLen[0], 0);	
			ans++;

			if(t) puts("");

			printf("%d\n", ans);

			int idx = 0;
			int vol = 0;

			alloc[0][0] = 0;

			FOR(i, 0, ans)
			{
				if(alloc[idx][vol] == 0)
					printf("port\n"), vol += CLen[idx], idx++;
				else if(alloc[idx][vol] == 1)
					printf("starboard\n"), idx++;
			}
		}
	}

	return 0;
}


#endif