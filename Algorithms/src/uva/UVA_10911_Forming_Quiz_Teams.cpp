#include "CommonHeader.h"

#ifdef UVA_10911_FORMING_QUIZ_TEAMS
READ_INPUT(UVA_10911_FORMING_QUIZ_TEAMS)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;
#define INF 0x3FFFFFFF
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN (8*2)

double dp[1<<MAXN];
double dist[MAXN][MAXN];
int Xcord[MAXN];
int Ycord[MAXN];
int N;
int M;
int bitmask = 0;

void reset()
{
	bitmask = 0;
	FOR(i, 0, (1<<MAXN))
		dp[i] = INF;
}

double calcAns(int bitmask)
{
	if(bitmask == ((1<<M)-1))
		return 0;

	if(dp[bitmask] < INF)
		return dp[bitmask];

	int i = 0;
	double ans = INF;

	for(i = 0; i < M; i++)
		if( !(bitmask & (1<<i)) )
			break;

	for(int j = i+1; j < M; j++)
		if( !(bitmask & (1<<j)) )
			ans = min(ans, dist[i][j] + calcAns(bitmask | (1 << i ) | (1 << j)) );

	return dp[bitmask] = ans;
}


int main()
{
	int t = 0;
	while(scanf("%d ", &N), N)
	{
		reset();
		M = 2*N; 

		FOR(i, 0, M)
			scanf("%*s %d %d ", &Xcord[i], &Ycord[i]);

		FOR(i, 0, M)
			FOR(j, 0, M)
			dist[i][j] = dist[j][i] = sqrt( ( (Xcord[i] - Xcord[j]) * (Xcord[i] - Xcord[j]))
			+ ( (Ycord[i] - Ycord[j]) * (Ycord[i] - Ycord[j]))); 

		printf("Case %d: %.2lf\n", ++t, calcAns(0));
	}
	return 0;
}


#endif