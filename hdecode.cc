/************************************************************************
		File: hdecode.cc
		Author: Sam Farber
		Date: December 6, 2016
		Assignment: Final Project(Huffman)

		Decodes the encoded file by recreating the tree that was given
		using hnodes, and then running through that tree using the bits
		of the encoded character. The characters decoded are then outputted
		to a new file with the original name and extension.

************************************************************************/

#include <iostream>
#include <cstdlib>
#include <fstream>
#include "heap.h"

using namespace std;


string byte2bitstr(unsigned char a)
{
	// Takes the encoded character and returns a string of 8 bits

	string bits = "";
	size_t byte = 128;

	while (byte > 0) {
		if (a/byte != 0) {
			bits += "1";
			a -= byte;
		}

		else
			bits += "0";

		byte /= 2;
	}

	return bits;
}

hnode * readTree(ifstream & fin)
{
	// Creates a tree with hnodes using the tree constructed with I's and L's

	if (char(fin.get()) == 'I') {
		hnode * leftTree = readTree(fin);
		hnode * rightTree = readTree(fin);
		return new hnode(0, 0, leftTree, rightTree);
	}

	else
		return new hnode(fin.get(), 0);
}

void decode(string & bits, hnode * tree, size_t & length,
							string & extra_bits, ofstream & fout)
{
	// Goes down the tree using bits until it hits a leaf, then outputs the letter

	if (bits.length() == 0)
		return;

	else if (!tree -> left && !tree -> right) {
		fout << tree -> letter;
		length++;
		extra_bits = ""; // Once a letter is reached, extra_bits can reset
		return;
	}

	else if (bits[0] == '0') {
		extra_bits += bits[0];
		bits = bits.substr(1);
		decode(bits, tree -> left, length, extra_bits, fout);
	}

	else {
		extra_bits += bits[0];
		bits = bits.substr(1);
		decode(bits, tree -> right, length, extra_bits, fout);
	}
}

void print_tree1(hnode *tree, size_t depth = 0)
{
  if (!tree)
    return;
  print_tree1(tree->right, depth + 1);
  for (size_t i = 0; i < depth; i++)
    cout << "     ";
  cout << tree->letter << ":" << tree->count << endl;
  print_tree1(tree->left, depth + 1);
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

	size_t length;

	// reads the file and stores the length of the original file
	ifstream fin(argv[1]);
	fin >> length;

	// outputs to a new file with the original extension and without .huf
	ofstream fout(string(argv[1]).substr(0, string(argv[1]).length()-4).c_str());

	size_t length1 = 0;
	string bits;
	string extra_bits = "";
	hnode * tree = readTree(fin);

	// Appends the bits that didn't reach a letter to the beginning of bits
	// Keeps decoding until the length equals the length of the original file
	while (length1 != length) {
		bits = extra_bits + byte2bitstr(fin.get());
		extra_bits = "";

		while(bits.length() != 0) {
			decode(bits, tree, length1, extra_bits, fout);
			if (length1 == length)
				break;
		}
	}

	// deletes encoded file
	remove(argv[1]);

	fout.close();
}
