#include <iostream>
#include <fstream>

#include "story.hpp"
#include "page.hpp"
#include "util.hpp"

/*
* This program takes in a folder name as a command line argument
* and reads in the story from the folder and prints it out.
* 
* The story is stored in a vector of Page objects.
* Each Page object contains a vector of Choice objects.
* Each Choice object contains a vector of strings that represent the text of the choice.
*
* With Step 1, we have added the ability to read in the story from a file, print
* out the contents of the story, and print out the contents of each page.
* 
* The story is read in from a file in the folder called "story.txt".
*/
int main(int argc, char ** argv) {
    // check the format of the command line
    if (argc != 2) {
        raiseError("Command format for cyoa-step1 is: ./cyoa-step1 [FOLDER]!");
    }

    std::ifstream file(argv[1]+START_FILENAME);
    // if file does not exists, raise error
    if (!file.is_open()) {
        raiseError("Error opening file!");
    }
    // create a story object
    Story story(argv[1], file);
    // simply print the story
    story.printStory();
    return EXIT_SUCCESS;
}