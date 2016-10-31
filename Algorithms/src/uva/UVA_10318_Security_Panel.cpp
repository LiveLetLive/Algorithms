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

//#define DEBUG

#define INF 0x3f3f3fL
typedef long long ll;

int sw[3][3];
int g[MAXN][MAXN];
int R, C;

int sol[MAXN*MAXN];
int solAns[MAXN*MAXN][MAXN*MAXN];
int fullPatt = 0;
int endPatt = 0;

int totalPress = 0;
int totalPressIndex = 0;

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
		g[i][j] = 0;

	FOR(i, 0, MAXN*MAXN)
		FOR(j, 0, MAXN*MAXN)
		sol[i] = 0, solAns[i][j] = 0;
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

int tmp[MAXN][MAXN] = { 0, };


void ApplyPatt1(int idx)
{
	int r = idx / C;
	int c = idx % C;

	if(r < 0 || c < 0) return;

	if(c == C-1)
	{
		if(r == 0)
		{
			tmp[0][C-1] ^= sw[1][1], tmp[1][C-1] ^= sw[2][1];
			if(C > 1)
				tmp[0][C-2] ^= sw[1][0], tmp[1][C-2] ^= sw[2][0]; 
		}
		else
		{
			tmp[r-1][C-1] ^= sw[0][1], tmp[r][C-1] ^= sw[1][1], tmp[r+1][C-1] ^= sw[2][1]; 
			if(C > 1)
				tmp[r-1][C-2] ^= sw[0][0], tmp[r][C-2] ^= sw[1][0], tmp[r+1][C-2] ^= sw[2][0]; 
		}
	}
	else if(c == 0)
	{
		if(r == 0)
		{
			tmp[0][0] ^= sw[1][1], tmp[0][1] ^= sw[1][2]; 
			if(R > 1)
				tmp[1][0] ^= sw[2][1], tmp[1][1] ^= sw[2][2]; 
		}
		else
		{
			tmp[r-1][0] ^= sw[0][1], tmp[r][0] ^= sw[1][1], tmp[r+1][0] ^= sw[2][1]; 
			tmp[r-1][1] ^= sw[0][2], tmp[r][1] ^= sw[1][2], tmp[r+1][1] ^= sw[2][2]; 
		}
	}
	else
	{
		if(r == 0)
			FOR(j, 0, 3)
			tmp[r][c+j-1] ^= sw[1][j], tmp[r+1][c+j-1] ^= sw[2][j]; 
		else
			FOR(j, 0, 3)
			tmp[r-1][c+j-1] ^= sw[0][j], tmp[r][c+j-1] ^= sw[1][j], tmp[r+1][c+j-1] ^= sw[2][j]; 
	}
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
				g[r-1][C-2] ^= sw[0][0], g[r][C-2] ^= sw[1][0], g[r+1][C-2] ^= sw[2][0]; 
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
		if(pressCnt < totalPress)
		{
			FOR(i, 0, pressCnt)
				solAns[totalPressIndex][i] = sol[i];
#ifdef DEBUG
			memset(tmp, 0, sizeof(tmp));

			FOR(i, 0, pressCnt)
			{
				printf("%d\n", sol[i]);
				ApplyPatt1(sol[i]);
				FOR(i, 0, R)
				{
					FOR(j, 0, C)
						if(tmp[i][j] == 1) printf("*");
						else printf(".");
						printf("\n");
				}
				printf("\n");
				printf("\n");
			}
#endif
			totalPressIndex++;
			totalPress = pressCnt; 
			return false;
		}
		return false;
	}

	if(idx >= R*C) return false;

	if(checkTillIndex(idx - C - 2) == false)
		return false;

	//Use this idx button and apply the pattern
	ApplyPatt(idx); 

	sol[pressCnt] = idx;
	if(solve(idx+1, pressCnt+1)) return true;
	ApplyPatt(idx); //Un-Apply

	//Dont press & move to next button
	if(solve(idx+1, pressCnt)) return true;

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

		totalPress = INF;
		totalPressIndex = 0;
		solve(0, 0);

		if(totalPress == INF)
			printf("Impossible.\n");
		else
		{
			FOR(i, 0, totalPress)
				printf("%d ", solAns[totalPressIndex-1][i]+1);
			printf("\n");
		}
	}
	return 0;
}

#endif
