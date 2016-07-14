#include "CommonHeader.h"

#ifdef UVA_1213_SUM_OF_DIFFERENT_PRIMES
READ_INPUT(UVA_1213_SUM_OF_DIFFERENT_PRIMES)

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
#define MAXN 1121
#define MAXK 15
#define CountOf(x1) (sizeof(x1)/(sizeof(x1[0])))

int n, k;
int primeCnt;

int prime[] = 
{
	2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73,
	79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163,
	167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251,
	257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349,
	353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443,
	449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557,
	563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647,
	653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757,
	761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863,
	877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983,
	991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 
	1087, 1091, 1093, 1097, 1103, 1109, 1117
};

#define PRIME_COUNT CountOf(prime)

int dp[PRIME_COUNT][MAXN][MAXK];

void reset()
{
	FOR(i, 0, primeCnt)
		FOR(j, 0, MAXN)
		FOR(k, 0, MAXK)
		dp[i][j][k] = -1;

	//FOR(i, 2, MAXN)
	//	prime[i] = 1;

	//prime[0] = 0;
	//prime[1] = 0;
	//prime[2] = 1;

	//FOR(i, 2, MAXN)
	//{
	//	FOR(j, 2, i)
	//	{
	//		if((i % j) == 0)
	//		{
	//			prime[i] = 0;
	//			break;
	//		}
	//	}
	//}

	//FOR(i, 2, MAXN)
	//	if(prime[i])
	//		printf("%d, ", i);
}

int ways(int idx, int remN, int remK)
{
	if(remN == 0 && remK == 0)
		return 1;
	else if(remN == 0 || remK == 0)
		return 0;
	else if(idx >= primeCnt || prime[idx] > remN)
		return 0;

	if(dp[idx][remN][remK] != -1)
		return dp[idx][remN][remK];

	int x = ways(idx + 1, remN - prime[idx], remK - 1);
	x += ways(idx + 1, remN, remK);

	return dp[idx][remN][remK] = x;
}

int solve()
{
	return ways(0, n, k);
}

int main()
{

	while(scanf("%d %d ", &n, &k), n, k)
	{
		primeCnt = sizeof(prime) / sizeof(prime[0]); 
		reset();

		printf("%d\n", solve());
	}

	return 0;
}


#endif