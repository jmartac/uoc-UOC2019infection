#ifndef __ERROR_H__
#define __ERROR_H__

// Errors enum for game library
typedef enum {
    OK = 0,
    ERR_NOT_IMPLEMENTED = -1,
    ERR_INVALID = -2,
    ERR_MEMORY_ERROR = -3, 
    ERR_NOT_FOUND = -4,
    ERR_DUPLICATED = -5
} tError;

#endif // __ERROR_H__