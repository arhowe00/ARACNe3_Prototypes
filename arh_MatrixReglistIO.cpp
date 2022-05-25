#include "ARACNe3.h"
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

/*
 * Reads a newline-separated regulator list and outputs a vector of strings
 */
const vector<string> readRegList(string filename = "regulators.txt") {
	std::getline(filename, 	
}

/*
 * Reads a copula-transformed tab-separated GxN gene expression matrix and 
 * outputs an unordered hash table corresponding to the {gene, expression} 
 * values
 *
 */
unordered_map<string, vector<float>> readTransformedGexpMatrix(string 
		filename = "exp_mat.txt") {

}


std::getline(inFile, americanName, '\t'); // read up to first tab
inFile >> pokedexNumber >> std::ws; // read number then second tab
std::getline(inFile, japaneseName); // read up to first newline
