#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "page.hpp"

/*
* Function: Page (constructor)
* ------------------------------------------------------------------
* @brief Constructs a Page object with the page number and page type.
*
* @param pageNum The page number.
* @param pageType The page type.
*/
Page::Page(size_t pageNum, size_t pageType) : pageNum(pageNum), pageType(pageType) {}

/*
* Function: Page (copy constructor)
* ------------------------------------------------------------------
* @brief Constructs a Page object with the page number, page type, choices, contents, and page variables.
*
* @param rhs The Page object to be copied.
*/
Page::Page(const Page & rhs) : pageNum(rhs.pageNum), pageType(rhs.pageType), choices(rhs.choices), contents(rhs.contents), pageVariables(rhs.pageVariables) {}

/*
* Function: operator=
* ------------------------------------------------------------------
* @brief Assigns the Page object on the right hand side to the Page object on the left hand side.
*
* @param rhs The Page object on the right hand side.
* @return The Page object on the left hand side.
*/
Page & Page::operator=(const Page & rhs) {
    if (this != &rhs) {
        pageNum = rhs.pageNum;
        pageType = rhs.pageType;
        choices = rhs.choices;
        contents = rhs.contents;
        pageVariables = rhs.pageVariables;
    }
    return (*this);
}

/*
* Function: ~Page (destructor)
* ------------------------------------------------------------------
* @brief Destructs the Page object.
*/
Page::~Page() {}

/*
* Function: getPageNum
* ------------------------------------------------------------------
* @brief get method for the page number.
*
* @return The page number.
*/
size_t Page::getPageNum() {
    return pageNum;
}

/*
* Function: getPageType
* ------------------------------------------------------------------
* @brief get method for the page type.
*
* @return The page type.
*/
size_t Page::getPageType() {
    return pageType;
}

/*
* Function: getContents
* ------------------------------------------------------------------
* @brief get method for the contents of the page.
*
* @return The contents of the page.
*/
std::string Page::getContents() {
    std::string text;
    for (size_t i=0; i<contents.size(); i++) {
        text += contents[i];
        text += "\n";
    }
    return text;
}

/*
* Function: getChoiceCount
* ------------------------------------------------------------------
* @brief get method for the number of choices of the page.
*
* @return The number of choices of the page.
*/
size_t Page::getChoiceCount() {
    return choices.size();
}

/*
* Function: getChoices
* ------------------------------------------------------------------
* @brief get method for the choices of the page.
*
* @return The choices of the page.
*/
std::vector<Choice> & Page::getChoices() {
    return choices;
}

/*
* Function: getPageVariables
* ------------------------------------------------------------------
* @brief get method for the page variables of the page.
*
* @return The page variables of the page.
*/
std::map<std::string, long int> & Page::getPageVariables() {
    return pageVariables;
}

/*
* Function: isPageVariableEmpty
* ------------------------------------------------------------------
* @brief Checks if the page variables of the page is empty.
*
* @return True if the page variables of the page is empty, false otherwise.
*/
bool Page::isPageVariableEmpty() {
    return pageVariables.empty();
}

/*
* Function: addChoice
* ------------------------------------------------------------------
* @brief Adds a choice to the page.
*
* @param choice The choice instance to be added.
*/
void Page::addChoice(Choice choice) {
    choices.push_back(choice);
}

/*
* Function: addContent
* ------------------------------------------------------------------
* @brief Adds a line of text to the contents of the page.
*
* @param line The line of text to be added.
*/
void Page::addContent(std::string line) {
    contents.push_back(line);
}

/*
* Function: addVariable
* ------------------------------------------------------------------
* @brief adds a page variable to the page.
*
* @param var The variable name.
* @param val The variable value.
*/
void Page::addVariable(std::string var, long int val) {
    pageVariables[var] = val;
}

/*
* Function: activateAllChoices
* ------------------------------------------------------------------
* @brief Activates all the choices of the page.
*/
void Page::activateAllChoices() {
    for (size_t j=0; j<getChoiceCount(); j++) {
        choices[j].activate();
    }
}

/*
* Function: deactivateAllChoices
* ------------------------------------------------------------------
* @brief Deactivates all the choices of the page.
*/
void Page::deactivateAllChoices() {
    for (size_t j=0; j<getChoiceCount(); j++) {
        choices[j].deactivate();
    }
}

/*
* Function: printPage
* ------------------------------------------------------------------
* @brief Prints the page.
*/
void Page::printPage() {
    for (size_t i=0; i<contents.size(); i++) {
        std::cout << contents[i] << std::endl;
    }
    if (pageType == NORMAL) {
        std::cout << "What would you like to do?" << std :: endl;
        std::cout << std::endl;

        for (size_t j=0; j<getChoiceCount(); j++) {
            std::cout << " " << j+1 << ". "; 
            choices[j].printChoice();
        }
    } else if (pageType == WIN) {
        std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    } else if (pageType == LOSE) {
        std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
}