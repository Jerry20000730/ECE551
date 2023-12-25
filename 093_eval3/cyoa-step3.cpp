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

* With Step 3, we have added the ability to find the path to the
* win page. The path is found using a depth-first search (DFS).
* The DFS is implemented using a stack.
* The path is printed out in the format:
* [PAGE_NUM] [CHOICE_NUM], [page_num] [choice_num], ...
*
* The story is read in from a file in the folder called "story.txt".
*/
int main(int argc, char ** argv) {
    // check the format of the command line
    if (argc != 2) {
        raiseError("Command format for cyoa-step3 is: ./cyoa-step3 [FOLDER]!");
    }

    std::ifstream file(argv[1]+START_FILENAME);
    if (!file.is_open()) {
        raiseError("Error opening file!");
    }

    Story story(argv[1], file);
    story.verifyStory();
    // traverse the story using DFS
    // after which print the path
    story.traverse();
    return EXIT_SUCCESS;
}