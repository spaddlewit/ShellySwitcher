/*
 Copyright 2020 Spaddlewit Inc. www.spaddlewit.com

 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at

     http://www.apache.org/licenses/LICENSE-2.0

 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.
 */

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
