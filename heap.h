/************************************************************************
		File: heap.h
		Author: Sam Farber
		Date: December 6, 2016
		Assignment: Final Project(Huffman)

		Declaration of the heap class.

************************************************************************/

#include <cstdlib>

struct hnode {

	unsigned char letter;
	size_t count;

	hnode *left, *right;

	hnode(unsigned char letter, size_t count, hnode *left = NULL, hnode *right = NULL) :
		letter(letter), count(count), left(left), right(right) {}
};

typedef hnode * heap_element;

class heap {

	public:

		heap(size_t (*p)(const heap_element &));
		// Constructor

		size_t size() const;

		heap_element front() const;

		void insert(const heap_element & item);
		// Inserts item at position size then reheaps up

		heap_element remove();
		// Removes first element then reheaps down


	private:

		heap_element _data[256];
		size_t _size;
		size_t (*priority)(const heap_element &); // Function pointer for priority

		size_t leftchild(size_t k) const;

		size_t rightchild(size_t k) const;

		size_t parent(size_t k) const;

		void swap(heap_element & x, heap_element & y);

		void reheap_up(size_t tree);
		// Recursively goes up the heap and swaps if parent is bigger than child

		void reheap_down(size_t tree);
		// Recursively goes down the heap and swaps if parent is bigger than child

};
