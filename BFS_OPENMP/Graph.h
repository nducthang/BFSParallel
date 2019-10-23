#pragma once
#pragma once

#include <vector>
#include "Bag.h"
using namespace std;

class Graph
{
public:
	Graph(int V);
	void addEdge(int v, int w);
	void BFS(int s);
	void PBFS(int s);
	void BAGPBFS(int s);
	void Result(std::vector<int> path, int s, int f);
	void processLevelBag(Bag* &frontier, Bag* &new_frontier, vector<int> &path);
private:
	std::vector<int> *adj;
	int V;
};


