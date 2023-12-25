#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void rotate_mat(FILE * f) {
    char input[100] = {0};
    char rotate_matrix[10][10] = {{0}};
    int count = 0;
    for (int i=0; i<10; i++) {
        if (fgets(input, 100, f)) {
            if (strlen(input) != 11) {
                fprintf(stderr, "One line should have only ten characters\n");
                exit(EXIT_FAILURE);
            }
            for (int j=0; j<10; j++) {
                rotate_matrix[j][9-i] = input[j];
            }
            count++;
        }
    }
    if (count < 10) {
        fprintf(stderr, "The input file has less than 10 lines\n");
        exit(EXIT_FAILURE);
    }
    if (fgets(input, 100, f)) {
        fprintf(stderr, "The input has more than 10 lines\n");
        exit(EXIT_FAILURE);
    }
    
    // print matrix
    for (int i=0; i<10; i++) {
        for (int j=0; j<10; j++) {
            printf("%c", rotate_matrix[i][j]);
        }
        printf("\n");
    }
}

int main(int argc, char ** argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: rotateMatrix inputFileName\n");
        return EXIT_FAILURE;
    }
    FILE * f = fopen(argv[1], "r");
    if (f == NULL) {
        fprintf(stderr, "Failed to open the input file!\n");
        exit(EXIT_FAILURE);
    }
    rotate_mat(f);
    if (fclose(f) != 0) {
        fprintf(stderr, "Failed to close the input file!\n");
        exit(EXIT_FAILURE);
    }
    return EXIT_SUCCESS;
}