#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <ctype.h>
#include <unistd.h>

#include "story.hpp"
#include "util.hpp"

/*
* Function: Story (constructor)
* ------------------------------------------------------------------
* @brief Constructs a Story object with the given path and file.
*
* @param path The path of the story file.
* @param file The input file stream containing the story data.
*
*/
Story::Story(std::string path, std::ifstream & file) : path(path), isInputOver(false) {
    parseStory(file);
    establishTransitionGraph();
}

/*
 * Function: Story (constructor)
 * ------------------------------------------------------------------
 * @brief Copy constructor for the Story class.
 * 
 * @param rhs The Story object to be copied.
 */
Story::Story(const Story & rhs) : path(rhs.path), pages(rhs.pages), transitionGraph(rhs.transitionGraph), globalStoryVariables(rhs.globalStoryVariables), isInputOver(rhs.isInputOver) {}

/*
 * Function: ~Story (destructor)
 * ------------------------------------------------------------------
 * @brief Destructor for the Story class.
 */
Story::~Story() {}

/*
 * Function: operator=
 * ------------------------------------------------------------------
 * @brief Assignment operator for the Story class.
 * 
 * @param rhs The Story object to be assigned.
 * @return The Story object after assignment.
 */
Story & Story::operator=(const Story & rhs) {
    if (this != &rhs) {
        path = rhs.path;
        pages = rhs.pages;
        transitionGraph = rhs.transitionGraph;
        globalStoryVariables = rhs.globalStoryVariables;
        isInputOver = rhs.isInputOver;
    }
    return (*this);
}

/*
 * Function: parseStory
 * ------------------------------------------------------------------
 * @brief Parses the story file and creates the pages.
 * 
 * @param file The input file stream containing the story data.
 */
void Story::parseStory(std::ifstream & file) {
    std::string line;
    while (file) {
        std::getline(file, line);
        if (line.size() != 0) {
            processLine(line);
        }        
    }
}

/*
 * Function: parsePageContent
 * ------------------------------------------------------------------
 * @brief Parses the content of a page.
 * 
 * @param page The page to be parsed.
 * @param file The input file stream containing the story data.
 */
void Story::parsePageContent(Page & page, std::ifstream & file) {
    if (!file.is_open()) {
        raiseError("Error opening file!");
    }

    std::string line;
    while (file) {
        std::getline(file, line);
        page.addContent(line);
    }
}

/*
 * Function: processLine
 * ------------------------------------------------------------------
 * @brief Processes a line of the story file.
 * 
 * @param line The line to be processed.
 */
void Story::processLine(std::string line) {
    bool format1, format2, format3, format4, format5;
    format1 = processPageDeclaration(line);
    if (format1) {
        if (pages.size() == 1 && pages[0].getPageNum() != 0) {
            raiseError("The first page must be page 0.");
        } else if (pages.size() > 1 && pages[pages.size()-1].getPageNum() != pages[pages.size()-2].getPageNum()+1) {
            raiseError("The page number is not in series.");
        }
        return;
    }
    format2 = processChoice(line);
    if (format2) {
        return;
    }
    format3 = processVariableDeclaration(line);
    if (format3) {
        return;
    }
    format4 = processChoiceWithVariableRequirement(line);
    if (format4) {
        return;
    }
    format5 = checkBlankLine(line);
    if (format5) {
        return;
    }
    std::string errmsg = "[ERROR] Wrong format appears in this line: " + line;
    raiseError(errmsg.c_str());
}

/*
* Function: processPageDeclaration
* ------------------------------------------------------------------
* @brief Processes a page declaration line.
* 
* @param line The line to be processed.
* @return True if the line is a page declaration line, false otherwise. 
*/
bool Story::processPageDeclaration(std::string line) {
    std::size_t at_pos = line.find(AT_CHAR);
    if (at_pos == std::string::npos) {
        return false;
    }
    std::size_t colon_pos = line.find(COLON_CHAR);
    if (colon_pos == std::string::npos) {
        return false;
    }
    if (checkUnsignedNumberConversion(line.substr(0, at_pos)) == false) {
        return false;
    }
    size_t pageNum = performUnsignedNumberConversion(line.substr(0, at_pos));
    if (errno == ERANGE) {
        return false;
    }
    if (!checkOrder(pageNum)) {
        raiseError("Page number is not in order.");
    }
    size_t pageType = processType(line.substr(at_pos+1, (colon_pos-at_pos-1)));
    if (pageType == UNDEFINED) {
        raiseError("Page type is undefined.");
    }
    if (line.substr(colon_pos+1).size() == 0) {
        raiseError("Page file name is empty.");
    }
    std::string storyFileName = path + "/" + line.substr(colon_pos+1);
    std::ifstream storyFile(storyFileName.c_str());
    if (!storyFile.is_open()) {
        raiseError("Error opening file!");
    }
    Page newPage = createPage(pageNum, pageType);
    parsePageContent(newPage, storyFile);
    addPage(newPage);
    return true;
}

