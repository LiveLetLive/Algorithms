#include "CommonHeader.h"


#ifdef UVA_1203_ARGUS
READ_INPUT(UVA_1203_ARGUS)

#include <iostream>
#include <cstdio>
#include <queue>
#include <climits>

using namespace std;

#define FOR(i, init, count) for(int i = init; i < count; i++)
#define MAXN 3001

class Query
{
public:
	int period;
	int val;
	int id;
	Query() { period = -1; val = 0; id = -1; }
	bool operator < (const Query &that) const
	{
		if(this->val < that.val)
			return true;

		if(this->val == that.val && this->id < that.id)
			return true;

		return false;
	}
};

template<class T>
class PQ
{
	T data[MAXN];
	int size;
public:
	PQ()
	{
		size = 0;
	}

	void push(T query) 
	{
		size++;
		data[size] = query;
		swim(size);
	}

	void swim(int idx)
	{
		int parent = idx / 2;

		if(data[idx] < data[parent] && idx > 1)
		{
			swap(data[idx] , data[parent]);
			swim(parent);
		}
	}

	void pop()
	{
		data[1] = data[size];
		size--;
		sink(1, size);
	}

	T top()
	{
		return data[1];
	}

	bool empty()
	{
		return size <= 0;
	}

	void sink(int idx, int size)
	{
		int left = idx*2;
		int right = idx*2+1;

		if(left > size)
			return;

		int mc = -1;

		if(right > size)
			mc = left;
		else
		{
			if(data[left] < data[right])
				mc = left;
			else
				mc = right;
		}

		if(data[idx] < data[mc])
			return;

		swap(data[idx], data[mc]);
		sink(mc, size);
	}
};

#define HAVE_STL 0

int main()
{
#if HAVE_STL
	std::priority_queue<Query> pq;
#else
	PQ<Query> pq;
#endif

	char str[20] = {};

	while(scanf("%s ", &str))
	{
		if(str[0] == '#')
			break;

		Query q;
		scanf("%d ", &q.id);
		scanf("%d ", &q.period);
		q.val = q.period;
		pq.push(q);
	}

	int N = 0;

	scanf("%d ", &N);

	while(N--)
	{
		Query q = pq.top();
		pq.pop();
		printf("%d\n", q.id);
		q.val += q.period;
		pq.push(q);
	}

	return 0;
}


#endif