#include "sunspots.h"

#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define MAX_LENGTH 100

void raiseError(char * errMsg);

/*
 * Function: isValidYear 
 * ------------------------------------------------------------------
 * judge whether a input string is a valid year in the format YYYY
 * the year should be within the range [0, 9999]
 *
 *  Arguments:
 *  str: the string in the format YYYY
 *
 *  returns: 1 if the input string is a valid year
 *           0 otherwise
 */
int isValidYear(char * str) {
  if (strlen(str) != 4) {
    return 0;
  }
  // ref: 041_reverse_str/reverse.c
  char * ptr = &str[0];
  while (*ptr != '\0') {
    /* if YYYY and MM are not digit
       then it is not valid */
    if (!isdigit(*ptr)) {
      return 0;
    }
    ptr++;
  }
  // the year given should be within the range [0, 9999]
  if (atoi(str) < 0 || atoi(str) > 9999) {
    return 0;
  }
  return 1;
}

/*
* Function: isValidMonth 
* ------------------------------------------------------------------
* judge whether a input string is a valid year in the format MM
* the year should be within the range [1, 12]
*
*  Arguments:
*  str: the string in the format MM
*
*  returns: 1 if the input string is a valid month
*           0 otherwise
*/
int isValidMonth(char * str) {
  if (strlen(str) != 2) {
    return 0;
  }
  // ref: 041_reverse_str/reverse.c
  char * ptr = &str[0];
  while (*ptr != '\0') {
    if (!isdigit(*ptr)) {
      return 0;
    }
    ptr++;
  }
  // The month given should be within the range [1, 12]
  if (atoi(str) < 1 || atoi(str) > 12) {
    return 0;
  }
  return 1;
}

/*
 * Function: isValidDouble 
 * -------------------------------------------------------------------
 * Judge if the input string is a valid double number
 *
 *  Arguments:
 *  str: string of a double number
 *
 *  returns: 0 if the input string is not a valid double
 *           1 otherwise
 */
int isValidDouble(char * str) {
  if (strlen(str) == 0) {
    return 0;
  }
  // ref: 041_reverse_str/reverse.c
  char * ptr = &str[0];
  int count = 0;
  int dotCount = 0;
  int digitCount = 0;
  while (*ptr != '\0') {
    /* if the character is not a digit
       and not a '.',
       then it is not valid. */
    if (!isdigit(*ptr) && *ptr != '.') {
      return 0;
    } else {
      if (isdigit(*ptr)) {
        digitCount++;
      }
      else {
        dotCount++;
        /* if there is more than one
          dot, then it is not valid */
        if (dotCount > 1) {
          return 0;
        }
      }
    }
    ptr++;
    count++;
  }
  // if there is only a dot, without anything else
  // it will not be accepted
  if (digitCount == 0 && dotCount >= 1) {
    return 0;
  }
  return 1;
}

/*
* Function: raiseError 
* -------------------------------------------------------------------
* write error message to the stderr and exit with "EXIT_FAILURE" signal
*
*  Arguments:
*  errMsg: a string of message you want to write to stderr
*
*/
void raiseError(char * errMsg) {
  fprintf(stderr, "%s\n", errMsg);
  exit(EXIT_FAILURE);
}

/*
 * Function: parseLine 
 * ------------------------------------------------------------------
 * Convert a line of format "date,number of sunspots" into a 
 * designated struct ss_monthly_t by seperating comma, slash and
 * convert string to int/double.
 *  
 *  struct ss_monthly_tag {
 *    double num;
 *    unsigned year;
 *    unsigned month;
 *  };
 *
 *  Arguments:
 *  line: one line of string in the format "date,number of sunspots"
 *
 *  returns: a ss_monthly struct contains year, month and number 
 */
ss_monthly_t parseLine(char * line) {
  /* handling the situation
     where line is empty */
  if (line == NULL || strlen(line) == 0 || (strlen(line) == 1 && line[0] == '\n')) {
    raiseError("[Error] the parsed line is empty");
  }

  // string to store date (including year, month) and num
  char date[MAX_LENGTH];
  char num[MAX_LENGTH];
  char year[MAX_LENGTH];
  char month[MAX_LENGTH];
  
  // define the seperator
  char comma = ',';
  char dash = '-';
  char newline = '\n';
  char nullTerm = '\0';
  
  // STEP1: tokenize the line parsed by comma
  char * sep_pointer = strchr(line, comma);
  char * start = line;
  int part = 0;
  // check if there is a comma
  if (sep_pointer == NULL) {
    raiseError("[Error] Two elements should be seperated with a comma");
  } else {
    // check if there are multiple comma
    while (sep_pointer != NULL) {
      part++;
      int length = sep_pointer - start;
      if (part == 1) {
        if (length != 7) {
          raiseError("[Error] the first parsed element should be a date in the format of YYYY-MM");
        } else {
          strncpy(date, start, length);
          date[length] = '\0';
        }
      }
      if (part >= 2) {
        raiseError("[Error] There are more than one comma in one line");
      }
      start = sep_pointer + 1;
      sep_pointer = strchr(start, comma);
    }
  }
  char * end_pointer = strchr(line, newline);
  // check if there is a newline character at the end
  if (end_pointer == NULL) {
    printf("%s", line);
    raiseError("[Error] Multiple lines in one line");
  }
  int length = end_pointer - start;
  if (length >= MAX_LENGTH) {
    raiseError("[Error] Too many characters for the second parsed element");
  } else {
    strncpy(num, start, length);
    num[length] = '\0';
  }
    
  // STEP 2: tokenize the date by dash
  sep_pointer = strchr(date, dash);
  start = &date[0];
  part = 0;
  // check if there is a dash
  if (sep_pointer == NULL) {
    raiseError("[Error] The first elements should be seperated with a dash");
  } else {
    // check if there are multiple dash
    part++;
    int length = sep_pointer - start;
    if (part == 1) {
      if (length != 4) {
        raiseError("[Error] the first parsed element should be a date in the format of YYYY-MM");
      } else {
        strncpy(year, start, length);
        year[length] = '\0';
      }
    }
    if (part >= 2) {
      raiseError("[Error] There are more than one dash in one line");
    }
    start = sep_pointer + 1;
    sep_pointer = strchr(start, comma);
  }
  end_pointer = strchr(date, nullTerm);
  length = end_pointer - start;
  strncpy(month, start, length);
  month[length] = '\0';
    
  // STEP3: check the validity of year, month and num
  if (!isValidYear(year)) {
    raiseError("[Error] the year given is not in the format YYYY or not within the range [0, 9999]");
  }
  if (!isValidMonth(month)) {
    raiseError("[Error] the month given is not in the format MM or not within the range [1, 12]");
  }
  if (!isValidDouble(num)) {
    raiseError("[Error] the num element should be a non-negative floating point number");
  }
    
  /* STEP4: if all check passes
    assign the struct with year
    month and num */
  ss_monthly_t ans;
  ans.num = atof(num);
  ans.year = atoi(year);
  ans.month = atoi(month);
  
  return ans;
}