/*
* Function: processChoice
* ------------------------------------------------------------------
* @brief Processes a choice line.
*
* @param line The line to be processed.
* @return True if the line is a choice line, false otherwise.
*/
bool Story::processChoice(std::string line) {
    std::size_t colon_pos1 = line.find(COLON_CHAR);
    if (colon_pos1 == std::string::npos) {
        return false;
    }
    if (checkUnsignedNumberConversion(line.substr(0, colon_pos1)) == false) {
        return false;
    }
    size_t pageSrcNum = performUnsignedNumberConversion(line.substr(0, colon_pos1));
    std::string next_str = line.substr(colon_pos1+1);
    std::size_t colon_pos2 = next_str.find(COLON_CHAR);
    if (colon_pos2 == std::string::npos) {
        return false;
    }
    if (checkUnsignedNumberConversion(next_str.substr(0, colon_pos2)) == false) {
        return false;
    }
    size_t pageDstNum = performUnsignedNumberConversion(next_str.substr(0, colon_pos2));
    std::string text = next_str.substr(colon_pos2+1);
    std::vector<Page>::iterator it = findPage(pageSrcNum);
    if (it == pages.end()) {
        raiseError("Page has not been created.");
    } else if (it->getPageType() == WIN || it->getPageType() == LOSE) {
        raiseError("Page type WIN or LOSE cannot have choices.");
    }
    Choice newChoice = createChoice(pageSrcNum, pageDstNum, text);
    it->addChoice(newChoice);
    return true;
}

/*
* Function: processVariableDeclaration
* ------------------------------------------------------------------
* @brief Processes a variable declaration line.
*
* @param line The line to be processed.
* @return True if the line is a variable declaration line, false otherwise.
*/
bool Story::processVariableDeclaration(std::string line) {
    std::size_t dollar_pos1 = line.find(DOLLAR_CHAR);
    if (dollar_pos1 == std::string::npos) {
        return false;
    }
    if (checkUnsignedNumberConversion(line.substr(0, dollar_pos1)) == false) {
        return false;
    }
    size_t pageNum = performUnsignedNumberConversion(line.substr(0, dollar_pos1));
    std::size_t equal_pos1 = line.find(EQUAL_CHAR);
    if (equal_pos1 == std::string::npos) {
        return false;
    }
    std::pair<std::string, long int> varValPair = seperateVarAndVal(line.substr(dollar_pos1+1));
    std::vector<Page>::iterator it = findPage(pageNum);
    if (it == pages.end()) {
        raiseError("Page has not been created.");
    }
    it->addVariable(varValPair.first, varValPair.second);
    return true;
}

