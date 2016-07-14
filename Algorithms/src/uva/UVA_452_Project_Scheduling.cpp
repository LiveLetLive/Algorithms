#include "CommonHeader.h"


#ifdef UVA_452_PROJECT_SCHEDULING
READ_INPUT(UVA_452_PROJECT_SCHEDULING)

#include <iostream>
#include <string.h>
#include <queue>
#include <stdio.h>

using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 28
#define INF 0x3f3f3f3f

int g[MAXN][MAXN];
int val[MAXN];
int zeroInDegree[MAXN];
bool in_queue[MAXN];
int dist[MAXN];
void reset()
{
	FOR(i, 0, MAXN)
	{
		FOR(j, 0, MAXN)
			g[i][j] = INF;
		val[i] = 0;
		zeroInDegree[i] = 0;
		dist[i] = INF;
	}
}

void sfpa(int s)
{
	queue<int> q;

	//FOR(i, 0, 26)
	//	dist[i] = INF;

	q.push(s);
	in_queue[s] = true;
	dist[s] = -val[s];

	while(!q.empty())
	{
		int u = q.front();
		q.pop();
		in_queue[u] = 0;

		FOR(v, 0, 26)
		{
			if(g[u][v] != INF && dist[v] >= (dist[u] + g[u][v]))
			{
				dist[v] = dist[u] + g[u][v];
				if(in_queue[v] == false)
				{
					in_queue[v] = true;
					q.push(v);
				}
			}
		}
	}

}

int main()
{
	int T = 0;

	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		char ch;
		char str[50] = {0,};
		char *ptr = NULL;
		int tmp;

		reset();

		scanf("%*");

		while(ptr = gets(str))
		{
			char str1[50] = {0,};

			if(str[0] == 0) break;

			sscanf(str, "%c %d %s", &ch, &tmp, &str1);

			val[ch - 'A'] = tmp;

			int len = strlen(str1);
			if(len == 0) zeroInDegree[ch - 'A'] = 1;

			FOR(i, 0, len)
				g[str1[i] - 'A'][ch - 'A'] = 1;
		}

		FOR(i, 0, 26)
			FOR(j, 0, 26)
		{
			if(g[i][j] == 1)
				g[i][j] = -val[j];
		}

		FOR(i, 0, 26)
		{
			if(zeroInDegree[i] == 1)
			{
				sfpa(i);
			}
		}

		int minVal = INF;

		FOR(i, 0, 26)
			minVal = min(minVal, dist[i]);

		printf("%d\n", -minVal);

		if(t < T-1)
			printf("\n");
	}

	return 0;
}

#endif