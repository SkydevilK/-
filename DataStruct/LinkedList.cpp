#include <iostream>
using namespace std;

struct Node
{
	int data;
	struct Node* next;
};
class LinkedList {
private:
	Node* head = nullptr;
	Node* tail = nullptr;
	Node* cur = nullptr;
public:
	void AddData(int value)
	{
		Node* newNode = new Node();
		newNode->data = value;
		newNode->next = NULL;
		if (head == nullptr)
			head = newNode;
		else
			tail->next = newNode;
		tail = newNode;
	}
	void DisplayList() {
		cout << "Display List : ";
		if (head == nullptr)
		{
			cout << "list is empty\n";
		}
		else
		{
			cur = head;
			cout << cur->data << " ";
			while (cur->next != nullptr)
			{
				cur = cur->next;
				cout << cur->data << " ";
			}
			cout << "\n";
		}
	}
	void DeleteData()
	{
		if (head == nullptr) {
			cout << "list is empty\n";
		}
		else
		{
			Node* delNode = head;
			Node* delNextNode = head->next;
			cout << head->data << " 을 삭제합니다\n";
			delete(delNode);
			delNode = nullptr;
			while (delNextNode != nullptr)
			{
				delNode = delNextNode;
				delNextNode = delNextNode->next;
				cout << delNode->data << " 을 삭제합니다\n";
				delete(delNode);
				delNode = nullptr;
			}
			head = nullptr;
			tail = nullptr;
			cur = nullptr;
		}
	}
};

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	LinkedList list;
	int n, input;
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		list.AddData(i);
	}
	list.DisplayList();
	list.DeleteData();
	list.DisplayList();
	return 0;
}
