#include "CommonHeader.h"

#ifdef SELF_TWO_MONSTER_IN_MAZE
READ_INPUT(SELF_TWO_MONSTER_IN_MAZE)

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
#define MAXN 25
#define INF 0x3f3f3f3fL
typedef long long ll;

int g[MAXN][MAXN];
int dis[MAXN][MAXN][MAXN][MAXN];
int s1r, s1c, d1r, d1c; 
int s2r, s2c, d2r, d2c;
int N;
int fw_dist[MAXN*MAXN][MAXN*MAXN];

int dr[] = { -1, -1, -1,  0, 0,  1, 1, 1, 0 };
int dc[] = { -1,  0,  1, -1, 1, -1, 0, 1, 0 };

int fr[] = { -1, -1, -1,  0 };
int fc[] = { -1,  0,  1, -1 };

class State
{
public:
	bool operator == (State& s)
	{
		return (i1 == s.i1 && i2 == s.i2 && j1 == s.j1 && j2 == s.j2);
	}

	/*bool operator < (const State& s) const
	{
	return (dis > s.dis);
	}*/

	bool operator < (const State& s) const
	{
		return (dis + fw_dist[i1*N+j1][d1r*N+d1c] + fw_dist[i2*N+j2][d2r*N+d2c] >  
			(s.dis + fw_dist[s.i1*N+s.j1][d1r*N+d1c] + fw_dist[s.i2*N+s.j2][d2r*N+d2c]  ));  
	}

	State() {}
	State(int x1, int y1, int x2, int y2, int d)
	{	i1 = x1, j1 = y1, i2 = x2, j2 = y2; dis = d;}
	int i1, j1;
	int i2, j2;
	int dis;
};

class Queue
{
public:
	Queue() { top = -1; cnt = 0; }
	void reset() { top = -1; cnt = 0; }
	State m_queue[MAXN*MAXN*MAXN*MAXN];
	void push(State s)
	{
		m_queue[++top] = s;
		cnt++;
	}

	State pop()
	{
		cnt--;
		return m_queue[top--];
	}
	int top;
	int cnt;
	bool isEmpty() { return top == -1;}
};

inline bool isAttack(int x1, int y1, int x2, int y2)
{
	if(fw_dist[x1*N+y1][x2*N+y2] <= 1 || fw_dist[x2*N+y2][x1*N+y1] <= 1 )
		return true;

	//FOR(i, 0, 9)
	//	if(x1 + dr[i] == x2 && y1 + dc[i] == y2)
	//		return true;
	return false;
}

inline bool isValid(int x1, int y1)
{
	if(x1 < 0 || y1 < 0 || x1 >= N || y1 >= N || g[x1][y1] == 1)
		return false;

	return true;
}

void reset()
{
	FOR(i, 0, N)
		FOR(j, 0, N)
		FOR(k, 0, N)
		FOR(l, 0, N)
		dis[i][j][k][l] = INF;

	FOR(i, 0, N*N)
		FOR(j, 0, N*N)
		fw_dist[i][j] = INF;
}

#if 0
void PrintSolution()
{
	State src(s1r, s1c, s2r, s2c, 0);
	State dst(d1r, d1c, d2r, d2c, 0);
	State s = dst;

	while(!(s == src))
	{
		gSol[s.i1][s.j1] = 1;
		gSol[s.i2][s.j2] = 2;
		printf("%d %d %d %d \n", s.i1, s.j1, s.i2, s.j2);
		s = sol[s.i1][s.j1][s.i2][s.j2];
	}
	gSol[s.i1][s.j1] = 1;
	gSol[s.i2][s.j2] = 2;
	printf("%d %d %d %d \n\n\n", s.i1, s.j1, s.i2, s.j2);

	FOR(i, 0, N)
	{
		FOR(j, 0, N)
		{
			if(i == s1r && j == s1c) printf("A ");
			else if(i == d1r && j == d1c) printf("B ");
			else if(i == s2r && j == s2c) printf("D ");
			else if(i == d2r && j == d2c) printf("E ");
			else printf("%d ", g[i][j]);
		}
		printf("\n");
	}
	printf("\n");
	printf("\n");

	FOR(i, 0, N)
	{
		FOR(j, 0, N)
			printf("%d ", gSol[i][j]);
		printf("\n");
	}

}
#endif
static int pushCounter = 0;

