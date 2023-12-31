#include <stdio.h>
#include <stdlib.h>

size_t maxSeq(int * array, size_t n) {
  if (array == NULL || n == 0) return 0;

  if (n == 1) return 1;

  size_t count = 1;
  size_t max_count = count;
  for (size_t i = 0; i < n - 1; i++) {
    if (array[i] < array[i + 1]) {
      count++;
      if (count > max_count) {
        max_count = count;
      }
    }
    else {
      count = 1;
    }
  }
  return max_count;
}
