#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define systemcall(x) { \
    errno = 0; \
    (x); \
    int err = errno; \
    if (err) { \
        fprintf(stderr, "In file %s at line %d: ", __FILE__, __LINE__); \
        perror(#x); \
        exit(err);} \
    } \
    errno = 0;

#define WRITESTRING(STRING) \
    systemcall(write(STDOUT_FILENO, STRING, strlen(STRING)));

int eye2eh(int i, char *buffer, int buffersize, int base);

#define WRITEINT(INT, LEN) { char buf[LEN]; \
    eye2eh(INT, buf, LEN, 10); WRITESTRING(buf); }
