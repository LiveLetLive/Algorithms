#include "CommonHeader.h"

#ifdef UVA_12160_UNLOCK_THE_LOCK
READ_INPUT(UVA_12160_UNLOCK_THE_LOCK)

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
#define MAXR 11
#define MAXN 10000
#define INF 0x3f3f3f3f3f3f3f3fL
typedef long long ll;

int rVal[MAXR];
int L, U, R;
bool vis[MAXN];
int step[MAXN];

void reset()
{
	FOR(i, 0, MAXN)
		vis[i] = false, step[i] = 0;
}


int bfs()
{
	queue<int> q;
	q.push(L);
	vis[L] = true;
	step[L] = 0;

	while(q.empty() == false)
	{
		int u = q.front();
		q.pop();

		if(u == U)
			return step[u];

		FOR(i, 0, R)
		{
			int sum = (u + rVal[i]) % MAXN;

			if(vis[sum] == false)
			{
				q.push(sum);
				vis[sum] = true;
				step[sum] = step[u] + 1;
			}
		}
	}

	return -1;
}

int main()
{
	int t = 1;
	while(scanf("%d %d %d ", &L, &U, &R), L, U, R)
	{
		FOR(i, 0, R)
			scanf("%d ", &rVal[i]);
		reset();

		int ans = bfs();
		if(ans == -1)
			printf("Case %d: Permanently Locked\n", t++);
		else
			printf("Case %d: %d\n", t++, ans);

	}
	return 0;
}

#endif
