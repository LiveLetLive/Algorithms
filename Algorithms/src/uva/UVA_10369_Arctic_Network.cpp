#include "CommonHeader.h"

#ifdef UVA_10369_ARCTIC_NETWORK
READ_INPUT(UVA_10369_ARCTIC_NETWORK)

#include <algorithm>
#include <iostream>
#include <cstdio>
#include <math.h>

#define MAXN 505
#define FOR(i, init, count) for(int i = init; i < count; i++)


	using namespace std;

int T, S, P;

class Point
{
public:
	int x, y;
};

class Edge
{
public:
	int p1, p2, d;
};

Edge g_edges[MAXN*MAXN];
Point g_Points[MAXN];
int p[MAXN];
int grank[MAXN];
int edgeCnt = 0;

void reset()
{
	edgeCnt = 0;
	FOR(i, 0, P+1)
		p[i] = -1, grank[i] = 0;
}

int find(int x)
{
	if(p[x] == -1) return x;
	return p[x] = find(p[x]);
}

void Union(int x, int y, int px, int py)
{
	if(grank[py] > grank[px]) 
		p[px] = py;
	else
	{
		p[py] = px;
		if(grank[px] == grank[py]) 
			grank[px]++;
	}
}


int mst()
{
	int maxD = 0;
	int joinCounter = 0;
	FOR(i, 0, edgeCnt)
	{
		Edge &e = g_edges[i];
		int pp1 = find(e.p1);
		int pp2 = find(e.p2);

		if(pp1 == pp2)
			continue;

		maxD = max(maxD, g_edges[i].d);

		joinCounter++;

		if(joinCounter >= (P-S))
			return maxD;

		Union(e.p1, e.p2, pp1, pp2);
		e.p1 = e.p1;
	}

	return maxD;
}

bool compare(Edge& e1, Edge& e2)
{
	return e1.d < e2.d;
}

int main()
{
	scanf("%d ", &T);

	FOR(t, 0, T)
	{
		scanf("%d %d ", &S, &P);
		reset();

		FOR(i, 0, P)
		{
			scanf("%d %d ", &g_Points[i].x, &g_Points[i].y);
		}

		//update distances N-square
		FOR(i, 0, P)
			for(int j = i-1; j >= 0; j--)
			{
				if(i == j) continue;
				int dx = g_Points[i].x - g_Points[j].x;
				dx *= dx;
				int dy = g_Points[i].y - g_Points[j].y;
				dy *= dy;

				g_edges[edgeCnt].p1 = i;
				g_edges[edgeCnt].p2 = j;
				g_edges[edgeCnt].d = dx + dy;
				edgeCnt++;
			}

			sort(g_edges, g_edges+edgeCnt, compare);

			if((P-S) > 0)
			{
				int ans = mst();
				printf("%.2lf\n", sqrt(ans));
			}
			else
				printf("%.2lf\n", 0);
	}


	return 0;
}

#endif