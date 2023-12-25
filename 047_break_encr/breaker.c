#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int findmax(int * freq_map, size_t n);

int decrypt(FILE * f) {
    int freq_map[26] = {0};
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (isalpha(c)) {
            c -= 'a';
            freq_map[c] += 1;
        }
    }
    int max_index = findmax(freq_map, 26);
    for (int i=0; i<26; i++) {
        if ((4+i) % 26 == max_index) {
            return i;
        }
    }
    return -1;
}

int findmax(int * freq_map, size_t n) {
    int max_count = 0;
    int max_index = 0;
    for (int i=0; i<n; i++) {
        if (freq_map[i] > max_count) {
            max_count = freq_map[i];
            max_index = i;
        }
    }

    return max_index;
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: breaker inputFileName\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    int key = decrypt(f);
    if (fclose(f) != 0) {
        perror("Failed to close the input file!");
        return EXIT_FAILURE;
    }
    fprintf(stdout, "%d\n", key);
    return EXIT_SUCCESS;
}