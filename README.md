***ARACNe3 prototypes***

Currently, to use the executable type

./ARACNe3 /path/to/regulators.txt /path/to/gexpmatrix.txt

in the commandline.  The program will output a file 'output.txt' that contains
the regulator-target MI values

Lukas, if you are having issues with compatability and running the executable
just recompile all cpp files and link ARACNe3 with them.  You might be able to
modify the Makefile and just run 'make'
