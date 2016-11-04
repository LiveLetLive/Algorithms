#include "CommonHeader.h"

#ifdef UVA_658_ITS_NOT_A_BUG_ITS_A_FEATURE
READ_INPUT(UVA_658_ITS_NOT_A_BUG_ITS_A_FEATURE)

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
#define MAXN 20
#define MAXM 103
#define INF 0x3f3f3f3fL
typedef long long ll;

int check[MAXM][MAXN];
int result[MAXM][MAXN];
int t[MAXM];

int N, M;

class Node
{
public:
	Node() {}
	Node(int s, int t) { state = s, time = t; }
	bool operator < (const Node& that) const
	{
		return this->time > that.time;
	}
	int state;
	int time;
};

void reset()
{
	FOR(i, 0, MAXM)
		FOR(j, 0, MAXN)
		check[i][j] = 0, result[i][j] = 0;
}

int solve()
{
	priority_queue<Node> pq;

	pq.push(Node(-1, 0));

	while(pq.empty() == false)
	{
		Node u = pq.top();
		pq.pop();

		if(u.state == 0)
			return u.time;


	}
	return INF;
}

int main()
{
	while(scanf("%d %d ", &N, &M))
	{
		reset();
		FOR(i, 0, M)
		{
			char str[MAXN] = { 0 };
			char str1[MAXN] = { 0 };
			scanf("%d ", t[i]);
			scanf("%s %s", &str, &str1);
			FOR(j, 0, N)
			{
				if(str[j] == '0') check[i][j] = 2; 
				else if(str[j] == '+') check[i][j] = 1; 
				if(str[j] == '-') check[i][j] = 0; 

				if(str1[j] == '0') result[i][j] = 2; 
				else if(str1[j] == '+') result[i][j] = 1; 
				if(str1[j] == '-') result[i][j] = 0; 
			}
		}

		int ans = solve();

		if(ans >= INF)
			printf("Bugs cannot be fixed.\n");
		else
			printf("Fastest sequence takes %d seconds.\n", ans);
	}
	return 0;
}

#endif
