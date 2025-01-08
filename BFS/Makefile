#------------------------------------------------------------------------------
#  Makefile for CMPS 101 Programming Assignment 2
#
#  make                     makes FindPath
#  make GraphClient         makes GraphClient
#  make GraphTest           makes GraphTest
#  make clean               removes binaries
#  make checkFind           tests FindPath for memory leaks on in7
#  make checkClient         tests GraphClient for memory leaks
#  make checkTest           tests GraphTest for memory leaks
#------------------------------------------------------------------------------

BASE_SOURCES   = Graph.c List.c
BASE_OBJECTS   = Graph.o List.o
HEADERS        = Graph.h List.h
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

# Target to make FindPath
FindPath : FindPath.o $(BASE_OBJECTS)
	$(LINK) FindPath FindPath.o $(BASE_OBJECTS)

# Target to make GraphClient
GraphClient : GraphClient.o $(BASE_OBJECTS)
	$(LINK) GraphClient GraphClient.o $(BASE_OBJECTS)

# Target to make GraphTest
GraphTest : GraphTest.o $(BASE_OBJECTS)
	$(LINK) GraphTest GraphTest.o $(BASE_OBJECTS)

# Compile FindPath.o
FindPath.o : FindPath.c $(HEADERS)
	$(COMPILE) FindPath.c

# Compile GraphClient.o
GraphClient.o : GraphClient.c $(HEADERS)
	$(COMPILE) GraphClient.c

# Compile GraphTest.o
GraphTest.o : GraphTest.c $(HEADERS)
	$(COMPILE) GraphTest.c

# Compile the base objects
$(BASE_OBJECTS) : $(BASE_SOURCES) $(HEADERS)
	$(COMPILE) $(BASE_SOURCES)

# Clean up all the binaries
clean :
	$(REMOVE) FindPath GraphClient GraphTest FindPath.o GraphClient.o GraphTest.o $(BASE_OBJECTS)

# Run Valgrind to check for memory leaks in FindPath
checkFind : FindPath
	$(MEMCHECK) FindPath in7 junk7

# Run Valgrind to check for memory leaks in GraphClient
checkClient : GraphClient
	$(MEMCHECK) GraphClient

# Run Valgrind to check for memory leaks in GraphTest
checkTest : GraphTest
	$(MEMCHECK) GraphTest
