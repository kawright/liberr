#include "err.h"

#include <core.h>

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

Void init_err(Err *err) {
    err->code           = ErrCode_OK;
    err->ln             = 0;
    err->msg[0]         = '\0';
    err->file[0]        = '\0';
}

Void throw(Err *err, ErrCode code, U32 ln, Ch *file, Ch *msg, ...) {
    err->code       = code;
    err->ln         = ln;
    strncpy(err->file, file, ERR_FILE_BUF_SZ - 1);
    
    // Set up va args and write to err->msg
    va_list args;
    va_start(args, msg);
    vsnprintf(err->msg, ERR_MSG_BUF_SZ - 1, msg, args);
    va_end(args);
}

Bool is_err(Err *err) {
    return err->code != ErrCode_OK;
}
