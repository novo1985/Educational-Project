CC=g++
INC=-I.
CFLAGS=-c -Wall -std=c++0x -O2
SOURCES=Data.cc TreeNode.cc DecisionTree.cc main.cc
OBJECTS=$(SOURCES:.cc=.o)
EXECUTABLE=decision_tree

all:	$(SOURCES) $(EXECUTABLE)

$(EXECUTABLE):	$(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.cc.o:
	$(CC) $(CFLAGS) $(INC) $< -o $@

clean:
	rm *.o decision_tree
