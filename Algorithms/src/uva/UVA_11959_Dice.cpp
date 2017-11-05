#include "CommonHeader.h"

#ifdef UVA_11959_DICE
READ_INPUT(UVA_11959_DICE)

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
#define MAXN 1003
#define INF 0x3f3f3f3fL
typedef long long ll;

class Dice
{
public:
	Dice(int v)
	{
		FOR(i, 0, 6)
		{
			val[i] = v % 10;
			v /= 10;
		}
	}

	Dice minimize()
	{
		Dice tmp = *this;
		Dice ans = *this;

		FOR(x, 0, 4)
		{
			tmp = ans;

			FOR(y, 0, 4)
			{
				int t = tmp.val[0];
				tmp.val[0] = tmp.val[1];
				tmp.val[1] = tmp.val[2];
				tmp.val[2] = tmp.val[3];
				tmp.val[3] = t;

				if(tmp < ans)
					ans = tmp;
			}

			tmp = ans;

			FOR(z, 0, 4)
			{
				int t = tmp.val[0];
				tmp.val[0] = tmp.val[5];
				tmp.val[5] = tmp.val[2];
				tmp.val[2] = tmp.val[4];
				tmp.val[4] = t;

				if(tmp < ans)
					ans = tmp;
			}

			int t = tmp.val[1];
			tmp.val[1] = tmp.val[5];
			tmp.val[5] = tmp.val[3];
			tmp.val[3] = tmp.val[4];
			tmp.val[4] = t;

			if(tmp < ans)
				ans = tmp;
		}

		return ans;
	}

	bool operator == (Dice &d2)
	{
		FOR(i, 0, 6)
			if(val[i] != d2.val[i])
			return false;
		
		return true;
	}

	bool operator < (Dice &d2)
	{
		FOR(i, 0, 6)
			if(val[i] != d2.val[i])
				return ((val[i] - d2.val[i]) < 0 );
		
		return false;
	}

	int val[6];
};


void reset()
{
}

int main()
{
	int T;
	scanf("%d ", &T);
	FOR(t, 0, T)
	{
		int v1, v2;
		
		scanf("%d %d ", &v1, &v2);

		Dice d1(v1);
		Dice d2(v2);

		Dice md1 = d1.minimize();
		Dice md2 = d2.minimize();

		if(md1 == md2)
			printf("Equal\n");
		else
			printf("Not Equal\n");
	}
	return 0;
}

#endif
