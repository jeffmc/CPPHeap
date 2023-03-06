// Jeff McMillan C++ Heap Data Structure 1/6/23

#include <cassert>
#include <iostream>
#include <cstdio>
#include <cstdlib>

#include <cctype>
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

void loadfile(IntHeap& ih) {
	char filename[32] = { '\0' };
	FILE* file = nullptr;
	while (file == nullptr) {
		printf("Filename: ");
		consolein(filename, 32);
		file = fopen(filename, "r");
		if (file == nullptr) {
			printf("Couldn't open \"%s\"!\n", filename);
		}
	}
	printf("File opened successfully!\n");
	char numbuf[32] = { '\0' };
	size_t bufpos = 0;
	int c;
	while (true) {
		c = fgetc(file);

		if (isdigit(c) || c == '+' || c == '-') { // Allow these characters as defined by atoi(const char*) spec.
			numbuf[bufpos] = c;
			numbuf[++bufpos] = '\0';
		}
		else {
			if (strlen(numbuf) > 0) {
				int num = atoi(numbuf);
				printf("Read: %i\n", num);
				ih.push(num);
				numbuf[0] = '\0';
				bufpos = 0;
			}
		}

		if (c == EOF) break;
	}
	assert(strlen(numbuf) == 0);
}

int main() {
	IntHeap ih;

	char buf[32] = { '\0' };
	while (true) {
		printf("INPUT TYPE (CMD/FILE/RANDOM): ");
		consolein(buf, 32);
		if (strcmp(buf,"CMD") == 0) {
			printf("CMD in!\n");
			break;
		}
		else if (strcmp(buf,"FILE") == 0) {
			loadfile(ih);
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
