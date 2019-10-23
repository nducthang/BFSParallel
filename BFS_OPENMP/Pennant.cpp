#include "Pennant.h"
#include "Node.h"
#include <iostream>
#include <stack>

using namespace std;

Pennant::Pennant(Node* root)
{
	this->root = root;
}


Pennant::~Pennant()
{
	if (this->root != NULL)
	{
		stack<Node *> nodes;
		nodes.push(this->root);
		while (nodes.size()>0)
		{
			Node *current = nodes.top();
			nodes.pop();
			if (current->left != NULL)
			{
				nodes.push(current->left);
			}
			if (current->right != NULL)
			{
				nodes.push(current->right);
			}
			delete current;
		}
	}
}

void Pennant::p_union(Pennant* &y)
{
	if (y == NULL) return;
	y->root->right = this->root->left;
	this->root->left = y->root;
	y->root = NULL;
	delete y;
	y = NULL;
}

Pennant* Pennant::p_split()
{
	if (this->root->left == NULL)
	{
		return NULL;
	}
	Pennant *y = new Pennant(this->root->left);
	this->root->left = y->root->right;
	y->root->right = NULL;
	return y;
}

void Pennant::FA(Pennant* &x, Pennant* &y, Pennant* &carry)
{
	if (x == NULL && y == NULL && carry == NULL) {
		return;
	}
	if (x != NULL && y == NULL && carry == NULL) {
		return;
	}
	if (x == NULL && y != NULL && carry == NULL) {
		x = y;
		y = NULL;
		return;
	}
	if (x == NULL && y == NULL && carry != NULL) {
		x = carry;
		carry = NULL;
		return;
	}
	if (x != NULL && y != NULL && carry == NULL) {
		x->p_union(y);
		carry = x;
		x = NULL;
		return;
	}
	if (x != NULL && y == NULL && carry != NULL) {
		x->p_union(carry);
		carry = x;
		x = NULL;
		return;
	}
	if (x == NULL && y != NULL && carry != NULL) {
		y->p_union(carry);
		carry = y;
		y = NULL;
		return;
	}
	if (x != NULL && y != NULL && carry != NULL) {
		carry->p_union(y);
		return;
	}
}
