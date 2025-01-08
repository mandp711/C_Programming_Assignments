Sparse.c
    This is the main program file that utilizes the Matrix and List ADTs to implement a sparse matrix calculator. It handles user inputs and performs matrix operations such as addition, subtraction, scalar multiplication, transposition, and multiplication on sparse matrices. The file is responsible for reading input data, managing matrix structures, and outputting results.

Matrix.c
    This file implements the Matrix Abstract Data Type (ADT) specifically designed for sparse matrices. It defines the internal structure of matrices, with optimized storage for non-zero elements, and provides functions to create, manipulate, and perform operations on matrices. Operations include matrix addition, subtraction, scalar multiplication, transposition, and matrix multiplication.

Matrix.h
    The header file for Matrix.c. It defines the Matrix ADT's public interface, including the data structures and function prototypes for matrix manipulation. This file allows other components of the program to interact with matrices while encapsulating implementation details.

MatrixTest.c
    A test file for the Matrix ADT. This file includes unit tests for all Matrix functions, verifying the correctness of operations such as matrix creation, addition, scalar multiplication, and transposition. It helps ensure the reliability and correctness of matrix operations.

List.c
    This file implements the List Abstract Data Type (ADT), which is used as a foundational data structure within the Matrix ADT. The List ADT is modified to support generic pointers, allowing flexible storage and manipulation of matrix elements in a sparse format. This file provides functions to create, insert, delete, and access elements within the list.

List.h
    The header file for List.c. It provides the public interface for the List ADT, including data structure definitions and function prototypes. This file allows the Matrix ADT and other components to interact with the list structure without knowing the details of its implementation.

ListTest.c
    A test file for the List ADT. This file includes unit tests for list operations, such as insertion, deletion, and traversal, to verify the List ADT's functionality. Ensuring a reliable list structure is essential for correct matrix manipulation in sparse matrix operations.

README.md
    This file provides an overview of the sparse matrix calculator project. It includes instructions on compiling and running the program, a description of each implemented ADT, usage examples, and any specific implementation details. It may also include information about limitations, assumptions, and potential improvements.

Makefile
    This file automates the compilation process for the project. It includes rules to compile the main program (Sparse.c), the Matrix and List ADTs, and their respective test programs. The Makefile simplifies building, cleaning, and running tests, ensuring all components are compiled and linked correctly.
