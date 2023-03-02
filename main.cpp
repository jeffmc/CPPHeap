// Jeff McMillan C++ Heap Data Structure 1/6/23

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "heap.hpp"

// Read in a line from the console.
void consolein(char* cstr, std::streamsize n) {
	std::cin.getline(cstr, n);
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore();
	}
	#ifdef CONSOLEINDBG
	printf("\"%s\"\n",cstr);
	#endif
}

void printNode(const IntHeap&, int, int);

void randomGen(IntHeap& ih, size_t count) {
	srand(time(NULL));

	printf("Generating %u numbers...\n", count);
	for (int i=0;i<count;i++) {
		int r = rand() % 1000;
		ih.push(r);
	}
}

int main() {
	IntHeap ih;

	char buf[32] = { '\0' };
	while (true) {
		printf("INPUT TYPE (\"CMD\" / \"FILE\" / \"RANDOM\"): ");
		consolein(buf, 32);
		if (strcmp(buf,"CMD") == 0) {
			printf("CMD in!\n");
			break;
		}
		else if (strcmp(buf,"FILE") == 0) {
			printf("TODO: File input!\n");
			break;
		}
		else if (strcmp(buf,"RANDOM") == 0) {
			randomGen(ih,100);
			break;
		}
		else {
			printf("Try again!\n");
		}
	}

	printf("\n TREE: \n");
	printNode(ih, 0, 1);

	printf("\n");
	while (ih) {
		printf("Extracted: %i\n", ih.pop());
		// printNode(ih, 0, 1);
		// printf("\n");
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
