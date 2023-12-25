#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "rand_story.h"


int main(int argc, char ** argv) {
    if (argc != 2) {
        raiseError("[ERROR] wrong argument number");
    }
    
    // STEP1: create file stream for input filename
    FILE * file_stream_step2 = createFileStream(argv[1]);

    // STEP2: create a file input struct by reading line by line
    file_input * step2_wordsfile = readInput(file_stream_step2);

    // STEP3: process the input struct according to the requirement
    processInput_step2(step2_wordsfile);

    // STEP4: free the file input struct
    freeFileInput(step2_wordsfile);

    // STEP5: close the file stream
    closeFileStream(file_stream_step2);

    return EXIT_SUCCESS;
}