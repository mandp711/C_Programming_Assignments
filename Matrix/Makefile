#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 4
#
#  make                     makes Sparse
#  make MatrixTest          makes MatrixTest
#  make ListTest            makes ListTest
#  make ListClient          makes ListClient
#  make MatrixClient        makes MatrixClient
#  make clean               removes all binaries
#  make SparseCheck         runs Sparse in valgrind on in5
#  make MatrixCheck         runs MatrixTest in valgrind
#  make ListCheck           runs ListTest in valgrind
#------------------------------------------------------------------------------

MAIN           = Sparse
ADT1           = Matrix
ADT2           = List
SOURCE         = $(MAIN).c
OBJECT         = $(MAIN).o
ADT1_TEST      = $(ADT1)Test
ADT1_SOURCE    = $(ADT1).c
ADT1_OBJECT    = $(ADT1).o
ADT1_HEADER    = $(ADT1).h
ADT2_TEST      = $(ADT2)Test
ADT2_SOURCE    = $(ADT2).c
ADT2_OBJECT    = $(ADT2).o
ADT2_HEADER    = $(ADT2).h
CLIENT         = ListClient
CLIENT_SOURCE  = $(CLIENT).c
CLIENT_OBJECT  = $(CLIENT).o
LIST_TEST      = ListTest
LIST_TEST_SOURCE = $(LIST_TEST).c
LIST_TEST_OBJECT = $(LIST_TEST).o
MATRIX_CLIENT  = MatrixClient
MATRIX_CLIENT_SOURCE = $(MATRIX_CLIENT).c
MATRIX_CLIENT_OBJECT = $(MATRIX_CLIENT).o
MATRIX_TEST    = MatrixTest
MATRIX_TEST_SOURCE = $(MATRIX_TEST).c
MATRIX_TEST_OBJECT = $(MATRIX_TEST).o
COMPILE        = gcc -std=c17 -Wall -c
LINK           = gcc -std=c17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT1_TEST): $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(ADT1_TEST) $(ADT1_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT)

$(ADT2_TEST): $(ADT2_TEST).o $(ADT2_OBJECT)
	$(LINK) $(ADT2_TEST) $(ADT2_TEST).o $(ADT2_OBJECT)

$(CLIENT): $(CLIENT_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(CLIENT) $(CLIENT_OBJECT) $(ADT2_OBJECT)

$(LIST_TEST): $(LIST_TEST_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(LIST_TEST) $(LIST_TEST_OBJECT) $(ADT2_OBJECT)

$(MATRIX_CLIENT): $(MATRIX_CLIENT_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MATRIX_CLIENT) $(MATRIX_CLIENT_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(MATRIX_TEST): $(MATRIX_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)
	$(LINK) $(MATRIX_TEST) $(MATRIX_TEST_OBJECT) $(ADT1_OBJECT) $(ADT2_OBJECT)

$(OBJECT): $(SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT1_TEST).o: $(ADT1_TEST).c $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(ADT1_TEST).c

$(ADT2_TEST).o: $(ADT2_TEST).c $(ADT2_HEADER)
	$(COMPILE) $(ADT2_TEST).c

$(CLIENT_OBJECT): $(CLIENT_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(CLIENT_SOURCE)

$(LIST_TEST_OBJECT): $(LIST_TEST_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(LIST_TEST_SOURCE)

$(MATRIX_CLIENT_OBJECT): $(MATRIX_CLIENT_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(MATRIX_CLIENT_SOURCE)

$(MATRIX_TEST_OBJECT): $(MATRIX_TEST_SOURCE) $(ADT1_HEADER) $(ADT2_HEADER)
	$(COMPILE) $(MATRIX_TEST_SOURCE)

$(ADT1_OBJECT): $(ADT1_SOURCE) $(ADT1_HEADER)
	$(COMPILE) $(ADT1_SOURCE)

$(ADT2_OBJECT): $(ADT2_SOURCE) $(ADT2_HEADER)
	$(COMPILE) $(ADT2_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ADT1_TEST) $(ADT2_TEST) $(CLIENT) $(LIST_TEST) $(MATRIX_CLIENT) $(MATRIX_TEST)
	$(REMOVE) $(OBJECT) $(ADT1_TEST).o $(ADT2_TEST).o $(ADT1_OBJECT) $(ADT2_OBJECT) $(CLIENT_OBJECT) $(LIST_TEST_OBJECT) $(MATRIX_CLIENT_OBJECT) $(MATRIX_TEST_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) in5 junk5

$(ADT1)Check: $(ADT1_TEST)
	$(MEMCHECK) $(ADT1_TEST)

$(ADT2)Check: $(ADT2_TEST)
	$(MEMCHECK) $(ADT2_TEST)

ListCheck: $(LIST_TEST)
	$(MEMCHECK) $(LIST_TEST)

MatrixClientCheck: $(MATRIX_CLIENT)
	$(MEMCHECK) $(MATRIX_CLIENT) in5 junk5

MatrixTestCheck: $(MATRIX_TEST)
	$(MEMCHECK) $(MATRIX_TEST)
