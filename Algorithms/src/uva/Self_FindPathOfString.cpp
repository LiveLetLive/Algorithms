#include "CommonHeader.h"

#ifdef SELF_FINDPATHOFSTRING
READ_INPUT(SELF_FINDPATHOFSTRING)

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
#define MAXN 52
#define MAXS 10002
#define INF 0x3f3f3f3fL
typedef long long ll;

class State
{
public:
	State()
	{}

	State(int xv, int yv, int disv, int idxv)
	{
		r = xv, c = yv, dist = disv, idx = idxv;
	}
	int r, c;
	int idx;
	int dist;
};

#define OWN_QUEUE 1

template <class T> class Queue
{
public:
	Queue()
	{
		f = tail = 0;
	}

	bool empty() { return f == tail; }
	T front() { return data[tail]; }
	void pop() { tail++; tail %= MAXS; }
	void push(T val) { data[f] = val; f++; f %= MAXS; }

	T data[MAXS];
	int f;
	int tail;
};

int R, C;
char str[MAXN][MAXN];

struct visit
{
	char vis[MAXS][MAXN][MAXN];
};

char s[10001];

int LenS;

int dr[4] = { -1, 0,	0, 1 };
int dc[4] = {  0, -1, 1, 0 };

class Cache
{
public:
	int cx[4][MAXN][MAXN];
	int cy[4][MAXN][MAXN];
};

Cache *cache = NULL;

inline bool isSafe(int r, int c)
{
	if(r < 0 || r >= R || c < 0 || c >= C)
		return false;
	return true;
}

char FindNextChar(int i, int j, int& x, int& y,int dir)
{
	int u = i;
	int v = j;

	if(cache->cx[dir][i][j] != INF)
	{
		if(cache->cx[dir][i][j] == -1)
			return -1;

		x = cache->cx[dir][i][j];
		y = cache->cy[dir][i][j];
		return str[x][y];
	}

	while(1)
	{
		u += dr[dir];
		v += dc[dir];

		if(isSafe(u,v) == false) 
		{
			cache->cx[dir][i][j] = -1;
			cache->cy[dir][i][j] = -1;

			return -1;
		}
		if(str[i][j] != str[u][v])
		{
			x = u, y = v;
			cache->cx[dir][i][j] = x;
			cache->cy[dir][i][j] = y;
			return str[u][v];
		}
	}
}

int bfs()
{
#ifdef OWN_QUEUE
	Queue<State> q;
#else
	queue<State> q;
#endif
	int si = 0, sj = 0;

	struct visit *v = (struct visit *)calloc(1, sizeof(struct visit));
	cache = (Cache *) calloc(1, sizeof(Cache));

	FOR(i, 0, 4)
		FOR(j, 0, MAXN)
		FOR(k, 0, MAXN)
		cache->cx[i][j][k] = INF, cache->cy[i][j][k] = INF; 

	if(str[0][0] == s[0])
	{
		q.push(State(si,sj, 1, 1));
		v->vis[1][0][0] = 1;
	}
	else
	{
		q.push(State(si,sj, 0, 0));
		v->vis[0][0][0] = 1;
	}

	while(q.empty() == false)
	{
		State u = q.front();
		q.pop();

		//printf("QQQ %d %d %d %d\n", u.r, u.c, u.idx, u.dist);

		if(u.idx == LenS)
			return u.dist;

		int nIdx = u.idx;

		FOR(x, 0, 4)
		{
			char sc = str[u.r][u.c];
			if(sc == s[nIdx])
				q.push(State(u.r, u.c, u.dist + 1, nIdx+1));

			int vr, vc;
			char c = FindNextChar(u.r, u.c, vr, vc, x);

			if(c == -1)
				continue;

			if(v->vis[u.idx][vr][vc])
				continue;

			if(c == s[nIdx])
				q.push(State(vr, vc, u.dist + 2, nIdx+1));
			else
			{
				q.push(State(vr, vc, u.dist+1, u.idx));
				v->vis[u.idx][vr][vc] = 1;
			}
		}
	}

	free(v);
	return -1;
}

int t = 0;

int main()
{
	int T;
	scanf("%d ", &T);
	for(t = 0; t < T; t++)
	{
		scanf("%d %d ", &R, &C);

		FOR(i, 0, R)
			scanf("%s ", &str[i]);

		scanf("%s ", &s);
		LenS = 0;
		FOR(i, 0, MAXS)
		{
			if(s[i] == 0)
				break;
			++LenS;
		}

		s[LenS++] = '*';
		s[LenS] = 0;

		printf("#%d %d\n", t+1, bfs());
	}
	return 0;
}

#endif