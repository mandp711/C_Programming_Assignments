/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Matrix.c
Implementation file of Matrix ADT 
*/
#include "Matrix.h"

double vectorDot(List P, List Q);

typedef struct EntryObj {
  int col;
  double value;
} EntryObj;

typedef struct MatrixObj {
  int size;
  int NNZ;
  List* rows;
} MatrixObj;




Entry newEntry(int col, double value) {
  Entry E = malloc(sizeof(EntryObj));
  E->col = col;
  E->value = value;
  return E;
}




void freeEntry(Entry* pE) {
  if( pE!=NULL && *pE!=NULL ){
    free(*pE);
    *pE = NULL;
 }
}




int getEntryCol(Entry E) {
    return E->col;
}




double getEntryValue(Entry E) {
  return E->value;
}




Matrix newMatrix(int n) {
  Matrix M = malloc(sizeof(MatrixObj));
  M->size = n;
  M->NNZ = 0;
  M->rows = calloc(n, sizeof(List));
  for (int i = 0; i < n; i++) {
      M->rows[i] = newList();
  }
  return M;
}




void freeMatrix(Matrix* pM) {
  if (pM != NULL && *pM != NULL) {
      for (int i = 0; i < (*pM)->size; i++) {
          List L = (*pM)->rows[i];
          moveFront(L);
          while (index(L) >= 0) {
              Entry* entry = (Entry*)get(L);
              free(entry);
              moveNext(L);
          }
          freeList(&(L));
      }
      free((*pM)->rows);  // Free the array of lists
      free(*pM);
      *pM = NULL;
  }
}


int size(Matrix M) {
  return M->size;
}




int NNZ(Matrix M) {
  return M->NNZ;
}

int equals(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling equals() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
   
    if (A->size != B->size || A->NNZ != B->NNZ) {
        return 0; // Matrices are not equal if their sizes or number of non-zero entries are different
    }

   for (int i = 1; i <= A->size; i++) {
       List LA = A->rows[i-1];
       List LB = B->rows[i-1];
       
       while ((index(LA) >= 0) && (index(LB) >= 0)) {
        Entry entryA = (Entry)get(LA);
        int valA = getEntryValue(entryA);
        double colA = getEntryCol(entryA);


        Entry entryB = (Entry)get(LB);
        double valB = getEntryValue(entryB);
        int colB = getEntryCol(entryB);


        if (valA != valB || colA != colB) {
            return 0;
        }
        moveNext(LA);
        moveNext(LB);
        } 
    }
    return 1; 
}


void makeZero(Matrix M) {
    if (M == NULL) {
      fprintf(stderr, "List Error: calling makeZero() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    for (int i = 1; i <= M->size; i++) {
       List L = M->rows[i-1];
       moveFront(L);
       while(index(L) >= 0) {
           Entry entry = (Entry)get(L);
           free(entry);
           moveNext(L);
       }
       clear(L);
   }
   M->NNZ = 0; 
}




void changeEntry(Matrix M, int i, int j, double x) {
    if (M == NULL) {
        fprintf(stderr, "Matrix Error: changeEntry() called on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    if (i < 1 || i > M->size || j < 1 || j > M->size) {
        fprintf(stderr, "Matrix Error: changeEntry() called with invalid indices\n");
        exit(EXIT_FAILURE);
    }

    List L = M->rows[i - 1];
    moveFront(L);

    while (index(L) >= 0) {
        Entry entry = (Entry)get(L);
        int col = getEntryCol(entry);

        if (col >= j) 
            break;
        moveNext(L);
    }

    if (index(L) >= 0) {
        Entry entry = (Entry)get(L);
        int col = getEntryCol(entry);

        if (col == j) {
            if (x != 0.0) {
                entry->value = x;
            } else {
                delete(L);
                M->NNZ--;
            }
        } else if (x != 0.0) {
            insertBefore(L, newEntry(j, x));  // Insert new entry
            M->NNZ++;
        }
    } else if (x != 0.0) {
        append(L, newEntry(j, x));  // Append if non-zero and no larger entry exists
        M->NNZ++;
    }
}

Matrix sum(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling sum() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling sum() on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
    if (A == B) {
        return scalarMult(2, A); 
    }

    Matrix C = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List LA = A->rows[i-1];
        List LB = B->rows[i-1];

        moveFront(LA);
        moveFront(LB);

        while (index(LA) >= 0 || index(LB) >= 0) {
            int colA = -1, colB = -1;
            double valA = 0, valB = 0;

            if (index(LA) >= 0) {
                Entry entryA = (Entry)get(LA);
                colA = getEntryCol(entryA);
                valA = getEntryValue(entryA);
            }

            if (index(LB) >= 0) {
                Entry entryB = (Entry)get(LB);
                colB = getEntryCol(entryB);
                valB = getEntryValue(entryB);
            }

            if (colA == colB) {
                double sum = valA + valB;
                if (sum != 0) {
                    changeEntry(C, i, colA, sum);
                }
                moveNext(LA);
                moveNext(LB);
            } else if (colA != -1 && (colB == -1 || colA < colB)) {
                changeEntry(C, i, colA, valA);
                moveNext(LA);
            } else {
                changeEntry(C, i, colB, valB);
                moveNext(LB);
            }
        }
    }
    return C;
}



Matrix copy(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling copy() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix copy = newMatrix(A->size);

    for (int i = 1; i <= A->size; i++) {
        List L = A->rows[i-1];
        moveFront(L);
        while (index(L) >= 0) {
            Entry entry = (Entry)get(L);
            int colA = getEntryCol(entry);
            double valA = getEntryValue(entry);
            changeEntry(copy, i, colA, valA);
            moveNext(L);
        }
    }
    return copy;
}




Matrix transpose(Matrix A) {
    if (A == NULL) {
        fprintf(stderr, "Matrix Error: calling transpose() on NULL Matrix reference\n");
        exit(EXIT_FAILURE);
    }
    Matrix T = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->rows[i-1];
        moveFront(L);
        while(index(L) >= 0) {
            Entry entry = (Entry)get(L);
            int colA = getEntryCol(entry);
            double valA = getEntryValue(entry);
            changeEntry(T, colA, i, valA);
            moveNext(L);
       }
   }
   return T;
}




