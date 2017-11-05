#include "CommonHeader.h"

#ifdef CG_CIRCUIT_BOARD_BATTERIES
READ_INPUT(CG_CIRCUIT_BOARD_BATTERIES)

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
#define MAXN 103
#define INF 0x3f3f3f3fL
typedef long long ll;
int N;

void reset()
{
}

class Line
{
public:
	Line(){}
	Line(int _x1, int _y1, int _x2, int _y2)
	{
		x1 = _x1, y1 = _y1, x2 = _x2, y2 = _y2;
	}

	int x1, y1, x2, y2;
};

Line l[MAXN*2];

int findNearPointsX(int i, int j)
{
	int minD = INF;
	minD = min(minD, abs(l[i].x1 - l[j].x1));
	minD = min(minD, abs(l[i].x1 - l[j].x2));
	minD = min(minD, abs(l[i].x2 - l[j].x1));
	minD = min(minD, abs(l[i].x2 - l[j].x2));

	return minD;
}

int findNearPointsY(int i, int j)
{
	int minD = INF;
	minD = min(minD, abs(l[i].y1 - l[j].y1));
	minD = min(minD, abs(l[i].y1 - l[j].y2));
	minD = min(minD, abs(l[i].y2 - l[j].y1));
	minD = min(minD, abs(l[i].y2 - l[j].y2));

	return minD;
}

int solve()
{
	int maxDX = 0;
	int maxDY = 0;
	FOR(i, 0, N)
	FOR(j, i+1, N)
	{
		if(i == j) continue;

		maxDX = max(maxDX, findNearPointsX(i, j));
		maxDY = max(maxDY, findNearPointsY(i, j));

		//printf("Line %d - Line %d X = %.1f Y = %.1f\n", i+1, j+1, (float)maxDX/2.0, (float)maxDY/2.0);
	}

	return min(maxDX, maxDY);
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);

		FOR(i, 0, N)
		{
			scanf("%d %d %d %d ", &l[i].x1, &l[i].y1, &l[i].x2, &l[i].y2);
			l[i].x1 *= 2, l[i].y1 *= 2, l[i].x2 *= 2, l[i].y2 *= 2;
		}

		int ans = solve();

		printf("Case #%d\n", t+1);
		
		if(ans % 2)
			printf("%d.5\n", ans/2);
		else
			printf("%d\n", ans/2);
	}
	return 0;
}

#endif
