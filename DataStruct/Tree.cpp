#include <iostream> 
#define MAX 15
using namespace std;
struct node
{
	int data;
	node* left;
	node* right;
};
void preorder(node* ptr)
{
	if (ptr) {
		cout << ptr->data << ' ';
		preorder(ptr->left);
		preorder(ptr->right);
	}
}
void inorder(node* ptr)
{
	if (ptr) {
		inorder(ptr->left);
		cout << ptr->data << ' ';
		inorder(ptr->right);
	}
}
void postorder(node* ptr)
{
	if (ptr) {
		postorder(ptr->left);
		postorder(ptr->right);
		cout << ptr->data << ' ';
	}
}
int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	node nodes[MAX + 1] = {};
	for (int i = 1; i <= MAX; ++i)
	{
		nodes[i].data = i;
		nodes[i].left = NULL;
		nodes[i].right = NULL;
	}
	for (int i = 2; i <= MAX; ++i)
	{
		if (i % 2 == 0)
		{
			nodes[i / 2].left = &nodes[i];
		}
		else
		{
			nodes[i / 2].right = &nodes[i];
		}
	}
	cout << "PreOrder : \n";
	preorder(&nodes[1]);
	cout << '\n';
	cout << "InOrder : \n";
	inorder(&nodes[1]);
	cout << '\n';
	cout << "PostOrder : \n";
	postorder(&nodes[1]);
	cout << '\n';
	return 0;
}
