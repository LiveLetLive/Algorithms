#include "CommonHeader.h"

#ifdef UVA_10282_BABELFISH
READ_INPUT(UVA_10282_BABELFISH)

#include <iostream>
#include <algorithm>
#include <string>
#include <string.h>
#include <math.h>
#include <float.h>
#include <queue>
#include <map>
#include <stdio.h>
#include <sstream>

	using namespace std;

#define FOR(i, init, cnt) for(int i = init; i < cnt; i++)
#define MAXN 1003

#define TABLE_SIZE 100000

#define INF 0x3f3f3f3fL
typedef long long ll;

unsigned long hashFunc(char* str)
{
	unsigned long hash = 5381;
	while(*str)
	{
		int i = *str;
		hash = (hash << 5) + hash + i;
		str++;
	}

	return hash % TABLE_SIZE;
}

inline void Strcpy(char* dest, char* src)
{
	while(*src)
		*dest++ = *src++;
	*dest = 0;
}
inline int Strlen(char* s)
{
	int l = 0;
	while(*s++) l++;
	return l;
}
inline int Strcmp(char* s1, char* s2)
{
	//int l1 = Strlen(s1);
	//int l2 = Strlen(s2);

	//int len = (l1 > l2) ? l1 : l2;

	while(*s1 && *s2 && *s1 == *s2)
		s1++, s2++;

	if(*s1 == 0 && *s2 == 0)
		return 0;
	else
		return 1;
}

class Node
{
public:
	Node() {
		key[0] = 0, val[0] = 0, next = NULL;
	}
	Node(char *k, char* v) 
	{
		Strcpy(key, k);
		Strcpy(val, v);
		next = NULL;
	}
	char key[11];
	char val[11];

	Node* next;
};

Node* ht[TABLE_SIZE];

Node* hash_find(char* key)
{
	unsigned long k = hashFunc(key);

	Node* ptr = ht[k];
	if(ptr == NULL)
	{
		return NULL;
	}
	else
	{
		while(ptr != NULL)
		{
			if(Strcmp(ptr->key, key) == 0)
				return ptr;
			ptr = ptr->next;
		}
	}

	return NULL;
}

void hash_insert(char* key, char* val)
{
	unsigned long k = hashFunc(key);

	Node* ptr = ht[k];
	if(ptr == NULL)
	{
		ptr = new Node(key, val);
		ht[k] = ptr;
	}
	else
	{
		while(ptr->next != NULL)
			ptr = ptr->next;

		ptr->next = new Node(key, val);
	}
}

// A defect here, collision list is leaked....
void reset()
{
	FOR(i, 0, TABLE_SIZE)
		if(ht[i] != NULL)
			delete ht[i], ht[i] = NULL;
}

int main()
{
	reset();
	
	while(1)
	{
		char s[25];
		char str[11], str1[11];
		cin.getline(s, 50);

		if(s[0] == 0)
			break;

		sscanf(s, "%s %s ", &str, &str1);
		hash_insert(str1, str);
	}

	char str[11];
	while(scanf("%s ", &str) != EOF)
	{
		Node* ptr = hash_find(str);

		if(ptr == NULL)
			printf("eh\n");
		else
			printf("%s\n", ptr->val);

	}


	return 0;
}

//int main()
//{
//	map<string, string> m;
//
//	while(1)
//	{
//		char s[25];
//		char str[11], str1[11];
//		cin.getline(s, 50);
//
//		if(s[0] == 0)
//			break;
//
//		sscanf(s, "%s %s ", &str, &str1);
//		m[str1] = str;
//	}
//
//	char str[11];
//	while(scanf("%s ", &str) != EOF)
//	{
//		map<string, string>::iterator it = m.find(str);
//
//		if(it == m.end())
//			printf("eh\n");
//		else
//			cout << m[str] << endl;
//	}
//
//
//	return 0;
//}

#endif
