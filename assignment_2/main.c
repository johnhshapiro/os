#define _POSIX_C_SOURCE 200809L
#include <unistd.h>
#include <sys/types.h>

int main(int ppid) {
    int status = fork();
}