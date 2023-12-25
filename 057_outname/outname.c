#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  int length1 = strlen(inputName);
  const char * suffix = ".counts";
  int length2 = strlen(suffix);
  char * outputName = malloc((length1+length2+1)*sizeof(*outputName));
  strncpy(outputName, inputName, length1);
  char * next = &outputName[length1];
  strncpy(next, suffix, length2);
  outputName[length1+length2] = '\0';

  return outputName;
}
