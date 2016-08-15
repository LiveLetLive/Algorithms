#include "CommonHeader.h"

#ifdef UVA_10465_HOMER_SIMPSON
READ_INPUT(UVA_10465_HOMER_SIMPSON)

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
#define MAXN 10003
#define INF 0x3f3f3f3fL
typedef long long ll;

class Pair
{
public:
	Pair() {}
	Pair(int r, int b) { remT = r, bur = b; }
	int remT;
	int bur;
};

int P1, P2, S;
Pair dp[MAXN];
int dp1[MAXN];



void reset()
{
	FOR(i, 0, MAXN)
		dp[i].remT = INF, dp1[i] = -1;
}




Pair solve(int rem, int d)
{
	dp1[0] = 0;
	FOR(i, 0, S+1)
	{
		if((i - P1) >= 0 && dp1[i - P1] != -1) 
			dp1[i] = max(dp1[i], dp1[i - P1] + 1);
		if((i - P2) >= 0 && dp1[i - P2] != -1) 
			dp1[i] = max(dp1[i], dp1[i - P2] + 1);
	}

	int remT = 0, bur = 0;
	for(int i = S; i >= 0; i--)
	{
		if(dp1[i] != -1)
		{
			bur = dp1[i];
			remT = S - i;
			break;
		}
	}

	return Pair(remT, bur);
}

// This recurcive is makring stack overflow.... Applied normal filling.
Pair solve1(int rem, int d)
{
	if(rem <= 0) 
		return Pair(rem, d);

	if(dp[rem].remT != INF) return dp[rem];

	Pair ans1 = solve(rem - P1, d+1);
	Pair ans2= solve(rem - P2, d+1);

	Pair ans;

	if(ans1.remT < 0 || ans2.remT < 0)
		if(ans1.remT > ans2.remT)
			ans.remT = abs(ans1.remT), ans.bur = ans1.bur;
		else
			ans.remT = abs(ans2.remT), ans.bur = ans2.bur;
	else
		if(ans1.remT < ans2.remT)
			ans.remT = abs(ans1.remT), ans.bur = ans1.bur;
		else
			ans.remT = abs(ans2.remT), ans.bur = ans2.bur;

	return dp[rem] = ans;
}

int main()
{
	int T;
	
	while(scanf("%d %d %d", &P1, &P2, &S) != EOF)
	{
		reset();
		Pair p = solve(S, 0);

		if(p.remT == 0)
			printf("%d\n", p.bur);
		else
			printf("%d %d\n", p.bur, p.remT);

	}
	return 0;
}

#endif
