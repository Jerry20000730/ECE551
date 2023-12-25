#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <climits>

#include "util.hpp"

/*
* function: raiseError
* ------------------------------------------------------------------
* @brief Prints the error message and exits the program.
*
* @param msg The error message to be printed.
*/
void raiseError(const char * msg) {
    std::cerr << msg << std::endl;
    exit(EXIT_FAILURE);
}

/*
* function: checkUnsignedNumberConversion
* ------------------------------------------------------------------
* @brief Checks if the string can be converted to an unsigned number.
*
* @param num The string to be checked.
* @return True if the string can be converted to an unsigned number, false otherwise.
*/
bool checkUnsignedNumberConversion(std::string num) {
    char * endptr;
    size_t res = std::strtoul(num.c_str(), &endptr, 10);
    if ((res == ULONG_MAX || res == ULLONG_MAX) || errno == ERANGE) {
        return false;
    } else if (*endptr != '\0') {
        return false;
    } else if (errno != 0 && res == 0) {
        return false;
    }

    return true;
}

/*
* function: performUnsignedNumberConversion
* ------------------------------------------------------------------
* @brief Converts the string to an unsigned number.
*
* @param num The string to be converted.
* @return The unsigned number.
*/
size_t performUnsignedNumberConversion(std::string num) {
    size_t res = std::strtoul(num.c_str(), NULL, 10);
    return res;
}

/*
* function: checkLongIntConversion
* ------------------------------------------------------------------
* @brief Checks if the string can be converted to a long int.
*
* @param num The string to be checked.
* @return True if the string can be converted to a long int, false otherwise.
*/
bool checkLongIntConversion(std::string num) {
    char * endptr;
    long int res = std::strtol(num.c_str(), &endptr, 10);
    if ((res == LONG_MAX || res == LONG_MIN || res == LLONG_MAX || res == LLONG_MIN) || errno == ERANGE) {
        return false;
    } else if (*endptr != '\0') {
        return false;
    } else if (errno != 0 && res == 0) {
        return false;
    }

    return true;
}

/*
* function: performLongIntConversion
* ------------------------------------------------------------------
* @brief Converts the string to a long int.
*
* @param num The string to be converted.
* @return The long int.
*/
long int performLongIntConversion(std::string num) {
    long int res = std::strtol(num.c_str(), NULL, 10);
    return res;
}