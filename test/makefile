# Makefile for bin/test
# created with makefile-creator


####################
#Settings:


CXX ?= g++
FLAGS +=  -Wall -Wextra -Wpedantic -std=c++1y -O0 -D_GLIBCXX_DEBUG -g 
LIBS += -lboost_unit_test_framework 
INCLUDES += 
TARGET = bin/test
OBJECTS = build/algorithm.o build/main.o


####################
#Rules:


$(TARGET) : $(OBJECTS)
	$(CXX) $(FLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

build/%.o:
	@if test ! -d 'build'; then mkdir 'build'; echo "created 'build'" ; fi
	$(CXX) $(FLAGS) $(INCLUDES) -c -o $@ $<

clean:
	rm build/*.o

all: $(TARGET)


####################
#Dependencies:


build/algorithm.o: src/algorithm.cpp makefile

build/main.o: src/main.cpp makefile

