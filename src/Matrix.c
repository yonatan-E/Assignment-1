#include "Matrix.h"
#include <stdlib.h>
#include <stdio.h>

struct Matrix {
    double* table;
    uint32_t height, width;
};

ErrorCode matrix_create(PMatrix* matrix, uint32_t height, uint32_t width) {
    // allocating memory for the matrix pointer, in case it's null
    if (matrix == NULL) {
        matrix = (PMatrix*)malloc(sizeof(PMatrix));
        // checking if the allocation succeeded
        if (matrix == NULL) {
            return ERROR_ALLOCATION_FAILED;
        }
    }

    // allocation memory for the matrix
    *matrix = (PMatrix)malloc(sizeof(struct Matrix));
    // checking if the allocation succeeded
    if (*matrix == NULL) {
        return ERROR_ALLOCATION_FAILED;
    }

    // allocating memory for the matrix table
    (*matrix)->table = (double*)malloc(height * width * sizeof(double));
    // checking if the allocation succeeded
    if ((*matrix)->table == NULL) {
        return ERROR_ALLOCATION_FAILED;
    }

    // initializing the size fields of the matrix
    (*matrix)->height = height;
    (*matrix)->width = width;
    return ERROR_SUCCESS;
}

ErrorCode matrix_copy(PMatrix* result, CPMatrix source) {
    if (source == NULL) {
        return ERROR_NULL_POINTER;
    }

    // allocating the result matrix
    ErrorCode error = matrix_create(result, source->height, source->width);
    // checking if the allocation succeeded
    if (!error_isSuccess(error)) {
        return error;
    }

    // initializing the values of the result matrix
    for (uint32_t i = 0; i < source->height; i++)
        for (uint32_t j = 0; j < source->width; j++) {
            double val;
            error = matrix_getValue(source, i, j, &val);
            if (!error_isSuccess(error)) {
                return error;
            }
            error = matrix_setValue(*result, i, j, val);
            if (!error_isSuccess(error)) {
                return error;
            }
        }
    return ERROR_SUCCESS;
}

void matrix_destroy(PMatrix matrix) {
    if (matrix == NULL) {
        return;
    }
    // freeing the memory of the matrix table
    free(matrix->table);
    free(matrix);
}

ErrorCode matrix_getHeight(CPMatrix matrix, uint32_t* result) {
    if (matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    *result = matrix->height;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getWidth(CPMatrix matrix, uint32_t* result) {
    if (matrix == NULL) {
        return ERROR_NULL_POINTER;
    }
    *result = matrix->width;
    return ERROR_SUCCESS;
}

ErrorCode matrix_setValue(PMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double value) {
    if (matrix == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_INDEX_OUT_OF_BOUND;
    }

    matrix->table[rowIndex * matrix->height + colIndex] = value;
    return ERROR_SUCCESS;
}

ErrorCode matrix_getValue(CPMatrix matrix, uint32_t rowIndex, uint32_t colIndex,
                          double* value) {
    if (matrix == NULL) {
        return ERROR_NULL_POINTER;
    }

    if (rowIndex >= matrix->height || colIndex >= matrix->width) {
        return ERROR_INDEX_OUT_OF_BOUND;
    }

    *value = matrix->table[rowIndex * matrix->height + colIndex];
    return ERROR_SUCCESS;
}

ErrorCode matrix_add(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (lhs == NULL || rhs == NULL)
        return ERROR_NULL_POINTER;
    // can't add matrices with different sizes
    if (lhs->height != rhs->height || lhs->width != rhs->width)
        return ERROR_MATRIX_INVALID_OPERATION;

    // allocating the result matrix
    ErrorCode error = matrix_create(result, lhs->height, lhs->width);
    // checking if the allocation succeeded
    if (!error_isSuccess(error)) {
        return error;
    }

    // initializing the values of the result matrix
    for (uint32_t i = 0; i < lhs->height; i++)
        for (uint32_t j = 0; j < lhs->width; j++) {
            double lhs_val, rhs_val;
            error = matrix_getValue(lhs, i, j, &lhs_val);
            if (!error_isSuccess(error)) {
                return error;
            }
            error = matrix_getValue(rhs, i, j, &rhs_val);
            if (!error_isSuccess(error)) {
                return error;
            }
            error = matrix_setValue(*result, i, j, lhs_val + rhs_val);
            if (!error_isSuccess(error)) {
                return error;
            }
        }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyMatrices(PMatrix* result, CPMatrix lhs, CPMatrix rhs) {
    if (lhs == NULL || rhs == NULL)
        return ERROR_NULL_POINTER;
    // can't multiply matrices with unmatched sizes
    if (lhs->width != rhs->height)
        return ERROR_MATRIX_INVALID_OPERATION;

    // allocating the result matrix
    ErrorCode error = matrix_create(result, lhs->height, rhs->width);
    // checking if the allocation succeeded
    if (!error_isSuccess(error)) {
        return error;
    }

    // initializing the values of the result matrix
    for (uint32_t i = 0; i < lhs->height; i++)
        for (uint32_t j = 0; j < rhs->width; j++) {
            double val = 0;
            uint32_t matrix_size = lhs->width;
            for (uint32_t k = 0; k < matrix_size; k++) {
                double lhs_val, rhs_val;
                error = matrix_getValue(lhs, i, k, &lhs_val);
                if (!error_isSuccess(error)) {
                    return error;
                }
                error = matrix_getValue(rhs, k, j, &rhs_val);
                if (!error_isSuccess(error)) {
                    return error;
                }
                val += lhs_val * rhs_val;
            }
            error = matrix_setValue(*result, i, j, val);
            if (!error_isSuccess(error)) {
                return error;
            }
        }
    return ERROR_SUCCESS;
}

ErrorCode matrix_multiplyWithScalar(PMatrix matrix, double scalar) {
    if (matrix == NULL)
        return ERROR_NULL_POINTER;

    // multiplying all the values of the matrix by the scalar
    for (uint32_t i = 0; i < matrix->height; i++)
        for (uint32_t j = 0; j < matrix->width; j++) {
            double val;
            ErrorCode error = matrix_getValue(matrix, i, j, &val);
            if (!error_isSuccess(error)) {
                return error;
            }
            error = matrix_setValue(matrix, i, j, scalar * val);
            if (!error_isSuccess(error)) {
                return error;
            }
        }
    return ERROR_SUCCESS;
}