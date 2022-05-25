#include "ARACNe3.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

typedef unordered_map<string, vector<float>> hashmap;

/*
 * Reads a newline-separated regulator list and outputs a vector of strings
 */
vector<string> readRegList(string filename = "regulators.txt") {
	fstream f {filename};
	vector<string> regs;
	string reg;
	if (!f.is_open()) {
        	cerr << "error: file open failed " << filename << ".\n";
		return regs;
	}
	while (getline(f, reg, '\n')) {
		regs.push_back(reg);
	}
	return regs;
}

/*
 * Reads a copula-transformed tab-separated GxN gene expression matrix and 
 * outputs an unordered hash table corresponding to the {gene, expression} 
 * values
 *
 */
hashmap readTransformedGexpMatrix(string filename = "exp_mat.txt") {
	vector<float> v{0.0};
	hashmap hm = {{"hi", v}};
	return hm;
}

int main() {
	//string regulator_file = "test/regulators.txt";
	//string matrix_file = "test/exp_mat.txt";
	//const vector<string> regulators = readRegList(regulator_file);
	//for (string reg : regulators) { cout << reg << endl; }
	//return 0;
}
