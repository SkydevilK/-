#include <iostream>
#define MAX 100

using namespace std;
template <typename T>

class Stack {
private:
	int top;
	T arr[MAX] = NULL;
public:
	void Init() {
		top = 0;
	}
	bool IsEmpty()
	{
		return (top == 0);
	}
	bool IsFull()
	{
		return (top == MAX);
	}
	void Push(T value)
	{
		if (IsFull())
		{
			cout << "stack is full\n";
			return;
		}
		arr[top] = value;
		++top;
	}
	T Pop()
	{
		if (IsEmpty())
		{
			cout << "stack is empty\n";
			return -1;
		}
		return arr[--top];
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	Stack<int> s;
	s.Init();
	s.Push(1);
	s.Push(2);
	s.Push(3);
	cout << s.Pop() << "\n";
	cout << s.Pop() << "\n";
	cout << s.Pop() << "\n";
	cout << s.Pop() << "\n";
	return 0;
}
