
#include "CommonHeader.h"

#ifdef UVA_11517_EXACT_CHANGE
READ_INPUT(UVA_11517_EXACT_CHANGE)

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

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 10005
#define MAXG 105
#define MAXC 105
#define INF 10000000
typedef long long ll;

class Pair
{
public:
	Pair() { val = 0, cnt = 0; }
	Pair(int v, int c) { val = v, cnt = c; }
	int cnt;
	int val;
};

Pair dp[MAXC][MAXN];

int c[MAXC];
int C;
int V;
static int counter = 0;

void reset()
{
	counter = 0;
	FOR(i, 0, C+1)
		FOR(j, 0, V+1)
		dp[i][j].cnt = INF, dp[i][j].val = INF;
}


Pair solve(int idx, int val, int d)
{
	if(val <= 0)
		return Pair(val, d);
	
	if(idx >= C)
		return Pair(INF, INF);

	if(dp[idx][val].val != INF)
		return dp[idx][val];

	Pair ans(INF, INF);
	counter++;

	FOR(i, idx, C)
	{
		Pair tmp = solve(i+1, val - c[i], d+1);

		if(abs(tmp.val) < abs(ans.val))
		{
			ans = tmp;
		}
		else if(tmp.val == ans.val)
			if(tmp.cnt < ans.cnt)
				ans = tmp;
	}
	return dp[idx][val] = ans;
}

int main()
{
	int T;
	scanf("%d", &T);
	FOR(t, 0, T)
	{
		scanf("%d", &V);
		scanf("%d", &C);

		reset();

		FOR(c1, 0, C)
			scanf("%d", &c[c1]);

		//FOR(i, 0, C)
		//	FOR(j, i, C)
		//	if(c[i] > c[j]) swap(c[i], c[j]);

		Pair ans = solve(0, V, 0);
		printf("%d %d\n", V - ans.val, ans.cnt);
		//printf("%d\n", counter);
	}

	return 0;
}

//
//#define sc(n) scanf("%d", &n)
//#define S 103
//using namespace std;
//typedef long long LL;
// 
//int p, n, mn, ans;
//int arr[S], dp[S][S*100];
// 
//int counter = 0;
//
//int Exchange(int ind, int tot, int coin){
//	if(tot >= p)return tot;
//    if(ind >= n)return INT_MAX;
//    if(dp[ind][tot] != -1)return dp[ind][tot];
// 	counter++;
//   dp[ind][tot] = 0;
//    dp[ind][tot] += Exchange(ind+1, tot+arr[ind], coin+1);
//    mn = min(mn, dp[ind][tot]);
//    Exchange(ind+1, tot, coin);
//    return mn;
//}
// 
//int Coins(int ind, int coin, int tot){
//    if(tot == ans)return coin;
//    if(tot > ans)return INT_MAX;
//    if(ind >= n)return INT_MAX;
//    if(dp[ind][tot] != -1)return dp[ind][tot];
//	counter++;
//    dp[ind][tot] = 0;
//    dp[ind][tot] += Coins(ind+1, coin+1, tot+arr[ind]);
//    mn = min(mn, dp[ind][tot]);
//    Coins(ind+1, coin, tot);
//    return mn;
//}
// 
//void Do(){
//    int t;
//    sc(t);
//    while(t--){
//        sc(p);
//        sc(n);
//		counter = 0;
//        memset(dp, -1, sizeof(dp));
//        for(int i = 0; i < n; i++)sc(arr[i]);
//    //    sort(arr, arr+n);
//      //  reverse(arr, arr+n);
//        mn = INT_MAX;
//        ans = Exchange(0, 0, 0);
//        cout << ans << " ";
//        memset(dp, -1, sizeof(dp));
//        mn = INT_MAX;
//        cout << Coins(0, 0, 0) << endl;
//		cout << counter << endl;
//    }
//}
// 
//int main(){
//    ios_base::sync_with_stdio(0); cin.tie(0);
//    #ifndef ONLINE_JUDGE
//    ///freopen("inp","r",stdout);
//    ///freopen("contest.txt","w",stdout);
//    #endif
//    Do();
//    return 0;
//}

#endif