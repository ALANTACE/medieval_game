#ifndef ERROR_H
#define ERROR_H

typedef enum {
    NONE,
    INPUT_ERROR,
    UPDATE_ERROR,
    RENDER_ERROR,
    FATAL_ERROR,
} ErrorType;

#endif