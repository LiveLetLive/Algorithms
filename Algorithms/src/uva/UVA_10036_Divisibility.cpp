#include "CommonHeader.h"

#ifdef UVA_10036_DIVISIBILITY
READ_INPUT(UVA_10036_DIVISIBILITY)

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
#define MAXK 100
#define MAXN 10001
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N, K, M;

int v[MAXN];
int dp[2][MAXK+MAXK][MAXN]; //[sign][remainder][index]

void reset()
{
	FOR(i, 0, 2)
		FOR(j, 0, MAXK+MAXK)
		FOR(k, 0, MAXN)
		dp[i][j][k] = -1;
}

int solve(int s, int rem, int id)
{
	if(id == N && rem == 0)
		return 1;

	if(id == N && rem != 0)
		return 0;

	if(dp[s][rem+MAXK][id] != -1)
		return dp[s][rem+MAXK][id];

	int val ;

	if(s) val = rem + v[id]; 
	else val = rem - v[id];

	val %= K;

	if(solve(0, val, id+1)) return 1;
	if(solve(1, val, id+1)) return 1;

	return dp[s][rem+MAXK][id] = 0;
}


int main()
{
	scanf("%d ", &M);
	FOR(m, 0, M)
	{
		scanf("%d %d", &N, &K);
		reset();

		FOR(i, 0, N)
			scanf("%d ", &v[i]);

		int ans = solve(0, v[0]%K, 1);
		if(ans == 0)
			ans = solve(1, v[0]%K, 1);

		if(ans)
			printf("Divisible\n");
		else
			printf("Not divisible\n");
	}
	return 0;
}


#endif