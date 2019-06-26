#include <sys/errno.h>
  
/*
 * Async-safe integer to a string (itoa). The number of characters converted is
 * returned; -1 will be returned if buffersize is less than one or if the
 * string isn't long enough to hold the entire number. Numbers are right
 * justified. The base must be between 2 and 16; otherwise -1 is returned.
*/

int eye2eh(int i, char *buffer, int buffersize, int base) {
    if (i < 0 || buffersize <= 1 || base < 2 || base > 16) {
        errno = EINVAL;
        return -1;
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
        return -1;
    }

    return count;
}