/*
* Function: processChoiceWithVariableRequirement
* ------------------------------------------------------------------
* @brief Processes a choice with variable requirement line.
*
* @param line The line to be processed.
* @return True if the line is a choice with variable requirement line, false otherwise.
*/
bool Story::processChoiceWithVariableRequirement(std::string line) {
    std::size_t left_bracket = line.find(LEFT_BRACKET);
    if (left_bracket == std::string::npos) {
        return false;
    }
    if (checkLongIntConversion(line.substr(0, left_bracket)) == false) {
        return false;
    }
    size_t pageSrcNum = performLongIntConversion(line.substr(0, left_bracket));
    std::size_t right_bracket = line.rfind(RIGHT_BRACKET);
    if (right_bracket == std::string::npos) {
        return false;
    }
    if (checkVarAndVal(line.substr(left_bracket+1, right_bracket-left_bracket-1)) == false) {
        return false;
    }
    std::pair<std::string, long int> choiceReq = seperateVarAndVal(line.substr(left_bracket+1, right_bracket-left_bracket-1));
    std::string next_str = line.substr(right_bracket+1);
    std::size_t colon_pos1 = next_str.find(COLON_CHAR);
    if (colon_pos1 == std::string::npos) {
        return false;
    }
    if (next_str.substr(0, colon_pos1).size() != 0) {
        return false;
    }
    std::string next_next_str = next_str.substr(colon_pos1+1);
    std::size_t colon_pos2 = next_next_str.find(COLON_CHAR);
    if (colon_pos2 == std::string::npos) {
        return false;
    }
    if (checkUnsignedNumberConversion(next_next_str.substr(0, colon_pos2)) == false) {
        return false;
    }
    size_t pageDstNum = performUnsignedNumberConversion(next_next_str.substr(0, colon_pos2));
    std::string text = next_next_str.substr(colon_pos2+1);
    std::vector<Page>::iterator it = findPage(pageSrcNum);
    if (it == pages.end()) {
        raiseError("Page has not been created.");
    }
    Choice newChoice = createChoice(pageSrcNum, pageDstNum, text, choiceReq);
    it->addChoice(newChoice);
    return true;
}

/*
* Function: checkBlankLine
* ------------------------------------------------------------------
* @brief checks if a line is a blank line (or with blanks).
*
* @param line The line to be checked.
* @return True if the line is a blank line, false otherwise.
*/
bool Story::checkBlankLine(std::string line) {
    for (size_t i=0; i<line.size(); i++) {
        if (line[i] != ' ' || !isspace(line[i])) {
            return false;
        }
    }
    return true;
}

/*
* Function: processType
* ------------------------------------------------------------------
* @brief Processes the type of a page.
*
* @param t The type in string to be processed.
* @return The type of the page.
*/
size_t Story::processType(std::string t) {
    if (t == "N") {
        return NORMAL;
    } else if (t == "W") {
        return WIN;
    } else if (t == "L") {
        return LOSE;
    } else {
        return UNDEFINED;
    }
}

/*
* Function: checkVarAndVal
* ------------------------------------------------------------------
* @brief checks if a line is a variable declaration line.
* variable declaration line format: ${page number}[{variable name}={variable value}]
*
* @param line The line to be checked.
* @return True if the line is a variable declaration line, false otherwise.
*/
bool Story::checkVarAndVal(std::string line) {
    std::size_t equal_pos1 = line.find(EQUAL_CHAR);
    if (equal_pos1 == std::string::npos) {
        return false;
    }
    std::string var = line.substr(0, equal_pos1);
    if (checkLongIntConversion(line.substr(equal_pos1+1)) == false) {
        return false;
    }
    return true;
}

/*
* Function: checkOrder
* ------------------------------------------------------------------
* @brief checks if the page number is in order.
*
* @param pageNum The page number to be checked.
* @return True if the page number is in order, false otherwise.
*/
bool Story::checkOrder(size_t pageNum) {
    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i].getPageNum() > pageNum) {
            return false;
        }
    }
    return true;
}

/*
* Function: seperateVarAndVal
* ------------------------------------------------------------------
* @brief seperates the variable name and value.
*
* @param line The line to be processed.
* @return a pair of variable name and value.
*/
std::pair<std::string, long int> Story::seperateVarAndVal(std::string line) {
    std::size_t equal_pos1 = line.find(EQUAL_CHAR);
    std::string var = line.substr(0, equal_pos1);
    long int val = performLongIntConversion(line.substr(equal_pos1+1));
    std::pair<std::string, long int> res(var, val);
    return res;
}

/*
* Function: initGlobalVariable
* ------------------------------------------------------------------
* @brief initializes the global story variables.
*/
void Story::initGlobalVariable() {
    for (size_t i=0; i<pages.size(); i++) {
        if (!pages[i].isPageVariableEmpty()) {
            for (std::map<std::string, long int>::const_iterator it = pages[i].getPageVariables().begin(); 
            it != pages[i].getPageVariables().end(); ++it) {
                globalStoryVariables[it->first] = 0;
            }
        }
    }
}

