***ARACNe3 prototypes***

Currently, to use the executable type

./ARACNe3 /path/to/regulators.txt /path/to/gexpmatrix.txt

in the commandline.  The program will CURRENTLY output a directory 'output/' 
that contains the regulator-target MI values.  

If running this again, DELETE 'output/', as this is a very primitive program

Lukas, if you are having issues with compatability and running the executable
just recompile all cpp files and link ARACNe3 with them.  You might be able to
modify the Makefile and just run 'make'


**LIST OF IMPROVEMENTS TO MAKE**
 - Lukas's idea of parallel for loop calculation (opmi something??)
 - More efficient hashmap processing
