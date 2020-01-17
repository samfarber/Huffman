/************************************************************************
		File: hencode.cc
		Author: Sam Farber
		Date: December 6, 2016
		Assignment: Final Project(Huffman)

		Encodes a text file using a min-heap priority queue and a huffman
		tree. It then outputs the length of the original file, the tree,
		and the encoded characters to a new file with a .huf extension
		after the original extension of the file.

************************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "heap.h"

using namespace std;

typedef hnode * heap_element;

size_t priority(const heap_element & n)
{
	// Returns the number of times a letter appears in the file
	return n -> count;
}

int COUNTS[256];
string CODES[256];

hnode * build_tree()
{
	// Builds huffman tree using a min-heap priority queue

	heap H(priority);
	for (size_t i = 0; i < 256; i++)
		if (COUNTS[i] > 0)
			H.insert(new hnode((unsigned char)i, COUNTS[i]));

	while (H.size() > 1) {
		hnode *left = H.remove();
		hnode *right = H.remove();
		H.insert(new hnode(0, left -> count + right -> count, left, right));
	}

	return H.front();
}

void gen_codes(hnode * tree, string code = "")
{
	// inserts codes into CODES array

	if (tree -> left)
		gen_codes(tree -> left, code + "0");

	if (tree -> right)
		gen_codes(tree -> right, code + "1");

	else
		CODES[tree -> letter] = code;
}

void print_tree(hnode * tree, ofstream & fout)
{
	// Outputs a text version of the tree using a preorder traversal
	// I's represent internal nodes and L's represent leaves with the letter after

	if (tree -> left || tree -> right) {
		fout << "I";
		print_tree(tree -> left, fout), print_tree(tree -> right, fout);
	}

	else
		fout << string("L") + char(tree -> letter);
}

unsigned char bitstr2byte(string a)
{
	// Converts a string of bits to an encoded character
	// Pre: a.length() == 8

	size_t byte = 128;
	unsigned char total = 0;
	for (size_t i = 0; i < 8; i++) {
		total += atoi(a.substr(i, 1).c_str()) * byte;
		byte /= 2;
	}

	return total;
}

void error(string msg)
{
	cout << msg << endl;
	exit(1);
}

int main(int argc, char ** argv)
{
	if (argc != 2)
		error("Wrong number of arguments");

	ifstream fin(argv[1]);
	for (size_t i = 0; i < 256; i++)
		COUNTS[i] = 0;

	size_t length = 0;

	// Reads the file and keeps track of length
	// and the number of times a letter appears in the file
	while (true) {
		int b = fin.get();
		if (!fin)
			break;
		COUNTS[b]++;
		length++;
	}

	if (length == 0)
		error("File length cannot be 0");

	// builds the tree
	hnode * tree = build_tree();

	// Inserts codes for each character into array
	gen_codes(tree);

	// Returns back to the beginning of the file
	// Source: stackoverflow.com
	fin.clear();
	fin.seekg(0, ios::beg);

	string codes = "";

	// outputs to a new file with the original extension plus .huf
	// outputs the length of the original file and the tree
	// source: Alex Dennis
	ofstream fout((string(argv[1]) + ".huf").c_str());
	fout << length;
	print_tree(tree, fout);

	// reads the file again
	// outputs the characters generated from the bytes
	while (true) {
		int b = fin.get();
		if (!fin)
			break;

		codes += CODES[b];
		while (codes.length() >= 8) {
			fout << bitstr2byte(codes.substr(0, 8));
			codes = codes.substr(8);
		}
	}

	// deletes original file
	std::remove(argv[1]);

	// adds 0's until code has length 8 and outputs the character generated
	while (codes.length() < 8)
		codes += "0";

	fout << bitstr2byte(codes);

	fout.close();
}
