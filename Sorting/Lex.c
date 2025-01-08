/*
Mandar Patil
mpatil2
Fall 24 - CSE 101
Lex.c 
Main program that sorts input file lines lexographically 
*/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

#include "List.h"

#define MAX_LEN 300

int main(int argc, char * argv[]){
    FILE *in, *out;

    // check command line for correct number of arguments
    if( argc != 3 ){
        printf("Usage: %s <input file> <output file>\n", argv[0]);
        exit(1);
    }

   // open files for reading and writing 
    in = fopen(argv[1], "r");
        if( in==NULL ){
        printf("Unable to open file %s for reading\n", argv[1]);
        exit(1);
    }
    
    out = fopen(argv[2], "w");
    if( out==NULL ){
        printf("Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    char line[MAX_LEN]; 
    int n = 0; 
    while (fgets(line, MAX_LEN, in) != NULL) {
        n++; 
    }

    rewind(in); // go to the beginning of the file 
    char** stringArray = calloc(n, sizeof(char*)); 
    for (int i = 0; i < n; i++) {
        fgets (line, MAX_LEN, in ); 
        stringArray[i] = calloc(strlen(line) + 1, sizeof(char)); 
        strcpy(stringArray[i], line); 
    }
    fclose(in); 

    // create a list to store indices of the strings 
    List indices = newList(); 
    append(indices, 0); 
    for (int i = 1; i < n; i++) {
        moveFront(indices);
        while (index(indices) >= 0 && strcmp(stringArray[get(indices)], 
        stringArray[i]) <= 0) { // if the elements are in alphabetical order
            moveNext(indices); 
        }
        if (index(indices) == -1) {
            append(indices, i); 
        } else {
            insertBefore(indices, i); 
        }
    }
    out = fopen(argv[2], "w");
    if (out == NULL) {
        fprintf(stderr, "Unable to open file %s for writing\n", argv[2]);
        exit(1);
    }

    moveFront(indices);
    while (index(indices) >= 0) {
        fprintf(out, "%s", stringArray[get(indices)]);
        moveNext(indices);
    }

    // Free memory and close output file
    for (int i = 0; i < n; i++) {
        free(stringArray[i]);
    }
    free(stringArray);
    freeList(&indices);
    fclose(out);
    return 0; 
}