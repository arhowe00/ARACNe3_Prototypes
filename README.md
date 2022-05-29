# ARACNe3

## ARACNe3 (Algorithm for the Accurate Reconstruction of Cellular Networks v. 3)

This is a prototype of the C++ implementation of ARACNe3 currently under
development.  ARACNe3 presents multiple computational and theoretical
improvements to the existing ARACNe-AP algorithm formulated in Java.  

Please contact Aaron T. Griffin and Lukas J. Vlahos for any questions in regards
to this project.

Aaron T. Griffin - atg2142@cumc.columbia.edu Lukas J. Vlahos -
lv2395@cumc.columbia.edu 

## Running the Most Recent Executable

This codebase is currently under development, but the most up-to-date ARACNe3
executable can still be run using the following commandline arguments: ./ARACNe3
/path/to/regulators.txt /path/to/gexpmatrix.txt

The program will CURRENTLY output a directory 'output/' that contains the
regulator-target MI values estimated via Adaptive Partitioning (APMI).  

To run this multiple times, DELETE 'output/', as this is a primitive program and
will append to the previous directory.

It may be the case that this executable is only operable on MacOS 12.3.1 arm64
devices.  C++ files may be recompiled to operate on any UNIX-based operating
system.  

## List of Improvements in Development:
 - **IN PROGRESS** Multithreading/non-multithreading option via commandline 
 - **IN PROGRESS** First MI-pruning step based on null model for MI and
   Benjamini-Hochberg principle control for user-parametrizable FDR. 
 - Second DPI-pruning step made optional and implemented
 - **IN PROGRESS** Low-level optimization and parallel for loop processing.
   Namely, minimizing heap allocation and using caches, as well as using the
most efficient data structures required to store edge information (hashmaps,
linked lists, adjacency matrices, etc.)

