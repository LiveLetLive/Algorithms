#include "CommonHeader.h"

#ifdef UVA_116_UNIDIRECTIONAL_TSP
READ_INPUT(UVA_116_UNIDIRECTIONAL_TSP)

	// Tried 13 times, still WA..... :-(
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
#define MAXR 102
#define MAXC 102
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int R, C;

typedef long long DPType;

//vector<vector<int> > g(MAXR, vector<int>(MAXC));
//vector<vector<DPType> > dp(MAXR, vector<DPType>(MAXC));

int g[MAXR][MAXC];
DPType dp[MAXR][MAXC];
bool visit[MAXR][MAXC];
int P[MAXR][MAXC];

void PrintMat(char *str, int type)
{
#if 0
	printf("------------> %s [%d, %d]\n", str, R, C);
	FOR(r, 0, R)
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
			dp[r][c] = INF, g[r][c] = 0, P[r][c] = 0, visit[r][c] = 0;
	}
}

DPType solve(int r, int c)
{
	if(c == C-1)
		return dp[r][c] = g[r][c];

	if(visit[r][c] != 0)
		return dp[r][c]; 

	visit[r][c] = 1;

	int i = (r-1+R) % R;
	int j = r;
	int k = (r + 1) % R;

	DPType ans1 = solve(i, c+1);
	DPType ans2 = solve(j, c+1);
	DPType ans3 = solve(k, c+1);
	
	int minIndex = i;
	
	if(ans1 > ans2 || (ans1 == ans2 && minIndex > j)) 
	{
		ans1 = ans2;
		minIndex = j;
	}
	if(ans1 > ans3 || (ans1 == ans3 && minIndex > k)) 
	{
		ans1 = ans3;
		minIndex = k;
	}

	dp[r][c] = ans1 + g[r][c];
	P[r][c] = minIndex;
	return dp[r][c];
}

void PrintPath(int r, int c) 
{
	if(c == C-1) 
	{
		printf(" %d", r+1);
		return;
	}
	if(c == 0) 
		printf("%d", r+1);
	else 
		printf(" %d", r+1);
	PrintPath(P[r][c], c+1);
}

void PrintPath1(int idx)
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
		static int cnt = 0;
		if(cnt++ > 0)
			printf("\n");

		reset();

		FOR(r, 0, R)
			FOR(c, 0, C)
			scanf("%d ", &g[r][c]);
		PrintMat("Grid:" , 1);
		DPType minVal = INF;
		int minIndex = 0;
		int first = 0;
		FOR(i, 0, R)
		{
			DPType tmp = solve(i, 0);
			if(first++ == 0)
				minVal = tmp, minIndex = i;
			else if(tmp < minVal)
				minVal = tmp, minIndex = i;
		}

		PrintMat("DP:" , 2);

		PrintPath(minIndex, 0);

		printf("\n%lld", minVal);
	}
	return 0;
}


#endif