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

map<string, int> idx;
int dp[MAXN][MAXN]; //[i][j]

int b1[MAXN];
int b2[MAXN];

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
		scanf("%d ", &N);


		reset();


	}
	return 0;
}


#endif