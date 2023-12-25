#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "rand_story.h"

int main(int argc, char ** argv) {
    if (argc < 3 || argc > 4) {
        raiseError("[ERROR] wrong argument number");
    }
    if (argc == 4 && strcmp(argv[1], "-n") != 0) {
        raiseError("[ERROR] the optional argument \"-n\" should be input");
    }

    // STEP1: create file stream for input filename
    FILE * word_file_stream_step4 = createFileStream(argv[argc-3+1]);
    FILE * story_file_stream_step4 = createFileStream(argv[argc-3+2]);

    // STEP2: create a file input struct by reading line by line
    file_input * step4_wordsfile = readInput(word_file_stream_step4);
    file_input * step4_storyfile = readInput(story_file_stream_step4);

    // STEP3: process the input struct according to the requirement
    int mode;
    
    if (argc == 4 && strcmp(argv[1], "-n") == 0) {
        mode = REPLACE_RANDOM_WITHOUT_REUSE;
    } else {
        mode = REPLACE_RANDOM;
    }
    processInput_step3And4(step4_wordsfile, step4_storyfile, mode);
    
    // STEP4: free the file input struct
    freeFileInput(step4_wordsfile);
    freeFileInput(step4_storyfile);

    // STEP5: close the file
    closeFileStream(word_file_stream_step4);
    closeFileStream(story_file_stream_step4);

    return EXIT_SUCCESS;
}