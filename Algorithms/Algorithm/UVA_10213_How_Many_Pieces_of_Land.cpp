#include "CommonHeader.h"


#ifdef UVA_10213_HOW_MANY_PIECES_OF_LAND
READ_INPUT(UVA_10213_HOW_MANY_PIECES_OF_LAND)

#include <iostream>
#include <cstdio>

#define FOR(i, init, count) for(int i = init; i < count; i++)
typedef long long ll;

int main()
{
	int S;
	ll N;
	scanf("%d", &S);
	FOR(i, 0, S)
	{
		scanf("%lld ", &N);
	
		ll ans = ( N * (N-1) * (N-2) * (N-3 )) / 24 + ( N * (N-1)) / 2 + 1;
		printf("%lld\n", ans);
	}
}

#endif