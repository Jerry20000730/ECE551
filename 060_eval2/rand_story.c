#include "rand_story.h"

/*
* Function: raiseError
* ------------------------------------------------------------------
* write error message to the stderr and 
* exit with "EXIT_FAILURE" signal
*
* Arguments:
*   1. errMsg: a string of message you want to write to stderr
*
*/
void raiseError(char * errMsg) {
  fprintf(stderr, "%s\n", errMsg);
  exit(EXIT_FAILURE);
}

/*
* Function: createFileStream
* ------------------------------------------------------------------
* create file stream for the given filename
*
* Arguments:
*   1. filename: a string of filename
*
*/
FILE * createFileStream(char * filename) {
    // filename cannot be empty
    if (filename == NULL || strlen(filename) == 0) {
        raiseError("[ERROR] given filename is empty");
    }
    FILE * f = fopen(filename, "r");
    if (f == NULL) {
        raiseError("[ERROR] file failed to open");
    }
    return f;
}

/*
* Function: readInput
* ------------------------------------------------------------------
* read the file stream and store the lines in the file_input struct:
*
*   struct file_input_t {
*       char ** lines;
*       size_t n;
*   }; typedef struct file_input_t file_input;
* 
* where `lines` is to store all lines in the given file stream,
* `n` is to store the number of lines
*
* Arguments:
* stream: FILE pointer of a file stream
*
*/
file_input * readInput(FILE * stream) {
    file_input * FI = initFileInput();
    char * cur = NULL;
    size_t linecap;
    size_t numLines = 0;
    
    while (getline(&cur, &linecap, stream) > 0) {
        FI->lines = realloc(FI->lines, (numLines+1) * sizeof(*FI->lines));
        FI->lines[numLines] = strdup(cur);
        numLines++;
        FI->n = numLines;
        free(cur);
        cur = NULL;
    }
    free(cur);
    return FI;
}

/*
* Function: processInput_step1
* ------------------------------------------------------------------
* the processing function for step1
* 
* Requirements: 
*   1. parse the story template
*   2. replace the blanks with the word "cat"
*
* Arguments:
* step1_storyfile: file_input struct containing all lines of the file
* containing the story template
*
*/
void processInput_step1(file_input * step1_storyfile) {
    for (size_t i=0; i<step1_storyfile->n; i++) {
        char * res = replaceBlank(step1_storyfile->lines[i], NULL, NULL, REPLACE_SAME);
        fprintf(stdout, "%s", res);
        free(res);
    }
}

/*
* Function: processInput_step2
* ------------------------------------------------------------------
* the processing function for step2
* 
* Requirements: 
*   1. parse the categories and words
*   2. store the words and category in the catarray_t struct
*
*       struct catarray_tag {
*           category_t * arr;
*           size_t n;
*       };
*
* Arguments:
* step2_storyfile: file_input struct containing all lines of the file
* containing the categories and words
*
*/
void processInput_step2(file_input * step2_wordsfile) {
    catarray_t * res = initCatArray();
    for (size_t i=0; i<step2_wordsfile->n; i++) {
        res = readCatWords(res, step2_wordsfile->lines[i]);
    }
    printWords(res);
    freeCatArray(res);
}

/*
* Function: processInput_step3And4
* ------------------------------------------------------------------
* the processing function for step3 and step4
* 
* Requirements: 
*   1. parse both the story template and the categories & words
*   2. replace the blank with the specific random word from
*   the category
*   3. replace the blank with a previously used word 
*   if the category name is a valid integer of at least one
*
* Arguments:
* step2_storyfile: file_input struct containing all lines of the file
* containing the categories and words
*
*/
void processInput_step3And4(file_input * step4_wordsfile, file_input * step4_storyfile, int mode) {
    // init the catarray and history category
    catarray_t * res = initCatArray();
    category_t * history = initCategory();
    // store the category and words
    for (size_t i=0; i<step4_wordsfile->n; i++) {
        res = readCatWords(res, step4_wordsfile->lines[i]);
    }
    // detect the blank and replace words according to words in that category
    for (size_t j=0; j<step4_storyfile->n; j++) {
        char * storyline = NULL;
        storyline = replaceBlank(step4_storyfile->lines[j], res, history, mode);
        fprintf(stdout, "%s", storyline);
        free(storyline);
    }
    freeCatArray(res);
    freeCategory(history);
}

/*
* Function: concatStr
* ------------------------------------------------------------------
* concatenate a list of strings together
*
* Arguments:
*   1. dest: the string to store the list of strings
*   2. strs: the list of strings to be concatenated
*   3. num_strs: number of strings
*/
char * concatStr(char * dest, char ** strs, size_t num_strs) {
    size_t overall_length = strlen(dest);
    for (size_t i=0; i<num_strs; i++) {
        overall_length += strlen(strs[i]);
    }
    dest = realloc(dest, (overall_length+1) * sizeof(*dest));
    if (dest == NULL) {
        raiseError("[ERROR] memory failed to malloc");
    }
    for (size_t i=0; i<num_strs; i++) {
        strcat(dest, strs[i]);
        free(strs[i]);
    }
    free(strs);
    return dest;
}

