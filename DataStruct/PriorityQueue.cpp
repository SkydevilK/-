//Minimum Priority Queue

#include <iostream>
#define MAX 100

using namespace std;
template <typename T>

class PriorityQueue
{
private:
	int size = 0;
	T arr[MAX] = {};
public:
	void Init()
	{
		size = 0;
	}
	void Push(T value)
	{
		if (size + 1 > MAX)
		{
			cout << "queue is full\n";
			return;
		}
		arr[size] = value;

		int cur = size++;
		while (cur > 0 && arr[cur] < arr[(cur - 1) / 2])
		{
			T temp = arr[(cur - 1) / 2];
			arr[(cur - 1) / 2] = arr[cur];
			arr[cur] = temp;
			cur = (cur - 1) / 2;
		}
	}
	T Pop()
	{
		if (size <= 0)
		{
			cout << "queue is empty\n";
			return -1;
		}
		T value = arr[0];
		arr[0] = arr[--size];
		int cur = 0;
		while (cur * 2 + 1 < size)
		{
			int child;
			if (cur * 2 + 2 == size)
			{
				child = cur * 2 + 1;
			}
			else
			{
				child = arr[cur * 2 + 1] < arr[cur * 2 + 2] ? cur * 2 + 1 : cur * 2 + 2;
			}
			if (arr[cur] < arr[child])
			{
				break;
			}

			T temp = arr[cur];
			arr[cur] = arr[child];
			arr[child] = temp;
			cur = child;
		}
		return value;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	PriorityQueue<int> pq;
	pq.Init();
	pq.Push(3);
	pq.Push(2);
	pq.Push(1);
	cout << pq.Pop() << "\n";
	cout << pq.Pop() << "\n";
	cout << pq.Pop() << "\n";
	cout << pq.Pop() << "\n";
	return 0;
}
