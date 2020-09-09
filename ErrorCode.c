#include "ErrorCode.h"

bool error_isSuccess(const ErrorCode code) { return code == ERROR_SUCCESS; }

const char* error_getErrorMessage(const ErrorCode code) {
    switch (code) {
        case ERROR_SUCCESS:
            return "The operation completed successfully'\n'";
        case ERROR_NULL_POINTER:
            return "The operation attempted to use a NULL pointer'\n'";
        case ERROR_ALLOCATION_FAILED:
            return "The memory allocation failed'\n'";
        case ERROR_INDEX_OUT_OF_BOUNDS:
            return "The index is out of the matrix bounds'\n'";
        case ERROR_MATRIX_INVALID_OPERATION:
            return "The matrix operation is invalid'\n'";
        default:
            return "Unexpected error'\n'";
    }
}