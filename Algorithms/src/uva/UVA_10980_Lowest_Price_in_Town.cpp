#include "CommonHeader.h"

#ifdef UVA_10980_LOWEST_PRICE_IN_TOWN
READ_INPUT(UVA_10980_LOWEST_PRICE_IN_TOWN)

#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>
#include <sstream>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 22
#define MAXK 105
#define INF 0x3f3f3f3fL
typedef long long ll;

int price[MAXN];
int size[MAXN];
int N, K;

int dp[MAXN][MAXK];

void reset()
{
	FOR(i, 0, MAXN)
	{
		price[i] = 0, size[i] = 0;

		FOR(j, 0, MAXK)
			dp[i][j] = -1;
	}

}

int solve(int idx, int iRem)
{
	if(iRem <= 0)
		return 0;

	if(idx >= N)
		return INF;

	if(dp[idx][iRem] != -1)
		return dp[idx][iRem];

	int ans = INF;

	FOR(i, 0, N)
		ans = min(ans, price[i] + solve(i, iRem - size[i]));

	return dp[idx][iRem] = ans;
}

int main()
{
	int h, l, t = 0;
	while(scanf("%d.%d %d", &h, &l, &N) != EOF)
	{
		t++;

		reset();

		price[0] = h*100+l;
		size[0] = 1;

		FOR(i, 0, N)
		{
			int len;
			scanf("%d %d.%d", &len, &h, &l);
			price[i+1] = h*100+l;
			size[i+1] = len;
		}

		N++;

		{
			while(getchar() != '\n');

			string str;
			getline(cin, str);
			stringstream line(str);

			printf("Case %d:\n", t);

			while(line >> K)
			{
				int ans = solve(0, K);
				printf("Buy %d for $%d.%02d\n", K, ans/100, ans%100);
			}
		}

	}
	return 0;
}

#endif
