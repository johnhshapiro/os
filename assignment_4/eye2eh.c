#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <sys/errno.h>
#include "systemcall.h"

/*
** Async-safe integer to a string. i is assumed to be positive. The number
** of characters converted is returned; -1 will be returned if buffersize is
** less than one or if the string isn't long enough to hold the entire
** number. Numbers are right justified. The base must be between 2 and 16;
** otherwise the string is filled with spaces and -1 is returned.
*/
int eye2eh(int i, char *buffer, int buffersize, int base) {
    if(buffersize <= 1 || base < 2 || base > 16) {
        errno = EINVAL;
        return(-1);
    }

    buffer[buffersize-1] = '\0';

    int count = 0;
    const char *digits = "0123456789ABCDEF";
    for (int j = buffersize-2; j >= 0; j--) {
        if (i == 0 && count != 0) {
            buffer[j] = ' ';
        }
        else {
            buffer[j] = digits[i%base];
            i = i/base;
            count++;
        }
    }

    if (i != 0) {
        errno = EINVAL;
        return(-1);
    }

    errno = 0;
    return(count);
}

#ifdef UNITTESTEYE2EH
#define BUFFERLEN 5
int main() {
    char buffer[BUFFERLEN];
    // not enough room
    assert(eye2eh (1, buffer, 1, 10) == -1);
    assert(errno == EINVAL);

    assert(eye2eh (12345, buffer, BUFFERLEN, 10) == -1);
    assert(errno == EINVAL);

    // bad base
    assert(eye2eh (1, buffer, BUFFERLEN, 1) == -1);
    assert(errno == EINVAL);

    assert(eye2eh(1, buffer, BUFFERLEN, 10) == 1);
    assert(strncmp(buffer, "   1", BUFFERLEN) == 0);

    assert(eye2eh (10, buffer, BUFFERLEN, 10) == 2);
    assert(strncmp(buffer, "  10", BUFFERLEN) == 0);

    assert(eye2eh (12, buffer, BUFFERLEN, 10) == 2);
    assert(strncmp(buffer, "  12", BUFFERLEN) == 0);

    assert(eye2eh (1234, buffer, BUFFERLEN, 10) == 4);
    assert(strncmp(buffer, "1234", BUFFERLEN) == 0);

    assert(eye2eh (6, buffer, BUFFERLEN, 2) == 3);
    assert(strncmp(buffer, " 110", BUFFERLEN) == 0);

    assert(eye2eh (6, buffer, BUFFERLEN, 16) == 1);
    assert(strncmp(buffer, "   6", BUFFERLEN) == 0);

    assert(eye2eh (12, buffer, BUFFERLEN, 16) == 1);
    assert(strncmp(buffer, "   C", BUFFERLEN) == 0);

    assert(eye2eh (12, buffer, BUFFERLEN, 8) == 2);
    assert(strncmp(buffer, "  14", BUFFERLEN) == 0);

    assert(eye2eh (0, buffer, BUFFERLEN, 10) == 1);
    assert(strncmp(buffer, "   0", BUFFERLEN) == 0);
}
#endif
