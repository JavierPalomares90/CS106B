/**********************************************************
 * File: HuffmanEncoding.cpp
 *
 * Implementation of the functions from HuffmanEncoding.h.
 * Most (if not all) of the code that you write for this
 * assignment will go into this file.
 */

#include "HuffmanEncoding.h"
#include "HuffmanPQueue.h"

/* Function: getFrequencyTable
 * Usage: Map<ext_char, int> freq = getFrequencyTable(file);
 * --------------------------------------------------------
 * Given an input stream containing text, calculates the
 * frequencies of each character within that text and stores
 * the result as a Map from ext_chars to the number of times
 * that the character appears.
 *
 * This function will also set the frequency of the PSEUDO_EOF
 * character to be 1, which ensures that any future encoding
 * tree built from these frequencies will have an encoding for
 * the PSEUDO_EOF character.
 */
Map<ext_char, int> getFrequencyTable(istream& file) {
	Map<ext_char, int> result;
	
	// Read over the stream
	while (true){
		
		// Next character in the line
		int ch = file.get();
		if (ch == EOF){
			break;
		}
		
		// Set an extended character equal to the character
		ext_char xch = ch;
		
		// Increase the frequency by one
		result[xch]++;
	}
	
	// End of file marker
	result[PSEUDO_EOF] = 1;
	return result;	
}

/* Function: buildEncodingTree
 * Usage: Node* tree = buildEncodingTree(frequency);
 * --------------------------------------------------------
 * Given a map from extended characters to frequencies,
 * constructs a Huffman encoding tree from those frequencies
 * and returns a pointer to the root.
 *
 * This function can assume that there is always at least one
 * entry in the map, since the PSEUDO_EOF character will always
 * be present.
 */
Node* buildEncodingTree(Map<ext_char, int>& frequencies) {
	HuffmanPQueue queue = getQueue(frequencies);
	Node* root = getTree(queue);
	return root;
}
	

/* Returns a queue holding all the nodes */
HuffmanPQueue getQueue(Map<ext_char, int>& frequencies){
	HuffmanPQueue queue;
	foreach (ext_char ch in frequencies){
		Node* singleton = new Node;
		singleton->character = ch;
		singleton->weight = frequencies[ch];
		singleton->one = NULL;
		singleton->zero = NULL;
		queue.enqueue(singleton);
	}
	
	return queue;
}

/* Returns the Huffman binary tree */
Node* getTree(HuffmanPQueue queue){
	while(true){
		// Stop when there is only one node remaining in the queue
		if (queue.size() == 1){
			break;
		}
		
		// Dequeue the 2 least nodes
		Node* left = queue.dequeueMin();
		Node* right = queue.dequeueMin();
		
		// Join the 2 nodes
		Node* interiorNode = new Node;
		interiorNode->zero = left;
		interiorNode->one = right;
		interiorNode->weight = left->weight + right->weight;
		interiorNode->character = NOT_A_CHAR;
		
		// Enqueue the interior node
		queue.enqueue(interiorNode);
	}
	return queue.dequeueMin();
}
	

/* Function: freeTree
 * Usage: freeTree(encodingTree);
 * --------------------------------------------------------
 * Deallocates all memory allocated for a given encoding
 * tree.
 */
void freeTree(Node* root) {
	if (root == NULL){
		return;
	}
	
	// Recursively delete the memory
	freeTree(root->zero);
	freeTree(root->one);
	delete root;	
}

/* Function: encodeFile
 * Usage: encodeFile(source, encodingTree, output);
 * --------------------------------------------------------
 * Encodes the given file using the encoding specified by the
 * given encoding tree, then writes the result one bit at a
 * time to the specified output file.
 *
 * This function can assume the following:
 *
 *   - The encoding tree was constructed from the given file,
 *     so every character appears somewhere in the encoding
 *     tree.
 *
 *   - The output file already has the encoding table written
 *     to it, and the file cursor is at the end of the file.
 *     This means that you should just start writing the bits
 *     without seeking the file anywhere.
 */ 
void encodeFile(istream& infile, Node* encodingTree, obstream& outfile) {
	// Scan over the file
	while (true){
		int ch = infile.get();
		if(ch == EOF){
			break;
		}
		
		// String of the encoding of the letter
		string encoding;
		ext_char xch = ch;
		findEncoding(xch, encodingTree, encoding);
		
		// Output the file
		outfile << encoding;
	}
	
	// Stop Marker
	string stop;
	findEncoding(PSEUDO_EOF, encodingTree, stop);
	outfile << stop;
}

/* Finds the encoding for a letter */
bool findEncoding(ext_char ch, Node* encodingTree, string& result){
	
	// End of the tree
	if(encodingTree == NULL){
		return false;
	}
	
	// Found the correct node
	if(encodingTree->character == ch){
		return true;
	}
	
	// The zero child is the character
	if (encodingTree->zero != NULL){
		if(encodingTree->zero->character == ch){
			result = result + "0";
			return true;
		}
	}
	// The one child is the character
	if(encodingTree->one != NULL){
		if(encodingTree->one->character == ch){
			result = result + "1";
			return true;
		}
	}
	
	if(findEncoding(ch, encodingTree->zero, result)){
		result = "0" + result;
		return true;
	}
	else if (findEncoding(ch, encodingTree->one, result)){
		result = "1" + result;
		return true;
	}
	return false;
}

