// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <string>
#include <Windows.h>

/// @brief Evaluates to true if a handle is not NULL or INVALID_HANDLE_VALUE (-1).
#define ValidHandle(_x) ((NULL != (_x)) && (INVALID_HANDLE_VALUE != (_x)))

/// @brief Evaluates to True if a handle is not valid.
#define InvalidHandle(_x) (!ValidHandle(_x))

/// @brief Calls CloseHandle on a handle if it is valid then sets it to NULL
#define HandleDelete(_x)       \
    do                         \
    {                          \
        if (ValidHandle((_x))) \
        {                      \
            CloseHandle(_x);   \
        }                      \
        (_x) = NULL;           \
    }                          \
    ONCE

// TODO: reference additional headers your program requires here
