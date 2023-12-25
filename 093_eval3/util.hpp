#ifndef __UTIL_H__
#define __UTIL_H__

#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>

#define START_FILENAME std::string("/story.txt")
#define AT_CHAR '@'
#define COLON_CHAR ':'
#define DOLLAR_CHAR '$'
#define EQUAL_CHAR '='
#define LEFT_BRACKET '['
#define RIGHT_BRACKET ']'

void raiseError(const char * msg);
bool checkUnsignedNumberConversion(std::string num);
bool checkLongIntConversion(std::string num);
size_t performUnsignedNumberConversion(std::string num);
long int performLongIntConversion(std::string num);

#endif