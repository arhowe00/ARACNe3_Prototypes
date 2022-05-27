CXX = g++

CXXFLAGS = -std=c++20 $(INCLUDES)

INCLUDES = -I/opt/homebrew/lib/R/4.1/site-library/Rcpp/include/ -I/Library/Frameworks/R.framework/Versions/4.1-arm64/Resources/include/
LDFLAGS = -L/opt/homebrew/Cellar/boost/1.78.0_1/lib/
LDLIBS = 


ARACNe3: arh_APMI.o arh_MatrixReglistIO.o
	rm *.o

arh_APMI.o:

arh_MatrixReglistIO.o:


arh_APMI: 

arh_MatrixReglistIO:


.PHONY: all
all: arh_ARACNe3 arh_APMI arh_MatrixReglistIO

.PHONY: clean
clean: 
	rm *.o arh_APMI arh_MatrixReglistIO
