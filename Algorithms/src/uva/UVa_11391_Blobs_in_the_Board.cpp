#include "CommonHeader.h"

#ifdef UVA_11391_BLOBS_IN_THE_BOARD
READ_INPUT(UVA_11391_BLOBS_IN_THE_BOARD)

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
#define MAXN 16

int R, C, N;
int M;
int dp[1 << MAXN];
int cell[MAXN][MAXN];
int bitmask;

void reset()
{
	bitmask = 0;
	FOR(i, 0, (1 << MAXN))
		dp[i] = -1;

	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		cell[i][j] = 0;
}

inline int GetIndex(int r, int c)
{
	return (r * C + c);
}

inline void MakeXY(int& r, int& c, int i)
{
	r = i / C;
	c = i % C;
	return;
}

int dr[] = { 0,  0, -2, 2, 2, -2, 2 , -2 };
int dc[] = { -2, 2, 0,  0, 2, -2, -2, 2 };

int cdr[] = { 0,  0, -1, 1, 1, -1, 1 , -1 };
int cdc[] = { -1, 1, 0,  0, 1, -1, -1, 1 };

bool checkDest(int i, int v, int bitmask, int& st, int& sm)
{
	int r, c;
	//Make x, y
	MakeXY(r, c, i);

	int rd1 = dr[v] + r;
	int cd1 = dc[v] + c;

	//Out of bounds
	if(rd1 < 0 || cd1 < 0 || rd1 >= R || cd1 >= C)
		return false;

	st = GetIndex(rd1, cd1);

	//Dest is not empty
	if(bitmask & (1 << st))
		return false;

	//Middle cell doesnt have blob
	int rm1 = cdr[v] + r;
	int cm1 = cdc[v] + c;
	sm = GetIndex(rm1, cm1);

	//Dest is not empty
	if(!(bitmask & (1 << sm)))
		return false;

	return true;
}

int solve(int bitmask, int count)
{
	if(dp[bitmask] != -1)
		return dp[bitmask];

	if(count == 1)
		return 1;

	int ans = 0;

	FOR(i, 0, M)
	{
		if(bitmask & (1 << i))
		{
			FOR(v, 0, 8)
			{
				int st, sm;
				if(checkDest(i, v, bitmask, st, sm))
				{
					int newBitmask = bitmask;
					
					newBitmask &= ~(1 << i);
					newBitmask &= ~(1 << sm);
					newBitmask |= (1 << st);
					
					ans += solve(newBitmask, count - 1);
				}
			}
		}
	}

	return dp[bitmask] = ans;
}



int main()
{
	int T;
	scanf("%d", &T);

	FOR(t, 0, T)
	{
		reset();
		scanf("%d %d %d ", &R, &C, &N);

		M = R*C;
		FOR(i, 0, N)
		{
			int x, y;
			int r, c;

			scanf("%d %d ", &x, &y);

			r = x-1, c = y-1;
			cell[r][c] = 1;

			bitmask |= (1 << GetIndex(r, c));
		}

		printf("Case %d: %d\n", t+1, solve(bitmask, N));
	}

	return 0;
}


#endif