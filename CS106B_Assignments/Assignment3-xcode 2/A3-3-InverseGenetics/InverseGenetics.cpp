/* File: InverseGenetics.cpp
 *
 * A program that, given a sequence of amino acids, returns all possible
 * RNA strands that could encode that amino acid sequence.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "map.h"
#include "console.h"
#include "simpio.h"
using namespace std;

/* Function: allRNAStrandsFor(string protein,
 *                            Map<char, Set<string> >& codons);
 * Usage: foreach (string rna in allRNAStrandsFor("PARTY", codons);
 * ==================================================================
 * Given a protein and a map from amino acid codes to the codons for
 * that code, returns all possible RNA strands that could generate
 * that protein.
 */
Set<string> allRNAStrandsFor(string protein, Map<char, Set<string> >& codons);

/* Function: loadCodonMap();
 * Usage: Map<char, Lexicon> codonMap = loadCodonMap();
 * ==================================================================
 * Loads the codon mapping table from a file.
 */
Map<char, Set<string> > loadCodonMap();

int main() {
	/* Load the codon map. */
	Map<char, Set<string> > codons = loadCodonMap();
	
	// Reads a protein from the user as letters for its amino acids
	string protein = getLine("Enter a protein as letters for its amino acids: ");
	Set<string> RNAstrands = allRNAStrandsFor(protein, codons);
	cout << protein << " can be represented by the following RNA strands: " << endl;
	foreach(string strand in RNAstrands){
		cout << "	" << strand << endl;
	}
	return 0;
}

Set<string> allRNAStrandsFor(string protein, Map<char, Set<string> >& codons) {
	// If the protein is a single amino acid, return all of the codons representing that acid
	if(protein.length() == 1){
		return codons[protein[0]];
	}else{
		string firstAminoAcidRemoved = protein.substr(1);
		
		// Strands of first acid
		Set<string> firstStrands = codons[protein[0]];
		
		// Strands of remaining acids
		Set<string> remainingStrands = allRNAStrandsFor(firstAminoAcidRemoved, codons);
		
		// Combines strands of the first acid with the strands of the rest of the acids
		Set<string> result;
		foreach(string first in firstStrands){
			foreach(string rest in remainingStrands){
				result += first + rest;
			}
		}
		return result;
	}
	
}

/* Returns a map of one letter codes for amino acids and the codons that represent the amino acid */
Map<char, Set<string> > loadCodonMap() {
	ifstream input("codons.txt");
	Map<char, Set<string> > result;
    
	/* The current codon / protein combination. */
	string codon;
	char protein;
	
	/* Continuously pull data from the file until all data has been
	 * read.  We did not cover this syntax in class, but it means
	 * "while reading a codon/protein pair succeeds, add the pair to
	 * the map."
	 */
	while (input >> codon >> protein) {
		result[protein] += codon;
	}
	
	return result;
}

