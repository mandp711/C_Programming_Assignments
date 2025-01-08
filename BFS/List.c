/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
List.c
Implementation file for List ADT
*/

#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<stdbool.h>
#include "List.h"



// structs --------------------------------------------------------------------

// private Node type
typedef struct NodeObj* Node;

// private NodeObj type
typedef struct NodeObj{
   int data;
   struct NodeObj* next;
   struct NodeObj* prev; 
} NodeObj;

// private QueueObj type
typedef struct ListObj{
   Node front;
   Node back;
   Node cursor; 
   int length;
   int index; 
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next and data fields.
Node newNode(int data){
   Node N = malloc(sizeof(NodeObj));
   assert( N!=NULL );
   N->data = data;
   N->next = NULL;
   return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

List newList(void){
   List L = malloc(sizeof(ListObj));
   L->front = L->back = L->cursor = NULL;
   L->length = 0;
   L->index = -1;
   return L;
}

void freeList(List* pL) {
   if (pL != NULL && *pL != NULL) {
        while ((*pL)->length > 0) {
            deleteFront(*pL);
        }
   free(*pL);
   *pL = NULL;
}
}

// Access functions 
int length(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling length() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return L->length; 
}

int index(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling index() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   return L->index; 
}

int front(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling length() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return L->front->data; 

}

int back(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling back() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling back() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   return L->back->data; 
   
}

int get(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling get() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling get() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling get() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0 && L->index >= 0) {
      return L->cursor->data; 
   }
   return -1; 
}

bool equals(List A, List B) {
   if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling equals() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (A->length != B->length) {
      return false; 
   }
   Node M = A->front;
   Node N = B->front; 
   while(M !=  NULL && N != NULL) {
      if (M->data != N->data) {
         return false; 
      }
      M = M->next; 
      N = N->next; 
   }
   return true; 
}

// Manipulation procedures 
void clear(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling clear() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   while (L->length > 0) {
      deleteFront(L);
   }
   L->cursor = NULL;
   L->index = -1;
}


void set(List L, int x) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling set() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling set() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling set() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0 && L->index >= 0) {
      L->cursor->data = x; 
   }
}

void moveFront(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveFront() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0) {
      L->cursor = L->front; 
      L->index = 0; 
   }
}

void moveBack(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0) {
      L->cursor = L->back; 
      L->index = L->length-1; 
   }
}

void movePrev(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveBack() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor != NULL && L->index != 0) {
      L->cursor = L->cursor->prev; 
      L->index -= 1; 
   }
   else if (L->cursor != NULL && L->index == 0) {
      L->cursor = NULL;
      L->index = -1; 
   }
}

void moveNext(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling moveNext() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor != NULL && L->index != L->length-1) {
      L->cursor = L->cursor->next; 
      L->index += 1; 
   }
   else if (L->cursor != NULL && L->index == L->length-1) {
      L->cursor = NULL; 
      L->index = -1; 
   }
}

void prepend(List L, int x) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling prepend() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode(x);
   if (L->length != 0 ) {
      N->next = L->front;
      L->front->prev = N;
      L->front = N;
   }
   else {
      L->front = L->back = N; 
   }
   if (L->cursor != NULL) {
      L->index++;
   }
   L->length++; 
}

void append(List L, int x) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling append() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = newNode(x);
   if (L->length != 0) {
      N->prev = L->back;
      L->back->next = N; 
      L->back = N; 
   }
   else {
      L->front = L->back = N;
   }
   L->length++; 
}

void insertBefore(List L, int x) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling insertBefore() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling insertBefore() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling insertBefore() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0 && L->index >= 0) {
      if (L->cursor == L->front) {
         prepend(L, x); 
      }
      else {
         Node N = newNode(x); 
         N->next = L->cursor; 
         N->prev = L->cursor->prev;
         L->cursor->prev->next = N; 
         L->cursor->prev = N; 
         L->index++; 
         L->length++; 
      }
   } else {
      exit(1); 
   }
}

void insertAfter(List L, int x) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling insertAfter() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (length(L) <= 0) {
      fprintf(stderr, "List Error: calling insertAfter() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (index(L) < 0) {
      fprintf(stderr, "List Error: calling insertAfter() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if (L->length > 0 && L->index >= 0) {
      if (L->cursor == L->back) {
         append(L, x); 
      }
      else {
         Node N = newNode(x); 
         N->prev = L->cursor; 
         N->next = L->cursor->next;
         L->cursor->next->prev = N; 
         L->cursor->next = N; 

         L->length++; 
      }
   } 
}

void deleteFront(List L) {
   if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteFront() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling deleteFront() on an empty List\n");
        exit(EXIT_FAILURE);
    }
   Node N = L->front;
   if (L->cursor == L->front) {
      L->cursor = NULL;  // Set cursor to NULL
      L->index = -1;     // Invalidate the index
   } else if (L->cursor != NULL) {
      // If cursor is defined but not at the front, update the index
      L->index--;  // Shift index since an element is being removed
   }
   if (L->length > 1) {
      L->front = L->front->next; 
      L->front->prev = NULL; 
   }
   else {
      L->front = NULL;
      L->back = NULL; 
   }

   freeNode(&N); 
   L->length--;
}

void deleteBack(List L) {
   if (L == NULL) {
        fprintf(stderr, "List Error: calling deleteBack() on NULL List reference\n");
        exit(EXIT_FAILURE);
    }
    if (L->length <= 0) {
        fprintf(stderr, "List Error: calling deleteBack() on an empty List\n");
        exit(EXIT_FAILURE);
    }
   Node N = L->back;
   if (L->cursor == L->back) {
      L->cursor = NULL;  // Set cursor to NULL
      L->index = -1;     // Invalidate the index
      
   } 
   if (L->length > 1) {
      L->back = L->back->prev; 
      L->back->next = NULL; 
   }
   else {
      L->front = NULL;
      L->back = NULL; 
   }

   freeNode(&N); 
   L->length--;
}


void delete(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling delete() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   if (L->length <= 0) {
      fprintf(stderr, "List Error: calling delete() on an empty List\n");
      exit(EXIT_FAILURE);
   }
   if (L->index < 0){
      fprintf(stderr, "List Error: calling delete() on an undefined cursor\n");
      exit(EXIT_FAILURE);
   }
   if (L->cursor == L->front) {
      deleteFront(L); 
   }
   else if (L->cursor == L->back) {
      deleteBack(L);
   }
   else {
      L->cursor->prev->next = L->cursor->next;
      L->cursor->next->prev = L->cursor->prev;    
      freeNode(&L->cursor); 
      L->length--;
      L->index = -1; 
   }
} 


void printList(FILE* out, List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling printList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   Node N = L->front;
    while (N != NULL) {
        fprintf(out, "%d ", N->data);
        N = N->next;
    }
    fprintf(out, "\n");

} 

List copyList(List L) {
   if (L == NULL) {
      fprintf(stderr, "List Error: calling copyList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   List copy = newList(); 
   Node N = L->front; 
   while (N != NULL) {
      append(copy, N->data); 
      N = N->next;  
   }
   return copy; 
}

List concatList(List A, List B) {
   if (A == NULL || B == NULL) {
      fprintf(stderr, "List Error: calling concatList() on NULL List reference\n");
      exit(EXIT_FAILURE);
   }
   List concat = newList(); 
   Node N = A->front; 
   Node M = B->front;
   while (N != NULL) {
      append(concat, N->data); 
      N = N->next; 
   }
   while (M != NULL) {
      append(concat, M->data); 
      M = M->next; 
   }
   return concat;
}