/*
* Function: checkValidIndex
* ------------------------------------------------------------------
* function to check whether a given category is a valid index
* 
* Requirements for the index (char *): 
*   1. must be a integer
*   2. value must be bigger than 1
*
* Arguments:
* indexStr: the string contains index
*
*/
int checkValidIndex(char * indexStr) {
    size_t length = strlen(indexStr);
    for (size_t i=0; i<length; i++) {
        // should be an integer
        // no other characters
        if (!isdigit(indexStr[i])) {
            return 0;
        }
    }
    // the index should be bigger than 0
    if (atoi(indexStr) <= 0) {
        return 0;
    }
    return 1;
}

/*
* Function: getPreviousWordAtIndex
* ------------------------------------------------------------------
* function to get the word according to the index given
* e.g., 1 refers to the immediate previous word, and
* 2 refers to the word before the immediate previous word
* and so on.
*
* Arguments:
*   1. history: a category_t struct containing the words that
*   has previously used
*   2. index: the index to the previous words
*
*/
char * getPreviousWordAtIndex(category_t * history, size_t index) {
    // the query index cannot exceed the number
    // of previously used words
    if (index > history->n_words) {
        raiseError("Quering index out of bounds");
    }
    return history->words[history->n_words-index];
}

/*
* Function: appendHistoryWord
* ------------------------------------------------------------------
* function to append word in the history
*
* Arguments:
*   1. history: a category_t struct containing the words that
*   has previously used
*   2. index: the index to the previous words
*
*/
void appendHistoryWord(category_t * history, char * word) {
    // add words in the history to store previously used words
    history->words = realloc(history->words, (history->n_words+1) * sizeof(*history->words));
    if (history->words == NULL) {
        raiseError("[ERROR] memory failed to allocate");
    }
    history->words[history->n_words] = strdup(word);
    history->n_words++;
}

/*
* Function: getPreviousWordAtIndex
* ------------------------------------------------------------------
* function to get the word according to the index given
* e.g., 1 refers to the immediate previous word, and
* 2 refers to the word before the immediate previous word
* and so on.
*
* Arguments:
*   1. history: a category_t struct containing the words that
*   has previously used
*   2. index: the index to the previous words
*
*/
void removeWordFromCategory(catarray_t * catarray, char * category, const char * word) {
    for (size_t i=0; i<catarray->n; i++) {
        // find the target category
        if (strcmp(catarray->arr[i].name, category) == 0) {
            for (size_t j=0; j<catarray->arr[i].n_words; j++) {
                // find the word and its index
                if (strcmp(catarray->arr[i].words[j], word) == 0) {
                    reArrangeCategoryWords(catarray, i, j);
                    break;
                }
            }
        }
    }
}

/*
* Function: reArrangeCategoryWords
* ------------------------------------------------------------------
* function to rearrange category words if one word in the list
* is removed. If the word is removed, the list should be reorganized
* and the memory related to that should be reallocated
*
* Arguments:
*   1. catarray: a catarray_t struct containing the category list
*   2. categoryIndex: the index of the category in the catarray
*   3. removeWordIndex: the index of the word to be removed 
*   in the category word list
*/
void reArrangeCategoryWords(catarray_t * catarray, size_t categoryIndex, size_t removeWordIndex) {
    // index out of bounds
    if (removeWordIndex >= catarray->arr[categoryIndex].n_words) {
        raiseError("removeWordIndex out of range.");
    }
    free(catarray->arr[categoryIndex].words[removeWordIndex]);
    catarray->arr[categoryIndex].words[removeWordIndex] = NULL;
    // move each element to point to the next element
    for (size_t i=removeWordIndex; i<catarray->arr[categoryIndex].n_words-1; i++) {
        catarray->arr[categoryIndex].words[i] = catarray->arr[categoryIndex].words[i+1];
    }
    catarray->arr[categoryIndex].n_words--;
    // realloc the memory
    catarray->arr[categoryIndex].words = realloc(catarray->arr[categoryIndex].words, catarray->arr[categoryIndex].n_words * sizeof(*catarray->arr[categoryIndex].words));
    if (catarray->arr[categoryIndex].n_words != 0 && catarray->arr[categoryIndex].words == NULL) {
        raiseError("[ERROR] memory failed to allocate");
    }
}

