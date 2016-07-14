#include "CommonHeader.h"

#ifdef UVA_10341_SOLVE_IT
READ_INPUT(UVA_10341_SOLVE_IT)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 100005

int E;
int p, q, r, s, t, u;

double func(double x)
{
	return ((double)p * exp(-x) 
		+ (double)q * sin(x) 
		+ (double)r * cos(x) 
		+ (double)s * tan(x) 
		+ (double)t * x * x 
		+ (double)u);
}

double solve(double l, double r, bool& res)
{
	int counter = 0;
	double mid = 0.0;
	double ym = 0;

	while(counter++ < 75) 
	{
		mid = (l + r) / 2.0;
		ym = func(mid);

		if(fabs(ym) < FLT_EPSILON)
		{
			res = true;
			return mid;
		}

		if(ym > 0) 
			l = mid;
		else r = mid;
	}

	res = false;
	return mid;
}

int main()
{
	while(scanf("%d %d %d %d %d %d ", &p, &q, &r, &s, &t, &u) != EOF)
	{
		 if(!p && !q && !r && !s && !t && !u) 
		 {
            puts("0.0000");
            continue;
        }

		bool res = false;
		double ans = solve(0.0, 1.0, res);

		if(res == false)
			printf("No solution\n");
		else
			printf("%.4lf\n", ans);
	}
	return 0; 
}
 
#endif