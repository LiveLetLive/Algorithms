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
#define MAXM 105
#define INF 1000000000
typedef unsigned int ll;

int checkMust[MAXM];
int checkMustNot[MAXM];
int resultIntro[MAXM];
int resultRemove[MAXM];

ll t[MAXM];
ll dp[1 << MAXN];
bool in_q[1 << MAXN];

int N, M;

class Node
{
public:
	Node() {}
	Node(unsigned int s, ll t) { state = s, time = t; }
	bool operator < (const Node& that) const
	{
		return this->time > that.time;
	}
	unsigned int state;
	ll time;
};

void reset()
{
	FOR(i, 0, MAXM)
		checkMust[i] = 0, checkMustNot[i] = 0, resultIntro[i] = 0, resultRemove[i] = 0;

	FOR(i, 0, 1 << MAXN)
		dp[i] = INF, in_q[i] = 0;
}

ll solve()
{
	queue<Node> pq;

	pq.push(Node((1<<N) - 1, 0));
	dp[(1<<N) - 1] = 0;
	in_q[(1<<N) - 1] = 1;
	
	while(pq.empty() == false)
	{
		Node u = pq.front();
		pq.pop();
		in_q[u.state] = 0;

		FOR(i, 0, M)
		{
			int s = u.state;

			//Check if possible to apply

			//Entry must have
			if(((~s & checkMust[i]) != 0))
				continue;

			//Entry must NOT have
			if(((s & checkMustNot[i]) != 0))
				continue;

			//Apply it in tmp, check if produce different result
			int newState = s | resultIntro[i];
			newState &= ~(resultRemove[i]);

			if(dp[newState] > (dp[s] + t[i]))
			{
				if(in_q[newState] != 1)
					pq.push(Node(newState, (dp[s] + t[i]))), in_q[newState]= 1;

				dp[newState] = dp[s] + t[i];
			}

		}
	}
	return INF;
}

int main()
{
	int test = 0;
	while(scanf("%d %d ", &N, &M))
	{
		if(N == 0 && M == 0)
			break;

		reset();
		FOR(i, 0, M)
		{
			char str[MAXN+1] = { 0 };
			char str1[MAXN+1] = { 0 };
			scanf("%d ", &t[i]);
			scanf("%s %s ", &str, &str1);
			FOR(j, 0, N)
			{
				//						
				if(str[j] == '+')	checkMust[i] |= (1<<j), checkMustNot[i]  &= ~(1<<j); 
				else if(str[j] == '-')		checkMust[i] &= ~(1<<j), checkMustNot[i]  |= (1<<j); 

				//						ORED							ANDED
				if(str1[j] == '+') resultIntro[i] |= (1 << j),  resultRemove[i] &= ~(1<<j); 
				else if(str1[j] == '-')		resultIntro[i] &= ~(1 << j), resultRemove[i] |= (1<<j); 
			}
		}

		ll ans = solve();

		printf("Product %d\n",++test);
		if (dp[0]==INF) printf("Bugs cannot be fixed.\n\n");
		else printf("Fastest sequence takes %d seconds.\n\n",dp[0]);
	}
	return 0;
}

#endif
