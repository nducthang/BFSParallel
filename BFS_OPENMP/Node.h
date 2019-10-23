#pragma once
class Node
{
public:
	Node(int vertex);
	~Node();
	int vertex;
	Node* left;
	Node* right;
};

