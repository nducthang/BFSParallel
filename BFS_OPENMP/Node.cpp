#include "Node.h"
#include <iostream>


Node::Node(int vertex)
{
	this->vertex = vertex;
	this->left = NULL;
	this->right = NULL;
}


Node::~Node()
{
}
