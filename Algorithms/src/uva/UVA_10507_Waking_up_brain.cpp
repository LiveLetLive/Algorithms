
#include "CommonHeader.h"

#ifdef UVA_10507_WAKING_UP_BRAIN
READ_INPUT(UVA_10507_WAKING_UP_BRAIN)

#include <iostream>
#include <algorithm>
#include <string.h>
#include <queue>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 30

class Edge
{
public:
	int x;
	int y;
};

Edge e[MAXN*MAXN];
int p[MAXN];
int cnt[MAXN];

int N;
int M;
int gWakeCnt = 0;

int mainSet = 0;
void reset()
{
	gWakeCnt = 0;

	FOR(i, 0, (MAXN*MAXN))
		e[i].x = 0, e[i].y = 0; 

	FOR(i, 0, MAXN)
		p[i] = -1, cnt[i] = 0;
}

int find(int x)
{
	if(p[x] == -1) return x;
	else return find(p[x]);
}

void Union(int x, int y)
{
	int px = find(x);
	int py = find(y);

	p[py] = px;
}

int FindTime()
{
	int nCounter = 0;
	while(1)
	{
		FOR(i, 0, MAXN)
			cnt[i] = 0;

		bool Found = false;
		FOR(i, 0, M)
		{
			int x = e[i].x;
			int y = e[i].y;

			int px = find(x);
			int py = find(y);

			if(px == mainSet && py != mainSet)
				cnt[py]++;
			else if(py == mainSet && px != mainSet)
				cnt[px]++;
		}


		FOR(i, 0, MAXN)
			if(cnt[i] >= 3)
				Union(mainSet, i), Found = true, gWakeCnt++;

		if(Found == false)
			break;

		nCounter++;
	}

	return nCounter;
}

int main()
{
	int t = 0;
	while(scanf("%d ", &N) != EOF)
	{
		t++;
		char str[30];
		reset();
		scanf("%d ", &M);
		scanf("%s ", &str);

		{
			int x = str[0] - 'A';
			int y = str[1] - 'A';
			int z = str[2] - 'A';
			Union(x, y);
			Union(y, z);
			mainSet = find(x);
		}

		gWakeCnt = 3;

		FOR(i, 0, M)
		{
			int x, y;
			scanf("%s ", &str);
			x = str[0] - 'A';
			y = str[1] - 'A';
			e[i].x = x;
			e[i].y = y;
		}

		int ans = FindTime();

		if(gWakeCnt == N)
			printf("WAKE UP IN, %d, YEARS\n", ans);
		else
			printf("THIS BRAIN NEVER WAKES UP\n");
	}
	return 0;
}

#endif