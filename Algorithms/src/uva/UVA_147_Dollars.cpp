#include "CommonHeader.h"

#ifdef UVA_147_DOLLARS
READ_INPUT(UVA_147_DOLLARS)

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
#define MAXN 305
#define MAXG 105
#define MAXC 105
#define INF 100000000
typedef long long ll;

ll dp[11][30005];

int c[] = { 5,10,20,50,	100,	200,	500,	1000,2000,5000,	10000};

void reset()
{
	FOR(i, 0, 11)
	FOR(j, 0, 30005)
		dp[i][j] = -1;
}

ll ways(int idx, int val)
{
	if(idx >= 11 || val < 0)
		return 0;

	if(val == 0)
		return 1;

	if(dp[idx][val] != -1)
		return dp[idx][val];

	ll ans = 0;
	ans = ways(idx+1, val) + ways(idx, val - c[idx]);

	return dp[idx][val] = ans;
}

int main()
{
	char str[20];
	double in;
	int Val;
	reset();	
	
	while(scanf("%s", &str))
	{
		int m, d;
		int len = strlen(str);
		sscanf(str + len - 2, "%d", &d);
		
		str[len-3] = 0;
		sscanf(str, "%d", &m);
		Val = m*100+d;
		
		if(Val == 0) break;

		ll ans = ways(0, Val);

		printf("%3d.%02d%17lld\n", Val/100, Val%100, ans);
	}

	return 0;
}


#endif