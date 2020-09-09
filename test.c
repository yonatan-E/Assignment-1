#include <stdio.h>
#include <stdlib.h>

#include "ErrorCode.h"
#include "Matrix.h"

#define MATRIX_HEIGHT 4
#define MATRIX_WIDTH 3

void printMatrix(const PMatrix matrix) {
    uint32_t height, width;
    matrix_getHeight(matrix, &height);
    matrix_getWidth(matrix, &width);
    for (uint32_t i = 0; i < height; i++) {
        for (uint32_t j = 0; j < width; j++) {
            double val;
            matrix_getValue(matrix, i, j, &val);
            printf("%f ", val);
        }
        printf("\n");
    } 
    printf("\n");
}

void initialize_matrix(const PMatrix matrix, const uint32_t height,
                            const uint32_t width) {
    uint32_t i = 0;
    uint32_t j = 0;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            matrix_setValue(matrix, i, j, i + j);
        }
    }
}

int main() {
    PMatrix matrix1 = NULL;
    matrix_create(&matrix1, MATRIX_HEIGHT, MATRIX_WIDTH);
    PMatrix matrix2 = NULL;
    matrix_create(&matrix2, MATRIX_HEIGHT, MATRIX_WIDTH);

    initialize_matrix(matrix1, MATRIX_HEIGHT, MATRIX_WIDTH);
    initialize_matrix(matrix2, MATRIX_HEIGHT, MATRIX_WIDTH);

    PMatrix sum = NULL;
    matrix_multiplyWithScalar(matrix1, 3);
    matrix_add(&sum, matrix1, matrix2);

    printMatrix(matrix1);
    printMatrix(matrix2);
    printMatrix(sum);

    return 0;
}