Matrix scalarMult(double x, Matrix A) {
    if (A == NULL) {
      fprintf(stderr, "Matrix Error: calling scalarMult() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    Matrix sM = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List L = A->rows[i-1];
        moveFront(L);
        while (index(L) >= 0) {
            Entry entry = (Entry)get(L);
            int colA = getEntryCol(entry);
            double valA = getEntryValue(entry);
            changeEntry(sM, i, colA, x * valA);
            moveNext(L);
        }
   }
   return sM;
}


Matrix diff(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling diff() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling diff() on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(A->size);
    for (int i = 1; i <= A->size; i++) {
        List LA = A->rows[i-1];
        List LB = B->rows[i-1];


        moveFront(LA);
        moveFront(LB);


        while (index(LA) >= 0 || index(LB) >= 0) {
            int colA = -1, colB = -1;
            double valA = 0, valB = 0;


            if (index(LA) >= 0) {
                Entry entryA = (Entry)get(LA);
                colA = getEntryCol(entryA);
                valA = getEntryValue(entryA);
            }


            if (index(LB) >= 0) {
                Entry entryB = (Entry)get(LB);
                colB = getEntryCol(entryB);
                valB = getEntryValue(entryB);
            }


            if (colA == colB) {
                double diff = valA - valB;
                if (diff != 0) {
                    changeEntry(C, i, colA, diff);
                }
                moveNext(LA);
                moveNext(LB);
            }
            else if (colA != -1 && (colB == -1 || colA < colB)) {
              // Only matrix A has an entry, or A's entry comes first
                changeEntry(C, i, colA, valA); 
                moveNext(LA);
            } else {
              // Only matrix B has an entry, or B's entry comes first
                changeEntry(C, i, colB, -valB);
                moveNext(LB);
            }
        }
    }
    return C; 
}


Matrix product(Matrix A, Matrix B) {
    if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling product() on NULL Matrix reference\n");
      exit(EXIT_FAILURE);
    }
    if (A->size != B->size) {
        fprintf(stderr, "Matrix Error: calling product() on matrices of different sizes\n");
        exit(EXIT_FAILURE);
    }
    Matrix C = newMatrix(A->size);
    // printf("Creates new matrix\n"); 

    Matrix BT = transpose(B);
    // printf("Creates new transpose\n"); 

    for (int i = 1; i <= A->size; i++) {
        List rowA = A->rows[i-1];
        // printf("Initializes row\n"); 
        if (length(rowA) == 0) { 
            continue; 
        }

        for (int j = 1; j <= B->size; j++) {
            List rowBT = BT->rows[j - 1];  // Use BT's rows for the dot product
            if (length(rowBT) == 0) {
                continue; 
            }

            // Compute the dot product of rowA and rowBT
            double dotProduct = vectorDot(rowA, rowBT);

            // If the dot product is non-zero, update matrix C
            if (dotProduct != 0.0) {
                changeEntry(C, i, j, dotProduct);
            }
        }
    }

    // Free the transpose matrix after we're done using it
    freeMatrix(&BT);
    return C;
}   

double vectorDot(List P, List Q) {
   double dotProduct = 0.0;


   if (length(P) == 0 || length(Q) == 0)  {
        // Handle the case where the list is empty
        printf("List is empty, cannot get an entry.\n");
}

   moveFront(P);
   moveFront(Q);


   while (index(P) >= 0 && index(Q) >= 0) {
       Entry entryP = (Entry)get(P);
       Entry entryQ = (Entry)get(Q);


       int colP = getEntryCol(entryP);
       double valP = getEntryValue(entryP);


       int colQ = getEntryCol(entryQ);
       double valQ = getEntryValue(entryQ);


       if (colP == colQ) {
           dotProduct += valP * valQ;
           moveNext(P);
           moveNext(Q);
       }
       else if (colP < colQ) {
           moveNext(P);
       }
       else {
           moveNext(Q);
       }
   }


   return dotProduct;
}
   


void printMatrix(FILE* out, Matrix M) {
   if (M == NULL) {
       fprintf(stderr, "Matrix Error: calling printMatrix() on NULL Matrix reference\n");
       exit(EXIT_FAILURE);
   }
   for (int i = 0; i < M->size; i++) {
       List L = M->rows[i];
       if (length(L) > 0) {
           fprintf(out, "%d: ", i + 1);
           moveFront(L);
           while (index(L) >= 0) {
               Entry E = (Entry)get(L);
               fprintf(out, "(%d, %.1f) ", getEntryCol(E), getEntryValue(E));
               moveNext(L);
           }
           fprintf(out, "\n");
       }
   }
}































