#include "ErrorCode.h"

bool error_isSuccess(const ErrorCode code) { return code == ERROR_SUCCESS; }

const char* error_getErrorMessage(const ErrorCode code) {
    switch (code) {
        case ERROR_SUCCESS:
            return "The operation completed successfully";
        case ERROR_NULL_POINTER:
            return "The operation attempted to use a NULL pointer";
        case ERROR_MATRIX_INVALID_OPERATION:
            return "The matrix operation is invalid";
        default:
            return "Unexpected error";
    }
}