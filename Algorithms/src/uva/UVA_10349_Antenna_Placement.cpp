#include "CommonHeader.h"

#ifdef UVA_10349_ANTENNA_PLACEMENT
READ_INPUT(UVA_10349_ANTENNA_PLACEMENT)

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
#define MAXN 400
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int N, M;
int g1[MAXN][MAXN];
int g[MAXN][MAXN];
int cnt[MAXN];
int vis[MAXN];
int match[MAXN];

void reset()
{
	FOR(i, 0, 40)
		FOR(j, 0, 10)
		g1[i][j] = 0;

	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = 0;
		cnt[i] = 0;
	}
}
int vCount = 0;

void PrepareGraph()
{
	vCount = 0;
	FOR(i, 0, N)
		FOR(j, 0, M)
	{
		if(g1[i][j] == 1) vCount++;

		if(g1[i][j] == 1 && (i+j)%2 )
		{
			int idx1 = i * M + j;
			if(i > 0 && g1[i-1][j] == 1) {
				int idx2 = ((i-1)*M+j);
				g[idx1][cnt[idx1]++] = idx2;
			}
			if(i < N-1 && g1[i+1][j] == 1) {
				int idx2 = ((i+1)*M+j);
				g[idx1][cnt[idx1]++] = idx2;
			}
			if(j > 0 && g1[i][j-1] == 1) {
				int idx2 = ((i)*M+(j-1));
				g[idx1][cnt[idx1]++] = idx2;
			}
			if(j < M-1 && g1[i][j+1] == 1) {
				int idx2 = (i*M+j+1);
				g[idx1][cnt[idx1]++] = idx2;
			}
		}
	}
}

int Aug(int l)
{
	if(vis[l])
		return 0;

	vis[l] = 1;

	FOR(x, 0, cnt[l])
	{
		int r = g[l][x];
		if(match[r] == -1 || Aug(match[r]))
		{
			match[r] = l;
			return 1;
		}
	}

	return 0;
}

int FindMCBM()
{
	int mcbm = 0;

	memset(match, -1, sizeof(match));

	FOR(l, 0, N*M)
	{
		memset(vis, 0, sizeof(vis));
		mcbm += Aug(l);
	}
	return mcbm;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d %d ", &N, &M);
		reset();
		char str[40][10] = { 0, };

		FOR(i, 0, N)
		{
			scanf("%s ", &str[i]);

			FOR(j, 0, strlen(str[i]))
				g1[i][j] = (str[i][j] == '*') ? 1 : 0;
		}

		PrepareGraph();
		printf("%d\n", vCount - FindMCBM()); 
	}
	return 0;
}

#endif
