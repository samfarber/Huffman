# Huffman
Huffman tree encoder and decoder for text documents

First run the makefile to compile the necessary files, like so:

    make
    
Then, run the encoder on a txt file:

    ./hencode moby.txt
    
This will delete moby.txt and create the encoded file moby.txt.huf

To then decode the encoded huf file, run:

    ./hdecode moby.txt.huf

This will delete the decoded huf file and create a new moby.txt file which will be the same as the original.
