#include "CommonHeader.h"


#ifdef UVA_11906_KNIGHT_IN_WAR_GRID
READ_INPUT(UVA_11906_KNIGHT_IN_WAR_GRID)


#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAX 105


int N, M, R, C, T;
char d[MAX][MAX];
char g[MAX][MAX];
bool visited[MAX][MAX];
int W;

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
	FOR(i, 0, R)
	{
		FOR(j, 0, C)
			printf("%3d ", d[i][j]);
		printf("\n");
	}
	printf("\n\n");
}

void resetVisit()
{
	FOR(i, 0, MAX)
		FOR(j, 0, MAX)
		visited[i][j] = 0;
}

void reset()
{
	FOR(i, 0, MAX)
		FOR(j, 0, MAX)
		d[i][j] = 0, g[i][j] = 0;

	resetVisit();
}

bool isSafe(int i, int j)
{
	if(i < 0 || j < 0)
		return false;

	if(i >= R || j >= C)
		return false;

	if(g[i][j] == -1)
		return false;

	return true;
}


void dfs(int i, int j)
{
	if(visited[i][j] == true && (i == 0 && j == 0))
		return;

	if(isSafe(i, j) == false || visited[i][j] == true)
		return;

	visited[i][j] = true;
	d[i][j]++;

	{
		int dr[] = { M, M, -M, -M, N, N, -N, -N };
		int dc[] = { N, -N, N, -N, M, -M, M, -M };

		FOR(k, 0, 8)
		{
			int m = i+dr[k];
			int n = j+dc[k];

			dfs(m , n);
		}
	}
}

int main()
{
	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		reset();

		scanf("%d %d %d %d ", &R, &C, &N, &M);
		scanf("%d ", &W);

		FOR(k, 0, W)
		{
			int x, y;
			scanf("%d %d ", &x, &y);
			g[x][y] = -1;
		}

		dfs(0,0);

		//PrintMat();

		int countOdd = 0, countEven = 0;

		FOR(m, 0, R)
		{
			FOR(n, 0, C)
			{
				if(M==0 || N == 0 || M == N)
					d[m][n] /= 2;

				if(d[m][n] > 0 && (d[m][n] % 2 == 1)) 
					countOdd++;
				else if(d[m][n] > 0) 
					countEven++;
			}
		}

		if(countEven == 0 && countOdd == 0)
			printf("Case %d: %d %d\n", t+1, 1, 0);
		else
			printf("Case %d: %d %d\n", t+1, countEven, countOdd);
	}
	return 0;
}

#endif
