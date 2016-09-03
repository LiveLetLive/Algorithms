#include "CommonHeader.h"

#ifdef UVA_1099_SHARING_CHOCOLATE
READ_INPUT(UVA_1099_SHARING_CHOCOLATE)

#include <iostream>
#include <algorithm>
#include <string>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>

	using namespace std;
#define INF 0x3FFFFFFF
#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 16

int W, H, N;
int dp[100][1 << MAXN];
int size[MAXN];
int bitmask;

void reset()
{
	bitmask = 0;
	FOR(i, 0, 100)
		FOR(j, 0, (1 << MAXN))
		dp[i][j] = -1;

	FOR(i, 0, MAXN)
		size[i] = 0;
}


int solve(int bitmask, int currW)
{
	if(dp[currW][bitmask] != -1)
		return dp[currW][bitmask];

	int ans = 0;

	FOR(i, 0, N)
	{
		if(bitmask & (1 << i))
		{
		}
	}

	return dp[currW][bitmask] = ans;
}

int main()
{
	int t = 0;
	while(scanf("%d", &N), N)
	{
		reset();
		scanf("%d %d %d ", &W, &H);

		int sum = 0;

		FOR(i, 0, N)
			scanf("%d", &size[i]), sum += size[i];

		if((W*H) != sum)
		{
			printf("Case %d: %s\n", t+1, "No");
			continue;
		}
		printf("Case %d: %s\n", t+1, solve(bitmask, W) ? "Yes" : "No");
	}

	return 0;
}

#endif
/*
#include <stdio.h> #include <string.h> 
#include <algorithm> 
#define min (a, b) ((a) <(b) (a) :( b?))
using namespace std; 
const int N = 17; 
const int MAXN = (1 << N); 
const int XN = 105; 
int n, x, y, big [N], sum [MAXN]; 
bool dp [MAXN] [XN], vis [MAXN ] [XN]; 

int bitcount (int x) 
{
	if (x == 0) return 0; return bitcount (x >> 1) + (x & 1);
} 

bool solve (int s, int x) 
{
	if (vis [ s] [x]) 
		return dp [s] [x]; 
	vis [s] [x] = 1;
	if (bitcount (s) == 1) 
		return dp [s] [x] = true; 
	
	if (sum [ s]% x) 
		return dp [s] [x] = false; 
	
	int y = sum [s] / x; 
	
	for (int s0 = (s - 1) & s; s0> 0; s0 = (s0 - 1) & s ) 
	{
		int s1 = (s ^ s0); 
		if (sum [s0]% x == 0 && solve (s0, min (x, sum [s0] / x)) 
			&& solve (s1, min (x, sum [ s1] / x))) 
			return dp [s] [x] = true; 
		
		if (sum [s0]% y == 0 && solve (s0, min (y, sum [s0] / y)) 
			&& solve (s1 , min (y, sum [s1] / y))) 
			return dp [s] [x] = true;
	} 
	
	return dp [s] [x] = false;
}

int main () 
{
	int cas = 0; 
	while ( ~ scanf ( "% d", & n) && n) 
	{
		scanf ( "% d% d", & x, & y); 
		memset (vis, 0, sizeof (vis)); 
		memset (sum, 0, sizeof (sum) ); 
		
		for (int i = 0; i <n; i ++) 
			scanf ( "% d", & big [i]); 
		
		for (int state = 0; state <(1 << n); state ++) 
		{
			for (int i = 0; i <n; i ++) 
				if (state & (1 << i)) 
					sum [state] + = big [i];
		}
		if (sum [(1 << n) -1] = x * y ) 
		{
			printf ( "Case% d: No \ n", ++ cas); 
			continue;
		}
		
		printf ( "Case% d:% s \ n", ++ cas, solve ((1 << n) - 1, ? min (x, y)) "Yes": "No");
	}
	return 0;
} */
