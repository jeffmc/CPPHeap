// Jeff McMillan C++ Heap Data Structure 1/6/23

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "heap.hpp"

int main() {
	
	srand(time(NULL));

	IntHeap ih;
	printf("Hello World!\n");
	
	for (int i=0;i<20;i++) {
		int r = rand() % 100;
		printf("%d\n", r);
		ih.add(r);
	}	

}
