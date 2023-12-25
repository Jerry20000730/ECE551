#ifndef __RAND_STORY_H__
#define __RAND_STORY_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#include "provided.h"

#define COLON ':'
#define NEWLINE '\n'
#define UNDERSCORE '_'
#define NULL_TEMINATOR '\0'

enum REPLACE_MODE_T {
  REPLACE_SAME = 0,
  REPLACE_RANDOM = 1,
  REPLACE_RANDOM_WITHOUT_REUSE = 2  
};

struct file_input_t {
  char ** lines;
  size_t n;
}; typedef struct file_input_t file_input;

//any functions you want your main to use
void raiseError(char * errMsg);
FILE * createFileStream(char * filename);
file_input * readInput(FILE * stream);
file_input * initFileInput();
catarray_t * initCatArray();
category_t * initCategory();
void freeCatArray(catarray_t * catarray);
void freeCategory(category_t * category);
void freeFileInput(file_input * input);
void processInput_step1(file_input * step1_storyfile);
void processInput_step2(file_input * step2_wordfile);
void processInput_step3And4(file_input * step4_wordsfile, file_input * step4_storyfile, int mode);
char * concatStr(char * dest, char ** strs, size_t num_strs);
int checkValidIndex(char * indexStr);
char * getPreviousWordAtIndex(category_t * history, size_t index);
void appendHistoryWord(category_t * history, char * word);
char * generateCategory(catarray_t * catarray, category_t * history, char * category, int mode);
char * replaceBlank(char * line, catarray_t * catarray, category_t * history, int mode);
void reArrangeCategoryWords(catarray_t * catarray, size_t categoryIndex, size_t removeWordIndex);
void removeWordFromCategory(catarray_t * catarray, char * category, const char * word);
int isCategoryExist(catarray_t * catarray, char * category);
void addCatArray(catarray_t * catarray, char * category, char * word);
catarray_t * readCatWords(catarray_t * res, char * line);
void closeFileStream(FILE * stream);

#endif
