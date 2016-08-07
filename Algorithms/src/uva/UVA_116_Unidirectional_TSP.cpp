#include "CommonHeader.h"

#ifdef UVA_116_UNIDIRECTIONAL_TSP
READ_INPUT(UVA_116_UNIDIRECTIONAL_TSP)

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
#define MAXR 48
#define MAXC 111
#define INF 0x7FFFFFFFFFFFFFFFL
typedef long long ll;
int R, C;

typedef long long DPType;

//vector<vector<int> > g(MAXR, vector<int>(MAXC));
//vector<vector<DPType> > dp(MAXR, vector<DPType>(MAXC));

int g[MAXR][MAXC];
DPType dp[MAXR][MAXC];

void PrintMat(char *str, int type)
{
#if 0
	printf("------------> %s [%d, %d]\n", str, R, C);
	FOR(r, 0, 3*R)
	{
		FOR(c, 0, C)
		{
			if(type == 1)
				printf("%2d ", g[r][c]);
			if(type == 2)
				printf("%2d ", dp[r][c]);
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
	if(r < 0 || r >= 3*R)
		return INF;

	if(c == C-1)
		return dp[r][c] = g[r][c];

	if(dp[r][c] != INF)
		return dp[r][c]; 

	DPType ans2 = solve(r, c+1);
	DPType ans1 = solve(r-1, c+1);
	DPType ans3 = solve(r+1, c+1);
	
	return dp[r][c] = (min(ans1, min(ans2, ans3)) + g[r][c]);
}

void PrintPath(int idx)
{
	printf("%d", (idx%R)+1);

	int P[3] = {};

	FOR(i, 1, C)
	{
		P[0] = (idx-1);
		P[1] = (idx);
		P[2] = (idx+1);

		int minIndex = 3*R;
		int minIndexOrg = 3*R;
		DPType val = INF;
		FOR(k , 0, 3) 
		{
			if(P[k] >= 0 && P[k] < (3*R))
			{
				//lexicographical output.
				if (dp[P[k]][i] < val || (dp[P[k]][i] == val && minIndex > ((P[k]+R)%R))) 
				{
					val = dp[P[k]][i];
					// Store min direction.
					minIndexOrg = P[k];
					minIndex = ((P[k]+R)%R);
				}
			}
		}

		idx = minIndexOrg;
		printf(" %d", ((idx+R)%R)+1);
	}
}

int main()
{
	while(scanf("%d %d", &R, &C) != EOF)
	{
		static int counter = 0;
		if(counter++ > 0)
			printf("\n");

		reset();

		FOR(r, 0, R)
			FOR(c, 0, C)
			scanf("%d ", &g[r][c]), g[r+R][c] = g[r][c], g[r+2*R][c] = g[r][c];
		PrintMat("Grid:" , 1);
		DPType minVal = INF;
		int minIndex = 0;

		FOR(i, 0, R)
		{
			DPType tmp = solve(R + i, 0);
			if(tmp < minVal)
				minVal = tmp, minIndex = i;
		}

		PrintMat("DP:" , 2);

		PrintPath(R+minIndex);

		printf("\n%lld", minVal);
	}
	return 0;
}


#endif