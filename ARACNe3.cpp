#include "ARACNe3.h"
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>

using namespace std;

/*
 * Assumes that simply the path to the regulator list and the path to the gene
 * expression matrix are commandline arguments
 *
 * e.g. ./ARACNe3 test/regfile.txt test/matrixfile.txt
 */
int main(int argc, char *argv[]) {
	vector<string> regs = readRegList(string(argv[1]));
	hashmap matrix = readTransformedGexpMatrix(string(argv[2]));
	if (mkdir("output", 0777) != 0) return 1;
	for (auto &reg : regs) {
		pid_t pid = fork();
		if (pid == 0) {
			// makes the regulator name the name of the file
			ofstream ofs{"output/" + reg + ".txt"};
			auto cout_buff = cout.rdbuf();
			cout.rdbuf(ofs.rdbuf());

			// cout << "REGULATOR\tTARGET\tMI\n";
			for (auto it = matrix.begin(); it != matrix.end(); ++it) {
				if (it->first != reg) {
					float mi = APMI(matrix[reg], it->second, 7.815, 4);
					cout << reg << "\t" << it->first << "\t" << mi << "\n";
				}	
			}
			cout.rdbuf(cout_buff);
			return 0;
		}
	}
}
