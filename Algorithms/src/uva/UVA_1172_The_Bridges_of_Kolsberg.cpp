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

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 1001
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;
int N, K, M;

map<string, int> osIdx;
int osIdxCnt;
int dp[MAXN][MAXN]; //[i][j]

int b1[MAXN];
int b2[MAXN];
int c1[MAXN];
int c2[MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXN)
		dp[i][j] = -1;
}

int main()
{
	scanf("%d ", &M);
	FOR(m, 0, M)
	{
		osIdxCnt = 0;

		scanf("%d ", &N);
		FOR(i, 0, N)
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

		scanf("%d ", &M);
		FOR(i, 0, M)
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


		reset();


	}
	return 0;
}


#endif