#include <iostream>

using namespace std;

struct AdjlistNode
{
	int vertex;
	AdjlistNode* next;
};

struct AdjList
{
	int num_members;
	AdjlistNode* head;
	AdjlistNode* tail;
};

struct Graph
{
	int num_vertices;
	AdjList* adjListArr;
};

AdjlistNode* CreateNode(int v)
{
	AdjlistNode* newNode = new AdjlistNode();
	newNode->vertex = v;
	newNode->next = nullptr;
	return newNode;
}

Graph* CreateGraph(int n)
{
	Graph* graph = new Graph();
	graph->num_vertices = n;
	graph->adjListArr = new AdjList[n];
	for (int i = 0; i < n; ++i)
	{
		graph->adjListArr[i].head = graph->adjListArr[i].tail = NULL;
		graph->adjListArr[i].num_members = 0;
	}
	return graph;
}

void DestroyGraph(Graph*& graph)
{
	if (graph)
	{
		if (graph->adjListArr)
		{
			for (int v = 0; v < graph->num_vertices; ++v)
			{
				AdjlistNode* adjListPtr = graph->adjListArr[v].head;
				while (adjListPtr)
				{
					AdjlistNode* tmp = adjListPtr;
					adjListPtr = adjListPtr->next;
					delete(tmp);
					tmp = nullptr;
				}
			}
			delete(graph->adjListArr);
			graph->adjListArr = nullptr;
		}
		delete(graph);
		graph = nullptr;
	}
}

void AddEdge(Graph* graph, int start, int end)
{
	AdjlistNode* newNode = CreateNode(end);
	if (graph->adjListArr[start].tail != NULL)
	{
		graph->adjListArr[start].tail->next = newNode;
		graph->adjListArr[start].tail = newNode;
	}
	else
	{
		graph->adjListArr[start].head = graph->adjListArr[start].tail = newNode;
	}
	++graph->adjListArr[start].num_members;

	newNode = CreateNode(start);
	if (graph->adjListArr[end].tail != NULL)
	{
		graph->adjListArr[end].tail->next = newNode;
		graph->adjListArr[end].tail = newNode;
	}
	else
	{
		graph->adjListArr[end].head = graph->adjListArr[end].tail = newNode;
	}
	++graph->adjListArr[end].num_members;
}

void DisplayGraph(Graph* graph, int i)
{
	if (graph == nullptr)
	{
		cout << "list is empty\n";
		return;
	}
	AdjlistNode* adjListPtr = graph->adjListArr[i].head;

	while (adjListPtr != nullptr)
	{
		cout << adjListPtr->vertex << " ";
		adjListPtr = adjListPtr->next;
	}
	cout << '\n';
}

int main()
{
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);
	int  v, e, sv, ev;
	cin >> v >> e;

	Graph* graph = CreateGraph(v);

	for (int i = 0; i < e; ++i)
	{
		cin >> sv >> ev;
		AddEdge(graph, sv, ev);
	}

	// 정점 i에 대해 인접한 인접리스트
	for (int i = 0; i < v; ++i)
	{
		cout << "정점 " << i << "의 인접리스트 : \n";
		DisplayGraph(graph, i);
	}
	DestroyGraph(graph);
	for (int i = 0; i < v; ++i)
	{
		cout << "정점 " << i << "의 인접리스트 : \n";
		DisplayGraph(graph, i);
	}
	return 0;
}
/*
6 7
0 1
0 2
0 3
1 2
1 4
3 4
4 5
*/
