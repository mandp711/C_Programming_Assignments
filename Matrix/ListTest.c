/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
ListTest.c
Test file for testing function of List.c 
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "List.h"

int main() {
    List L = newList(); 

    // Test append() and length()
    append(L, 10);
    prepend(L, 20);
    prepend(L, 30);
    printf("Length: %d\n", length(L)); // prints 3

    moveFront(L); 
    printf("Front element: %d\n", get(L)); // print 30

    moveBack(L); 
    printf("Back element: %d\n", get(L)); // print 10

    // Testing moveNext(List L) and movePrev(List L)
    moveFront(L); 
    moveNext(L); 
    printf("Next element after front: %d\n", get(L)); // print 20
    movePrev(L); 
    printf("Previous element: %d\n", get(L)); // print 30

    // Testing insertBefore and insert After
    moveNext(L); 
    insertBefore(L, 25); 
    insertAfter(L, 15);

    // updated List 
    printf("Updated List: "); 
    printList(stdout, L); // should print 30 25 20 15 10 
    
    // Testing set 
    set(L, 17); 

    // updated List 
    printf("Updated List with cursor changed: "); 
    printList(stdout, L); // should print 30 25 17 15 10 

    // Testing deleteFront and deleteBack
    deleteFront(L); 
    deleteBack(L); 

    // updated List 
    printf("Updated List with Front and Back deleted: ");
    printList(stdout, L); // should print 25 17 15
    

    // Testing delete
    delete(L); 
    printf("Updated List of cursor element deleted: "); 
    printList(stdout, L); // should print 25 15
    
    // Testing concatList
    List M = newList(); 
    append(M, 70); 
    append(M, 80); 
    append(M, 90); 
    List concat = concatList(L, M); 
    printf("Concatinated List: "); 
    printList(stdout, concat);  // should print 25 15 70 80 90
    
    // Testing clear 
    
    clear(L); 
    printf("Cleared List: "); 
    printList(stdout, L);  // should print empty list

    freeList(&L);
    freeList(&M); 
    freeList(&concat);

    return 0; 
}