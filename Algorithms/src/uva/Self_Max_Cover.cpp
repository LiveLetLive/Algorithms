#include "CommonHeader.h"

#ifdef SELF_MAX_COVER
READ_INPUT(SELF_MAX_COVER)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

typedef long long ll;
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 21
#define MAXM 21
#define INF 0xfffffffffLL

int N, M, T;
char gr[MAXN][MAXM];
int gVertI[MAXN*MAXM];
int gVertJ[MAXN*MAXM];
int vertCnt = 0;

int AdjMat[MAXN*MAXM];
int mxMIS = -1;

//#define DEBUG

void reset()
{
	mxMIS = -1;
	vertCnt = 0;
	FOR(i, 0, MAXN)
		FOR(j, 0, MAXM)
		gr[i][j] = 0;

	FOR(i, 0, MAXN*MAXM)
		AdjMat[i] = 0, gVertI[i] = 0, gVertJ[i] = 0;
}

void InitBases()
{
	//Initialize bases
	FOR(i, 0, N)
	{
		if(gr[i][0] == 0) gr[i][0] = 2;
		else gr[i][0] = -1;
	}
	FOR(j, 0, M)
	{
		if(gr[0][j] == 0) gr[0][j] = 2;
		else gr[0][j] = -1;
	}
}

void PrintGrid()
{
#ifdef DEBUG
	FOR(i, 0, N)
	{
		FOR(j, 0, M)
			printf("%c ", gr[i][j]);
		printf("\n");
	}
#endif
}

void PrintGraph()
{
#ifdef DEBUG
	FOR(i, 0, vertCnt)
		printf("%d (%d, %d) --> %x \n", i, gVertI[i], gVertJ[i], AdjMat[i]);
#endif
}

//Find Max Independent set in a general graph (can be optimized for claw-free graphs)
void MIS(int i, int used, int d)
{
	if(used == ((1 << vertCnt) - 1))
		mxMIS = max(mxMIS, d);
	else
	{
		FOR(j, i, vertCnt)
			if(!(used & (1 << j)))
				MIS(j+1, used | AdjMat[j], d+1 );
	}
}

void Preprocess()
{
	PrintGrid();

	FOR(i, 0, N-1)
		FOR(j, 0, M-1)
	{
		if(gr[i+1][j] != 'X' && gr[i+1][j+1] != 'X' && gr[i][j+1] != 'X' && gr[i][j] != 'X')
			gVertI[vertCnt] = i, gVertJ[vertCnt] = j,vertCnt++;
	}
}

bool isOverlap(int x, int y)
{
	//All 2x2 cells of src & dest to compare, if even 1 cell overlap declare this combination as overlap
	int xi = gVertI[x]; 
	int xj = gVertJ[x];	

	int yi = gVertI[y]; 
	int yj = gVertJ[y];	

	FOR(i, 0, 2)
	{
		FOR(j, 0, 2)
		{
			int xii = xi + i;
			int xjj = xj + j;

			FOR(m, 0, 2)
			{
				FOR(n, 0, 2)
				{
					int yii = yi + m;
					int yjj = yj + n;

					if(xii == yii && xjj == yjj)
						return true;
				}
			}
		}
	}

	return false;
}

void MakeGraph()
{
	//Left presence
	FOR(i, 0, vertCnt)
		AdjMat[i] |= (1 << i);

	//Make a bit-wise graph with all neighbors info
	FOR(i, 0, vertCnt)
	{
		FOR(j, i+1, vertCnt)
		{
			if(isOverlap(i, j))
			{
				AdjMat[i] |= (1 << j);
				AdjMat[j] |= (1 << i);
			}
		}
	}
	PrintGraph();
}

int solve()
{
	//Find The possible 2x2 & detect vertcies as left top cell of the 2x2 possible squares
	Preprocess();

	//Make a graph with the given vertices, overlapping squares will make adjacant edges.
	MakeGraph();

	//Find the maximum independent sets
	MIS(0, 0, 0);

	return 0;
}

int main()
{
	int T1 = 0;
	scanf("%d ", &T1);
	FOR(t, 0, T1)
	{
		scanf("%d %d %d ", &N, &M, &T);
		reset();
		FOR(i, 0, N)
			scanf("%s ", &gr[i]);

		solve();
		printf("%d\n", mxMIS); 
	}
	return 0;  
} 
#endif