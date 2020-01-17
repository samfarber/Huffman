/************************************************************************
		File: heap.cc
		Author: Sam Farber
		Date: December 6, 2016
		Assignment: Final Project(Huffman)

		Implementation of the heap class.

************************************************************************/

#include "heap.h"


heap::heap(size_t (*p)(const heap_element &)) : _size(0), priority(p) {}
// Constructor

/*** const member functions ***/

size_t heap::size() const
{
	return _size;
}

heap_element heap::front() const
{
	return _data[0];
}

size_t heap::leftchild(size_t k) const
{
	return 2*k + 1;
}

size_t heap::rightchild(size_t k) const
{
	return 2*k + 2;
}

size_t heap::parent(size_t k) const
{
	return (k - 1)/2;
}

/*** non-const member functions ***/

void heap::insert(const heap_element & item)
{
	// Inserts item at position size then reheaps up
	_data[_size++] = item;
	reheap_up(size() - 1);
}

heap_element heap::remove()
{
	// Removes first element then reheaps down
	heap_element removed = _data[0];
	_data[0] = _data[--_size];
	reheap_down(0);
	return removed;
}

void heap::swap(heap_element & x, heap_element & y)
{
	heap_element temp = x;
	x = y;
	y = temp;
}

void heap::reheap_up(size_t tree)
{
	// Recursively goes up the heap and swaps if parent is bigger than child

	if (tree == 0)
		return;

	size_t par = parent(tree);

	if (priority(_data[tree]) < priority(_data[par])) {
		swap(_data[tree], _data[par]);
		reheap_up(par);
	}
}

void heap::reheap_down(size_t tree)
{
	// Recursively goes down the heap and swaps if parent is bigger than child

	if (leftchild(tree) >= size())
		return;

	size_t child = leftchild(tree);

	if (rightchild(tree) < size() &&
				priority(_data[rightchild(tree)]) < priority(_data[child]))
		child = rightchild(tree);

	if (priority(_data[child]) < priority(_data[tree])) {
		swap(_data[child], _data[tree]);
		reheap_down(child);
	}
}
