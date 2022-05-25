CXX = g++

CXXFLAGS = -std=c++11 $(INCLUDES)

INCLUDES = -I/opt/homebrew/lib/R/4.1/site-library/Rcpp/include/ -I/Library/Frameworks/R.framework/Versions/4.1-arm64/Resources/include/
LDFLAGS = -L/opt/homebrew/Cellar/boost/1.78.0_1/lib/
LDLIBS = 


.PHONY: all
all: arh_APMI 

arh_APMI: 
