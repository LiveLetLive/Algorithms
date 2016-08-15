#include "CommonHeader.h"

#ifdef UVA_1172_THE_BRIDGES_OF_KOLSBERG
READ_INPUT(UVA_1172_THE_BRIDGES_OF_KOLSBERG)

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
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int B1, B2;

map<string, int> osIdx;
int osIdxCnt;

int b1[MAXN];
int b2[MAXN];
int c1[MAXN];
int c2[MAXN];

class Pair
{
public:
	Pair() { }
	Pair(ll t, int c) {  tr = t; cnt = c;}
	ll tr;
	int cnt;

	bool operator > (Pair& p)
	{
		if(this->tr > p.tr) return true;
		else if(this->tr == p.tr)
			if(this->cnt < p.cnt) return true;
			else return false;
		else return false;
	}
};

Pair dp[MAXN][MAXN]; //[i][j]

void reset()
{
	osIdx.clear();
	osIdxCnt = 0;
	FOR(i, 0, MAXN)
	{
		b1[i] = 0, b2[i] = 0, c1[i] = 0, c2[i] = 0; 
		FOR(j, 0, MAXN)
			dp[i][j].tr = 0, dp[i][j].cnt = 0;
	}
}
void PrintDPTable()
{
	FOR(i, 1, B2+1)
	{
		FOR(j, 1, B1+1)
			printf("(%3lld, %d) ", dp[i][j].tr, dp[i][j].cnt);
		printf("\n\n");
	}
	printf("-----------------\n");
}

Pair solve()
{
	FOR(i , 1, B2+1)
		FOR(j , 1, B1+1)
	{
		// Calculate the best out of self, top, left & left-top

		//Take the bigger one from left & top
		if(dp[i-1][j] > dp[i][j-1])
			dp[i][j] = dp[i-1][j];
		else
			dp[i][j] = dp[i][j-1];

		// If new bridge can be made, then check if that will yeild more benefit than existing best.
		if(b1[j] == b2[i]) 
		{
			ll tmp = dp[i-1][j-1].tr + c1[j] + c2[i];
			int tmpN = dp[i-1][j-1].cnt + 1;

			Pair p(tmp, tmpN);
			if(p > dp[i][j])
				dp[i][j] = p;
		}
	}
	//PrintDPTable();

	return dp[B2][B1];
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(m, 0, T)
	{
		osIdxCnt = 0;
		reset();

		scanf("%d ", &B1);
		FOR(i, 1, B1+1)
		{
			char str[11];
			int val;
			scanf("%*s");
			scanf("%s %d", &str, &val);

			if(osIdx[str] == NULL)
				b1[i] = osIdxCnt+1, c1[i] = val, osIdxCnt++, osIdx[str] = osIdxCnt; 
			else
				b1[i] = osIdx[str], c1[i] = val; 
		}

		scanf("%d ", &B2);
		FOR(i, 1, B2+1)
		{
			char str[11];
			int val;
			scanf("%*s");
			scanf("%s %d", &str, &val);

			if(osIdx[str] == NULL)
				b2[i] = osIdxCnt+1, c2[i] = val, osIdxCnt++, osIdx[str] = osIdxCnt; 
			else
				b2[i] = osIdx[str], c2[i] = val; 
		}

		if(B1 == 0 || B2 == 0) {printf("0 0\n");}
		else
		{
			Pair p = solve();
			printf("%lld %d\n", p.tr, p.cnt);
		}
	}
	return 0;
}


#endif