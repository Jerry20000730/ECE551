#include <iostream>
#include <cstdlib>
#include <vector>

#include "choice.hpp"

/*
* function: Choice (first constructor)
* ------------------------------------------------------------------
* @brief Constructs a Choice object with the source page number,
* destination page number, and text.
*
* @param pageSrcNum The source page number.
* @param pageDstNum The destination page number.
* @param text The text of the choice.
*/
Choice::Choice(size_t pageSrcNum, size_t pageDstNum, std::string text) : pageSrcNum(pageSrcNum), pageDstNum(pageDstNum), text(text), isActivated(true) {}

/*
* function: Choice (second constructor)
* ------------------------------------------------------------------
* @brief Constructs a Choice object with the source page number,
* destination page number, text, and variable requirement.
*
* @param pageSrcNum The source page number.
* @param pageDstNum The destination page number.
* @param text The text of the choice.
* @param varValPair The variable requirement of the choice.
*/
Choice::Choice(size_t pageSrcNum, size_t pageDstNum, std::string text, std::pair<std::string, long int> varValPair) : pageSrcNum(pageSrcNum), pageDstNum(pageDstNum), text(text), isActivated(true) {
    choiceVariableRequirement[varValPair.first] = varValPair.second;
}

/*
* function: Choice (copy constructor)
* ------------------------------------------------------------------
* @brief Constructs a Choice object with the source page number,
* destination page number, text, and variable requirement.
*
* @param rhs The Choice object to be copied.
*/
Choice::Choice(const Choice & rhs) : pageSrcNum(rhs.pageSrcNum), pageDstNum(rhs.pageDstNum), text(rhs.text), choiceVariableRequirement(rhs.choiceVariableRequirement), isActivated(rhs.isActivated) {}
Choice & Choice::operator=(const Choice & rhs) {
    if (this != &rhs) {
        pageSrcNum = rhs.pageSrcNum;
        pageDstNum = rhs.pageDstNum;
        text = rhs.text;
        choiceVariableRequirement = rhs.choiceVariableRequirement;
        isActivated = rhs.isActivated;
    }
    return (*this);
}

/*
* function: getPageSrcNum
* ------------------------------------------------------------------
* @brief get method for the source page number.
*
* @return The source page number.
*/
size_t Choice::getPageSrcNum() {
    return pageSrcNum;
}

/* 
* function: getPageDstNum
* ------------------------------------------------------------------
* @brief get method for the destination page number.
*
* @return The destination page number.
*/
size_t Choice::getPageDstNum() {
    return pageDstNum;
}

/*
* function: getText
* ------------------------------------------------------------------
* @brief get method for the text of the choice.
*
* @return The text of the choice.
*/
std::string Choice::getText() {
    return text;
}

/*
* function: getChoiceVariableRequirement
* ------------------------------------------------------------------
* @brief get method for the variable requirement of the choice.
*
*/
std::map<std::string, long int> & Choice::getChoiceVariableRequirement() {
    return choiceVariableRequirement;
}

/*
* function: isChoiceReqEmpty
* ------------------------------------------------------------------
* @brief Checks if the variable requirement of the choice is empty.
*
* @return True if the variable requirement of the choice is empty, false otherwise.
*/
bool Choice::isChoiceReqEmpty() {
    return choiceVariableRequirement.empty();
}

/*
* function: isActivate
* ------------------------------------------------------------------
* @brief Checks if the choice is activated.
*
* @return True if the choice is activated, false otherwise.
*/
bool Choice::isActivate() {
    return isActivated;
}

/*
* function: activate
* ------------------------------------------------------------------
* @brief Activates the choice.
*/
void Choice::activate() {
    isActivated = true;
}

/*
* function: deactivate
* ------------------------------------------------------------------
* @brief Deactivates the choice.
*/
void Choice::deactivate() {
    isActivated = false;
}

/*
* function: printChoice
* ------------------------------------------------------------------
* @brief Prints the choice.
*/
void Choice::printChoice() {
    if (isActivated) {
        std::cout << text << std::endl;
    } else {
        std::cout << "<UNAVAILABLE>" << std::endl;
    }
}