/*
* Function: createPage
* ------------------------------------------------------------------
* @brief creates a page.
*
* @param pageNum The page number of the page to be created.
* @param pageType The page type of the page to be created.
* @return The page created.
*/
Page Story::createPage(size_t pageNum, size_t pageType) {
    return Page(pageNum, pageType);
}

/*
* Function: createChoice
* ------------------------------------------------------------------
* @brief creates a choice.
*
* @param pageSrcNum The page number of the source page.
* @param pageDstNum The page number of the destination page.
* @param text The text of the choice.
* @return The choice instance created.
*/
Choice Story::createChoice(size_t pageSrcNum, size_t pageDstNum, std::string text) {
    return Choice(pageSrcNum, pageDstNum, text);
}

/*
* Function: createChoice
* ------------------------------------------------------------------
* @brief creates a choice.
*
* @param pageSrcNum The page number of the source page.
* @param pageDstNum The page number of the destination page.
* @param text The text of the choice.
* @param varValPair The variable name and value pair of the choice.
* @return The choice instance created.
*/
Choice Story::createChoice(size_t pageSrcNum, size_t pageDstNum, std::string text, std::pair<std::string, long int> varValPair) {
    return Choice(pageSrcNum, pageDstNum, text, varValPair);
}

/*
* Function: addPage
* ------------------------------------------------------------------
* @brief adds a page to the story.
*
* @param p The page to be added.
*/
void Story::addPage(const Page & p) {
    pages.push_back(p);
}

/*
* Function: findPage
* ------------------------------------------------------------------
* @brief finds a page in the story.
*
* @param pageNum The page number of the page to be found.
* @return The iterator pointing to the page found.
*/
std::vector<Page>::iterator Story::findPage(size_t pageNum) {
    std::vector<Page>::iterator it = pages.begin();
    while (it != pages.end()) {
        if (it->getPageNum() == pageNum) {
            return it;
        }
        ++it;
    }
    return it;
}

/*
* Function: establishTransitionGraph
* ------------------------------------------------------------------
* @brief establishes the transition graph of the story.
*/
void Story::establishTransitionGraph() {
    for (size_t i=0; i<pages.size(); i++) {
        std::map<size_t, size_t> temp;
        for (size_t j=0; j<pages[i].getChoiceCount(); j++) {
            temp[j+1] = pages[i].getChoices()[j].getPageDstNum();
        }
        transitionGraph[pages[i].getPageNum()] = temp;
    }
}

/*
* Function: traverse
* ------------------------------------------------------------------
* @brief traverses the story using DFS.
*/
void Story::traverse() {
    std::map<size_t, bool> visited;
    for (size_t i=0; i<pages.size(); i++) {
        visited[pages[i].getPageNum()] = false;
    }
    std::vector<std::pair<size_t, size_t> > path;
    Page & cur_page = *findPage(0);
    bool isReachable = false;
    DFSHelper(cur_page, path, visited, isReachable);
    if (!isReachable) {
        std::cout << "This story is unwinnable!" << std::endl;
    }
}

/*
* Function: DFSHelper
* ------------------------------------------------------------------
* @brief helper function for DFS.
*
* @param cur The current page.
* @param path The path of the story.
* @param visited The map of visited pages.
* @param isReachable The flag indicating if the story is winnable.
*/
void Story::DFSHelper(Page & cur, std::vector<std::pair<size_t, size_t> > & path, std::map<size_t, bool> & visited, bool & isReacheable) {
    if (cur.getPageType() == WIN) {
        std::pair<size_t, size_t> win(cur.getPageNum(), 1000000);
        path.push_back(win);
        printPath(path);
        path.pop_back();
        isReacheable = true;
        return;
    } else if (transitionGraph[cur.getPageNum()].empty()) {
        return;
    }

    std::map<size_t, size_t> & adj = transitionGraph[cur.getPageNum()];
    std::map<size_t, size_t>::const_iterator it = adj.begin();
    visited[cur.getPageNum()] = true;
    while (it != adj.end()) {
        if (visited[it->second] == false) {
            std::pair<size_t, size_t> element(cur.getPageNum(), it->first);
            path.push_back(element);
            DFSHelper(*findPage(it->second), path, visited, isReacheable);
            path.pop_back();
        }
        it++;
    }
    visited[cur.getPageNum()] = false;
    return;
}