int astar()
{
	State dst(d1r, d1c, d2r, d2c, 0);
	priority_queue<State> q;
	q.push(State(s1r, s1c, s2r, s2c, 0));
	dis[s1r][s1c][s2r][s2c] = 0;

	while(q.empty() == false)
	{
		//Find the least distance node first
		State s = q.top();
		q.pop();

		//Terminate on reaching desination at first shot.
		if(s == dst)
			break;

		if(dis[s.i1][s.j1][s.i2][s.j2] < s.dis)
			continue;

		//Find all 81 combinations
		FOR(x, 0, 9)
		{
			int ni = s.i1 + dr[x];
			int nj = s.j1 + dc[x];

			if(isValid(ni, nj) == false) continue;

			FOR(y, 0, 9)
			{
				//Skip coming to halt, when both monster doesnt move.
				if(x == 8 && y == 8) continue;

				int di = s.i2 + dr[y];
				int dj = s.j2 + dc[y];

				if(isValid(di, dj) == false) continue;
				if(isAttack(ni, nj, di, dj)) continue;

				//Minimize the distance table for this combination
				if(dis[ni][nj][di][dj] > (dis[s.i1][s.j1][s.i2][s.j2] + 1))
				{
					State ns(ni, nj, di, dj, (dis[s.i1][s.j1][s.i2][s.j2] + 1));
					q.push(ns);
					pushCounter++;
					dis[ni][nj][di][dj] = (dis[s.i1][s.j1][s.i2][s.j2] + 1);
				}
			}
		}
	}

	int ans;
	if(dis[d1r][d1c][d2r][d2c] == INF)
		ans = -1;
	else
		ans = dis[d1r][d1c][d2r][d2c];

	printf("%d\tpushCnt=%d\tremInQueue=%d\n", ans, pushCounter, q.size());
	pushCounter = 0;
	return 0;
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		scanf("%d %d %d %d ", &s1r, &s1c, &d1r, &d1c);
		scanf("%d %d %d %d ", &s2r, &s2c, &d2r, &d2c);

		reset();

		FOR(i, 0, N)
			FOR(j, 0, N)
		{
			scanf("%d ", &g[i][j]);

			if(g[i][j] == 0)
			{
				FOR(k, 0, 4)
				{
					int ni = i + dr[k];
					int nj = j + dc[k];
					if(isValid(ni, nj))
					{
						fw_dist[ni*N+nj][i*N+j] = fw_dist[i*N+j][ni*N+nj] = 1;  
						fw_dist[i*N+j][i*N+j] = 0;  
						fw_dist[ni*N+nj][ni*N+nj] = 0;  
					}
				}
			}
		}

		int NB = N*N;

		FOR(k, 0, NB)
			FOR(i, 0, NB)
			FOR(j, 0, NB)
			fw_dist[i][j] = min(fw_dist[i][j], fw_dist[i][k] + fw_dist[k][j]);
#if 0
		FOR(i, 0, N)
		{
			FOR(j, 0, N)
				printf("%d ", g[i][j]);
			printf("\n");
		}

		printf("\n");
		printf("\n");

		FOR(i, 0, NB)
		{
			FOR(j, 0, NB)
				printf("%d ", fw_dist[i][j] >= INF ? 0 : fw_dist[i][j]);
			printf("\n");
		}
#endif
		s1r--, s1c--, d1r--, d1c--, s2r--, s2c--, d2r--, d2c--;
		astar();

	}
	return 0;
}

#endif

/*
#include <cstdio> 
#include <algorithm> 
#include <cstring> 

using namespace std; const int maxn = 9; int n, a [maxn]; 
// h () represents the successor to the incorrect number, a maximum change 
//three digits subsequent digital 

int h () 
{
	int cnt = 0; 
	for (int i = 0; i <n- 1; i ++) 
	{
		if (!(a[i] + 1 == a [i + 1]))
			cnt ++; 
	} 
	if (!a[n-1] == n) cnt ++; 
	return cnt;} 

bool is_sorted ()
{
	for (int i = 0; i <n; i ++) 
	{if (! a [i] = i + 1) return false;} return true;
} 

bool dfs (int d, int maxd) 
{
	// pruning condition 
	if (3 * d + h ( )> 3 * maxd) return false; 
	
	if (is_sorted ()) return true; 
	
	int b [maxn], olda [maxn] ; 
	
	memcpy (olda, a, sizeof (a)); 
	
	// exhaustive cut start and end position 
	
	for (int i = 0; i <n; i ++) 
	{
		for (int j = i; j <n; j ++ ) 
		{
			int cnt = 0; 
			for (int k = 0; k <n; k ++) 
			{
				if (k <i || k> j) 
				{
					b [cnt ++] = a [k]; 
				}
			}
			
			// exhaustive attaching position 
			for (int k = 0; k <= cnt; k ++) 
			{
				int cnt2 = 0; 
				for (int p = 0; p <k; p ++) 
				{
					a [cnt2 ++] = b [p ];
				} 
				
				for (int p = i; p <= j; p ++) 
				{
					a [cnt2 ++] = olda [p];
				}
				
				for (int p = k; p <cnt; p ++) 
				{
					a [cnt2 ++] = b [ p];
				}
				
				if (dfs ( d + 1, maxd)) return true; 
				
				memcpy (a, olda, sizeof (olda));
			}
		}
	} 
	return false;
} 

int solve () 
{
	if (is_sorted ()) return 0; 
	
	// Code after the warehouse mentioned in the experimental maximum edits to 5. 
	
	int ans = 5; 
	for ( int maxd = 1; maxd <ans; maxd ++) 
	{
		if (dfs (0, maxd)) 
		{
			return maxd;
		}
	} return ans;
} 

int main () 
{
	//freopen("in.txt","r",stdin); 
	int kase = 0; 
	while (scanf ( "% d", & n) == 1 && n) 
	{
		for ( int i = 0; i <n ; i ++) 
		{
			scanf ( "% d", & a [i]);
		}
		
		printf ( "Case% d:% d \ n", ++ kase, solve ());
	} return 0; 
}
*/