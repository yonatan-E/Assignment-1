#include <stdio.h>
#include <stdlib.h>

#include "ErrorCode.h"
#include "Matrix.h"

#define MATRIX_HEIGHT 4
#define MATRIX_WIDTH 4

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

ErrorCode initialize_matrix(const PMatrix matrix, const uint32_t height,
                            const uint32_t width) {
    uint32_t i = 0;
    uint32_t j = 0;
    ErrorCode result = ERROR_SUCCESS;

    for (i = 0; i < height; ++i) {
        for (j = 0; j < width; ++j) {
            result = matrix_setValue(matrix, i, j, (double)(i * 10 + j));
            if (!error_isSuccess(result)) {
                fprintf(stderr, "Error matrix_setValue: %s\n",
                        error_getErrorMessage(result));
                return result;
            }
        }
    }

    return ERROR_SUCCESS;
}

int main() {
    PMatrix matrix = NULL;
    initialize_matrix(matrix, MATRIX_HEIGHT, MATRIX_WIDTH);
    printMatrix(matrix);

    return 0;
}