/*
* Function: verifyStory
* ------------------------------------------------------------------
* @brief verifies the story.
* 1. checks if the referenced page exists.
* 2. checks if all pages have been referenced at least once.
* 3. checks if there is at least one win page and one lose page.
*/
void Story::verifyStory() {
    if (!checkReferencedPageExists()) {
        raiseError("[ERROR] Wrong reference page in the choice");
    } else if (!checkPageReferencedAtLeastOnce()) {
        raiseError("[ERROR] Exist page that have not been referenced");
    } else if (!checkWinAndLosePage()) {
        raiseError("[ERROR] No Win or Lose page is found");
    }
}

/*
* Function: checkReferencedPageExists
* ------------------------------------------------------------------
* @brief checks if the referenced page exists.
*
* @return True if the referenced page exists, false otherwise.
*/
bool Story::checkReferencedPageExists() {
    for (size_t i=0; i<pages.size(); i++) {
        for (size_t j=0; j<pages[i].getChoiceCount(); j++) {
            if (findPage(pages[i].getChoices()[j].getPageDstNum()) == pages.end()) {
                return false;
            }
        }
    }
    return true;
}

/*
* Function: checkPageReferencedAtLeastOnce
* ------------------------------------------------------------------
* @brief checks if all pages have been referenced at least once.
*
* @return True if all pages have been referenced at least once, false otherwise.
*/
bool Story::checkPageReferencedAtLeastOnce() {
    std::map<size_t, int> freqMap;
    // initialize the freqMap
    for (size_t i=0; i<pages.size(); i++) {
        freqMap[pages[i].getPageNum()] = 0;
    }

    // record the time a page is being referenced
    for (size_t i=0; i<pages.size(); i++) {
        for (size_t j=0; j<pages[i].getChoiceCount(); j++) {
            freqMap[pages[i].getChoices()[j].getPageDstNum()]++;
        }
    }
    // check if all pages have been referenced at least once
    std::map<size_t, int>::iterator it = freqMap.begin();
    while (it != freqMap.end()) {
        if (it->first != 0 && it->second == 0) {
            return false;
        }
        it++;
    }
    return true;
}

/*
* Function: checkWinAndLosePage
* ------------------------------------------------------------------
* @brief checks if there is at least one win page and one lose page.
*
* @return True if there is at least one win page and one lose page, false otherwise.
*/
bool Story::checkWinAndLosePage() {
    int numWin = 0;
    int numLose = 0;
    for (size_t i=0; i<pages.size(); i++) {
        if (pages[i].getPageType() == WIN) {
            numWin++;
        } else if (pages[i].getPageType() == LOSE) {
            numLose++;
        }
    }
    if (numWin >= 1 && numLose >= 1) {
        return true;
    } else {
        return false;
    }
}

/*
* Function: isValidChoiceNumber
* ------------------------------------------------------------------
* @brief checks if the user input is a valid choice number.
*/
bool isValidChoiceNumber(const std::string & userInput) {
    if (userInput.size() == 0) {
        return false;
    }
    for (size_t i=0; i<userInput.size(); i++) {
        if (!(isdigit(userInput[i]) || (i == 0 && userInput[i] == '+'))) {
            return false;   
        }
    }
    return true;
}

/*
* Function: performUnsignedNumberConversion
* ------------------------------------------------------------------
* @brief Converts the string to an unsigned number.
*
* @param num The string to be converted.
* @return The unsigned number.
*/
size_t Story::getUserChoice(Page & cur_page) {
    std::string userInput;
    std::cin >> userInput;
    size_t choiceNum;
    bool isValid = false;
    bool isActivated = false;
    while (!isValid || !isActivated) {
        // check if the user entered a valid number
        if (checkUnsignedNumberConversion(userInput)) {
            choiceNum = performUnsignedNumberConversion(userInput);
            if (choiceNum >= 1 && choiceNum <= cur_page.getChoiceCount()) {
                if (cur_page.getChoices()[choiceNum-1].isActivate()) {
                    isValid = true;
                    isActivated = true;
                } else {
                    isValid = true;
                    isActivated = false;
                }
            }
        }
        if (!isValid) {
            std::cout << "That is not a valid choice, please try again" << std::endl;
            if (std::cin >> userInput) {
                continue;
            } else {
                isInputOver = true; 
                break;
            }
        } else if (!isActivated) {
            std::cout << "That choice is not available at this time, please try again" << std::endl;
            if (std::cin >> userInput) {
                continue;
            } else {
                isInputOver = true; 
                break;
            }
        }
    }
    
    return choiceNum;
}

