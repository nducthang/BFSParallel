#ifdef _MSC_VER
#define _CRT_SECURE_NO_WARNINGS
#endif
#include <iostream>
#include <time.h>
#include "Graph.h"
using namespace std;

void ReadEdges(Graph &g)
{
	int a, b;
	while (cin >> a >> b)
	{
		if (a == b) continue;
		g.addEdge(a, b);
		g.addEdge(b, a);
	}
}

int main()
{
	freopen("graph_1000000_nodes.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	Graph g(1000000);
	ReadEdges(g);
	clock_t start = clock();
	g.BAGPBFS(0);
	clock_t end = clock();
	cout << "Process time: " << (end - start) << " ms" << endl;
}