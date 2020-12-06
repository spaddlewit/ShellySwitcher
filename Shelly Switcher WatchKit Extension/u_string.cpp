//
//  u_string.cpp
//  Shelly Switcher WatchKit Extension
//
//  Created by Arthur Freda on 12/4/20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include "u_string.h"

// https://stackoverflow.com/questions/7344683/utf8-aware-strncpy
char *utf8cpy(char* dst, const char* src, int sizeDest)
{
    if (sizeDest > 0) {
        int sizeSrc = (int)strlen(src); // number of bytes not including null
        while (sizeSrc >= sizeDest) {

            const char* lastByte = src + sizeSrc; // Initially, pointing to the null terminator.
            while (lastByte-- > src)
                if ((*lastByte & 0xC0) != 0x80) // Found the initial byte of the (potentially) multi-byte character (or found null).
                    break;

            sizeSrc = (int)(lastByte - src);
        }
        memcpy(dst, src, sizeSrc);
        dst[sizeSrc] = '\0';
    }
    return dst;
}