/*
* Function: generateCategory
* ------------------------------------------------------------------
* generate word in the specific category and replace the blanks 
* in the story according to specific mode
*
* Modes:
*   REPLACE_SAME: simply replace the blank with word "cat"
*   REPLACE_RANDOM: select random word from the specific category
*   REPLACE_RANDOM_WITHOUT_REUSE: similar to `REPLACE_RANDOM`, 
*   except that the word used should not repeat
*
* Arguments:
*   1. catarray: a catarray_t struct containing the category list
*   2. categoryIndex: the index of the category in the catarray
*   3. history: a category that tracks the words that have been
*   previously used
*   4. mode: the mode for replace the category word
*/
char * generateCategory(catarray_t * catarray, category_t * history, char * category, int mode) {
    // check whether the given category
    // is a reference index
    if (!checkValidIndex(category)) {
        // check if the category exists
        if (!isCategoryExist(catarray, category)) {
            raiseError("[ERROR] category does not exist");
        } else {
            char * word = strdup(chooseWord(category, catarray));
            if (word == NULL) {
                raiseError("[ERROR] No enough word in category array");
            }
            appendHistoryWord(history, word);
            // if mode is REPLACE_RANDOM_WITHOUT_REUSE
            // words cannot repeat and therefore must be
            // deleted from the catarray
            if (mode == 2) {
                removeWordFromCategory(catarray, category, word);
            }
            return word;
        }
    } else {
        int index = atoi(category);
        char * word = strdup(getPreviousWordAtIndex(history, index));
        appendHistoryWord(history, word);
        return word;
    }
    return NULL;
}

/*
* Function: replaceBlank
* ------------------------------------------------------------------
* function to randomly choose a word from the named category 
* to replace each blank and support references to previously 
* used words.
*
* Modes:
*   REPLACE_SAME: simply replace the blank with word "cat"
*   REPLACE_RANDOM: select random word from the specific category
*   REPLACE_RANDOM_WITHOUT_REUSE: similar to `REPLACE_RANDOM`, 
*   except that the word used should not repeat
*
* Arguments:
*   1. line: one line of file input from the file
*   2. catarray: the category list
*   3. history: a category that tracks the words that have been
*   previously used
    4. mode: the mode for replace the category word
*/
char * replaceBlank(char * line, catarray_t * catarray, category_t * history, int mode) {
    if (line == NULL || strlen(line) == 0) {
        raiseError("[ERROR] input line is null");
    }

    char * sep_pointer = NULL;
    char * start = line;
    // the res must be initialized with null terminator
    // before being concatenated
    char * res = malloc(sizeof(*res));
    res[0] = NULL_TEMINATOR;
    char ** strs = NULL;
    int count = 0;

    while ((sep_pointer = strchr(start, UNDERSCORE)) != NULL) {
        int length = sep_pointer - start;
        strs = realloc(strs, (count+1) * sizeof(*strs));
        // number of colon must be even number
        if (count % 2 == 0) {
            strs[count] = strndup(start, length);     
        } else {
            // mode = 0 <= REPLACE_SAME
            // mode = 1 <= REPLACE_RANDOM
            // mode = 2 <= REPLACE_RANDOM_WITHOUT_REUSE
            char * category = strndup(start, length);
            if (mode == 0) {
                strs[count] = strdup(chooseWord(NULL, NULL));
            } else {
                char * word = generateCategory(catarray, history, category, mode);
                strs[count] = strdup(word);
                free(word);
            }
            free(category);
        }
        start = sep_pointer + 1;
        count++;
    }

    // to check if the '_' is even number or
    // there is no _ in the sentence
    if (count == 0 || count % 2 != 0) {
        raiseError("[ERROR] lack underscore");
    }

    // add left over part to the string
    char * end_pointer = strchr(start, NEWLINE);
    if (end_pointer == NULL) raiseError("[ERROR] no newline operator");
    int length = end_pointer - start + 1;
    strs = realloc(strs, (count+1) * sizeof(*strs));
    if (strs == NULL) raiseError("[ERROR] memory failed to allocate");
    strs[count] = strndup(start, length);
    res = concatStr(res, strs, (count+1));
    return res;
}

/*
* Function: initFileInput
* ------------------------------------------------------------------
* function to initialize the file input struct
* and returns a pointer pointing to the struct
*
*/
file_input * initFileInput() {
    file_input * FI = malloc(sizeof(*FI));
    FI->lines = NULL;
    FI->n = 0;
    return FI;
}

/*
* Function: initCatArray
* ------------------------------------------------------------------
* function to initialize struct catarray_t
* and returns a pointer pointing to the struct
*
*/
catarray_t * initCatArray() {
    catarray_t * res = malloc(sizeof(*res));
    res->arr = NULL;
    res->n = 0;
    return res;
}

