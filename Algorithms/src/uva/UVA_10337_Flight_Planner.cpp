#include "CommonHeader.h"

#ifdef UVA_10337_FLIGHT_PLANNER
READ_INPUT(UVA_10337_FLIGHT_PLANNER)

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

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXR 11
#define MAXC 1001
#define INF 0x3F3F3F3F
typedef long long ll;
int R, C;

typedef long long DPType;

//vector<vector<int> > g(MAXR, vector<int>(MAXC));
//vector<vector<DPType> > dp(MAXR, vector<DPType>(MAXC));

int g[MAXR][MAXC];
DPType dp[MAXR][MAXC];

void PrintMat(char *str, int type)
{
#if 1
	printf("------------> %s [%d, %d]\n", str, R, C);
	FOR(r, 0, R)
	{
		FOR(c, 0, C)
		{
			if(type == 1)
				printf("%3d ", g[r][c]);
			if(type == 2)
				(dp[r][c] >= INF) ? printf("!!! "): printf("%3d ", dp[r][c]);
		}
		printf("\n");
	}
	printf("------------\n");
#endif
}

void reset()
{
	FOR(r, 0, MAXR)
	{
		FOR(c, 0, MAXC)
			dp[r][c] = INF, g[r][c] = 0;
	}
}

DPType solve(int r, int c)
{
	if(r < 0 || r >= R || c > C)
		return INF;

	if(c == C)
		if(r == R-1)	return 0;
		else			return INF;

	if(dp[r][c] != INF)
		return dp[r][c]; 

	DPType ans2 = solve(r, c+1) + 30- g[r][c];
	DPType ans1 = solve(r-1, c+1) + 60- g[r][c];
	DPType ans3 = solve(r+1, c+1) + 20- g[r][c];
	
	dp[r][c] = (min(ans1, min(ans2, ans3)) );

	//PrintMat("DP:", 2);
	return dp[r][c];
}

int main()
{
	int T, M;
	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		scanf("%d ", &M);

		R = 10, C = M/100;
		
		reset();
		
		FOR(r, 0, R)
			FOR(c, 0, C)
			scanf("%d ", &g[r][c]);

		//PrintMat("Grid:" , 1);
		solve(R-1, 0);

		//PrintMat("DP:" , 2);
		printf("%lld\n\n", dp[9][0]);
	} 
	return 0;
}


#endif