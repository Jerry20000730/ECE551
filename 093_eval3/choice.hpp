#ifndef __CHOICE_H__
#define __CHOICE_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <map>

/*
* This class represents a choice in the story.
* Each choice has a source page number, destination page number, text, and variable requirements.
* The source page number is the page number of the page that the choice is on.
* The destination page number is the page number of the page that the choice leads to.
* The text is the text of the choice.
* The variable requirements is a map of variable names to variable values that 
* represent the requirements of the choice.
* The choice is activated if the variable requirements are empty or
* the global variable is the same as the requirement.
*/
class Choice {
private:
    size_t pageSrcNum;
    size_t pageDstNum;
    std::string text;
    std::map<std::string, long int> choiceVariableRequirement;
    bool isActivated;
public:
    Choice(size_t pageSrcNum, size_t pageDstNum, std::string text);
    Choice(size_t pageSrcNum, size_t pageDstNum, std::string text, std::pair<std::string, long int> varValPair);
    Choice(const Choice & rhs);
    Choice & operator=(const Choice & rhs);
    size_t getPageSrcNum();
    size_t getPageDstNum();
    std::string getText();
    std::map<std::string, long int> & getChoiceVariableRequirement();
    bool isChoiceReqEmpty();
    bool isActivate();
    void activate();
    void deactivate();
    void printChoice();
};

#endif