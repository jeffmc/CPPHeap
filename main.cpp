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
	// printf("Generation:\n");
	// for (int i=0;i<10;i++) {
	// 	int r = rand() % 1000;
	// 	printf("%i\n", r);
	// 	ih.push(r);
	// }

	// BUG TESTING DATA:
	ih.rawSizeSet(5);
	ih.rawSet(0,451);
	ih.rawSet(1,336);
	ih.rawSet(3,72);
	ih.rawSet(4,115);
	ih.rawSet(2,243);

	printf("\n TREE: \n");
	printNode(ih, 0, 1);

	printf("\n\n");
	while (ih) {
		printf("Extracted: %i\n NEWTREE:\n", ih.pop());
		printNode(ih, 0, 1);
		printf("\n\n");
	}
}

void printNode(const IntHeap& ih, int i, int indent) {
	if (!ih) return;
	printf("[%3d]%*c%d\n", i, indent, ' ', ih.peek(i));
	indent += 2;
	const int l = ih.lchild(i), r = ih.rchild(i);
	if (l >= 0 && l < ih.size()) printNode(ih, l, indent);
	if (r >= 0 && r < ih.size()) printNode(ih, r, indent);
}
