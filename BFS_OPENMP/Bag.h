#pragma once
#include "Pennant.h"
class Bag
{
public:
	Bag();
	Bag(int r);
	~Bag();
	void clear();
	void init(int r);
	void insert_vertex(int x);
	bool empty();
	int size();
	Bag* split();
	void insert(Pennant *&vertices);
	void print();
	void merge(Bag* y);
	//void copy(Bag *y);

	Pennant** backbone; // mảng chứa dữ liệu
	int largest_nonempty_index; // chỉ số lớn nhất không rỗng
	int r;
};