/*
* Function: updateGlobalVariable
* ------------------------------------------------------------------
* @brief updates the global story variables.
*
* @param page The page to be updated.
*/
void Story::updateGlobalVariable(Page & page) {
    if (!page.isPageVariableEmpty()) {
        for (std::map<std::string, long int>::const_iterator it = page.getPageVariables().begin(); 
        it != page.getPageVariables().end(); ++it) {
            globalStoryVariables[it->first] = it->second;
        }
    }
}

/*
* Function: updateChoiceActivation
* ------------------------------------------------------------------
* @brief updates the choice activation.
*
* @param page The page to be updated.
*/
void Story::updateChoiceActivation(Page & page) {
    page.deactivateAllChoices();
    for (size_t i=0; i<page.getChoiceCount(); i++) {
        if (!page.getChoices()[i].isChoiceReqEmpty()) {
            for (std::map<std::string, long int>::const_iterator it = page.getChoices()[i].getChoiceVariableRequirement().begin(); 
            it != page.getChoices()[i].getChoiceVariableRequirement().end(); ++it) {
                if (globalStoryVariables[it->first] == it->second) {
                    page.getChoices()[i].activate();
                }
            }
        } else {
            page.getChoices()[i].activate();
        }
    }
}

/*
* Function: printStory
* ------------------------------------------------------------------
* @brief prints the story by pages and page declarations
*/
void Story::printStory() {
    initGlobalVariable();
    for (size_t i=0; i<pages.size(); i++) {
        updateGlobalVariable(pages[i]);
        updateChoiceActivation(pages[i]);
        std::cout << "Page " << pages[i].getPageNum() << std::endl;
        std::cout << "==========" << std::endl;
        pages[i].printPage();
    }
}

/*
* Function: printPath
* ------------------------------------------------------------------
* @brief prints the path of the story
*
* @param path The path to be printed.
*/
void Story::printPath(std::vector<std::pair<size_t, size_t> > & path) {
    std::stringstream pathStrStream;
    std::string pathStr;
    for (size_t i=0; i<path.size()-1; i++) {
        pathStrStream << path[i].first << "(" << path[i].second << "),";
        pathStr += pathStrStream.str();
        pathStrStream.str("");
    }
    pathStrStream << path[path.size()-1].first << "(win)";
    pathStr += pathStrStream.str();
    pathStrStream.str("");
    std::cout << pathStr << std::endl;
}

/*
* Function: printTransitionGraph
* ------------------------------------------------------------------
* @brief prints the transition graph of the story
*/
void Story::printTransitionGraph() {
    for(std::map<size_t, std::map<size_t,size_t> >::const_iterator it = transitionGraph.begin();
    it != transitionGraph.end(); ++it) {
        for (std::map<size_t, size_t>::const_iterator it2 = it->second.begin(); it2 != it->second.end(); ++it2) {
            std::cout << it->first;
            std::cout << "--";
            std::cout << it2->first;
            std::cout << "->";
            std::cout << it2->second << std::endl;
        }
    }
}

/*
* Function: start
* ------------------------------------------------------------------
* @brief main function to start interacting with the story
*/
void Story::start() {
    // initialize the global story variables
    initGlobalVariable();
    // print the first page
    Page & cur_page = *findPage(0);
    // update the global story variables
    updateGlobalVariable(cur_page);
    // update the choice activation
    updateChoiceActivation(cur_page);
    // print the page
    cur_page.printPage();
    // get user's choice num
    while (cur_page.getPageType() != WIN && cur_page.getPageType() != LOSE) {
        size_t choiceNum = getUserChoice(cur_page);
        if (isInputOver) {
            break;
        }
        cur_page = *findPage(transitionGraph[cur_page.getPageNum()][choiceNum]);
        updateGlobalVariable(cur_page);
        updateChoiceActivation(cur_page);
        cur_page.printPage();
    }
    // check if the input is over while the ending is not win or lose
    if (cur_page.getPageType() != WIN && cur_page.getPageType() != LOSE) {
        raiseError("The input is over but the final page is not WIN or LOSE");
    }
}