/*
 * Function: meanFilter 
 * ------------------------------------------------------------------
 * A mean filter operates by replacing each data point with the 
 * average of itself and its neighboring data points within a window w
 *
 *  data: an array of ss_monthly_t "data"
 *  n: the size of the array
 *  mean: another array to store the ss_monthly_t "data" after filtered
 *  w: size of the window
 */
void meanFilter(ss_monthly_t * data, size_t n, ss_monthly_t * mean, unsigned w) {
  // check if the input data is NULL
  if (data == NULL || n == 0) {
    raiseError("[Error] the input array is empty");
  }

  /* special handling:
     the input w must
     be a positive odd */
  if (w <= 0 || w % 2 == 0) {
    raiseError("[Error] the input w must be a positive odd");
  }
  // check the size of window
  if (w > n) {
    raiseError("[Error] the size of window cannot be larger than the number of elements in array");
  }

  int start = 0;
  int end = 0;
  double res = 0;

  for (int i = 0; (unsigned)i < n; i++) {
    start = i - (w - 1) / 2;
    end = i + (w - 1) / 2;

    // index bound control
    if (start < 0) {
      start = 0;
    }
    if ((unsigned)end >= n) {
      end = n - 1;
    }

    // calculate the mean number
    res = 0;
    for (int j = start; j <= end; j++) {
      res += data[j].num;
    }
    res = res / (end - start + 1);

    // assign the struct
    ss_monthly_t ans;
    ans.num = res;
    ans.year = data[i].year;
    ans.month = data[i].month;
    mean[i] = ans;
  }
}

/*
 * Function: findLocalMax 
 * ------------------------------------------------------------------
 * finding the local maximum value of a sequence of input data
 * P.S. the function will not work if the given sequence of data 
 * is not concave down
 *
 *  data: an array of ss_monthly_t data after mean filtered
 *  n: size of the array
 *
 *  returns: a double value indicating the local maximum value
 *  of the given sequence of data.
 */
double findLocalMax(ss_monthly_t * data, size_t n) {
  /* special handling: 
     the number of elements 
     in the array cannot be zero */
  if (data == NULL || n == 0) {
    raiseError("[Error] the number of elements inside array cannot be zero");
  }

  // find the local maximum
  double max_number = 0;
  double max_timestamp = 0;
  for (int i = 0; (unsigned)i < n; i++) {
    if (data[i].num > max_number) {
      max_number = data[i].num;
      // timestamp = year + month / 12.0
      max_timestamp = data[i].year + data[i].month / 12.0;
    }
  }

  return max_timestamp;
}

/*
 * Function: calcSsPeriod 
 * ------------------------------------------------------------------
 * Calculate the differences of the adjacent values in array timeStamps
 *
 *  timeStamps: an array of doubles "timeStamps", includes values of 
 *  time stamps corresponding to the local maximums of the sunspots data
 *  n: size of the array
 *
 *  returns: a double value indicates the  estimated period of the sunspots
 */
double calcSsPeriod(double * timeStamps, size_t n) {
  // check if the pointer is NULL
  if (timeStamps == NULL) {
    raiseError("[Error] the input array cannot be empty");
  }

  /* special handling:
     the number of elements
     in the array should be at least 2 */
  if (n < 2) {
    raiseError("[Error] the number of array must be at least 2");
  }

  // calculate average period
  double diff_sum = 0;
  // timestamp cannot be negative
  if (timeStamps[0] < 0) {
      raiseError("[Error] timeStamps cannot be negative");
  }
  for (int i = 1; i < n; i++) {
    // timestamp cannot be negative
    if (timeStamps[i] < 0) {
      raiseError("[Error] timeStamps cannot be negative");
    }
    diff_sum += timeStamps[i] - timeStamps[i - 1];
  }

  return diff_sum / (n - 1);
}
