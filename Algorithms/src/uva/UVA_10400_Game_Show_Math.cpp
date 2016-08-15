#include "CommonHeader.h"

#ifdef UVA_10400_GAME_SHOW_MATH
READ_INPUT(UVA_10400_GAME_SHOW_MATH)

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
#define MAXN 103
#define MAXS 32001

#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int N, TGT;
int dp[4][MAXN][MAXS+MAXS];
int inp[MAXN];
int Exp[MAXN];

void reset()
{
	FOR(i, 0, 4)
	{
		inp[i] = 0, Exp[i] = 0;
		FOR(j, 0, MAXN)
			FOR(k, 0, MAXS+MAXS)
			dp[i][j][k] = -1;
	}
}

bool CheckRange(int n)
{
	if(n < -32000 || n > 32000) return false;
	return true;
}

//sign[4] = +, -, *, /

int solve(int op,int idx, int val)
{
	if(idx == N && val == TGT)
		return 1;

	if(idx == N)
		return 0;

	if(dp[op][idx][val+MAXS] != -1)
		return dp[op][idx][val+MAXS];

	int nVal = val + inp[idx];
	if(CheckRange(nVal)) {
		if(solve(0, idx+1, nVal) == 1)
		{
			Exp[idx-1] = 0;
			return 1;
		}
	}
	nVal = val - inp[idx];
	if(CheckRange(nVal)) {
		if(solve(1, idx+1, nVal) == 1)
		{
			Exp[idx-1] = 1;
			return 1;
		}
	}

	nVal = val * inp[idx];
	if(CheckRange(nVal)) {
		if(solve(2, idx+1, nVal) == 1)
		{
			Exp[idx-1] = 2; 
			return 1;
		}
	}

	if((val % inp[idx]) == 0)
	{
		nVal = val / inp[idx];
		if(CheckRange(nVal)) {
			if(solve(3, idx+1, nVal) == 1)
			{
				Exp[idx-1] = 3;
				return 1;
			}
		}
	}

	return dp[op][idx][val+MAXS] = 0;
}

char getsign(int x)
{
	if(x == 0) return '+';
	if(x == 1) return '-';
	if(x == 2) return '*';
	if(x == 3) return '/';
}
void PrintExp()
{
	printf("%d", inp[0]);

	FOR(i, 1, N)
		printf("%c%d", getsign(Exp[i-1]), inp[i]);

	printf("=%d\n", TGT);
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		reset();
		scanf("%d ", &N);

		FOR(i, 0, N)
			scanf("%d ", &inp[i]);
		scanf("%d ", &TGT);

		int ans = solve(0, 1, inp[0]);

		if(ans == 0)
			printf("NO EXPRESSION\n");
		else
			PrintExp();
	}
	return 0;
}

#endif
