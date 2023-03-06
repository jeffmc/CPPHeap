// Jeff McMillan C++ Heap Data Structure 1/6/23
// This program allows the user to manipulate a max-heap data structure.
// This includes adding and removing integers using different methods.

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

// Print node at index using specified indentation.
void printNode(const IntHeap& ih, int i, int indent) {
	if (!ih) return;
	printf("[%3d]%*c%d\n", i, indent, ' ', ih.peek(i));
	indent += 2;
	const int l = ih.lchild(i), r = ih.rchild(i);
	if (l >= 0 && l < ih.size()) printNode(ih, l, indent);
	if (r >= 0 && r < ih.size()) printNode(ih, r, indent);
}

// Randomly generate numbers and add to heap.
void randomGen(IntHeap& ih, size_t count) {
	srand(time(NULL));

	printf("Generating and adding %u numbers...\n", count);
	for (int i=0;i<count;i++) {
		int r = rand() % 1000;
		ih.push(r);
	}
}

// Load from space-delimited file of numbers.
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
	size_t count = 0;
	while (true) {
		c = fgetc(file); // Grab next character from file
		if (isdigit(c) || c == '+' || c == '-') { // Allow these characters as defined by atoi(const char*) spec.
			assert(bufpos < 32);
			numbuf[bufpos] = c; // Add character and move null-terminator
			numbuf[++bufpos] = '\0';
		}
		else {
			if (strlen(numbuf) > 0) {
				int num = atoi(numbuf);
				// printf("Read: %i\n", num);
				count++;
				ih.push(num); // Push number to heap and reset integer building buffer.
				numbuf[0] = '\0';
				bufpos = 0;
			}
		}
		if (c == EOF) break;
	}
	assert(strlen(numbuf) == 0);
	printf("Read %u numbers!\n");
}

// Manual number entry via console.
void cmdinput(IntHeap& ih) {
	char buf[32] = { '\0' };
	while (true) {
		printf("Enter a number (or \"STOP\"): ");
		consolein(buf, 32);
		if (strlen(buf)==0) {
			printf("Enter STOP if you wish to stop inputting numbers!\n");
			continue;
		}
		if (strcmp(buf,"STOP") == 0) break;
		int num = atoi(buf);
		ih.push(num);
		printf("Added %i\n", num);
	}
}

int main() {
	IntHeap ih;
	const char* const HELP_STR = "Commands:\n"
		"	HELP - displays this list of commands.\n"
		"	MANUAL - type in numbers manually to the heap.\n"
		"	FILE - type in a filename to load numbers from.\n"
		"	RANDOM - generates 100 random integers to be added.\n"
		"	ALL - extracts all numbers from heap (highest to lowest) and prints them.\n"
		"	SINGLE - extracts the highest number from heap and print it.\n"
		"	CLEAR - remove all numbers from heap without printing.\n"
		"	TREE - visualize the heap as a tree in the console.\n";

	printf(HELP_STR);

	char buf[32] = { '\0' };
	while (true) {
		printf("> ");
		consolein(buf, 32);
		if (strcmp(buf,"HELP") == 0) {
			printf(HELP_STR);
		}
		else if (strcmp(buf,"MANUAL") == 0) {
			cmdinput(ih);
		}
		else if (strcmp(buf,"FILE") == 0) {
			loadfile(ih);
		}
		else if (strcmp(buf,"RANDOM") == 0) {
			randomGen(ih,100);
		}
		else if (strcmp(buf,"ALL") == 0) {
			if (!ih) printf("Heap is empty!\n");
			while (ih) printf("Extracted: %i\n", ih.pop()); // While heap contains integers, pop max and print it.
		}
		else if (strcmp(buf,"SINGLE") == 0) {
			if (ih) {
				printf("Extracted: %i\n", ih.pop());
			}
			else {
				printf("Heap is empty!\n");
			}
		}
		else if (strcmp(buf,"CLEAR") == 0) {
			ih.clear();
			printf("Cleared heap!\n");
		}
		else if (strcmp(buf,"TREE") == 0) {
			printf("\n TREE: \n");
			printNode(ih, 0, 1);
		}
		else if (strcmp(buf,"QUIT") == 0) {
			printf("Exiting!\n");
			break;
		}
		else {
			printf("\"%s\" is not a valid command!\n", buf);
		}
	}

	printf("Goodbye World!\n");
}