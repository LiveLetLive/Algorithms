#include "CommonHeader.h"


#ifdef UVA_11906_KNIGHT_IN_WAR_GRID
READ_INPUT(UVA_11906_KNIGHT_IN_WAR_GRID)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAX 105
typedef int ll;

struct Water
{
	char x;
	char y;
};

int N, M, R, C, T;
char d[MAX][MAX];
struct Water w[MAX];
int visited[MAX][MAX];
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
		d[i][j] = 0, w[j].x = -1, w[j].y = -1;

	resetVisit();
}

bool isSafe(int i, int j)
{
	if(i < 0 || j < 0)
		return false;

	if(i >= R || j >= C)
		return false;

	FOR(k, 0, W)
	{
		if(w[k].x == i && w[k].y == j)
			return false;
	}

	return true;
}


void dfs(int i, int j)
{


	if(visited[i][j] == true && i == 0 && j == 0)
		return;

	visited[i][j] = true;


	//printf("%d %d \n",i, j);
	//PrintMat();

	if(M == 0)
	{
		int dr[] = { 0, 0, N, -N };
		int dc[] = { N, -N, 0, 0 };

		FOR(k, 0, 4)
		{
			int m = i+dr[k];
			int n = j+dc[k];

			if(isSafe(m,n) == true)
			{
				d[m][n]++;
				if(visited[m][n] == false)
					dfs(m , n);
			}
		}
	}
	else if(N == 0)
	{
		int dr[] = { M, -M, 0, 0 };
		int dc[] = { 0, 0, M, -M };

		FOR(k, 0, 4)
		{
			int m = i+dr[k];
			int n = j+dc[k];

			if(isSafe(m,n) == true)
			{
				d[m][n]++;
				if(visited[m][n] == false)
					dfs(m , n);
			}
		}

	}
	else if(N == M)
	{
		int dr[] = { M, M, -M, -M };
		int dc[] = { M, -M, M, -M };

		FOR(k, 0, 4)
		{
			int m = i+dr[k];
			int n = j+dc[k];

			if(isSafe(m,n) == true)
			{
				d[m][n]++;
				if(visited[m][n] == false)
					dfs(m , n);
			}
		}
	}
	else
	{
		int dr[] = { M, M, -M, -M, N, N, -N, -N };
		int dc[] = { N, -N, N, -N, M, -M, M, -M };

		FOR(k, 0, 8)
		{
			int m = i+dr[k];
			int n = j+dc[k];

			if(isSafe(m,n) == true)
			{
				d[m][n]++;
				if(visited[m][n] == false)
					dfs(m , n);
			}
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
			scanf("%d %d ", &w[k].x, &w[k].y);

		dfs(0,0);

		PrintMat();

		int countOdd = 0, countEven = 0;

		FOR(m, 0, R)
			FOR(n, 0, C)
			if(d[m][n] > 0 && (d[m][n] % 2 == 1)) countOdd++;
			else if(d[m][n] > 0) countEven++;

			printf("Case %d: %d %d\n", t+1, countEven, countOdd);

	}
	return 0;
}

#endif
