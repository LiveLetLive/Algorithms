#include "CommonHeader.h"

#ifdef UVA_10154_WEIGHTS_AND_MEASURES
READ_INPUT(UVA_10154_WEIGHTS_AND_MEASURES)

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
#define MAXN 5610
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int w[MAXN];
int wSum[MAXN];
int diff[MAXN];
int s[MAXN];
int lis[MAXN];
int N;

void reset()
{
	FOR(i, 0, N)
		lis[i] = 0;
	//FOR(i, 0, MAXN)
	//	w[i] = 0, s[i] = 0, wSum[i] = 0;
}

int main()
{
	int T, idx = 0;

	while(scanf("%d %d ", &w[idx], &s[idx]) != EOF)
		diff[idx] = s[idx]-w[idx], idx++;

	reset();

	N = idx;

	FOR(i, 0, N)
		FOR(j, 0, N)
	{
		if(diff[i] < diff[j])
			swap(diff[i],diff[j]),swap(w[i],w[j]), swap(s[i], s[j]);
		/*if(w[i] < w[j])
			swap(w[i],w[j]), swap(s[i], s[j]);
		else if(w[i] == w[j])
			if(s[i] < s[j])
				swap(s[i], s[j]);*/
	}

	FOR(i, 0, N)
	{
		if(s[i] >= w[i])
			lis[i] = 1;
		wSum[i] = w[i];
	}

	FOR(i, 1, N)
		FOR(j, 0, i)
	{
		if(s[i] >= (wSum[j] + w[i]) && lis[i] < (lis[j]+1))
		{
			lis[i] = lis[j] + 1;
			wSum[i] = wSum[j] + w[i];
		}
	}

	int maxVal = -1;

	FOR(i, 0, N)
		maxVal = max(maxVal, lis[i]);

	printf("%d\n", maxVal);

	return 0;
}

#endif
