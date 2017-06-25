#include "CommonHeader.h"

#ifdef SELF_ELECTRONIC_GADGET
READ_INPUT(SELF_ELECTRONIC_GADGET)

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
#define MAXN 10000
#define INF 0x3f3f3f3fL
typedef long long ll;

int mpool[MAXN];
int pool[MAXN];
char guess[4];

void reset()
{
	FOR(i, 0, MAXN)
		pool[i] = mpool[i];
}

int getScore()
{
	return 0;
}

int countOccur(char num[4], char digit)
{
	int cnt = 0;
	FOR(i, 0, 4)
		if(num[i] == digit)
			cnt++;
	return cnt;
}

void itoa(int i, char *str)
{
	FOR(k, 0, 4) str[k] = '0';
	int cnt = 1;
	int j = i;
	while(j)
	{
		str[4 - cnt++] = (j % 10) + '0';

		j /= 10;
	}
}

int mul[] =
{
	0, 
	10,
	100,
	1000
};

int countCandidateinPool()
{
	int cnt = 0;
	FOR(i, 0, MAXN)
		if(pool[i])
			cnt++;
	return cnt;
}

int atoi(char *str)
{
	int j = 0;
	FOR(cnt, 0, 4)
	{
		j *= mul[cnt];
		int k = str[3 - cnt] + '0';
		j += k;
	}

	return j;
}

int getNextCandidate()
{
	FOR(i, 0, MAXN)
		if(pool[i])
			return i;
}


void fillPool()
{
	int cnt = 0;
	FOR(i, 0, MAXN)
	{
		char str[4] = {'0', '0', '0', '0'};

		itoa(i, str);

		FOR(j, 0, 4)
		{
			if(countOccur(str, str[j]) > 1)
			{
				mpool[i] = 0;
				break;
			}
			else
				mpool[i] = 1;
		}

		if(mpool[i])
		{
			cnt++;
		}

	}

	//printf("total search %d", cnt);

}


char secret[5];

typedef struct res
{
	int bull;
	int cow;
}RESULT;

RESULT match(char str[4])
{
	RESULT res;
	int b = 0, c = 0;

	FOR(i, 0, 4)
	{
		if(secret[i] == str[i]) b++;

		FOR(j, 0, 4)
		{
			if(secret[i] == str[j])
				c++;
		}
	}

	res.bull = b;
	res.cow = c;
	return res;
}

RESULT calcScore(char str[4], char str1[4])
{
	RESULT res;
	int b = 0, c = 0;

	FOR(i, 0, 4)
	{
		if(str1[i] == str[i]) b++;

		FOR(j, 0, 4)
		{
			if(str1[i] == str[j])
				c++;
		}
	}

	res.bull = b;
	res.cow = c;
	return res;
}


void prune(char guess[4], RESULT r)
{
	FOR(i, 0, MAXN)
	{
		if(pool[i])
		{
			char s[4];
			itoa(i, s);

			RESULT r1 = calcScore(s, guess);

			if((r1.bull != r.bull) || (r1.cow != r.cow))
				pool[i] = 0;
		}
	}
}

int main()
{
	int T;
	fillPool();

	scanf("%d ", &T);

	FOR(i, 0, T)
	{
		reset();

		scanf("%s ", &secret);

		while(1)
		{
			char guessStr[4];

			//printf("Candidate Remain = %d\n", countCandidateinPool());

			int guess = getNextCandidate();

			itoa(guess, guessStr);

			RESULT res = match(guessStr);
			if(res.bull == 4)
			{
				printf("1\n");
				break;
			}

			prune(guessStr, res);
		}
	}
	return 0;
}

#endif
