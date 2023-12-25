#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "rand_story.h"


int main(int argc, char ** argv) {
    if (argc != 3) {
        raiseError("[ERROR] wrong argument number");
    }

    // STEP1: create file stream for both input filename
    FILE * word_file_stream_step3 = createFileStream(argv[1]);
    FILE * story_file_stream_step3 = createFileStream(argv[2]);

    // STEP2: create file input struct for both input file
    file_input * step3_wordsfile = readInput(word_file_stream_step3);
    file_input * step3_storyfile = readInput(story_file_stream_step3);
    
    // STEP3: process the input file struct for both input file
    // according to the requirement
    processInput_step3And4(step3_wordsfile, step3_storyfile, REPLACE_RANDOM);
    
    // STEP4: free the file input struct
    freeFileInput(step3_wordsfile);
    freeFileInput(step3_storyfile);

    // STEP5: close the file stream
    closeFileStream(word_file_stream_step3);
    closeFileStream(story_file_stream_step3);

    return EXIT_SUCCESS;
}