/* Function: decodeFile
 * Usage: decodeFile(encodedFile, encodingTree, resultFile);
 * --------------------------------------------------------
 * Decodes a file that has previously been encoded using the
 * encodeFile function.  You can assume the following:
 *
 *   - The encoding table has already been read from the input
 *     file, and the encoding tree parameter was constructed from
 *     this encoding table.
 *
 *   - The output file is open and ready for writing.
 */
void decodeFile(ibstream& infile, Node* encodingTree, ostream& file) {
	// Read over the file
	while (true){
		int ch = infile.get();
		if( ch == EOF){
			break;
		}
		string encoding;
		encoding += ch;
		ext_char decoded = getCharacter(encoding, encodingTree);
		// Read characters until we have come to a valid encoding
		while(decoded == NOT_A_CHAR){
			encoding += infile.get();
			decoded = getCharacter(encoding, encodingTree);
		}
		if(decoded == PSEUDO_EOF){
			break;
		}
		file << char(decoded);
	}		
}

/* Decodes a character from a sequence of bits. Returns '' as a sentinel value if the sequence does not correspond to a character */
ext_char getCharacter(string str, Node* encodingTree){
	Node* root = encodingTree;
	ext_char result;
	
	// Iterate over the encoding
	for(int i = 0; i < str.length(); i++){
		
		// If the bit is zero go to the zero child
		if (str[i] == '0'){
			result = root->zero->character;
			root = root->zero;
			
		// Go to the one child	
		}else{
			result = root->one->character;
			root = root->one;
		}
	}
	return result;
}
	

/* Function: writeFileHeader
 * Usage: writeFileHeader(output, frequencies);
 * --------------------------------------------------------
 * Writes a table to the front of the specified output file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to decompress input files once they've been
 * compressed.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * readFileHeader function defined below this one so that it
 * can properly read the data back.
 */
void writeFileHeader(obstream& outfile, Map<ext_char, int>& frequencies) {
	/* The format we will use is the following:
	 *
	 * First number: Total number of characters whose frequency is being
	 *               encoded.
	 * An appropriate number of pairs of the form [char][frequency][space],
	 * encoding the number of occurrences.
	 *
	 * No information about PSEUDO_EOF is written, since the frequency is
	 * always 1.
	 */
	 
	/* Verify that we have PSEUDO_EOF somewhere in this mapping. */
	if (!frequencies.containsKey(PSEUDO_EOF)) {
		error("No PSEUDO_EOF defined.");
	}
	
	/* Write how many encodings we're going to have.  Note the space after
	 * this number to ensure that we can read it back correctly.
	 */
	outfile << frequencies.size() - 1 << ' ';
	
	/* Now, write the letter/frequency pairs. */
	foreach (ext_char ch in frequencies) {
		/* Skip PSEUDO_EOF if we see it. */
		if (ch == PSEUDO_EOF) continue;
		
		/* Write out the letter and its frequency. */
		outfile << char(ch) << frequencies[ch] << ' ';
	}
}

/* Function: readFileHeader
 * Usage: Map<ext_char, int> freq = writeFileHeader(input);
 * --------------------------------------------------------
 * Reads a table to the front of the specified input file
 * that contains information about the frequencies of all of
 * the letters in the input text.  This information can then
 * be used to reconstruct the encoding tree for that file.
 *
 * This function is provided for you.  You are free to modify
 * it if you see fit, but if you do you must also update the
 * writeFileHeader function defined before this one so that it
 * can properly write the data.
 */
Map<ext_char, int> readFileHeader(ibstream& infile) {
	/* This function inverts the mapping we wrote out in the
	 * writeFileHeader function before.  If you make any
	 * changes to that function, be sure to change this one
	 * too!
	 */
	Map<ext_char, int> result;
	
	/* Read how many values we're going to read in. */
	int numValues;
	infile >> numValues;
	
	/* Skip trailing whitespace. */
	infile.get();
	
	/* Read those values in. */
	for (int i = 0; i < numValues; i++) {
		/* Get the character we're going to read. */
		ext_char ch = infile.get();
		
		/* Get the frequency. */
		int frequency;
		infile >> frequency;
		
		/* Skip the space character. */
		infile.get();
		
		/* Add this to the encoding table. */
		result[ch] = frequency;
	}
	
	/* Add in 1 for PSEUDO_EOF. */
	result[PSEUDO_EOF] = 1;
	return result;
}

/* Function: compress
 * Usage: compress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman compressor.  Compresses
 * the file whose contents are specified by the input
 * ibstream, then writes the result to outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void compress(ibstream& infile, obstream& outfile) {
	Map<ext_char, int> frequencies = getFrequencyTable(infile);
	Node* root = buildEncodingTree(frequencies);
	encodeFile(infile, root, outfile);
	freeTree(root);
	writeFileHeader(outfile, frequencies);
	
}

/* Function: decompress
 * Usage: decompress(infile, outfile);
 * --------------------------------------------------------
 * Main entry point for the Huffman decompressor.
 * Decompresses the file whose contents are specified by the
 * input ibstream, then writes the decompressed version of
 * the file to the stream specified by outfile.  Your final
 * task in this assignment will be to combine all of the
 * previous functions together to implement this function,
 * which should not require much logic of its own and should
 * primarily be glue code.
 */
void decompress(ibstream& infile, ostream& outfile) {
	Map<ext_char, int> frequencies = readFileHeader(infile);
	Node* root = buildEncodingTree(frequencies);
	decodeFile(infile, root, outfile);
	freeTree(root);
}

