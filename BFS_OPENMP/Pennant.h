#pragma once
#include "Node.h"
class Pennant
{
public:
	Pennant(Node* root);
	~Pennant();
	Pennant* p_split();
	void p_union(Pennant* &y);
	static void FA(Pennant* &x, Pennant* &y, Pennant* &carry);
	Node *root;
};

