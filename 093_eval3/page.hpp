#ifndef __PAGE_H__
#define __PAGE_H__

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#include "choice.hpp"

/*
* This enum represents a page type in the story.
*/
enum PAGE_TYPE_T {
    NORMAL = 0,
    WIN = 1,
    LOSE = 2,
    UNDEFINED = 3
};

/*
* This class represents a page in the story.
* Each page has a page number, page type, contents, and choices.
* The page number is the unique identifier of the page.
* The page type is either NORMAL, WIN, or LOSE.
* The contents is a vector of strings that represent the text of the page.
* The choices is a vector of Choice objects that represent the choices of the page.
*/
class Page {
private:
    size_t pageNum;
    size_t pageType;
    std::vector<Choice> choices;
    std::vector<std::string> contents;
    std::map<std::string, long int> pageVariables;
public:
    Page(size_t pageNum, size_t pageType);
    Page(const Page & rhs);
    ~Page();
    Page & operator=(const Page & rhs);
    size_t getPageNum();
    size_t getPageType();
    std::string getContents();
    size_t getChoiceCount();
    std::vector<Choice> & getChoices();
    std::map<std::string, long int> & getPageVariables();
    bool isPageVariableEmpty();
    std::vector<Page>::iterator findChoice(int choiceNum);
    void addChoice(Choice choice);
    void addContent(std::string line);
    void addVariable(std::string var, long int val);
    void activateAllChoices();
    void deactivateAllChoices();
    void printPage();
};

#endif