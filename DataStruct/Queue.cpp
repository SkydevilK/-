#include <iostream>
#define MAX 100

using namespace std;
template <typename T>

class Queue {
private:
	int front;
	int rear;
	T arr[MAX] = {};
public:
	void Init()
	{
		front = 0;
		rear = 0;
	}
	bool IsEmpty()
	{
		return (front == rear);
	}
	bool IsFull()
	{
		if ((rear + 1) % MAX == front)
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void Enqueue(T value)
	{
		if (IsFull())
		{
			cout << "queue is full\n";
			return;
		}
		arr[rear++] = value;
		if (rear == MAX)
		{
			rear = 0;
		}
	}
	T Dequeue()
	{
		if (IsEmpty())
		{
			cout << "queue is empty\n";
			return -1;
		}
		T value = arr[front++];
		if (front == MAX)
		{
			front = 0;
		}
		return value;
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	Queue<int> q;
	q.Init();
	q.Enqueue(1);
	q.Enqueue(2);
	q.Enqueue(3);
	cout << q.Dequeue() << "\n";
	cout << q.Dequeue() << "\n";
	cout << q.Dequeue() << "\n";
	cout << q.Dequeue() << "\n";
	return 0;
}
