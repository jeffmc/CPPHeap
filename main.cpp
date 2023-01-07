// Jeff McMillan C++ Heap Data Structure 1/6/23

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "heap.hpp"

void printNode(const IntHeap&, int, int);

int main() {	
	//srand(time(NULL));
	srand(10240);

	IntHeap ih;
	for (int i=0;i<1000;i++) {
		int r = rand() % 1000;
		ih.add(r);
	}
	printf("\n TREE: \n");
	printNode(ih, 0, 1);

	std::cin.get();
}

void printNode(const IntHeap& ih, int i, int depth) {
	printf("[%3d]%*c%d\n", i, depth, ' ', ih.peek(i));
	depth += 2;
	int l = ih.lchild(i), r = ih.rchild(i);
	if (l >= 0 && l < ih.size()) printNode(ih, l, depth);
	if (r >= 0 && r < ih.size()) printNode(ih, r, depth);
}
