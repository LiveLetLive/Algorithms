#include "CommonHeader.h"

#ifdef UVA_403_POSTSCRIPT
READ_INPUT(UVA_403_POSTSCRIPT)

#include <iostream>
#include <stdio.h>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 1003
#define INF 0x3f3f3f3fL
typedef long long ll;

char grid[61][61];
int r = 0, c = -1;


void reset()
{
	FOR(i, 0, 61)
		FOR(j, 0, 61)
		grid[i][j] = '.';
}


char *chTbl[5] = {
	".***.. ****.. .****. ****.. *****. *****. .****. *...*. *****. ..***. *...*. *..... *...*. *...*. .***.. ****.. .***.. ****.. .****. *****. *...*. *...*. *...*. *...*. *...*. *****. ......",
	"*...*. *...*. *...*. *...*. *..... *..... *..... *...*. ..*... ...*.. *..*.. *..... **.**. **..*. *...*. *...*. *...*. *...*. *..... *.*.*. *...*. *...*. *...*. .*.*.. .*.*.. ...*.. ......",
	"*****. ****.. *..... *...*. ***... ***... *..**. *****. ..*... ...*.. ***... *..... *.*.*. *.*.*. *...*. ****.. *...*. ****.. .***.. ..*... *...*. .*.*.. *.*.*. ..*... ..*... ..*... ......",
	"*...*. *...*. *..... *...*. *..... *..... *...*. *...*. ..*... *..*.. *..*.. *..... *...*. *..**. *...*. *..... *..**. *..*.. ....*. ..*... *...*. .*.*.. **.**. .*.*.. ..*... .*.... ......",
	"*...*. ****.. .****. ****.. *****. *..... .***.. *...*. *****. .**... *...*. *****. *...*. *...*. .***.. *..... .****. *...*. ****.. .***.. .***.. ..*... *...*. *...*. ..*... *****. ......"
};


int main()
{
	char str[1024] = { 0,};
	reset();
	while(1)
	{
		r = 0, c = -1;
		char txt[1024];
		int fonttype;

		int ret = scanf("%s ", str);

		if(ret < 0)
			break;

		if(str[1] == 'E' && str[2] == 'O')
		{
			FOR(i, 0, 60)
			{
				FOR(j, 0, 60)
					printf("%c", grid[i][j]);
				printf("\n");
			}
			printf("\n");
			FOR(j, 0, 60)
				printf("-");

			printf("\n");
			printf("\n");
			reset();
			continue;
		}

		scanf("%s ", &txt);

		fonttype = txt[1] - '0';
		int len = 0;
		if(str[1] == 'C' || str[1] == 'L' || str[1] == 'R')
		{
			char ch = 0;
			int idx = 0;
			scanf("%d ", &r);

			while(ch != '|')
				scanf("%c", &ch);
			ch = 0;
			while(ch != '|')
				scanf("%c", &ch), txt[idx++] = ch, ++len;
		}
		else if(str[1] == 'P')
		{
			char ch = 0;
			int idx = 0;
			scanf("%d ", &r);
			scanf("%d ", &c);
			--c;
			while(ch != '|')
				scanf("%c", &ch);
			ch = 0;
			while(ch != '|')
				scanf("%c", &ch), txt[idx++] = ch, ++len;
		}

		if(c == -1)
		{
			int l = len;
			--l;

			if(str[1] == 'C')
			{
				if(fonttype == 5)
					c = (60 - (l * 6)) / 2;
				else
					c = (60 - (l) + 1) / 2;
			}
			else if(str[1] == 'R')
			{
				if(fonttype == 5)
					c = (60 - (l * 6));
				else
					c = (60 - (l));
			}
			else if(str[1] == 'L')
				c = 0;
		}

		--r;

		// Draw Char
		if(fonttype == 1)
		{
			int idx = c;
			char *ptr = txt;
			while(*ptr != '|')
			{
				char ch = *ptr;
				if(ch == ' ');
				else
					grid[r][idx] = ch;
				++ptr;
				++idx;
			}
		}
		else
		{
			int idx = c;
			char *ptr = txt;
			while(*ptr != '|')
			{
				char ch = *ptr;

				{
					int chIdx = 0;

					if(ch == ' ')
					{
						chIdx = 'Z' - 'A' + 1;
						chIdx *= 6;
						chIdx += ('Z' - 'A' + 1);
					}
					else
					{
						chIdx = ch - 'A';
						chIdx *= 6;
						chIdx += (ch - 'A');
					}
					FOR(i, 0, 5)
					{
						int tmpIdx = idx;
						int tmpChIdx = chIdx;
						FOR(j, 0, 6)
						{
							char c = chTbl[i][chIdx];
							if(c == '.' || c == ' ' || idx > 59 || idx < 0)
							{
								++chIdx;
								++idx;
								continue;
							}

							grid[r+i][idx] = chTbl[i][chIdx++];
							++idx;
						}

						if(i < 4)
							idx = tmpIdx, chIdx = tmpChIdx; 
					}
				}
				++ptr;
			}
		}
	}
	return 0;
}

#endif
