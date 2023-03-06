#pragma once

#include <cassert>
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
		assert(a < _size);
		assert(b < _size);
		int t = array[a];
		array[a] = array[b];
		array[b] = t;
	}
	void swim(size_t idx) {
		assert(idx < _size);
		while (true) {
			if (idx == 0) break;
			size_t pidx = parent(idx);
			if (array[pidx] < array[idx]) {
				swap(pidx, idx);
				idx = pidx;
			}
			else {
				break;
			}
		}
	}
	void sink(size_t idx) {
		assert(idx < _size);
		while (true) {
			size_t li = lchild(idx), ri = rchild(idx);
			if (ri < _size) { // If ri is less than size, this means li is also less than size
				int si = array[li] > array[ri] ? li : ri;
				if (array[si] > array[idx]) {
					swap(si, idx);
					idx = si;
				}
				else {
					break;
				}
			}
			else if (li < _size) {
				if (array[li] > array[idx]) {
				swap(li, idx);
				idx = li;
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	}
public:
	operator bool() const { return _size > 0; }
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
	// Increment size, grow if needed, add element to end and "swim" it upwards
	void push(int number) 
	{ 
		++_size;
		if (_size > _space) grow();
		array[_size-1] = number;
		swim(_size-1);
	}
	// Remove the max element (decrement size), replace it with last element in heap and sink that element downwards
	int pop() 
	{
		assert(_size > 0);
		int num = array[0];
		--_size;
		if (_size > 0) {
			array[0] = array[_size];
			sink(0);
		}
		return num;
	}
	// Peek the highest element in the heap. This might be a bad output if size = 0.
	int peek(size_t index) const {
		assert(_size > 0);
		return array[index];
	}

	// Clear all elements from heap, shrink internal array back to small default size.
	void clear() {
		_size = 0;
		_space = 8;
		
		free(array);
		array = (int*) malloc(sizeof(int) * _space);
	}
};
