CXX = g++

CXXFLAGS = -std=c++11
LDFLAGS = -L/opt/homebrew/Cellar/boost/1.78.0_1/lib/ 
LDLIBS = 

.PHONY: all
all: arh_APMI 

arh_APMI: 
