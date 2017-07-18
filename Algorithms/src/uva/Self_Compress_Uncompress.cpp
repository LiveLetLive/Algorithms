#include "CommonHeader.h"

#ifdef SELF_COMPRESS_UNCOMPRESS
READ_INPUT(SELF_COMPRESS_UNCOMPRESS)

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


#include<stdio.h> 
#include<stdlib.h>

int N;

#define T 50
#define MAXVAL 999996 
#define MAXS 166666

static char TC[T][MAXVAL]; 
static int OP[T][MAXS]; 
static char ANS[T][MAXVAL]; 
static int length[T];

static char c[31]  = {
	'a','b','c','d','e','f','g','h','i','j','k','l','m','n', 'o','p','q','r','s','t','u','v','w','x','y','z','+','-','/','*',' '
};


extern void compress(const char *input, int inputLength, int *output, int outputLength); 
extern void decompress(const int *input, int inputLength, char *output, int outputLength); 
extern void Init();


void generateTC()
{
	{
		N = MAXVAL;
		length[0] = N;
		for(int j=0;j<N;j++)
			TC[0][j] = c[rand()%31];
	}

	for(int i = 1; i < T;i++)
	{
		N = 500000 + rand() % 500000; 
		N = N - N%6;

		length[i] = N; 
		for(int j=0;j<N;j++)
			TC[i][j] = c[rand() % 31];
	}
}


int tcorder[T] = {0,}; 
int visited[T] = {0,};
int op[50];


//int main()
//{
//	char str[50] = {0,};
//	char str2[50] = {0,};
//
//	strncpy(str, c, 31);
//	str[31] = 0;
//
//	printf("%s\n", str);
//	compress(str, 31, op, 50);
//	decompress(op, 50, str2, 50);
//	str2[49] = 0;
//
//	printf("%s\n", str2);
//
//}

int main()
{
	int t = 0,i,j; 
	srand(31);

	while(t != T)
	{
		i = rand() % T; 
		if(visited[i] == 0)
		{
			tcorder[t] = i; 
			visited[i] = 1; 
			t++;

		}
	}

	generateTC(); 
	Init();

	for(i = 0;i < T; i++)
		compress(TC[tcorder[i]], length[tcorder[i]], OP[tcorder[i]], MAXS);

	for(i=0;i<T;i++)
		decompress(OP[i], MAXS, ANS[i], MAXVAL);

	for(i = 0; i < T; i++) 
	{
		int lim = length[i]; 
		for(j = 0;j < lim;j++) 
		{
			if(TC[i][j] != ANS[i][j])
			{
				printf("0\n"); 
				break;
			}
		}
		if(j == lim)
			printf("1\n");
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

struct Header
{
	long long len:20;

	long long a1:5;
	long long a2:5;
	long long a3:5;
	long long a4:5;
	long long a5:5;
	long long a6:5;
	long long a7:5;
	long long a8:5;
};

void MemCpy(void* dest, void* src, int n)
{
	char *d = (char*) dest;
	char *s = (char*) src;
	while(n--)
		*d++ = *s++;
}

typedef struct strTab
{
	char c;
	int idx;
}Tab;

const Tab sp[] = 
{
	{ '+', 1 },
	{ '-', 2 },
	{ '/', 3 },
	{ '*', 4 },
	{ ' ', 5 }
};

#define CountOf(x) sizeof(x)/sizeof(x[0])

int GetIndex(char c)
{
	if(c >= 'a' && c <= 'z')
		return c - 'a';

	FOR(i, 0, CountOf(sp))
		if(c == sp[i].c)
			return 'z' - 'a' + sp[i].idx;
}

char GetChar(int idx)
{
	idx &= 0x1F;
	if(idx >= 'a' - 'a' && idx <= 'z' - 'a')
		return idx + 'a';

	int sIdx = idx - ('z' - 'a');

	FOR(i, 0, CountOf(sp))
		if(sIdx == sp[i].idx)
			return sp[i].c;
}


void compress(const char *input, int inputLength, int *output, int outputLength)
{
	struct Header h = { 0,};

	h.len = inputLength;
	h.a1 = GetIndex(input[0]);
	h.a2 = GetIndex(input[1]);
	h.a3 = GetIndex(input[2]);
	h.a4 = GetIndex(input[3]);
	h.a5 = GetIndex(input[4]);
	h.a6 = GetIndex(input[5]);
	h.a7 = GetIndex(input[6]);
	h.a8 = GetIndex(input[7]);

	MemCpy(output, &h, sizeof(long long));

	int *ptr = (int*)((char*)output +sizeof(long long));

	for(int i = 0; i < inputLength - 8; )
	{
		int k = i/6;
		ptr[k] = 0;

		for(int j = 0; j < 6 && i < (inputLength - 8); ++j) 
			ptr[k] |= (GetIndex(input[i+8]) << (5 * j)), ++i;
	}
}

void decompress(const int *input, int inputLength, char *output, int outputLength)
{
	long long l = *((long long*) input);
	struct Header *h1 = (struct Header*)&l;
	struct Header h = *h1;

	int len = h.len;
	len &= ((1<<20)-1);

	output[0] = GetChar(h.a1);
	output[1] = GetChar(h.a2);
	output[2] = GetChar(h.a3);
	output[3] = GetChar(h.a4);
	output[4] = GetChar(h.a5);
	output[5] = GetChar(h.a6);
	output[6] = GetChar(h.a7);
	output[7] = GetChar(h.a8);

	char *ptr = (char*)((char*)output +sizeof(long long));

	for(int i = 0; i < (len - 8); )
	{
		int k = i/6;
		int tmp = input[k+2];

		for(int j = 0; j < 6 &&  i < (len - 8); ++j)
		{
			int idx = (tmp >> (5*j)) & 0x1F;
			ptr[i++] = GetChar(idx);
		}
	}
}

void Init()
{
}


#endif
