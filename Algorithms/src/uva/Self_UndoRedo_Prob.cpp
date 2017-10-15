#include "CommonHeader.h"

#ifdef SELF_UNDOREDO_PROB
READ_INPUT(SELF_UNDOREDO_PROB)
	#include <stdio.h>

const int INIT_METHOD = 0;
const int WRITE_METHOD = 1;
const int MOVE_CURSOR_METHOD = 2;
const int UNDO_METHOD = 3;
const int REDO_METHOD = 4;
const int SHOW_METHOD = 5;

const int MAX_STR_SIZE = 50000;

extern void undo();
extern void redo();
extern void moveCursor(int pos);
extern char* show();
extern void init(char *str);
extern void write(char ch);

int compare(char str1[], char str2[]);
char getChar(char ch);
int getStrLen(char* str);

char ans[MAX_STR_SIZE+5];


int main() {
	//freopen("input.txt", "r", stdin);

	int tests;
	scanf("%d", &tests);
	int totalActualPoints = 0;
	int totalUserPoints = 0;
	for (int i = 0; i<tests; i++) {
		int actualPoints = 0;
		int userPoints = 0;

		int numberOfMethodCalls;
		scanf("%d", &numberOfMethodCalls);
		for (int j = 0; j<numberOfMethodCalls; j++) {
			int methodName;
			scanf("%d", &methodName);

			switch (methodName) {
			case INIT_METHOD:
			{
				char str[MAX_STR_SIZE];
				scanf(" %[^\r\n]", str);
				init(str);
			}
			break;
			case WRITE_METHOD:
			{
				char charArray[MAX_STR_SIZE];
				scanf(" %[^\r\n]", charArray);
				for (int k = 0; charArray[k]; k++) {
					char ch = charArray[k];
					if (ch == '\\') {
						k++;
						write(getChar(charArray[k]));
					}
					else {
						write(ch);
					}
				}
			}
			break;
			case MOVE_CURSOR_METHOD:
			{
				int pos;
				scanf("%d", &pos);
				moveCursor(pos);
			}
			break;
			case UNDO_METHOD:
			{
				undo();
			}
			break;
			case REDO_METHOD:
			{
				redo();
			}
			break;
			case SHOW_METHOD:
			{
				char answer[MAX_STR_SIZE];
				scanf(" %[^\r\n]", answer);
				char* userAnswer = show();
				actualPoints += getStrLen(answer);
				userPoints += compare(answer, userAnswer);

				if(compare(answer, userAnswer) != getStrLen(answer))
				{
					printf("Error %d Ans = \n%s\n\n User=\n%s\n\n", j, answer, userAnswer);
				}

			}
			break;
			}
		}

		printf("Test-%d points: %d of %d\n", (i + 1), userPoints, actualPoints);
		totalUserPoints += userPoints;
		totalActualPoints += actualPoints;
	}
	printf("-----------------------------\n");
	printf("Total points: %d of %d\n", totalUserPoints, totalActualPoints);

	fclose(stdin);
	return 0;
}

int compare(char str1[], char str2[]) {
	int points = 0;

	for (int i = 0; str1[i]; i++) {
		if (str1[i] == str2[i]) {
			points++;
		}
		else {
			break;
		}
	}

	return points;
}

char getChar(char ch) {
	if (ch == 'b') {
		return '\b';
	}if (ch == 'n') {
		return '\n';
	}if (ch == 's') {
		return ' ';
	}
	else {
		return ' ';
	}
}

int getStrLen(char* str) {
	int len = 0;

	while (str[len]) {
		len++;
	}

	return len;
}

///////////////////////////////////////////////////////////


#define FOR(i, init, count) for(int i = init; i < count; ++i)

class TXChange
{
public:
	TXChange()
	{

	}
	int idx;
	char ch;
	bool IsInsert;
};


int curPos = 0;
int curLen = 0;

int stIdx = 0;
int stLen = 0;

extern void undo();
extern void redo();
extern void moveCursor(int pos);
extern char* show();
extern void init(char *str);
extern void write(char ch);

TXChange chng[MAX_STR_SIZE+5];

int StrLen(char* str) 
{
	int len = 0;

	while (str[len]) {
		len++;
	}

	return len;
}

inline void insertAt(int idx, char ch)
{
	for(int i = curLen-1; i >= idx; --i)
		ans[i+1] = ans[i];

	ans[idx] = ch;
}

inline void removeAt(int idx)
{
	FOR(i, idx, curLen)
		ans[i] = ans[i+1];
}

void undo()
{
	if(stLen == 0)
		return;

	int idx = stIdx - 1;

	if(chng[idx].IsInsert == 1)
	{
		removeAt(chng[idx].idx);

		--curLen;
		curPos = chng[idx].idx;
	}
	else
	{
		insertAt(chng[idx].idx, chng[idx].ch);

		++curLen;
		curPos = chng[idx].idx + 1;
	}

	--stIdx;
}

void redo()
{
	if(stLen == stIdx)
		return;

	if(stLen == 0)
		return;

	int idx = stIdx;

	if(chng[idx].IsInsert == 0)
	{
		removeAt(chng[idx].idx);

		--curLen;
		curPos = chng[idx].idx;
	}
	else
	{
		insertAt(chng[idx].idx, chng[idx].ch);

		++curLen;
		curPos = chng[idx].idx + 1;
	}

	++stIdx;
}

void moveCursor(int pos)
{
	//if(pos > curLen)
	//	return;

	curPos = pos;
}

char* show()
{
	return ans;
}

void init(char *str)
{
	int len = StrLen(str);

	FOR(i, 0, len)
		ans[i] = str[i];
	
	ans[len] = 0;

	curPos = len;
	curLen = len;

	stIdx = 0;
	stLen = 0;

}

void write(char ch)
{
	//insert char at last
	if(ch != '\b')
	{
		++curLen;
		insertAt(curPos, ch);
	
		ans[curLen] = 0;

		chng[stIdx].ch = ch;
		chng[stIdx].IsInsert = 1;
		chng[stIdx].idx = curPos;

		++curPos;
		++stIdx;
		stLen = stIdx;
	}
	else
	{
		if(curPos == 0)
			return;

		chng[stIdx].ch = ans[curPos - 1];
		chng[stIdx].IsInsert = 0;
		chng[stIdx].idx = curPos - 1;

		removeAt(curPos-1);

		--curLen;
		--curPos;
		++stIdx;
		stLen = stIdx;
	}
}

#endif
