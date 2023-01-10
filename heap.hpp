#pragma once

#include <cstdlib>
#include <cstring>

class IntHeap {
	int* array;
	size_t _size, _space; // space is available, size is used.
	void grow() {
		if (_space > 0) {
			_space *= 2;
		}
		else {
			_space = 1;
		}
		int* newptr = (int*) realloc(array, sizeof(int) * _space);
		array = newptr;
	}
	// Swap two values in array at specified indices.	
	void swap(size_t a, size_t b) {
		int t = array[a];
		array[a] = array[b];
		array[b] = t;
	}
	void swim(size_t idx) {
		while (true) {
			size_t pidx = parent(idx);
			if (pidx < _size && array[pidx] < array[idx]) {
				swap(pidx, idx);
				idx = pidx;
			}
			else {
				break;
			}
		}
	}
	void sink(size_t idx) {
		while (true) {
			size_t li = lchild(idx), ri = rchild(idx);
			if (li < _size && ri < _size) {
				int si = array[li] > array[ri] ? li : ri;
				swap(si, idx);
				idx = si;
			}
			else if (li < _size) {
				swap(li, idx);
				idx = li;
			}
			else if (ri < _size) {
				swap(ri, idx);
				idx = ri;
			}
			else {
				break;
			}
		}
	}
public:
	size_t size() const { return _size; }
	size_t space() const { return _space; }
	// Left child index
	size_t inline lchild(size_t index) const { return index * 2 + 1; }
	// Right child index
	size_t inline rchild(size_t index) const { return index * 2 + 2; }
	// Parent index
	size_t inline parent(size_t index) const { return (index-1) / 2; }
	IntHeap() {
		_space = 8;
		_size = 0;
		array = (int*) malloc(sizeof(int) * _space);
	}
	IntHeap(const IntHeap& o) {
		_space = o._size;
		_size = o._size;
		array = (int*) malloc(_space * sizeof(int));
		if (array && o.array) memcpy(array, o.array, _size * sizeof(int));
	}
	~IntHeap() {
		if (array) free(array);
	}
	void add(int number) {
		_size++;
		if (_size > _space) grow();
		array[_size-1] = number;
		swim(_size-1);
	}
	int remove() {
		int num = array[0];
		array[0] = array[--_size];
		sink(0);
		return num;
	}
	int peek(size_t index) const {
		return array[index];
	}
	int* getRaw() {
		return array;
	}
};
