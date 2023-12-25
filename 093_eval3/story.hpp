#ifndef __STORY_H__
#define __STORY_H__

#include <iostream>
#include <cstdlib>
#include <vector>
#include <iterator>
#include <map>
#include <stack>

#include "page.hpp"

/*
    Story class is the main class of the program. 
    It contains a vector of Page objects, 
    a map of transition graph, and a map of global variables.
    It also contains a boolean variable to indicate whether the user 
    has finished the story.
*/
class Story {
private:
    std::string path;
    std::vector<Page> pages;
    std::map<size_t, std::map<size_t, size_t> > transitionGraph;
    std::map<std::string, long int> globalStoryVariables;
    bool isInputOver;
public:
    Story(std::string path, std::ifstream & file);
    Story(const Story & rhs);
    ~Story();
    Story & operator=(const Story & rhs);
    void parseStory(std::ifstream & file);
    void parsePageContent(Page & page, std::ifstream & file);
    void processLine(std::string line);
    bool processPageDeclaration(std::string line);
    bool processChoice(std::string line);
    bool processVariableDeclaration(std::string line);
    bool processChoiceWithVariableRequirement(std::string line);
    bool checkBlankLine(std::string line);
    size_t processType(std::string t);
    bool checkVarAndVal(std::string line);
    bool checkOrder(size_t pageNum);
    std::pair<std::string, long int> seperateVarAndVal(std::string line);
    void initGlobalVariable();
    size_t getUserChoice(Page & cur_page);
    Page createPage(size_t pageNum, size_t pageType);
    Choice createChoice(size_t pageSrcNum, size_t pageDstNum, std::string text);
    Choice createChoice(size_t pageSrcNum, size_t pageDstNum, std::string text, std::pair<std::string, long int> varValPair); 
    void addPage(const Page & P);
    std::vector<Page>::iterator findPage(size_t pageNum);
    void establishTransitionGraph();
    void traverse();
    void DFSHelper(Page & cur, std::vector<std::pair<size_t, size_t> > & path, std::map<size_t, bool> & visited, bool & isReachable);
    void verifyStory();
    bool checkReferencedPageExists();
    bool checkPageReferencedAtLeastOnce();
    bool checkWinAndLosePage();
    void updateGlobalVariable(Page & page);
    void updateChoiceActivation(Page & page);
    void printStory();
    void printPath(std::vector<std::pair<size_t, size_t> > & path);
    void printTransitionGraph();
    void start();
};

#endif