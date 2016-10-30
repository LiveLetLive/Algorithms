#include "CommonHeader.h"

#ifdef UVA_1098_ROBOTS_ON_ICE
READ_INPUT(UVA_1098_ROBOTS_ON_ICE)

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
#define MAXR 8
#define MAXC 8
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

//#define DEBUG 1

int R, C;

int r1, c1;
int r2, c2;
int r3, c3;

int g[MAXR][MAXC];
int cg[MAXR][MAXC];
int vis[MAXR][MAXC];

int visCnt1 = 0;
int visCnt2 = 0;
int visCnt3 = 0;
int stepCnt = 0;
int	phase = 1;
int recCounter = 0;
int totalPathCnt = 0;

void reset()
{
	FOR(i, 0, MAXR)
		FOR(j, 0, MAXC)
		g[i][j] = 0, vis[i][j] = 0;

	visCnt1 = (R*C)/4;
	visCnt2 = (R*C)/2;
	visCnt3 = (R*C*3)/4;
	totalPathCnt = 0;
	stepCnt = 1;
	phase = 1;
}

int dr[] = { 0,  0, 1, -1 };
int dc[] = { 1, -1, 0, 0 };

void dfs2(int r, int c)
{
	cg[r][c] = 1;

	FOR(x, 0, 4)
	{
		int nr = r + dr[x];
		int nc = c + dc[x];

		if(nr < 0 || nc < 0 || nr >= R || nc >= C)		continue;
		if(cg[nr][nc]) continue;
		
		dfs2(nr, nc);
	}
}

bool isMultipleConnected()
{
	memcpy(cg, vis, sizeof(vis));

	int noOfComp = 0;

	FOR(i, 0, R)
		FOR(j, 0, C)
	{
		if(cg[i][j] == 0)
		{
			if(noOfComp > 0)
				return true;
			noOfComp++;
			dfs2(i, j);
		}
	}
	return false;
}


void solve(int r, int c)
{
	if(r == r1 && c == c1 && stepCnt != visCnt1)
		return;
	if(r == r2 && c == c2 && stepCnt != visCnt2)
		return;
	if(r == r3 && c == c3 && stepCnt != visCnt3)
		return;

	if((r != r1 || c != c1) && stepCnt == visCnt1)
		return;
	if((r != r2 || c != c2) && stepCnt == visCnt2)
		return;
	if((r != r3 || c != c3) && stepCnt == visCnt3)
		return;

	if(r == 0 && c == 1 && stepCnt != R*C)
		return;
	if(r == 0 && c == 1 && stepCnt == R*C)
	{
		totalPathCnt++;
		return;
	}
	if((r != 0 || c != 1) && stepCnt == R*C)
		return;

	if(phase == 1)
		if((abs(r-r1)+abs(c-c1) + stepCnt) > visCnt1)
			return;
	if(phase == 2)
		if((abs(r-r2)+abs(c-c2) + stepCnt) > visCnt2)
			return;
	if(phase == 3)
		if((abs(r-r3)+abs(c-c3) + stepCnt) > visCnt3)
			return;

	if(isMultipleConnected()) 
		return;

	vis[r][c] = 1;
	
	if(r == r1 && c == c1)
		phase++;
	if(r == r2 && c == c2)
		phase++;
	if(r == r3 && c == c3)
		phase++;

	//recCounter++;

	FOR(x, 0, 4)
	{
		int nr = r + dr[x];
		int nc = c + dc[x];

		if(nr < 0 || nc < 0 || nr >= R || nc >= C)		continue;
		if(vis[nr][nc]) continue;
		
		stepCnt++;
		solve(nr, nc);
		stepCnt--;
	}

	vis[r][c] = 0;

	if(r == r1 && c == c1)
		phase--;
	if(r == r2 && c == c2)
		phase--;

	return;
}

int main()
{
	int t = 1;
	while(scanf("%d %d ", &R, &C), R, C)
	{
		scanf("%d %d ", &r1, &c1);
		scanf("%d %d ", &r2, &c2);
		scanf("%d %d ", &r3, &c3);
		reset();

		//recCounter = 0;

		solve(0, 0);
#ifndef DEBUG
		printf("Case %d: %d\n", t++, totalPathCnt);
#else
		printf("Case %d: %d %d\n", t++, totalPathCnt, recCounter);
#endif
	}

	return 0;
}

#endif
