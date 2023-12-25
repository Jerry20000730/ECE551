#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counts.h"

void addToCountArray(counts_t * c, one_count_t * count) {
  if (c->cur_index == c->size) {
    if ((c->arr = realloc(c->arr, c->size * 2 * sizeof(*c->arr))) == NULL) {
        fprintf(stderr, "No enough memory to be create.\n");
        exit(EXIT_FAILURE);
    }
    c->size *= 2;
  }
  c->arr[c->cur_index] = count;
  c->cur_index++;
}

counts_t * createCounts(void) {
  //WRITE ME
  counts_t * counts = malloc(sizeof(*counts));
  ssize_t init_size = 8;
  counts->arr = malloc(init_size * sizeof(*counts->arr));
  counts->size = init_size;
  counts->cur_index = 0;

  return counts;
}

void addCount(counts_t * c, const char * name) {
  //WRITE ME
  int isFind = 0;
  if (name == NULL) {
    name = "<unknown>";
  }
  for (int i=0; i<c->cur_index; i++) {
    if (strcmp(c->arr[i]->str, name)==0) {
      c->arr[i]->num++;
      isFind = 1;
    }
  }
  if (isFind != 1) {
    one_count_t * temp = malloc(sizeof(*temp));
    temp->str = malloc((strlen(name)+1) * sizeof(*temp->str));
    strncpy(temp->str, name, strlen(name)+1);
    temp->num = 1;
    addToCountArray(c, temp);
  }
}

void printCounts(counts_t * c, FILE * outFile) {
  //WRITE ME
  if (outFile == NULL) {
    fprintf(stderr, "File provided is NULL\n");
    exit(EXIT_FAILURE);
  }
  
  int j = -1;
  for (int i=0; i<c->cur_index; i++) {
    if (strcmp(c->arr[i]->str, "<unknown>")==0) {
      j = i;
      continue;
    }
    fprintf(outFile, "%s: %d\n", c->arr[i]->str, c->arr[i]->num);
  }
  if (j != -1) {
    fprintf(outFile, "%s : %d\n", c->arr[j]->str, c->arr[j]->num);
  }
}

void freeCounts(counts_t * c) {
  //WRITE ME
  for (int i=0; i<c->cur_index; i++) {
    free(c->arr[i]->str);
    free(c->arr[i]);
  }
  free(c->arr);
  free(c);
}
