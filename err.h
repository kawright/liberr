/* Error signaling and handling */

#ifndef ERR_H
#define ERR_H

#include <core.h>

#include <stdarg.h>

/* ----- CONSTANTS ----- */

/* The size of the error message buffer. */
#define ERR_MSG_BUF_SZ      128

/* The size of the error filename buffer. */
#define ERR_FILE_BUF_SZ     64

/* ----- MACROS ----- */

/* Throw an error. Takes a 'printf' formatted message. */
#define THROW(err, code, msg, ...) \
    throw(err, code, __LINE__, __FILE__, msg, ##__VA_ARGS__);

/* ----- TYPES ----- */

/* Indicates the type or source of an error condition. */
typedef enum ENUM_ERR_CODE {

    /* No failure. */
    ErrCode_OK              = 0,

    /* General runtime error. */
    ErrCode_RUN             = 1,

    /* Bad argument vector. */
    ErrCode_ARGV            = 2,

    /* Out of memory. */
    ErrCode_MEM             = 3,

    /* Debug-mode specific failure. */
    ErrCode_DEBUG           = 4,

    /* Test suite failure. */
    ErrCode_TEST            = 5,

    /* IO operation failure. */
    ErrCode_IO              = 6,

    /* Bad user data. */
    ErrCode_DATA            = 7,

    /* Illegal math operation. */
    ErrCode_MATH            = 8,

    /* Operation timeout. */
    ErrCode_TIMEOUT         = 9,

    /* Authorization failure. */
    ErrCode_AUTH            = 10,

    /* Network error. */
    ErrCode_NET             = 11,

    /* Out-of-bounds access. */
    ErrCode_BOUNDS          = 12,

    /* Subsytem failure. */
    ErrCode_SUBSYS          = 13,

    /* Initialization failure. */
    ErrCode_INIT            = 14
} ErrCode;

/* Stores an error state. */
typedef struct STRUCT_ERR {
    
    /* A code that indicates the type of error. */
    ErrCode                 code;

    /* The line-number where the error was thrown. */
    U32                     ln;

    /* A message explaining the error. */
    Ch                      msg[ERR_MSG_BUF_SZ];

    /* The name of the file where the error was thrown. */
    Ch                      file[ERR_FILE_BUF_SZ];
} Err;

/* ----- FUNCTIONS ----- */

/* Initialize an 'Err'. */
Void init_err(Err *err);

/* SYSTEM FUNCTION; USE 'THROW' MACRO INSTEAD! Throw an error. Takes a 'printf' 
formatted message. */
Void throw(Err *err, ErrCode code, U32 ln, Ch *file, Ch *msg, ...);

/* Test in an 'Err' is in an error state (the code is anything but 
'ErrCode_OK'). */
Bool is_err(Err *err);

/* Report an error to 'stderr'. */
Void warn(Err *err);

#endif
