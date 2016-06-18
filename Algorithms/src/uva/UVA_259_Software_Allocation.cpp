#include "CommonHeader.h"


#ifdef UVA_259_SOFTWARE_ALLOCATION
READ_INPUT(UVA_259_SOFTWARE_ALLOCATION)

#include <iostream>
#include <cstdio>
#include <queue>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 3001

// 0 src, 1-26 app, 27-36 comp, 37 sink
int edge[38][38];
int mf, f;

void reset()
{
	f = 0;
	mf = 0;

	FOR(i, 0, 38)
	{
		FOR(j, 0, 38)
			edge[i][j] = 0;
	}
}

#define INF 1000000

int dist[39];
int Parent[39];

bool bfs(int s)
{
	FOR(i, 0, 38)
		dist[i] = INF, Parent[i] = -1;

	queue<int> q;
	dist[s] = 0;
	q.push(s);

	while(!q.empty())
	{
		int u = q.front();
		q.pop();

		if(u == 37)
			return true;

		FOR(v, 0, 38)
		{
			if(u == v) continue;
			if(dist[v] == INF && edge[u][v] > 0)
			{
				q.push(v);
				dist[v] = dist[u]+1;
				Parent[v] = u;
			}
		}
	}

	return false;
}

void augment(int v, int minEdge)
{
	if(Parent[v] == -1) return;

	int p = Parent[v];

	if(minEdge > edge[p][v])
		minEdge = edge[p][v];

	augment(p, minEdge);

	f = minEdge;

	edge[p][v] -= minEdge;
	edge[v][p] += minEdge;
}

int maxflow()
{
	while(bfs(0))
	{
		augment(37, INF);

		if(f == 0)
			break;

		mf += f;
	}
	return mf;
}

int t = 0;
int main()
{
	char str[50] = {};
	char *str1;

	while(1)
	{
		int usr_total = 0;
		reset();		
	
		char *ptr = NULL;
		t++;
		while(1)
		{
			ptr = gets(str);

			if(ptr == NULL || str[0] == 0)
				break;

			int e = str[0] - 'A' + 1;
			int usrnum = str[1] - '0';
			usr_total += usrnum;

			edge[0][e] = usrnum;

			str1 = str + 3;
			int i = 0;
			while(str1[i] != ';')
			{
				edge[e][str1[i] - '0' + 27] = INF;
				edge[str1[i] - '0' + 27][37] = 1;
				i++;
			}
		}
	

		int ans = maxflow();
		if(usr_total != mf)
			printf("!\n");
		else
		{
			int j  = 0;
			for(int i = 27; i <= 36; i++)
			{
				for(j = 1; j <= 26; j++)
				{
					if(edge[i][j] == 1)
					{
						char ch = 'A' + j - 1;
						printf("%c", ch);
						break;
					}
				}

				if(j == 27)
					printf("_");
			}

			printf("\n");
		}

		if(ptr == NULL && str[0] != 0)
				break;
	}

	return 0;
}

#endif