#include "CommonHeader.h"


#ifdef SPOJ_FISHMONGER
READ_INPUT(SPOJ_FISHMONGER)

#include <iostream>
#include <stdio.h>

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 51
#define INF 0xFFFFFFF

class TTP
{
public:
	TTP() {};
	TTP(int t, int tt) { m_time = t; m_toll = tt; }
	int m_toll;
	int m_time;
};

int g_toll[MAXN][MAXN];
int g_time[MAXN][MAXN];
int N, Time;
TTP dp[MAXN][1001];

void reset()
{
	FOR(i, 0, N)
		FOR(j, 0, 1001)
		dp[i][j].m_time = -1, dp[i][j].m_toll = -1;
}

/*
TTP go(int u, int timeleft, int tollspent)
{
if(timeleft < 0) return TTP(INF, INF);
if(u == N -1) 
return TTP(timeleft, tollspent);

if(dp[u][timeleft].m_time != INF) return dp[u][timeleft];

FOR(v, 0, N)
{
if(u == v) continue;

TTP tmp = go(v, timeleft - g_time[u][v], tollspent + g_toll[u][v]);

if(tmp.m_time != INF && tmp.m_toll < dp[u][timeleft].m_toll)
dp[u][timeleft] = tmp;
}

return dp[u][timeleft];
}
*/




TTP go(int cur, int t_left) 
{ // returns a pair (tollpaid, timeneeded)
	if (t_left < 0) 
		return TTP(INF, INF); // invalid state, prune

	if (cur == N - 1) 
		return TTP(0, 0); // at market, tollpaid=0, timeneeded=0

	if (dp[cur][t_left].m_time != -1) 
		return dp[cur][t_left];
	TTP ans = TTP(INF, INF);

	for (int X = 0; X < N; X++) 
		if (cur != X) 
		{ // go to another city
			TTP nextCity = go(X, t_left - g_time[cur][X]); // recursive step
			if (nextCity.m_toll + g_toll[cur][X] < ans.m_toll) 
			{ // pick the min cost
				ans.m_toll = nextCity.m_toll + g_toll[cur][X];
				ans.m_time = nextCity.m_time + g_time[cur][X];
			} 
		}
		return dp[cur][t_left] = ans; 
} // store the answer to memo table

int main()
{
	int T = 0;

	while(1)
	{
		scanf("%d %d ", &N, &Time);

		if(N == 0 && Time == 0 )
			break;

		reset();

		FOR(i, 0, N)
			FOR(j, 0, N)
			scanf("%d ", &g_time[i][j]);

		FOR(i, 0, N)
			FOR(j, 0, N)
			scanf("%d ", &g_toll[i][j]);

		TTP tmp = go(0, Time);

		printf("%d %d\n", tmp.m_toll, tmp.m_time);
	}

	return 0;
}

#endif