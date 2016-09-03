#include "CommonHeader.h"

#ifdef UVA_607_SCHEDULING_LECTURES
READ_INPUT(UVA_607_SCHEDULING_LECTURES)

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
#define MAXN 1003
#define MAXL 501

#define INF 0x3f3f3f3fL
typedef long long ll;

class Pair
{
public:
	Pair() { l = INF, sat = INF;}
	Pair(int al, int aSat) { l = al, sat = aSat;}
	int l;
	int sat;
};

int N, L, C;
int t[MAXN];
Pair dp[MAXN][MAXL];

void reset()
{
	FOR(i, 0, N+1)
	{
		t[i] = 0;
		FOR(j, 0, L+1)
			dp[i][j].l = INF, dp[i][j].sat = INF;
	}
}

int Getsat(int l)
{
	if(l == 0) return 0;
	else if (l <= 10) return -C;
	else return ((l-10)*(l-10));
}


Pair solve(int idx, int remL)
{
	if(remL < 0)
		return Pair(INF, INF);

	if(idx >= N && remL >= 0)
		return Pair(1, Getsat(remL));

	if(dp[idx][remL].l != INF)
		return dp[idx][remL];

	int MinSat = INF;

	Pair ans = solve(idx + 1, remL - t[idx]);
	Pair ans2 = solve(idx + 1, L - t[idx]);
	ans2.l++;
	ans2.sat += Getsat(remL);

	MinSat = ans.sat;

	if(ans.l > ans2.l)
	{
		ans = ans2;
		MinSat = ans2.sat;
	}
	else if(ans.l == ans2.l)
	{
		if(MinSat > (ans2.sat))
			MinSat = ans2.sat;
	}

	return dp[idx][remL] = Pair(ans.l, MinSat);
}

int main()
{
	int t1 = 1;
	while(scanf("%d ", &N), N)
	{
		if(t1 > 1) printf("\n");
		scanf("%d %d ", &L, &C);
		reset();

		FOR(i, 0, N)
			scanf("%d ", &t[i]);

		Pair ans = solve(0, L);

		printf("Case %d:\n", t1++);
		printf("Minimum number of lectures: %d\n", ans.l);
		printf("Total dissatisfaction index: %d\n", ans.sat);
	}
	return 0;
}

#endif
