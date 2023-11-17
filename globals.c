#include "globals.h"

PointersToFree globals_pointers_list = {.numPointers = 0};

char* currentInputPointer;  //We will free this pointer if the program is interrupted by a SIGNAL

// Add the pointer to the list for later memory deallocation
void addPointerToList(void* pointer, PointersToFree* pointers_list2) {

    int numPointers = (*pointers_list2).numPointers;
    
    if ((*pointers_list2).numPointers == 0) {
        (*pointers_list2).pointers = malloc(sizeof(void**));
    } else {
        (*pointers_list2).pointers = realloc((*pointers_list2).pointers, sizeof(void**) * (numPointers + 1));
    }

    (*pointers_list2).pointers[numPointers] = pointer;
    (*pointers_list2).numPointers += 1;

}

//Returns the current input pointer, in order to be freed if the program is interrupted by a SIGNAL
char* getGlobalsCurrentInputPointer() {
    return currentInputPointer;
}

// Read characters until reaching either endChar or endChar2. If endChar2 is found, set endChar2Found to 1.
char* readUntilEitherChar(int fd, char endChar, char endChar2, int* endChar2Found) {
    int size;
    int i = 0;
    char c = '\0';

    char* string = malloc(sizeof(char));

    while (1) {
        size = read(fd, &c, sizeof(char));
        
        if (size > 0 && c != endChar && c != endChar2) {
            string = realloc(string, sizeof(char) * (i + 2));
            string[i++] = c;

        } else {

            if (c == endChar2) {
                *endChar2Found = 1;
            }
            break;
        }
    }

    string[i] = '\0';

    return string;
}

//Read until reach the char endChar and return the string.
char* readUntilChar(int fd, char endChar) {
    int size;
    int i = 0;
    char c = '\0';

    char* string = malloc(sizeof(char));

    currentInputPointer = string;
    while (1) {
        size = read(fd, &c, sizeof(char));
        
        if (size > 0 && c != endChar) {
            string = realloc(string, sizeof(char) * (i + 2));
            string[i++] = c;

            currentInputPointer = string;
        } else {
            break;
        }
    }
    string[i] = '\0';

    currentInputPointer = NULL; //If we can return the string because no SIGNALs have interrupted the program, we set the pointer to NULL so it is not freed (we will free the string)
    return string;
}

// Read characters until reaching the char endChar, ignoring any exception letters, and return the string.
char* readUntilCharExceptLetter(int fd, char endChar, char exception) {
    int size;
    int i = 0;
    char c = '\0';

    char* string = malloc(sizeof(char));

    currentInputPointer = string;
    while (1) {
        size = read(fd, &c, sizeof(char));
        
        if (size > 0 && c != endChar) {
            if (exception != c){
                string = realloc(string, sizeof(char) * (i + 2));
                string[i++] = c;

                currentInputPointer = string;
            }
        } else {
            break;
        }
    }
    string[i] = '\0';

    currentInputPointer = NULL; //If we can return the string because no SIGNALs have interrupted the program, we set the pointer to NULL so it is not freed (we will free the string)
    return string;
}

//Prints dynamic string, where we cannot use strlen
void printDynStr(char* buffer, int bufferSize) {
     write(1, buffer, bufferSize);
}