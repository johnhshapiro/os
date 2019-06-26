#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define syscall(x) { \
    (x); \
    int err = errno; \
    if (err) { \
        fprintf(stderr, "In file %s at line %d: ", __FILE__, __LINE__); \
        perror(#x); \
        exit(err);} \
    }

#define WRITESTRING(STRING) \
    syscall(write(STDOUT_FILENO, STRING, strlen(STRING)));

#define WRITEINT(INT, LEN) { char buf[LEN]; \
    syscall(eye2eh(INT, buf, LEN, 10)); WRITESTRING(buf); }