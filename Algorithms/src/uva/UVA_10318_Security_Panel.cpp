#include "CommonHeader.h"

#ifdef UVA_10318_SECURITY_PANEL
READ_INPUT(UVA_10318_SECURITY_PANEL)

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
#define MAXN 7
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int sw[3][3];
int g[MAXN][MAXN];
int R, C;

int sol[MAXN*MAXN];
int fullPatt = 0;
int endPatt = 0;

int totalPress = 0;

int dc[] = { -1, 0, 1, -1, 0, 1, -1, 0, 1 };
int dr[] = { -1, -1, -1, 0, 0, 0, 1, 1, 1 };

void reset()
{
	totalPress = 0;
	FOR(i, 0, 3)
		FOR(j, 0, 3)
		sw[i][j] = 0;

	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		g[i][j] = 0, sol[MAXN*i+j] = 0;
}

bool checkTillIndex(int idx)
{
	int r = idx / C;
	int c = idx % C;

	if(r < 0 || c < 0) return true;
	
	FOR(i, 0, r+1)
		FOR(j, 0, c+1)
		if((g[i][j]) == 0)
			return false;
	return true;
}



void ApplyPatt(int idx)
{
	int r = idx / C;
	int c = idx % C;

	if(r < 0 || c < 0) return;

	if(c == C-1)
	{
		if(r == 0)
		{
			g[0][C-1] ^= sw[1][1], g[1][C-1] ^= sw[2][1];
			if(C > 1)
				g[0][C-2] ^= sw[1][0], g[1][C-2] ^= sw[2][0]; 
		}
		else
		{
			g[r-1][C-1] ^= sw[0][1], g[r][C-1] ^= sw[1][1], g[r+1][C-1] ^= sw[2][1]; 
			if(C > 1)
				g[r-1][C-2] ^= sw[0][0], g[r][C-1] ^= sw[1][0], g[r+1][C-1] ^= sw[2][0]; 
		}
	}
	else if(c == 0)
	{
		if(r == 0)
		{
			g[0][0] ^= sw[1][1], g[0][1] ^= sw[1][2]; 
			if(R > 1)
				g[1][0] ^= sw[2][1], g[1][1] ^= sw[2][2]; 
		}
		else
		{
			g[r-1][0] ^= sw[0][1], g[r][0] ^= sw[1][1], g[r+1][0] ^= sw[2][1]; 
			g[r-1][1] ^= sw[0][2], g[r][1] ^= sw[1][2], g[r+1][1] ^= sw[2][2]; 
		}
	}
	else
	{
		if(r == 0)
			FOR(j, 0, 3)
				g[r][c+j-1] ^= sw[1][j], g[r+1][c+j-1] ^= sw[2][j]; 
		else
			FOR(j, 0, 3)
				g[r-1][c+j-1] ^= sw[0][j], g[r][c+j-1] ^= sw[1][j], g[r+1][c+j-1] ^= sw[2][j]; 
	}
}

bool solve(int idx, int pressCnt)
{
	if(checkTillIndex(R*C-1))
	{
		FOR(i, 0, pressCnt)
			printf("%d ", sol[i]+1);
		printf("\n");
		return true;
	}

	if(idx >= R*C) return false;

	//if(checkTillIndex(idx - C - 1) == false)
	//	return false;

		//Dont press & move to next button
	if(solve(idx+1, pressCnt)) return true;

	//Use this idx button and apply the pattern
	ApplyPatt(idx); 

	sol[pressCnt] = idx;
	if(solve(idx+1, pressCnt+1)) return true;
	ApplyPatt(idx); //Un-Apply



	return false;
}

int main()
{
	int t = 0;
	while(scanf("%d %d ", &R, &C), R, C)
	{
		reset();
		fullPatt = 0;
		endPatt = 0;
		FOR(i, 0, 3)
		{
			char str[4];
			scanf("%s ", &str);	
			FOR(j, 0, 3)
				if(str[j] == '*')
					sw[i][j] = 1;
				else
					sw[i][j] = 0;
		}

		memset(g, 0, sizeof(g));

		printf("Case #%d\n", ++t);

		if(solve(0, 0) == false)
			printf("Impossible.\n");
	}
	return 0;
}

#endif
