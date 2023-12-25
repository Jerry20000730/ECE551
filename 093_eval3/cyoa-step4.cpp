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
* Each Choice object contains a vector of strings that 
* represent the text of the choice.
* 
* With Step 4, we have added the ability to have variable requirements
* for choices. The variable requirements is a map of variable names to
* variable values that represent the requirements of the choice.
* The choice is activated if the variable requirements are empty or
* the global variable is the same as the requirement.
*
* The story is read in from a file in the folder called "story.txt".
*/
int main(int argc, char ** argv) {
    // check the format of the command line
    if (argc != 2) {
        raiseError("Command format for cyoa-step3 is: ./cyoa-step4 [FOLDER]!");
    }

    std::ifstream file(argv[1]+START_FILENAME);
    if (!file.is_open()) {
        raiseError("Error opening file!");
    }

    // create a story object
    Story story(argv[1], file);
    // verify the story
    story.verifyStory();
    // start the interactive story
    story.start();
    return EXIT_SUCCESS;
}