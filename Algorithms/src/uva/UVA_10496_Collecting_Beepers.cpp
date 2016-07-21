
#include "CommonHeader.h"

#ifdef UVA_10496_COLLECTING_BEEPERS
READ_INPUT(UVA_10496_COLLECTING_BEEPERS)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 12
#define INF 0x3f3f3f3f

int N;
int beepX[MAXN];
int beepY[MAXN];
int dp[MAXN][1<<MAXN];
int dist[MAXN][MAXN];
int R, C;
int si, sj;

void reset()
{
	FOR(i, 0, (MAXN))
	FOR(j, 0, (1 << MAXN))
		dp[i][j] = INF;
}

int calc(int bitmask, int currPos)
{
	if(bitmask == ((1 << (N+1)) - 1) )
		return dist[0][currPos];

	if(dp[currPos][bitmask] != INF)
		return dp[currPos][bitmask];


	int ans = INF;

	FOR(i, 0, N+1)
		if(!(bitmask & (1 << i)))
		{
			ans = min(ans, calc( bitmask | (1 << i), i) + dist[i][currPos] );
		}

	return dp[currPos][bitmask] = ans;
}

int main()
{
	int T;

	scanf("%d", &T);

	FOR(t, 0, T)
	{
		reset();

		scanf("%d %d ", &C, &R);
		scanf("%d %d ", &sj, &si);
		scanf("%d", &N);

		beepX[0] = sj;
		beepY[0] = si;

		FOR(i, 1, N+1)
			scanf("%d %d ", &beepX[i], &beepY[i]);

		FOR(i, 0, N+1)
			FOR(j, 0, N+1)
			dist[i][j] = dist[j][i] = abs(beepX[i] - beepX[j]) + abs(beepY[i] - beepY[j]);

 		printf("The shortest path has length %d\n", calc(0, 0));
	}
	return 0; 
}

#endif