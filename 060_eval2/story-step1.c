#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "rand_story.h"


int main(int argc, char ** argv) {
    if (argc != 2) {
        raiseError("[ERROR] wrong argument number");
    }

    // STEP1: create file stream for input filename
    FILE * file_stream_step1 = createFileStream(argv[1]);

    // STEP2: create a file input struct by reading line by line
    file_input * file_input_step1 = readInput(file_stream_step1);
    
    // STEP3: process the input struct according to the requirement
    processInput_step1(file_input_step1);
    
    // STEP4: free the file input struct
    freeFileInput(file_input_step1);
    
    // STEP5: close the file
    closeFileStream(file_stream_step1);

    return EXIT_SUCCESS;
}
