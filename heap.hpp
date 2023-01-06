class IntHeap {
	int* array;
	size_t _size, _space; // space is available, size is used.

	// Swap two values in array at specified indices.	
	void swap(size_t a, size_t b) {
		int t = array[a];
		array[a] = array[b];
		array[b] = t;
	}
	void swim(int idx) {
		
	}
	void sink() {
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
		_space = 130;
		_size = 0;
		array = new int[_space];
	}
	void add(int number) {
		array[_size++] = number;
	}
	int get(size_t index) {
		return array[index];
	}
};
