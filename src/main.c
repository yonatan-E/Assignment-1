#include <stdio.h>
#include <stdlib.h>

#include "ErrorCode.h"
#include "Matrix.h"

#define MATRIX_HEIGHT 4
#define MATRIX_WIDTH 4

#define CHECK_MATRIX_CALL(call)                                                     \
    result = call;                                                                  \
    if (!error_isSuccess(result)) {                                                 \
        fprintf(stderr, "Error in %s: %s\n", #call, error_getErrorMessage(result)); \
    } else

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
    PMatrix otherMatrix = NULL;
    PMatrix multiplicationResult = NULL;
    ErrorCode result = ERROR_SUCCESS;

    CHECK_MATRIX_CALL(matrix_create(&matrix, MATRIX_HEIGHT, MATRIX_WIDTH)) {
        CHECK_MATRIX_CALL(initialize_matrix(matrix, MATRIX_HEIGHT, MATRIX_WIDTH)) {
            CHECK_MATRIX_CALL(matrix_copy(&otherMatrix, matrix)) {
                CHECK_MATRIX_CALL(matrix_multiplyWithScalar(otherMatrix, 2.0)) {
                    CHECK_MATRIX_CALL(matrix_multiplyMatrices(&multiplicationResult,
                                                              matrix, otherMatrix)) {
                        printf("Success!");
                        matrix_destroy(multiplicationResult);
                    }
                }
                matrix_destroy(otherMatrix);
            }
        }
        matrix_destroy(matrix);
    }

    return 0;
}