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
* With Step 2, we have added the ability to start interacting
* with the story. The story is started by printing out the
* contents of the first page. The user is then prompted to
* enter a choice number until the page reaches WIN or LOSE. 
*
* The story is read in from a file in the folder called "story.txt".
*/
int main(int argc, char ** argv) {
    // check the format of the command line
    if (argc != 2) {
        raiseError("Command format for cyoa-step2 is: ./cyoa-step2 [FOLDER]!");
    }

    std::ifstream file(argv[1]+START_FILENAME);
    if (!file.is_open()) {
        raiseError("Error opening file!");
    }

    Story story(argv[1], file);
    // verify the story
    // 1. check if all referenced pages exist
    // 2. check if all pages are referenced at least once
    // 3. check if there is at least one win page and one lose page
    story.verifyStory();
    story.start();
    return EXIT_SUCCESS;
}