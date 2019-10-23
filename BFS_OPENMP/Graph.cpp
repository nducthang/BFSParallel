#include "Graph.h"
#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <omp.h>
#include "Bag.h"

using namespace std;
int f = 7;
#define MIN_SET 25

/* Thiết lập cho cấu trúc đồ thị (có hướng) - đối tượng Graph */
Graph::Graph(int V)
{
	this->V = V;
	this->adj = new vector<int>[this->V];
}
void Graph::addEdge(int v, int w)
{
	this->adj[v].push_back(w);
}
void Graph::BFS(int s)
{
	vector<int> path(V, -1);
	vector<int>::iterator it;
	queue<int> q;
	path[s] = s;

	q.push(s);
	while (!q.empty())
	{
		int u = q.front(); q.pop();
		for (it = this->adj[u].begin(); it != this->adj[u].end(); it++)
		{
			if (path[*it] == -1)
			{
				q.push(*it);
				path[*it] = u;
			}
		}
	}
	this->Result(path, s, f);
}

void Graph::PBFS(int s)
{
	vector<int> path(V, -1);
	vector<int> L, L2; //Tập các đỉnh level hiện tại và sau
	path[s] = s; L.push_back(s);
	while (!L.empty())
	{
#pragma omp parallel for
		for (int i = 0; i < L.size(); i++)
		{
#pragma omp critical
			{
				for (vector<int>::iterator it = this->adj[L[i]].begin(); it != this->adj[L[i]].end(); it++)
				{
					if (path[*it] == -1) {
						path[*it] = L[i];
						L2.push_back(*it);
					}
				}
			}
		}
		L.clear();
		L = L2;
		L2.clear();
	}
	this->Result(path, s, f);
}
void Graph::processLevelBag(Bag* &L, Bag* &L2, vector<int> &path)
{
	if (L->size() > MIN_SET)
	{
		Bag* y = L->split();
		Bag* L21 = new Bag();
#pragma omp parallel sections
		{
#pragma omp section
			{
				processLevelBag(y, L21, path);
			}
#pragma omp section
			{
				processLevelBag(L, L2, path);
			}
		}
		L2->merge(L21);
	}
	else
	{
		// XỬ LÝ TUẦN TỰ
		stack<Node *> nodes;
		for (int i = 0; i <= L->largest_nonempty_index; i++)
		{
			if (L->backbone[i] != NULL)
			{
				nodes.push(L->backbone[i]->root);
				while (nodes.size() > 0)
				{
					Node* current = nodes.top();
					nodes.pop();
					if (current->left != NULL)
					{
						nodes.push(current->left);
					}
					if (current->right != NULL)
					{
						nodes.push(current->right);
					}
					for (vector<int>::iterator it = this->adj[current->vertex].begin(); it != this->adj[current->vertex].end(); it++)
					{
						if (path[*it] == -1)
						{
							L2->insert_vertex(*it);
							path[*it] = current->vertex;
						}
					}
				}
			}
		}
	}
}
void Graph::BAGPBFS(int s)
{
	vector<int> path(V, -1);
	Bag* L = new Bag(); // túi chứa các đỉnh hiện tại

	L->insert_vertex(s);
	path[s] = s;
	int count = 0;

	while (!L->empty())
	{
		Bag* L2 = new Bag();
		this->processLevelBag(L, L2, path);
		L->clear();
		//L->copy(L2);
		L = L2;
	}
	this->Result(path, s, f);
}


void Graph::Result(std::vector<int> path, int s, int f)
{
	if (path[f] == -1) {
		std::cout << "Not Found Path" << std::endl;
	}
	else
	{
		while (f != s)
		{
			cout << f << " <- ";
			f = path[f];
		}
		cout << s << endl;
	}
}