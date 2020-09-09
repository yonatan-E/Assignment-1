#pragma once

#include <stdbool.h>
#include <stdint.h>

typedef enum {
    ERROR_SUCCESS = 0,
    ERROR_NULL_POINTER,
    ERROR_ALLOCATION_FAILED,
    ERROR_INDEX_OUT_OF_BOUND,
    ERROR_MATRIX_INVALID_OPERATION,
} ErrorCode;

/**
 * @brief Checks if a given error code indicates a success or not.
 *
 * @param[in] code the error code.
 * @return whether the error code indicates a success or not.
 */
bool error_isSuccess(ErrorCode code);

/**
 * @brief gets a textual error message for a given error code.
 *
 * @param[in] code the error code.
 * @return const char* the textual representation of the error code.
 */
const char* error_getErrorMessage(ErrorCode code);