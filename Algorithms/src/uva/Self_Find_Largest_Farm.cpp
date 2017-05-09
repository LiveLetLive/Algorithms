#include "CommonHeader.h"

#ifdef SELF_FIND_BIGGEST_RECTANGLE
READ_INPUT(SELF_FIND_BIGGEST_RECTANGLE)

#include <iostream>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 16
#define MAXL 41

typedef int us;
int N;
us s[MAXN];

class DP
{
public:
	short data[MAXN][MAXL][MAXL][MAXL][MAXL];
};

DP *dp = NULL;

#define Mymax(a,b)            (((a) > (b)) ? (a) : (b))


void reset()
{
	FOR(i, 0, N)
		FOR(j, 0, MAXL)
		FOR(k, 0, MAXL)
		FOR(m, 0, MAXL)
		FOR(n, 0, MAXL)
		dp->data[i][j][k][m][n] = 0;
}

us solve(us idx, us l1, us l2, us w1, us w2)
{
	if(idx == N)
	{
		if(l1 && w1 && l1 == l2 && w1 == w2)
			return l1*w1;
		else 
			return -1;
	}

	if(l1 >= MAXL || l2 >= MAXL || w1 >= MAXL || w2 >= MAXL)
		return -1;

	if(dp->data[idx][l1][l2][w1][w2] != 0)
		return dp->data[idx][l1][l2][w1][w2];

	if(dp->data[idx][l1][l2][w2][w1] != 0)
		return dp->data[idx][l1][l2][w2][w1];

	if(dp->data[idx][l2][l1][w1][w2] != 0)
		return dp->data[idx][l2][l1][w1][w2];

	if(dp->data[idx][l2][l1][w2][w1] != 0)
		return dp->data[idx][l2][l1][w2][w1];

	if(dp->data[idx][w1][w2][l1][l2] != 0)
		return dp->data[idx][w1][w2][l1][l2];

	if(dp->data[idx][w1][w2][l2][l1] != 0)
		return dp->data[idx][w1][w2][l2][l1];

	if(dp->data[idx][w2][w1][l2][l1] != 0)
		return dp->data[idx][w2][w1][l2][l1];

	if(dp->data[idx][w2][w1][l1][l2] != 0)
		return dp->data[idx][w2][w1][l1][l2];

	us ans = -1;

	int r1 = solve(idx+1, l1 + s[idx],	l2,				w1,				w2);
	int r2 = solve(idx+1, l1 ,			l2 + s[idx],	w1,				w2);
	int r3 = solve(idx+1, l1 ,			l2,				w1 + s[idx],	w2);
	int r4 = solve(idx+1, l1 ,			l2,				w1,				w2 + s[idx]);
	int r5 = solve(idx+1, l1 ,			l2,				w1,				w2);

	ans = Mymax(ans, r1);
	ans = Mymax(ans, r2);
	ans = Mymax(ans, r3);
	ans = Mymax(ans, r4);
	ans = Mymax(ans, r5);

	return dp->data[idx][l1][l2][w1][w2] = ans;
}

int main()
{
	int T;
	dp = new DP;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		scanf("%d ", &N);
		reset();

		FOR(i, 0, N)
			scanf("%d ", &s[i]);
		
		int ans = solve(0, 0, 0, 0, 0);
		printf("%d\n", ans);
	}

	delete dp;
	return 0;
}

#endif
