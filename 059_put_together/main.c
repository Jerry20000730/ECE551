#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
#include "counts.h"
#include "outname.h"

counts_t * countFile(const char * filename, kvarray_t * kvPairs) {
  //WRITE ME
  FILE * f = fopen(filename, "r");
  if (f == NULL) {
    fprintf(stderr, "file failed to open\n");
    exit(EXIT_FAILURE);
  }

  counts_t * c = createCounts();

  char * line = NULL;
  size_t sz = 0;
  while (getline(&line, &sz, f) > 0) {
    //printf("%s", line);
    char * sep = strchr(line, '\n');
    if (sep != NULL) *sep = '\0';
    addCount(c, lookupValue(kvPairs, line));
    free(line);
    line = NULL;
  }
  free(line);

  if (fclose(f) != 0) {
    fprintf(stderr, "file failed to close\n");
    exit(EXIT_FAILURE);
  }
  return c;
}

int main(int argc, char ** argv) {
  //WRITE ME (plus add appropriate error checking!)
 //read the key/value pairs from the file named by argv[1] (call the result kv)
  if (argc <= 2) {
    fprintf(stderr, "argument less than 1\n");
    exit(EXIT_FAILURE);
  }
  kvarray_t * kv = readKVs(argv[1]);

 //count from 2 to argc (call the number you count i)
  for (int i=2; i<argc; i++) {
    //count the values that appear in the file named by argv[i], using kv as the key/value pair
    //   (call this result c)
    counts_t * c = countFile(argv[i], kv);
    //compute the output file name from argv[i] (call this outName)
    char * outName = computeOutputFileName(argv[i]);
    //open the file named by outName (call that f)
    FILE * f = fopen(outName, "w+");
    if (f == NULL) {
      fprintf(stderr, "file failed to open\n");
      exit(EXIT_FAILURE);
    }
    //print the counts from c into the FILE f
    printCounts(c, f);
    //close f
    if (fclose(f) != 0) {
      fprintf(stderr, "file failed to close\n");
      exit(EXIT_FAILURE);
    }
     //free the memory for outName and c
    freeCounts(c);
    free(outName);
  }
  //free the memory for kv
  freeKVs(kv);
  return EXIT_SUCCESS;
}
