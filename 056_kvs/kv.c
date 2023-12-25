#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"

void addToKVArray(kvarray_t * arr, kvpair_t pair) {
  if (arr->cur_index == arr->length) {
    if ((arr->kvpairs = realloc(arr->kvpairs, 2 * (arr->length) * sizeof(*arr->kvpairs))) == NULL) {
      fprintf(stderr, "No enough memory, malloc failed!\n");
      exit(EXIT_FAILURE);
    }
    arr->length *= 2;
  }
  arr->kvpairs[arr->cur_index] = pair;
  arr->cur_index++;
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE * f = fopen(fname, "r");
  if (f == NULL) {
    fprintf(stderr, "[Error] File failed to open\n");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t sz = 0;
  ssize_t len = 0;

  int init_size = 4;
  kvarray_t * arr = malloc(sizeof(*arr));
  arr->kvpairs = malloc(init_size * sizeof(*arr->kvpairs));
  arr->length = init_size;
  arr->cur_index = 0;

  while ((len = getline(&line, &sz, f)) >= 0) {
    char * sep_pointer = strchr(line, '=');
    char * start = line;
    if (sep_pointer == NULL) {
      fprintf(stderr, "[Error] Two elements should be seperated with =");
      exit(EXIT_FAILURE);
    }
    int length = sep_pointer - start;
    char * key = malloc((length+1) * sizeof(*key));
    strncpy(key, start, length);
    key[length] = '\0';
    start = sep_pointer + 1;
    char * end_pointer = strchr(line, '\n');
    length = end_pointer - start;
    char * value = malloc((length+1) * sizeof(*value));
    strncpy(value, start, length);
    value[length] = '\0';

    kvpair_t pair;
    pair.key = key;
    pair.value = value;
    addToKVArray(arr, pair);
  }
  free(line);
  if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file!\n");
        exit(EXIT_FAILURE);
  }
  return arr;
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i=0; i<pairs->cur_index; i++) {
    free(pairs->kvpairs[i].key);
    free(pairs->kvpairs[i].value);
  }
  free(pairs->kvpairs);
  free(pairs);
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  for (int i=0; i<pairs->cur_index; i++) {
    printf("key = '%s' value = '%s'\n", pairs->kvpairs[i].key, pairs->kvpairs[i].value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  for (int i=0; i<pairs->cur_index; i++) {
    if (strcmp(pairs->kvpairs[i].key, key) == 0) {
      return pairs->kvpairs[i].value;
    }
  }
  return NULL;
}
