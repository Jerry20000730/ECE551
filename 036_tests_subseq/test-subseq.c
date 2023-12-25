#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n);

void doTest(int * array, size_t n, size_t expected_s) {
  size_t s = maxSeq(array, n);
  if (s != expected_s) {
    printf("the test failed, expected %lu but got %lu\n", expected_s, s);
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  int array1[5] = {0};
  int array3[] = {-3, -5, -7, -9, 11, 13, 15, 17, 19};
  int array4[] = {1, 2, 3, 4, 5, 5, 6, 7, 8};

  doTest(array1, 5, 1);
  doTest(array1, 10, 1);
  doTest(array1, 0, 0);
  doTest(NULL, 0, 0);
  doTest(array3, 9, 6);
  doTest(&array3[4], 5, 5);
  doTest(array4, 9, 5);
  doTest(array4, 2, 2);

  exit(EXIT_SUCCESS);
}
