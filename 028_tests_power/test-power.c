#include <stdio.h>
#include <stdlib.h>

unsigned power(unsigned x, unsigned y);

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
  if (power(x, y) != expected_ans) {
    printf("the output of power did not match the expected answer.\n");
    exit(EXIT_FAILURE);
  }
}

int main(void) {
  run_check(0, 0, 1);
  run_check(1, 0, 1);
  run_check(4000000000, 1, 4000000000);
  run_check((unsigned int)'a', 1, 97);
  run_check(3, 3, 27);
}
