#include "CommonHeader.h"


#ifdef UVA_469_WETLANDS_OF_FLORIDA
READ_INPUT(UVA_469_WETLANDS_OF_FLORIDA)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAX 105
typedef int ll;

int N, M, K, T;
char d[MAX][MAX];

int g_Size;

inline int MyMin(int i, int j)
{
	return i<j ? i : j;
}

inline int MyMax(int i, int j)
{
	return i>j ? i : j;
}

void PrintMat()
{
	/*	FOR(i, 0, count)
	printf("%3d ", Mat[i]);
	printf("\n");*/	
	printf("\n");
}

bool visited[MAX][MAX];

void reset()
{
	FOR(i, 0, MAX)
		FOR(j, 0, MAX)
		d[i][j] = 0;
}

void resetVisit()
{
	FOR(i, 0, MAX)
		FOR(j, 0, MAX)
		visited[i][j] = false;
}

int dc[] = {1, -1, 0, 0, -1, -1, 1, 1 };
int dr[] = {0,  0, 1, -1, -1, 1, 1, -1};

void dfs(int i, int j)
{
	if(i < 0 || j < 0)
		return;

	if(visited[i][j] == true)
		return;

	visited[i][j] = true;

	if(d[i][j] == 'W')
	{
		//d[i][j] = '.';
		g_Size++;

		FOR(x, 0, 8)
		{
			dfs(i + dr[x], j + dc[x]);
		}
	}
}

int main()
{

	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		char str[105];
		int idx = 0;
		reset();
		resetVisit();

		while(gets(str))
		{
			if(str[0] == '\0')
			{
				idx = 0;
				printf("\n");
				break;
			}
			else if(str[0] != 'L' && str[0] != 'W')
			{
				int x1, y1;
				sscanf(str, "%d %d ", &x1, &y1);
				
				resetVisit();

				dfs(x1-1, y1-1);
				printf("%d\n", g_Size);
				g_Size = 0;
			}
			else
			{
				sscanf(str, "%s ", &d[idx++]);
			}
		}
	}
	return 0;
}

#endif