/*
* Function: initCategory
* ------------------------------------------------------------------
* function to initialize the category_t struct
* and returns a pointer pointing to the struct
*
*/
category_t * initCategory() {
    category_t * res = malloc(sizeof(*res));
    res->name = NULL;
    res->words = NULL;
    res->n_words = 0;
    return res;
}

/*
* Function: isCategoryExist
* ------------------------------------------------------------------
* function to check whether the category exists in the catarray
*
* Arguments:
*   1. catarray: catarray_t struct containing the category list
*   2. category: the category to be validate that whether it exists
*   
*/
int isCategoryExist(catarray_t * catarray, char * category) {
    for (size_t i=0; i<catarray->n; i++) {
        if (strcmp(catarray->arr[i].name, category) == 0) {
            return 1;
        }
    }
    return 0;
}

/*
* Function: addCatArray
* ------------------------------------------------------------------
* function to add the word into the specific category word list
*
* Arguments:
*   1. catarray: catarray_t struct containing the category list
*   2. category: the category to be validate that whether it exists
*   3. word: the word to be added to the category word list
*/
void addCatArray(catarray_t * catarray, char * category, char * word) {
    // check if there exists an array
    if (!isCategoryExist(catarray, category)) {
        // if not, create a new struct category_t
        category_t temp;
        temp.name = strdup(category);
        temp.n_words = 1;
        temp.words = NULL;
        temp.words = realloc(temp.words, temp.n_words * sizeof(*temp.words));
        if (temp.words == NULL) {
            raiseError("[ERROR] memory failed to allocate");
        }
        temp.words[temp.n_words-1] = strdup(word);
        catarray->arr = realloc(catarray->arr, (catarray->n+1)*sizeof(*catarray->arr));
        if (catarray->arr == NULL) {
            raiseError("[ERROR] memory failed to allocate");
        }
        catarray->arr[catarray->n] = temp;
        catarray->n++;
    } else {
        for (size_t i=0; i<catarray->n; i++) {
            if (strcmp(catarray->arr[i].name, category) == 0) {
                catarray->arr[i].words = realloc(catarray->arr[i].words, 
                (catarray->arr[i].n_words+1) * sizeof(*catarray->arr[i].words));
                if (catarray->arr[i].words == NULL) {
                    raiseError("[ERROR] memory failed to allocate");
                }
                catarray->arr[i].words[catarray->arr[i].n_words] = strdup(word);
                catarray->arr[i].n_words++;
            }
        }
    }
}

/*
* Function: readCatWords
* ------------------------------------------------------------------
* function to read lines in the format of category:word
* and add word in the specific category 
*
* Arguments:
*   1. res: catarray_t struct containing the category list
*   2. line: one line of file input from the file
*   
*/
catarray_t * readCatWords(catarray_t * res, char * line) {
    char * sep_pointer = strchr(line, COLON);
    char * end_pointer = strchr(line, NEWLINE);
    if (sep_pointer == NULL) {
        raiseError("[ERROR] wrong format, should be catogory:word");
    }
    char * category = strndup(line, sep_pointer - line);
    char * word = strndup(sep_pointer+1, end_pointer - sep_pointer - 1);
    addCatArray(res, category, word);
    free(category);
    free(word);
    return res;
}

/*
* Function: freeCatArray
* ------------------------------------------------------------------
* function to free the struct catarray_t
*
* Arguments:
*   1. catarray: the catarray_t struct category array
*   Note, it should be a pointer
*/
void freeCatArray(catarray_t * catarray) {
    for (size_t i=0; i<catarray->n; i++) {
        // free category name
        free(catarray->arr[i].name);
        // free each word inside a word list
        for (size_t j=0; j<catarray->arr[i].n_words; j++) {
            free(catarray->arr[i].words[j]);
        }
        // free whole word list
        free(catarray->arr[i].words);
    }
    // free the category and category list
    free(catarray->arr);
    free(catarray);
}

/*
* Function: freeCategory
* ------------------------------------------------------------------
* function to free the category
*
* Arguments:
*   1. category: category_t struct single category
*   Note: it should be a pointer
*/
void freeCategory(category_t * category) {
    for (size_t i=0; i<category->n_words; i++) {
        free(category->words[i]);
    }
    free(category->words);
    free(category);
}

/*
* Function: freeFileInput
* ------------------------------------------------------------------
* function to free the file input
*
* Arguments:
*   1. input: file_input containing all lines in the file
*/
void freeFileInput(file_input * input) {
    for (size_t i=0; i<input->n; i++) {
        free(input->lines[i]);
    }
    free(input->lines);
    free(input);
}

/*
* Function: closeFileStream
* ------------------------------------------------------------------
* function to close the file stream
*
* Arguments:
*   1. stream: file stream created by fopen function
*/
void closeFileStream(FILE * stream) {
    if (fclose(stream) != 0) {
        raiseError("[ERROR] file failed to close");
    }
}