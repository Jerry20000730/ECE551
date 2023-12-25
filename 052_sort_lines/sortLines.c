#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//This function is used to figure out the ordering of the strings
//in qsort. You do not need to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}

void process(FILE * f) {
  char ** lines = malloc(sizeof(*lines)); 
  if (lines == NULL) {
    fprintf(stderr, "memory not enough\n");
    exit(EXIT_FAILURE);
  }
  char * line = NULL;
  size_t linecapp = 0;
  size_t lineNum = 0;
  while (getline(&line, &linecapp, f) >= 0) {
    lines = realloc(lines, (linecapp+1)*sizeof(lines));
    lines[lineNum] = line;
    lineNum++;
    line = NULL;
  }
  free(line);
  // get each line from line
  sortData(lines, lineNum);
  for (size_t i=0; i<lineNum; i++) {
    printf("%s", lines[i]);
    free(lines[i]);
  }
  free(lines);
}

int main(int argc, char ** argv) {
  //WRITE YOUR CODE HERE!
  if (argc == 1) {
    process(stdin);
  } else {
    for (int i=1; i<argc; i++) {
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        fprintf(stderr, "Failed to open the file.\n");
        exit(EXIT_FAILURE);
      }
      process(f);
      if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        exit(EXIT_FAILURE);
      }
    }
  }
  return EXIT_SUCCESS;
}
